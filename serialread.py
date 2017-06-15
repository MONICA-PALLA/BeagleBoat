import numpy as np
import cv2
import serial, time

ch = ' '
line = " "
lat = " "
lon = " "

cap = cv2.VideoCapture(0)

# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('10.avi', fourcc, 20.0, (640,480))
ser = serial.Serial('/dev/ttyACM1', baudrate=115200)
latlong=0
while(1):
        ch = ser.read()
	line+=ch
	print line	
                
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    
# Release everything if job is finished
cap.release()
out.release()
cv2.destroyAllWindows()

