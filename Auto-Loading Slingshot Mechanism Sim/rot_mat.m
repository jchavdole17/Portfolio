function M = rot_mat(theta)
t_rad = deg2rad(theta);
M = [cos(t_rad) -sin(t_rad); sin(t_rad) cos(t_rad)];
end 
   
