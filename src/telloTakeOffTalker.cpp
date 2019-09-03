#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include <sstream>
#include <iostream>


using namespace std;
int main(int argc, char **argv)
{
  ros::init(argc, argv, "telloTakeOffTalker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Empty>("tello/takeOff", 1000);
  ros::Rate loop_rate(10);
  int count = 0;
  while (ros::ok())
  {
    cin.get();
    std_msgs::Empty msg;
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}

