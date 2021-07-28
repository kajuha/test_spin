#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
int main(int argc, char **argv) {
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub =     
  n.advertise<std_msgs::String>("chatter", 1000);
  int chatter_count = 0;
  // ros::Timer timer = n.createTimer(ros::Duration(0.01),
  ros::Timer timer = n.createTimer(ros::Duration(1),
  [&](const ros::TimerEvent&) {
    std_msgs::String msg;
    std::stringstream ss;
    ss << "chatter messages: " << chatter_count;
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);
    chatter_count++;
  });
  
  ros::spin();
  return 0;
}