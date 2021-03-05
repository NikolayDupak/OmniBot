# Robot based on mecanum wheels
robot photo
## Kinematics
<img src="photos/kinematics.jpeg" width="350">

### The configuration parameters of the system are defined as follows:
- x, y, <img src="http://latex.codecogs.com/svg.latex?\phi"> - robot position coordinates and orientation angle
- lx, ly - half of the distance between wheels
- r - radius of the wheels
- <img src="http://latex.codecogs.com/svg.latex?\omega_i"> - wheels angular velocity
- vx, vy, <img src="http://latex.codecogs.com/svg.latex?\phi"> - robot linear and angular velocities
- <img src="http://latex.codecogs.com/svg.latex?l=sqrt(l_x^2+l_y^2)">
- <img src="http://latex.codecogs.com/svg.latex?\alpha_1_2=\pm\;atan(l_x/l_y);\alpha_3_4=\pm\pi\mp\;atan(l_x/l_y)">

### Inverse kinematics
<img src="http://latex.codecogs.com/svg.latex?\begin{bmatrix}\omega_1\\\omega_2\\\omega_3\\\omega_4\\\end{bmatrix}=1/r\begin{bmatrix}-1&1&-l*sin(3*pi/4-\alpha_1_2)/sin(-pi/4)\\1&1&-l*sin(-3*pi/4-\alpha_1_2)/sin(pi/4)\\1&1& l*sin(pi/4-\alpha_3_4)/sin(pi/4)\\-1&1&l*sin(-pi/4-\alpha_3_4)/sin(-pi/4)\\\end{bmatrix}\begin{bmatrix}v_x\\v_y\\\omega\end{bmatrix}\">

### Forward kinematics
<img src="http://latex.codecogs.com/svg.latex?\begin{bmatrix}v_x\\v_y\\\omega\end{bmatrix}=r/4\begin{bmatrix}1&1&1&1\\-1&1&1&-1\\-1/(l_x+l_y)&1/(l_x+l_y)&-1/(l_x+l_y)&1/(l_x+l_y)\end{bmatrix}\begin{bmatrix}\omega_1\\\omega_2\\\omega_3\\\omega_4\end{bmatrix}">

## Path planning

## Results
video
