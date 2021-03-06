#include <ros/ros.h>
#include<sensor_msgs/JointState.h>
#include <dynamic_reconfigure/server.h>
#include <dynamic_angle/anglesConfig.h>
#include "std_msgs/String.h"
ros::Publisher pub;
sensor_msgs::JointState msg;
void callback(dynamic_angle::anglesConfig &config, uint32_t level) {
  ROS_INFO("Reconfigure Request: %d %d %d %d %d", 
            config.base_joint_axis1, config.shoulder_joint_axis2, 
            config.arm_joint_axis3, 
            config.wristroll_joint_axis4, 
            config.wristyaw_joint_axis5);
msg.position.resize(5);
msg.name.resize(5);
msg.name[0]="base_joint_axis1";
msg.name[1]="shoulder_joint_axis2";
msg.name[2]="arm_joint_axis3";
msg.name[3]="wristroll_joint_axis4";
msg.name[4]="wristyaw_joint_axis5";
msg.position[0]=config.base_joint_axis1;
msg.position[1]=config.shoulder_joint_axis2;
msg.position[2]=config.arm_joint_axis3;
msg.position[3]=config.wristroll_joint_axis4;
msg.position[4]=config.wristyaw_joint_axis5;

pub.publish(msg);

}
int main(int argc, char **argv) {
  ros::init(argc, argv, "dynamic_angle");
  ros::Time::init();
  ros::NodeHandle n;
  pub = n.advertise<sensor_msgs::JointState>("/Joint_state", 10);
  ros::Rate loop_rate(10);
  dynamic_reconfigure::Server<dynamic_angle::anglesConfig> server;
  dynamic_reconfigure::Server<dynamic_angle::anglesConfig>::CallbackType f;
  f = boost::bind(&callback, _1, _2);
  server.setCallback(f);
  ROS_INFO("Spinning node");
  ros::spin();
  return 0;
}
