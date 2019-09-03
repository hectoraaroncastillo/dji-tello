#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Empty.h"
#include "std_msgs/String.h"
#include <sstream>
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include "socketUDP.hpp" 


socketUDP TelloControl, TelloState, TelloImage;

void die(char *s)
{
	perror(s);
	exit(1);
}

void positionCallback(const geometry_msgs::Twist& msg)
{
	
  	ROS_INFO("I heard: [%f]", msg.linear.x);
}

void takeOffCallback(const std_msgs::Empty& msg)
{
	sendDataThroughUDP(&TelloControl,"takeoff", sizeof("takeoff"));
  	ROS_INFO("takeoff");
}


void landCallback(const std_msgs::Empty& msg)
{
	sendDataThroughUDP(&TelloControl, "land", sizeof("land"));
  	ROS_INFO("land");
}


int main(int argc, char **argv)
{
	char buff[512];	
	std_msgs::String msg;
	std_msgs::Empty emptyMsg;
  	ros::init(argc, argv, "tello");
  	ros::NodeHandle n;
	/***  Subscribers nodes ***/
  	ros::Subscriber velocityNode = n.subscribe("tello/cmd_vel", 1000, positionCallback);
  	ros::Subscriber takeoffNode = n.subscribe("tello/takeOff", 1000, takeOffCallback);
  	ros::Subscriber landNode = n.subscribe("tello/land", 1000, landCallback);
	/*** Publishers nodes ***/
	ros::Publisher state_string = n.advertise<std_msgs::String>("tello/state_str", 1000);
	ros::Publisher image_start = n.advertise<std_msgs::Empty>("tello/image_start", 1000);
	/*** Init UDP sockets ***/
	initUDPSocket(&TelloControl, PORT);
	initUDPSocket(&TelloState, PORT_READ_DATA);
	//initUDPSocket(&TelloImage, PORT_IMAGE);
	sendDataThroughUDP(&TelloControl, "command", sizeof("command"));
	sendDataThroughUDP(&TelloControl, "streamon", sizeof("streamon"));
    	
	while(true)
	{	
		image_start.publish(emptyMsg);
		/*** Read state and send ***/	
		readDataThroughUDP(&TelloState, buff);
		msg.data = buff;
		state_string.publish(msg);
	}

  ros::spin();
	//close(s);
	return 0;
}
