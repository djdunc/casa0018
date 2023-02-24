# Based on examples on OpenCV website - last tested on OpenCV 4 with Python 3 on a mac
# DW Feb 2023

# Note for future self - sometimes when the script is run from terminal:
# > python3 face_detector_video.py 
# it comes up with color bars and no video, ctrl c to quit and re-run script, usually works second time

import cv2
import sys
import time 

# assumes the two classifier files are in the same folder - see
# docs for more info on CascadeClassifier https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html
face_cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier('haarcascade_eye.xml')

# initialize the video stream and allow camera sensor to warmup
# note - my camera is src 1 (mac), if you only have one camera on your
# device it is more likely to be 0
print("[INFO] starting video stream, please wait...")
video_capture = cv2.VideoCapture(1)
time.sleep(3)

# start the loop to look for faces in each "image" of the video stream
print("[INFO] looking for faces")
while True:
    # Capture frame-by-frame
    # The read() function reads one frame from the video source, which in this example is the webcam. 
    # Returns: The actual video frame read and a return code 
    # Return code can tell us if we have run out of frames if fed a file, we are reading from the webcam so we will ignore it.
    ret, frame = video_capture.read()

    # convert from RGB to greyscale
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # look for faces 
    # face_cascade object has a method detectMultiScale() - receives an image as an argument and runs the classifier cascade over the image. 
    # "MultiScale" indicates algorithm looks at subregions of the image in multiple scales, to detect faces of varying sizes
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)

    # Draw a rectangle around each face detected in "faces"
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        
        # define the sub region of interest to look for eyes 
        roi_gray = gray[y:y+h, x:x+w]   # this is in grey scale image
        roi_color = frame[y:y+h, x:x+w] # this is in RGB

        eyes = eye_cascade.detectMultiScale(roi_gray)
        for (ex,ey,ew,eh) in eyes:
            cv2.rectangle(roi_color,(ex,ey),(ex+ew,ey+eh),(0,255,0),2)
   
    # Display the resulting frame
    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()



