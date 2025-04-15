#import packages
import mediapipe as mp
import cv2
import numpy as np
import math
import itertools
from rpi_hardware_pwm import HardwarePWM
import RPi.GPIO as GPIO
import time

#GPIO setup
GPIO.setmode(GPIO.BCM)

#set pin numbers
light_list = (16, 21, 20, 26)
headrest_button = 6
green_LED_input = 27
red_LED = 5
yellow_LED = 22
green_LED = 17
left_cal_button = 12
right_cal_button = 25
#photoresistor_pin = 25  
#led_pin = 24

#GPIO pin setup
GPIO.setup(light_list[0], GPIO.OUT)
GPIO.setup(light_list[1], GPIO.OUT)
GPIO.setup(light_list[2], GPIO.OUT)
GPIO.setup(light_list[3], GPIO.OUT)
GPIO.setup(headrest_button,GPIO.IN,pull_up_down = GPIO.PUD_UP)
GPIO.setup(green_LED_input,GPIO.IN,pull_up_down = GPIO.PUD_UP)
GPIO.setup(red_LED,GPIO.OUT)
GPIO.setup(yellow_LED,GPIO.OUT)
GPIO.setup(green_LED,GPIO.OUT)
GPIO.setup(left_cal_button,GPIO.IN,pull_up_down = GPIO.PUD_UP)
GPIO.setup(right_cal_button,GPIO.IN,pull_up_down = GPIO.PUD_UP)
#GPIO.setup(photoresistor_pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
#GPIO.setup(led_pin, GPIO.OUT)


#initialize light outputs
GPIO.output(light_list[0], 1)
GPIO.output(red_LED, GPIO.HIGH)
GPIO.output(yellow_LED, GPIO.LOW)
GPIO.output(green_LED, GPIO.LOW)
#GPIO.output(led_pin, GPIO.LOW)

#set time variables
time_pressed = 0
time_released = 0

#sounds
sound_list = (6,13)
for sound in sound_list:
    GPIO.setup(sound, GPIO.OUT)

#MediaPipe mesh variables
mp_face_mesh = mp.solutions.face_mesh
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
face_mesh = mp_face_mesh.FaceMesh(refine_landmarks=True)

#MediaPipe points for eye outline
left_iris = [474, 475, 476, 477]
right_iris = [469, 470, 471, 472]
eye_line = [34, 35, 33, 471, 468, 469, 133, 244, 6, 464, 362, 476, 473, 474, 263, 265, 264]
track_pts = [33, 471, 474, 263]

#setting initial frame, overlay, and facial landmarks
frame = ()
overlay = ()
facial_landmarks = ()

#setting initial indices
drive_index = 0
down_index = 0

#drive and steer PWM
drive = HardwarePWM(pwm_channel=0, hz=1000)
steer = HardwarePWM(pwm_channel=1, hz=1000)

steer.start(50)
drive.start(50)

#dwell times
drive_dwell = 10    #threshold for time to start driving
down_dwell = 5      #threshold for time to stop the car from eye closure
enable_dwell = 15   #threshold for time to change car enable's state

#gaze range (larger range gives more control)
gaze_range = (-6, 6)

#enable/disable driving
car_enable = False

#sets values for calibration if system is not calibrated
far_left_cal = 12
far_right_cal = 70
cal_button_state = 0
down_state = 0
headrest_button_state = 1

#font
font = cv2.FONT_HERSHEY_PLAIN

#distance formula
def distance(point1, point2):
    x1,y1 = point1
    x2,y2 = point2
    return math.sqrt(pow((x2-x1),2) + pow((y2-y1),2))

#resets steering to "center" and speed to "stopped" when drive is false
def resetCar():
    
    global steer
    global drive
    
    steer.change_duty_cycle(50)
    drive.change_duty_cycle(50) 
    
#maps gaze output from 0 to 100 (50 in the middle) based on R and L calibration values    
def carOutput(gaze):
    
    global gaze_out
    
    gaze_out = int(((gaze - gaze_range[0])/(gaze_range[1] - gaze_range[0]))*100)
    
    #sets min and max gaze out values to 0 and 100 respectively
    if gaze_out < far_left_cal:
        gaze_out = 0
    elif gaze_out > far_right_cal:
        gaze_out = 100
        
    #scales gaze output value between 0 and 100 based on R and L calibration values
    else:
        if far_left_cal < 0:
            gaze_out = int((gaze_out-far_left_cal)/(abs(far_left_cal)+abs(far_right_cal))*100)
        else:
            gaze_out = int((gaze_out-far_left_cal)/(abs(far_right_cal)-abs(far_left_cal))*100)
            
    steer.change_duty_cycle(gaze_out)   #steering output based on gaze output
    drive.change_duty_cycle(0)         #speed output of car
    
    #prints gaze output onto the video screen
    cv2.putText(overlay, str(gaze_out), (50, 260), font, 4, (255,0,255), 5)

#prints state of the car onto the video screen
def printScreen(gaze_text, text_color, drive):
    
    if not text_color:
        text_color = (0,0,0)
        gaze_text = ""
        
    enable_text = "Car Enabled:" + str(car_enable)
    
    if drive:
      cv2.putText(overlay, "Driving", (50, 160), font, 4, text_color, 5)

    cv2.putText(overlay, enable_text, (50, 460), font, 4, (255, 255, 255), 5)
    
    if frame is not None:
        cv2.imshow("FRAME", frame)
        cv2.imshow("OVERLAY", overlay)

#def get_light_level():
#    return GPIO.input(photoresistor_pin)
#
#def switch_lights():
#    
#    light_level = get_light_level()
#        
#    if light_level == GPIO.HIGH:
#        GPIO.output(led_pin, GPIO.LOW)
#        print("off")
#    else:
#        GPIO.output(led_pin, GPIO.HIGH)
#        print("on")
#        
#    time.sleep(0.1)

#car lighting based on state of the car
def showLights():
    
    global down_index
    global car_enable
     
    if down_index > down_dwell:
        GPIO.output(light_list[1], 1)
    else:
        GPIO.output(light_list[1], 0)
         
    if down_index > int((enable_dwell + down_dwell)/2):
        GPIO.output(light_list[2], 1)
    else:
        GPIO.output(light_list[2], 0)
       
    if car_enable:
        GPIO.output(light_list[3], 1)
    else:
        GPIO.output(light_list[3], 0)

#car sound based on state of the car
def playSound(index):
    
    if index == -1:
        for sound in sound_list:
            GPIO.output(sound, 1)
            
    else:
        GPIO.output(sound_list[index], 0)

#captures MediaPipe facial landmarks (returns arrays of key points)
def captureLandmarks():
    
    global frame
    global overlay
    global facial_landmarks
    
    ret, frame = cap.read()
    
    if frame is None:
        return
    
    overlay = frame.copy()
    frame = cv2.resize(frame, (640, 480))
    overlay = cv2.resize(overlay, (640, 480))
    rgb_frame = cv2.cvtColor(overlay, cv2.COLOR_BGR2RGB)
    results = face_mesh.process(rgb_frame)
    img_h, img_w = overlay.shape[:2]
    if not results.multi_face_landmarks:
        return None
    
    for facial_landmarks in results.multi_face_landmarks:
        mesh_points = np.array(
            [np.multiply([p.x, p.y], [img_w, img_h]).astype(int) for p in results.multi_face_landmarks[0].landmark])
        counter = 0
        
        #draws all 468 landmarks
        for count in range(0, 468):
            point = facial_landmarks.landmark[count]
            x = int(point.x*640)
            y = int(point.y*480)
            cv2.circle(frame, (x,y), 1, (0, 255, 0), 1)

        #draws 4 tracking landmarks
        for count in range(0, 4):
            point = results.multi_face_landmarks[0].landmark[track_pts[counter]]
            x = int(point.x * 640)
            y = int(point.y * 480)
            cv2.circle(overlay, (x, y), 1, (255, 200, 0), 1)
            counter = counter + 1

        #draws cicles around irises
        (l_cx, l_cy), l_radius = cv2.minEnclosingCircle(mesh_points[left_iris])
        (r_cx, r_cy), r_radius = cv2.minEnclosingCircle(mesh_points[right_iris])
        center_left = np.array([l_cx, l_cy], dtype=np.int32)
        center_right = np.array([r_cx, r_cy], dtype=np.int32)
        cv2.circle(overlay, tuple(center_left), int(l_radius), (0, 0, 255), 1, cv2.LINE_AA)
        cv2.circle(overlay, tuple(center_right), int(r_radius), (0, 255, 0), 1, cv2.LINE_AA)

    #creates arrays for lists of points for left eye, right eye, and irises
    left_eye_index = list(set(itertools.chain(*mp_face_mesh.FACEMESH_LEFT_EYE)))
    right_eye_index = list(set(itertools.chain(*mp_face_mesh.FACEMESH_RIGHT_EYE)))
    iris_index = list(set(itertools.chain(*mp_face_mesh.FACEMESH_IRISES)))
        
    return (iris_index, left_eye_index, right_eye_index)

#takes in lists of landmarks and returns key points of data for irises, left eye, and right eye
def findContours(index_list):
    
    if index_list is None:
        return []
    
    all_indices = (4,6,0,2,7,6,2,11,1,4,-1,8)   #first four irises,
                                                #next four left eye (horizontal then vertical),
                                                #last four right eye (horizontal then vertical)
    iris_index = index_list[0]
    left_eye_index = index_list[1]
    right_eye_index = index_list[2]
    
    eye_data = []
    
    #first two: pupil locations
    #next two: left eye horizontal line
    #next two: left eye vertical line
    #next two: right eye horizontal line
    #last two: right eye vertical line
    
    for count in range(0,12,2):
        if count < 4: #fill data for irises
            pt1 = facial_landmarks.landmark[iris_index[all_indices[count]]]
            pt2 = facial_landmarks.landmark[iris_index[all_indices[count+1]]]
            x = int((pt1.x + pt2.x) * 640 / 2)
            y = int((pt1.y + pt2.y) * 480 / 2)
            cv2.circle(overlay, (x,y), 1, (255, 255, 255), 2)
            eye_data.append((x,y))
        elif count < 8: #fill data for left eye
            pt1 = facial_landmarks.landmark[left_eye_index[all_indices[count]]]
            pt2 = facial_landmarks.landmark[left_eye_index[all_indices[count+1]]]
            x1 = int(pt1.x * 640)
            y1 = int(pt1.y * 480)
            x2 = int(pt2.x * 640)
            y2 = int(pt2.y * 480)
            eye_data.append((x1,y1))
            eye_data.append((x2,y2))
        else: #fill data for right eye
            pt1 = facial_landmarks.landmark[right_eye_index[all_indices[count]]]
            pt2 = facial_landmarks.landmark[right_eye_index[all_indices[count+1]]]
            x1 = int(pt1.x * 640)
            y1 = int(pt1.y * 480)
            x2 = int(pt2.x * 640)
            y2 = int(pt2.y * 480)
            eye_data.append((x1,y1))
            eye_data.append((x2,y2))
            
    return eye_data

#calculates gaze given key points of data for irises, left eye, and right eye and returns the gaze and down data
def findGaze(eye_data):
    
    if len(eye_data) == 0:
        return 0, ()
    
    #determines horizontal and vertical distances for each eye to determine if looking down
    #deteremines the distance between the edge of the scalera and and the edge of the iris in both the x and y direction
    left_hor = distance(eye_data[2], eye_data[3])
    left_vert = distance(eye_data[4], eye_data[5])
    left_xdist = (facial_landmarks.landmark[263].x * 640) - (facial_landmarks.landmark[474].x * 640)
    left_ydist = (facial_landmarks.landmark[263].y * 480) - (facial_landmarks.landmark[474].y * 480)
    
    right_hor = distance(eye_data[6], eye_data[7])
    right_vert = distance(eye_data[8], eye_data[9])
    right_xdist = (facial_landmarks.landmark[471].x * 640) - (facial_landmarks.landmark[33].x * 640)
    right_ydist = (facial_landmarks.landmark[471].y * 480) - (facial_landmarks.landmark[33].y * 480)

    #average gaze in the y-direction
    gazeY = (left_ydist - right_ydist)/2

    # down detection
    down_data = (left_hor, left_vert, right_hor, right_vert)
    
    #average distances to endpoints
    left_distance = (distance(eye_data[0], eye_data[2])+distance(eye_data[1], eye_data[6]))/2
    right_distance = (distance(eye_data[0], eye_data[3])+distance(eye_data[1], eye_data[7]))/2

    #average gaze in the x-direction
    gazeX = (left_xdist - right_xdist)/2

    #calculated gaze point using average in x direction and y direction
    gaze = (gazeX, gazeY)
    
    return gaze, down_data

#different states the car can be in while detecting the eyes
def gazeOutput(gaze, down_data):
    
    global drive_index
    global down_index
    global car_enable
    global drive_dwell
    global headrest_button_state
    global far_left_cal
    global far_right_cal
    global down_state
    global cal_button_state
    
    gaze_text = ""
    text_color = 0
    
    drive = False
    
    #calibration buttons
    #look as far left as comfortable and press the L calibration button
    #look as far right as comfortable and press the R calibration button
    if GPIO.input(left_cal_button) == GPIO.LOW and car_enable == False and cal_button_state == 0:  # Detect when the "c" key is pressed
        calibrationSystem(gaze[0], 'L')
    elif GPIO.input(right_cal_button) == GPIO.LOW  and car_enable == False and cal_button_state == 0:  # Detect when the "c" key is pressed
        calibrationSystem(gaze[0], 'R')
        
    #include strength value for how far left/right
    strength = ""
    if(type(gaze) == int):
        gaze_text = "Face Count Error"
        text_color = (255, 255, 255)
        drive_index = 0
        car_enable = False
        headrest_button_state = 1
    else:
        if (abs(gaze[0]) > 2):
            for i in range(0,int(abs(gaze[0]))-1):
                strength = strength + "+"
        
        drive_index = drive_index + 1 #increment drive timer
        
    #if no face is detected
    if (len(down_data) == 0):
        gaze_text = "Face Count Error"
        text_color = (255, 255, 255)
        drive_index = 0
        car_enable = False
        headrest_button_state = 1
        down_state = 0
        cal_button_state = 1
        
    #if looking down or eyes are closed    
    elif (down_data[1] < down_data[0]/7 or down_data[3] < down_data[2]/7):
        gaze_text = "Looking Down"
        text_color = (0, 255, 255)
        down_index = down_index + 1
        down_state = 1
        cal_button_state = 1
    
    #if looking left
    elif (gaze[0] > 2.4 and abs(gaze[1]) <= 6):
        gaze_text = "Left" + strength
        text_color = (0, 0, 255)
        down_index = 0
        down_state = 0
        cal_button_state = 0
        
    #if looking right    
    elif (gaze[0] < -2.7 and abs(gaze[1]) <= 6):
        gaze_text = "Right" + strength
        text_color = (0, 255, 0)
        down_index = 0
        down_state = 0
        cal_button_state = 0
    
    #gaze text to show strength of L and R gaze
    elif (abs(gaze[1]) > 6):
        if gaze[1] > 0:
            if gaze[0] <= -1:
                gaze_text = "Left" + strength
                text_color = (0, 0, 255)
                down_index = 0
            elif gaze[0] >= 2:
                gaze_text = "Right" + strength
                text_color = (0, 255, 0)
                down_index = 0      
            else:
                gaze_text = "Center"
                text_color = (255, 0, 0)
                down_index = 0
                
        else:
            if gaze[0] <= -2:
                gaze_text = "Left" + strength
                text_color = (0, 0, 255)
                down_index = 0
            
            elif gaze[0] >= 1:
                gaze_text = "Right" + strength
                text_color = (0, 255, 0)
                down_index = 0    
            else:
                gaze_text = "Center"
                text_color = (255, 0, 0)
                down_index = 0
                
        down_state = 0
        cal_button_state = 0
                
    else:
        gaze_text = "Center"
        text_color = (255, 0, 0)
        down_index = 0
        down_state = 0
        cal_button_state = 0
        
    #if looking down or eyes are closed for long enough     
    if (down_index > down_dwell):
        gaze_text = "Stopping"
        drive_index = 0   #car stops driving
        headrest_button_state = 1
    
    #if drive index exceeds the threshold and car enable is true
    if (drive_index > drive_dwell and car_enable):
        drive = True   #car starts driving
        headrest_button_state = 2
        GPIO.output(red_LED, GPIO.LOW)   #red LED off
        GPIO.output(green_LED,GPIO.HIGH) #green LED on
    else:
        GPIO.output(red_LED, GPIO.HIGH)  #red LED on
        GPIO.output(green_LED,GPIO.LOW)  #green LED off

    if (down_index == enable_dwell):     #if looking down or eyes closed for long enough
        car_enable = not car_enable      #car enable changes state
        if car_enable:
            playSound(0)
        else:
            playSound(1)
    else:
        playSound(-1)   #reset all sound GPIO pins

    #if drive is true, allow the car to start and be steered with the eyes
    if drive:
        carOutput(gaze[0])
    else:
        resetCar()
        
    showLights()
    
    printScreen(gaze_text, text_color, drive)

#controls the start/stop using the button on the headrest
#controls LEDs on the camera mount
def pressHeadrestButton(count):

    global car_enable
    global headrest_button_state
    global down_state
         
    #if button is pressed, records current time     
    if GPIO.input(headrest_button) == GPIO.LOW and count == 1:
        time_pressed = time.time()
        
        #while button is being pressed
        while GPIO.input(headrest_button) == GPIO.LOW:
            
                #while button is being pushed, yellow LED turns on
                if time.time() - time_pressed >= 0.1 and (headrest_button_state == 1 or headrest_button_state == 3):
                    GPIO.output(red_LED, GPIO.LOW)
                    GPIO.output(yellow_LED, GPIO.HIGH)
                    
                    #establishes a time delay to prevent accidental starting of the car
                    if (time.time() - time_pressed >= 1 and car_enable == False):
                        headrest_button_state = 2
                        GPIO.output(red_LED, GPIO.LOW) 
                        GPIO.output(yellow_LED, GPIO.LOW) 
                        GPIO.output(green_LED,GPIO.HIGH)   #green LED turns on
                        car_enable = True   #the car starts
                        time.sleep(0.1)
                        
                    else:
                        GPIO.output(yellow_LED, GPIO.LOW)
                        
                    if down_state == 1:
                        down_state = 0
                        break;
                    
    #if the button is pressed again              
    if GPIO.input(headrest_button) == GPIO.LOW and car_enable == True:
            if count == 2 or count == 3:
                time_pressed2 = time.time() 
                while GPIO.input(headrest_button) == GPIO.LOW:
                    if time.time() - time_pressed2 >= 0.001: 
                        GPIO.output(green_LED,GPIO.LOW)   #green LED turns off (red turns on)
                        car_enable = False   #the car stops
                        headrest_button_state = 1
                    
                    #allows headrest button to work with looking down or eye closure
                    if down_state == 1:
                        down_state = 0
                        break;
                    
    #if the green LED is off, the red LED is on                
    if GPIO.input(green_LED_input) == GPIO.LOW: 
        GPIO.output(red_LED, GPIO.HIGH)

#when calibration buttons are used, gaze output is saved as far_left_cal and far_right_cal
def calibrationSystem(gaze, side):
    
    global far_left_cal
    global far_right_cal
    
    gaze_out = int(((gaze - gaze_range[0])/(gaze_range[1] - gaze_range[0]))*100)
    if side == 'L':
        far_left_cal = gaze_out
        cv2.putText(overlay, str(gaze_out), (50, 260), font, 4, (255,0,255), 5)
    elif side == 'R':
        far_right_cal = gaze_out - 5 #accounts for slightly off linear actuator placement
        cv2.putText(overlay, str(gaze_out), (50, 260), font, 4, (255,0,255), 5)

#capture video
cap = cv2.VideoCapture(0)

while True:
        
    index_list = captureLandmarks()
    
    eye_data = findContours(index_list)
    
    gaze, down_data  = findGaze(eye_data)
    
    gazeOutput(gaze, down_data)
    
    pressHeadrestButton(headrest_button_state)
    
    if cv2.waitKey(1) & 0xFF == 27:
        break

#clean up GPIO on program exit
GPIO.cleanup()
cap.release()
cv2.destroyAllWindows()
