#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "my_srv2/Target.h"


ros::Publisher velocity_pub;  //Defining a global publisher to control the robot's velocity
ros::ServiceClient client;   //a service client for requesting randorm targets from tserver
float xt=0;           //global variable to store x of the current target
float yt=0;           //global variable to store y of the current target
float k = 0.5;         //constant value for tuning the velocity value



void subscriberCallback(const nav_msgs::Odometry::ConstPtr& pose_msg)
{
    //Printing the current (x, y) position of the robot
    //ROS_INFO("Robot position [%f,%f]",pose_msg->pose.pose.position.x,pose_msg->pose.pose.position.y);

    float x = pose_msg->pose.pose.position.x;
    float y = pose_msg->pose.pose.position.y;

    //Checking if the robot has reached the target x and y
    if ((xt-x < 0.1 && xt-x > -0.1))
    {
        if (yt-y < 0.1 && yt-y > -0.1)
        { 
           ROS_INFO("I reached the target");
	   my_srv2::Target t;   // initializing the service message to request a new target
           t.request.min = -6.0;    //setting minimum value for target
           t.request.max = 6.0;     //setting maximum value for target
           client.call(t);          //Calling the service for receiving a new random target
           xt = t.response.x_t;       //storing the received x value for target in the global variable
           yt = t.response.y_t;       //storing the received y value for target in the global variable
           ROS_INFO("New Target [%f,%f]",xt,yt);
        }
    }
    
    
       
       geometry_msgs::Twist vel_msg;   //initializing the valocity message
       vel_msg.linear.x = k*(xt-x);    //setting the x value of the velocity linearly proportional to distance from the target
       vel_msg.linear.y = k*(yt-y);    //setting the y value of the velocity linearly proportional to distance from the target
       velocity_pub.publish(vel_msg);

       //Printing the current (x, y) target position
       //ROS_INFO("Current Target [%f,%f]",xt,yt);

       //Printing the current (x, y) velocity of the robot
       //ROS_INFO("Current Velocity [%f,%f]",vel_msg.linear.x,vel_msg.linear.y);
       

    
    
}

int main(int argc, char **argv){

  ros::init(argc, argv, "controller");
  ros::NodeHandle n;
  
  //Initializing the client to the service /Target_random to request a random target between min and max value
  client = n.serviceClient<my_srv2::Target>("/Target_random");

  //Initializing the publisher to /cmd_vel topic for controlling the robot's velocity
  velocity_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  //Initializing the subscriber the /odom topic to receive the robot's current position
  ros::Subscriber pose_sub = n.subscribe("/odom", 1000, subscriberCallback);

  


  ros::spin();
  return 0;
}
