
%% Prepare Workspace
clc; close all;
clear
%% Position
L =  [148, 60, 123.60, 115]; % Link lengths
d = L(1); % define link lengths as letter variables
a = L(2);
b = L(3);
c = L(4);
delta = 1; % crossed configuration
t1 = 0; % all angles defined relative to theta_1

t3 =[]; % empty vector for t3 and t4
t4= [];
t2 = 0:1:360;
for n = 1:length(t2) % loop to obtain theta_3 and theta_4
    output =(four_bar(L,t1,deg2rad(n),delta)); % run fourbar position function
    t3(n) = output(3);
    t4(n) = output(4);
end 

P = 183.60 ; % length of AP on ternary link
% With the local frame
RA_O2 = a*cos(deg2rad(t2)) + a*sin(deg2rad(t2))*1i; % define A's position with respect to origin
R_PA = P*(cos(t3 + deg2rad(31)) + sin(t3 + deg2rad(31))*1i); % Position P with respect to A
   
R_PO2 = RA_O2 + R_PA; % P position with respect to O2 (coupler)

in_coor_pos = [real(R_PO2); imag(R_PO2)]; % Partition into real and imaginary components
rot_angle = 26.5 ; % angle for coordinate system transformation
% Apply rot_mat rotational matrix to obtain the coupler's position in the
% global frame
out_coor = rot_mat(rot_angle) * in_coor_pos;

X = out_coor(1,:); % Index for x-pos
Y = out_coor(2,:); % index for y-pos
%% Velocity
omega_2 =  convangvel(100,'rpm','rad/s'); % 100 rpm

% From algebra, define omega_3 and omega_4 (angular velocities)
omega_3 = (a./b).*(omega_2).*(sin(t4-deg2rad(t2))./sin(t3-t4));
omega_4 = (a./c).*(omega_2).* (sin(deg2rad(t2)-t3)./sin(t4-t3));

% Define A's velocity with respect to O2, P's velocity with respect to A
VA_O2 = a.*omega_2.*-sin(deg2rad(t2)) + a.*omega_2.*cos(deg2rad(t2)).*1i;
V_PA = P.*omega_3.*(-sin(t3 + deg2rad(31)) + cos(t3 + deg2rad(31))*1i);
V_PO2 = VA_O2 + V_PA; % local frame velocity of coupler point with respect to O2


% Convert to global frame
in_coor_vel = [real(V_PO2); imag(V_PO2)];
out_coor_vel = rot_mat(rot_angle) * in_coor_vel;
V_x = out_coor_vel(1,:);
V_y = out_coor_vel(2,:);


%% Acceleration

% Matrix approach. Define vectors for accelerations and angular (alpha)
% acceleration
A_AO2 = [];
A_PA = [];
A_PO2 = [];
alpha_3 = [];
alpha_4 = [];

% Solve the linear system for M*(alpha_vec) = k for every instance of
% theta_2
for n = 1:length(t2)
    M = [-b.*sin(t3(n)) c.*sin(t4(n)); b.*cos(t3(n)) -c.*cos(t4(n))];
    k = [a.*omega_2.^2.*cos(deg2rad(t2(n))) + b.*omega_3(n).^2.*cos(t3(n)) - c*omega_4(n).^2*cos(t4(n)); a*omega_2.^2*sin(deg2rad(t2(n))) + b*omega_3(n).^2*sin(t3(n)) - c*omega_4(n).^2*sin(t4(n))];
    alpha_vec = inv(M)*k;
    alpha_3(n) = alpha_vec(1);
    alpha_4(n) = alpha_vec(2);
    A_AO2(n) = -a.*(omega_2).^2.*(cos(deg2rad(t2(n))) + 1i.*sin(deg2rad(t2(n))));
    A_PA(n) = P.*alpha_3(n).*(-sin(t3(n)+deg2rad(31)) + 1i.*cos(t3(n) + deg2rad(31))) + -P.*(omega_3(n)).^2.*(cos(t3(n)+ deg2rad(31)) + 1i.*sin(t3(n)+ deg2rad(31)));
    A_PO2(n) =  A_AO2(n) + A_PA(n);
end 

% Convert to global frame
in_coor_acc = [real(A_PO2); imag(A_PO2)];
out_coor_acc = rot_mat(rot_angle) * in_coor_acc;
A_x = out_coor_acc(1,:);
A_y = out_coor_acc(2,:);   
%% Mechanical Considerations
angular_velocity_ratio = omega_3./omega_2;
torque_ratio = 1./(angular_velocity_ratio);
P_motor = 12 * 1.1; % voltage * current

V_mag = vecnorm([V_x; V_y].',2,2).';
F_coupler = P_motor./V_mag * 1000; % Watt-second/mm to N conversion
%% Plot results

figure(1)
plot(t2,X)
xlabel('\theta_2 (deg)');ylabel('x-pos (mm)'); title('X-position of Coupler Point vs. \theta_2 (deg)')

figure(2)
plot(X,Y)
xlabel('x-pos (mm)');ylabel('y-pos (mm)'); title('Path of Coupler Point')

figure(3)
subplot(2,1,1)
plot(t2,V_x)
xlabel('\theta_2 (deg)');ylabel('V_x of point P (mm/s)'); title('X-Velocity of Coupler Point')

subplot(2,1,2)
plot(t2,V_y)
xlabel('\theta_2 (deg)');ylabel('V_y of point P (mm/s)'); title('Y-Velocity of Coupler Point')

figure(4)
subplot(2,1,1)
plot(t2,A_x)
xlabel('\theta_2 (deg)');ylabel('A_x of point P (mm/s^2)'); title('X-Acceleration of Coupler Point')

subplot(2,1,2)
plot(t2,A_y)
xlabel('\theta_2 (deg)');ylabel('A_y of point P (mm/s^2)'); title('Y-Acceleration of Coupler Point')



figure(5)
subplot(3,1,1)
plot(t2,angular_velocity_ratio)
xlabel('\theta_2 (deg)');ylabel('angular velocity ratio (m_v)'); title('Angular Velocity Ratio vs. \theta_2')

subplot(3,1,2)
plot(t2,torque_ratio)
xlabel('\theta_2 (deg)');ylabel('torque ratio (m_T)'); title('Torque Ratio vs. \theta_2')

subplot(3,1,3)
plot(t2,F_coupler)
xlabel('\theta_2 (deg)');ylabel('Coupler force F_c (N)'); title('Coupler force (N) vs. \theta_2')
%% Animation

% Setup joint positions, grounds, and rotate coordinates to global as
% needed
figure(6)

t2 = 0:1:360;
t2  = deg2rad(t2);

O2x = 0;
O2y = 0;
O2 = [0; 0];


O4= [O2(1,:) + d*cos(deg2rad(26.5)); O2(2,:) + d*sin(deg2rad(26.5))];
O4x = O4(1,:);
O4y = O4(2,:);

O6= [O4x + 76.2 ; O4y];

O6x = O6(1,:);
O6y = O6(2,:);



A = [a*cos(t2);a*sin(t2)]; % rotate A last to avoid double rotating (simplest syntax)


B = rot_mat(rot_angle)*[ A(1,:) + b*cos(t3); A(2,:) + b*sin(t3)];
Bx = B(1,:);
By = B(2,:);


point_P = rot_mat(rot_angle)*[A(1,:) + P*cos(t3 + deg2rad(31)); A(2,:) + P*sin(t3+deg2rad(31))];
point_Px = point_P(1,:);
point_Py = point_P(2,:);

B_para = [Bx + 130; By];

Bx_para = B_para(1,:);
By_para = B_para(2,:);
P_para = [point_Px + 130 ;point_Py];
Px_para = P_para(1,:);
Py_para = P_para(2,:);



A = rot_mat(rot_angle) * [a*cos(t2);a*sin(t2)]; % rotate A last to avoid double rotating (simplest syntax)
Ax = A(1,:);
Ay = A(2,:);


xTrace = point_Px + (130/2);
yTrace = point_Py(n) + 75;

vidStr = 'linkanimation'; % name of the video
nFrames = length(t2);
duration = 10; % length of video in secs

vidObj = VideoWriter(vidStr,'MPEG-4'); % create video object in mp4
vidObj.FrameRate = floor(nFrames/duration);% set frame rate
vidObj.Quality = 100; % max vid quality

open(vidObj);
% loop for animation
for n = 1:3: length(t2)

  plot(O2x,O2y,'g.','MarkerSize',10); hold on
  plot(O4x,O4y,'g.','MarkerSize',10)
  plot(Ax(n), Ay(n),'g.', 'MarkerSize',10);
  plot(Bx(n),By(n),'g.','MarkerSize',10)
  plot(point_Px(n),point_Py(n),'g.','MarkerSize',10)
  plot(Bx_para(n),By_para(n),'g.','MarkerSize',10)
  plot(Px_para(n),Py_para(n),'g.','MarkerSize',10)
  plot(O6x,O6y,'g.','MarkerSize',10)
  plot((point_Px(n) + (130/2)), (point_Py(n) + 75), 'rx','markersize', 10)

    
  plot([O2x Ax(n)],[O2y Ay(n)], 'r-')
  plot([O2x O4x],[O2y O4y], 'k-')
  plot([O4x O6x],[O4y O6y], 'k-')

  plot([Ax(n) Bx(n)],[Ay(n) By(n)], 'm-')
  plot([O4x Bx(n)],[O4y By(n)], 'c-')
  plot([Ax(n) point_Px(n)], [Ay(n) point_Py(n)],'m-')
  plot([Bx(n) point_Px(n)], [By(n) point_Py(n)],'m-')
  plot([Bx(n) Bx_para(n)], [By(n) By_para(n)], 'color','#D95319')
  plot([point_Px(n) Px_para(n)], [point_Py(n) Py_para(n)],'color','#D95319')
  plot([Bx_para(n) Px_para(n)], [By_para(n) Py_para(n)],'color','#EDB120')
  plot([O6x Bx_para(n)],[O6y By_para(n)],'color','#7E2F8E')
  plot([(point_Px(n) + (130/2)) (point_Px(n) + (130/2))], [point_Py(n) (point_Py(n) + 75)], 'color', '#D95319')
  
  xTrace = point_Px(1:n) + (130/2);
  yTrace = point_Py(1:n) + 75;
  plot(xTrace ,yTrace,'b--'); hold off

  
  title('Linkage Position Animation - Y-Position vs. X-Position in mm')
  xlim([-150 400])
  ylim([-300 300])
  legend('Joints','Link 2')
  xlabel('X-Pos (mm)')
  ylabel('Y-Pos (mm)')

 drawnow  %Force plot to update before code advances
 writeVideo(vidObj, getframe(gcf)); 
%  Draw arm trace (parallel to coupler point P)
%  if n ==  length(t2)
%      hold on
%      for n = 1:length(t2)
%         plot(point_Px(n) + (130/2) ,point_Py(n) + 75,'b.')
%         drawnow
%      end
%      hold off
end

close(vidObj);