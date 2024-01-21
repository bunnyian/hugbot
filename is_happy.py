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
            horizontal_position = int(((boxes_face[0][0] + boxes_face[0][2]) / 1400)*7)
            print(horizontal_position)
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
                    # ser.write(b'0') # user is sad/disgusted/angry
                    send_data(0, horizontal_position)
                    buffer.clear()
                elif (max(state_0_count, state_1_count, state_2_count) == state_1_count):
                    print('sending b!')
                    # ser.write(b'1') # user is neutral / not in frame
                    send_data(1, horizontal_position)
                    buffer.clear()
                else:
                    print('sending c!')
                    # ser.write(b'2')
                    send_data(2, horizontal_position)
                    buffer.clear()
        
        if cv2.waitKey(1) &0xFF == ord('q'):
            break

def send_data(state_index, horizontal_position):
    # Ensure the values are within the correct range
    if 0 <= state_index <= 2 and 0 <= horizontal_position <= 6:
        # Encoding: assuming value1 uses the upper 3 bits and value2 uses the lower 5 bits
        encoded_byte = (state_index << 5) | horizontal_position
        ser.write(bytes([encoded_byte]))
    else:
        print("Values out of range")


# labels = ['angry','disgust','fear','happy','neutral','sad','surprise']

if __name__ == "__main__":
    needs_hug()