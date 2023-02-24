import numpy as np
import cv2

# built-in camera
cap = cv2.VideoCapture(1)

while(True):
    ret, frame = cap.read()

    if frame is not None:
        cv2.imshow("image", frame)

    rval, frame = cap.read()

    # gray image
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    cv2.imshow('frame', gray)
    # when hit 'q', terminate the program
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
