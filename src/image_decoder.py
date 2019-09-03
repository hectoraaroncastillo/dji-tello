#!/usr/bin/env python

import rospy
import numpy as np
import cv2
from std_msgs.msg import Empty


startStreaming = False

def callback(data):
    global startStreaming, cap
    if startStreaming == False:
        print("Starting capture")
        cap = cv2.VideoCapture('udp://@0.0.0.0:11111',cv2.CAP_FFMPEG)
        startStreaming = True
        


if __name__ == '__main__':
    global cap
    rospy.init_node('image_decoder', anonymous=True)
    rospy.Subscriber('tello/image_start', Empty, callback)
    while not rospy.is_shutdown():
        if (startStreaming == True):
            if not cap.isOpened():
                print('VideoCapture not opened')
            ret, frame = cap.read()
            cv2.imshow("image", frame)
            if cv2.waitKey(1)&0xFF == ord('q'):
                break
            #rate.sleep()
    cap.release()
    cv2.destroyAllWindows()
    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()
    
