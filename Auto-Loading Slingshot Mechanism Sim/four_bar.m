function q = four_bar(L,theta_1,theta_2,delta)
d = L(1);
a = L(2);
b = L(3);
c= L(4);


q(1) = theta_1;
q(2) = theta_2;

k1 = d / a; 
k2 = d / c;
k3 = (a^2 -b^2 + c^2 +d^2)/ (2*a*c);
k4 = d/b;
k5 = (c^2 - d^2 - a^2 - b^2) / (2*a*b);

A = cos(q(2)) - k1 - k2*cos(q(2)) + k3;
B = -2*sin(q(2));
C = k1  - (k2+1)*cos(q(2)) + k3;
D = cos(q(2)) - k1 + k4*cos(q(2)) + k5;
E = -2*sin(q(2));
F = k1 + (k4-1)*cos(q(2)) + k5;

q(4) = 2*atan((-B + delta*sqrt(B^2 - 4*A*C)) / (2*A));
q(3) = 2*atan((-E + delta*sqrt(E^2 - 4*D*F))/(2*D));
end



