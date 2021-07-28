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
  ros::init(argc, argv, "listener3");
  ros::NodeHandle n;
  #if 0
  // 스피너를 증가시키더라도 멀티쓰레드로 동작하지 않음
  // 콜백함수를 동시에 실행할 수 없기 때문
  ros::Subscriber sub = n.subscribe("chatter", 1, ChatterCallback);
  #else
  // 콜백함수를 동시에 동작할 수 있도록 변경
  ros::SubscribeOptions ops;
  ops.template init<std_msgs::String>("chatter", 1, ChatterCallback);
  ops.allow_concurrent_callbacks = true;
  ros::Subscriber sub1 = n.subscribe(ops);
  #endif
  
  ros::MultiThreadedSpinner spinner(2);
  spinner.spin();
  return 0;
}