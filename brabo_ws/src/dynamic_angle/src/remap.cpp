#include "ros/ros.h"
#include<sensor_msgs/JointState.h>
#include "std_msgs/String.h"
#include <dynamic_reconfigure/server.h>
#include <dynamic_angle/anglesConfig.h>
sensor_msgs::JointState msg;
ros::Publisher pub;
void velCallback(dynamic_angle::anglesConfig &config, uint32_t level)
{
ROS_INFO("Reconfigure Request: %d %d %d %d %d", 
            config.base_joint_axis1, config.shoulder_joint_axis2, 
            config.arm_joint_axis3, 
            config.wristroll_joint_axis4, 
            config.wristyaw_joint_axis5);


//pub.publish(msg);
}


int main(int argc, char **argv)
{


ros::init(argc, argv, "rhino_pub");
ros::NodeHandle n;
pub = n.advertise<std_msgs::String>("direction_data", 10);
ros::Subscriber sub = n.subscribe("/dynamic_angle/parameter_updates", 10);

ros::spin();

return 0;
}
