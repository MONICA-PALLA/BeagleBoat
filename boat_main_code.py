import numpy as np
import cv2
import serial, time

ch = ''
line = ""
latitude = ""
longitude = ""
Humidity =""
Date =""
Time=""
Temp=""

cap = cv2.VideoCapture(0)

print time.localtime()
# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter(str(time.localtime())+'14.avi', fourcc, 20.0, (640,480))
ser = serial.Serial('/dev/ttyACM0', baudrate=115200)
latlong=0
while(1):
    ret, frame = cap.read()
#    print "start"
    if ret==True:
#        print "True"
        ch = ser.read()
     	frame = cv2.flip(frame,180)
       	font = cv2.FONT_HERSHEY_COMPLEX_SMALL

	

        if ch == ';':
            line = ""
        else:
            line += ch

      	if line == "LN":
	    
            ch=ser.read()
	    ch=''
  	    longitude=""

            while(1):
            	ch=ser.read()
                if ch==';':
                    break
		longitude+=ch
	    ch=''
	    line=""
        elif line == "LT":
            ch=ser.read()
            ch=' '
            latitude=""
            while(1):
		ch=ser.read()
                if ch==';':
                    break
		latitude+=ch
	    ch=''
 	    line=""
        elif line == "Hu":
            ch=ser.read()
            ch=' '
            Humidity=""
            while(1):
		ch=ser.read()
                if ch==';':
                    break
		Humidity+=ch
	    ch=''
 	    line=""
 	elif line == "Te":
            ch=ser.read()
            ch=''
            Temp=""
            while(1):
		ch=ser.read()
                if ch==';':
                    break
		Temp+=ch
	    ch=''
 	    line=""
 	elif line == "Da":
            ch=ser.read()
            ch=' '
            Date=""
            while(1):
		ch=ser.read()
                if ch==';':
                    break
		Date+=ch
	    ch=''
 	    line=""
 	elif line == "Time":
            ch=ser.read()
            ch=' '
            Time=""
            while(1):
		ch=ser.read()
                if ch==';':
                    break
		Time+=ch
	    ch=''
 	    line=""
        cv2.putText(frame, "Latitude:",(10,15), font, 0.98, (0,0,275))
	cv2.putText(frame, latitude,(140,15), font, 0.98, (0,0,275))
	cv2.putText(frame, "Longitude:",(10,35), font, 0.98, (0,0,275))
	cv2.putText(frame, longitude,(140,35), font, 0.98, (0,0,275))
	cv2.putText(frame, "Date:",(440,15), font, 0.98, (0,0,275))
	cv2.putText(frame, "05/26/2017",(510,15), font, 0.98, (0,0,275))
	cv2.putText(frame, "Time:",(440,35), font, 0.98, (0,0,275))
	cv2.putText(frame, Time,(510,35), font, 0.98, (0,0,275))
 	cv2.putText(frame, "Temp:",(10,440), font, 0.98, (0,0,275))
        cv2.putText(frame, Temp,(135,440), font, 0.98, (0,0,275))
    	cv2.putText(frame, "Humidity:",(10,460), font, 0.98, (0,0,275))
	cv2.putText(frame, Humidity,(135,460), font, 0.98, (0,0,275))
    
	#cv2.putText(frame, "Longitude:",(10,30), font, 0.7, (0,0,275))
	#print latitude,longitude
	out.write(frame)
	
                
       	cv2.imshow('frame',frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    else:
        print "false"
        break
# Release everything if job is finished
cap.release()
out.release()
cv2.destroyAllWindows()

