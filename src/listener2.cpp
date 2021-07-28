#include "ros/ros.h"
#include "std_msgs/String.h"

#include <thread>
#include <chrono>

void ChatterCallback(const std_msgs::String::ConstPtr& msg) {
  ROS_INFO(" I heard: [%s]", msg->data.c_str());
  // std::this_thread::sleep_for(std::chrono::duration<double>(0.02));
  std::this_thread::sleep_for(std::chrono::duration<double>(2));
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "listener2");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 10, ChatterCallback);
  ros::spin();

  return 0;
}