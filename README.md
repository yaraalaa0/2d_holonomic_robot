# 2d_holonomic_robot
2D holonomic robot controlled using 2 ROS nodes to go to random targets

The repo is composed of 2 packages: assignment1 and my_srv2

my_srv2 package: contains tserver node, a service server used for calculating random targets (x,y) given min and max values

assignment1 packeage: contains controller node that is used to request random target (x,y) from tserver, control the robot to go to the target, then requesting another random target (forever). 

The rqt_graph of the program:

![alt text](https://github.com/yaraalaa0/2d_holonomic_robot/blob/main/graph.PNG?raw=true)

## How to run the simulation

download the repository into your ros workspace

in the root of your workspace:

$ catkin_make 

$ rosrun my_srv2 tserver

$ rosrun stage_ros stageros $(rospack find aignment1)/world/exercise.world

$ rosrun assignment1 controller


