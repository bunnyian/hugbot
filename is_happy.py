import f_emotion_detection as fed
import cv2
from imutils.video import VideoStream
import imutils
import argparse
import time
from collections import deque

import serial

# ser = serial.Serial('/dev/tty.usbmodem2101', 9600) #the team arduino 
ser = serial.Serial('/dev/cu.usbmodem1101', 9600) #anoop's arduino (just for testing)

def needs_hug():
    buffer = deque(maxlen=10)
# instanciar detector
    Detector = fed.predict_emotions()
    # ----------------------------- video -----------------------------
    #ingestar data
    vs = VideoStream(src=0).start()
    while True:
        star_time = time.time()
        im = vs.read()
        im = cv2.flip(im, 1)
        im = imutils.resize(im, width=720)
        # detectar_rostro
        emotions,boxes_face = Detector.get_emotion(im)
        # visualizacion
        if len(emotions)!=0:
            img_post = fed.bounding_box(im,boxes_face,emotions)
            offset = int(((boxes_face[0][0] + boxes_face[0][2]) / 1400)*7) - 3
            print(offset)
        else:
            img_post = im 

        cv2.imshow('emotion_detection',img_post)
        if cv2.waitKey(1) &0xFF == ord('q'):
            break
        
        if len(emotions)!=0:
            buffer.append(emotions[0])
            if len(buffer) == 10:
                state_0_count = buffer.count('sad') + buffer.count('disgust') + buffer.count('angry')
                state_1_count = buffer.count('neutral') 
                state_2_count = buffer.count('happy') + buffer.count('surprise') 


                if (max(state_0_count, state_1_count, state_2_count) == state_0_count):
                    print('sending a!')
                    ser.write(b'0') # user is sad/disgusted/angry
                    buffer.clear()
                elif (max(state_0_count, state_1_count, state_2_count) == state_1_count):
                    print('sending b!')
                    ser.write(b'1') # user is neutral / not in frame
                    buffer.clear()
                else:
                    print('sending c!')
                    ser.write(b'2')
                    buffer.clear()
        
        if cv2.waitKey(1) &0xFF == ord('q'):
            break

            
# labels = ['angry','disgust','fear','happy','neutral','sad','surprise']

if __name__ == "__main__":
    needs_hug()