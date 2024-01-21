import f_emotion_detection as fed
import cv2
from imutils.video import VideoStream
import imutils
import argparse
import time
from collections import deque

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
        else:
            img_post = im 

        cv2.imshow('emotion_detection',img_post)
        if cv2.waitKey(1) &0xFF == ord('q'):
            break
        
        if len(emotions)!=0:
            buffer.append(emotions[0])
            if len(buffer) == 10:
                if buffer.count('happy') + buffer.count('neutral') < 5:
                    print('Needs a hug')
                    buffer.clear()
        
        if cv2.waitKey(1) &0xFF == ord('q'):
            break

            
# labels = ['angry','disgust','fear','happy','neutral','sad','surprise']

if __name__ == "__main__":
    needs_hug()