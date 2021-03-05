# Robot based on macanum wheels
## Kinematics
image
The configuration parameters of the system are defined as follows:
- x, y, \phi - robot position coordinates and orientation angle
- ly - half of the distance between wheels
- r - radius of the wheels
- \omega_i - wheels angular velocity
- vx, vy, \omega - robot linear and angular velocities
- <img src="http://latex.codecogs.com/svg.latex?l=sqrt(l_x^2+l_y^2)">
- <img src="http://latex.codecogs.com/svg.latex?\alpha_1,_2=+-atan(l_x/l_y);\alpha_3_,_4=+-\pi-+atan(l_x/l_y)">

Inverse kinematics
