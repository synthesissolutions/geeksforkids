import mediapipe as mp
import cv2
import numpy as np
import math
import itertools
#from playsound import playsound
#import RPi.GPIO as GPIO
#GPIO.setmode(GPIO.BCM)  #Set pin configuration for board type

#global variables:

camera_index = 0

#mediapipe mesh variables
mp_face_mesh = mp.solutions.face_mesh
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
face_mesh = mp_face_mesh.FaceMesh(refine_landmarks=True)

frame = ()
overlay = ()
facial_landmarks = ()

#counters
drive_timer = 0
down_timer = 0

#dwell times
drive_dwell = 10
down_dwell = 5
enable_dwell = 100

#gaze range (larger gives more control, more eye strain)
gaze_range = (-5, 5)

#enable/disable driving
car_enable = False

#sounds
sounds = ()


#font
font = cv2.FONT_HERSHEY_PLAIN

def distance(point1, point2):
    x1,y1 = point1
    x2,y2 = point2
    return math.sqrt(pow((x2-x1),2) + pow((y2-y1),2))

def resetCar():
    steer.ChangeDutyCycle(50)
    drive.ChangeDutyCycle(50)
    
def carOutput(gaze):
    #map gaze output from 0 to 100, 50 in the middle
    gaze_out = int(((gaze - gaze_range[0])/(gaze_range[1] - gaze_range[0]))*100)
    
    if gaze_out < 0:
        gaze_out = 0
    elif gaze_out > 100:
        gaze_out = 100
    
    steer.ChangeDutyCycle(gaze_out)
    drive.ChangeDutyCycle(75)
    
    cv2.putText(overlay, str(gaze_out), (50, 260), font, 4, (255,0,255), 5)
    
def printScreen(gaze_text, text_color, drive):

    if not text_color:
        text_color = (0,0,0)
        gaze_text = ""
        
    enable_text = "Car Enabled:" + str(car_enable)
    
    if drive:
      cv2.putText(overlay, "Driving", (50, 160), font, 4, text_color, 5)  
    
    cv2.putText(overlay, gaze_text, (50, 60), font, 4, text_color, 5)
    cv2.putText(overlay, enable_text, (50, 460), font, 4, (255, 255, 255), 5)
    
def playSound(index):
    #playsound(sounds[index])
    #playsound("C:\Users\Joe H\Documents\Sound recordings\Drive_Off.m4a")
    return

def captureLandmarks():
    
    global frame
    global overlay
    global facial_landmarks
    
    ret, frame = cap.read()
    overlay = frame.copy()
    frame = cv2.resize(frame, (640, 480))
    overlay = cv2.resize(overlay, (640, 480))
    rgb_frame = cv2.cvtColor(overlay, cv2.COLOR_BGR2RGB)
    results = face_mesh.process(rgb_frame)
    if not results.multi_face_landmarks:
        return ()
    
    for facial_landmarks in results.multi_face_landmarks:

        #draw all 468 landmarks:
        for count in range(0, 468):
            point = facial_landmarks.landmark[count]
            x = int(point.x*640)
            y = int(point.y*480)
            cv2.circle(frame, (x,y), 1, (0, 255, 0), 1)

        #draw contour around left eye
        mp_drawing.draw_landmarks(overlay, facial_landmarks,
                                  mp_face_mesh.FACEMESH_LEFT_EYE,
                                  None)
        #draw contour around right eye
        mp_drawing.draw_landmarks(overlay, facial_landmarks,
                                  mp_face_mesh.FACEMESH_RIGHT_EYE,
                                  None)

        #draw contours around irises
        mp_drawing.draw_landmarks(overlay, facial_landmarks,
                                  mp_face_mesh.FACEMESH_IRISES,
                                  None,
                                  mp_drawing_styles.get_default_face_mesh_iris_connections_style())
        
    left_eye_index = list(set(itertools.chain(*mp_face_mesh.FACEMESH_LEFT_EYE)))
    right_eye_index = list(set(itertools.chain(*mp_face_mesh.FACEMESH_RIGHT_EYE)))
    iris_index = list(set(itertools.chain(*mp_face_mesh.FACEMESH_IRISES)))
        
    return (iris_index, left_eye_index, right_eye_index)

def findContours(index_list):
    
    if len(index_list) == 0:
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
            cv2.line(overlay, (x1,y1), (x2,y2), (255, 255, 0), 2)
            eye_data.append((x1,y1))
            eye_data.append((x2,y2))
        else: #fill data for right eye
            pt1 = facial_landmarks.landmark[right_eye_index[all_indices[count]]]
            pt2 = facial_landmarks.landmark[right_eye_index[all_indices[count+1]]]
            x1 = int(pt1.x * 640)
            y1 = int(pt1.y * 480)
            x2 = int(pt2.x * 640)
            y2 = int(pt2.y * 480)
            cv2.line(overlay, (x1,y1), (x2,y2), (255, 255, 0), 2)
            eye_data.append((x1,y1))
            eye_data.append((x2,y2))
            
    return eye_data
    

def findGaze(eye_data):
    
    if len(eye_data) == 0:
        return 0, ()
    
    #Down detection
    left_hor = distance(eye_data[2], eye_data[3])
    left_vert = distance(eye_data[4], eye_data[5])
    
    right_hor = distance(eye_data[6], eye_data[7])
    right_vert = distance(eye_data[8], eye_data[9])
    
    down_data = (left_hor, left_vert, right_hor, right_vert)
    

      
    #Left/Right/Center detection
      
    #average distances to left endpoints:
    left_distance = (distance(eye_data[0], eye_data[2])+distance(eye_data[1], eye_data[6]))/2
    right_distance = (distance(eye_data[0], eye_data[3])+distance(eye_data[1], eye_data[7]))/2
    
    gaze = (left_distance - right_distance)/((left_hor+right_hor)/2)*10

    return gaze, down_data

    
def gazeOutput(gaze, down_data):
    
    global drive_timer
    global down_timer
    global car_enable
    
    gaze_text = ""
    text_color = 0
    
    #flags for left, right, drive, and down
    down = False
    drive = False
    right = False
    left = False
    
    #include strength value for how far left/right
    strength = ""
    if abs(gaze) > 2:
        for i in range(0,int(abs(gaze))-1):
            strength = strength + "+"

    drive_timer = drive_timer + 1 #increment drive timer

    if (len(down_data) == 0): #if we don't see a face
        gaze_text = "Face Count Error"
        text_color = (255, 255, 255)
        drive_timer = 0
        car_enable = False
        
    elif (down_data[1] < down_data[0]/4 or down_data[3] < down_data[2]/4):
        gaze_text = "Looking Down"
        text_color = (0, 255, 255)
        down_timer = down_timer + 1
        down = True
        
    elif (gaze > 1.5):
        gaze_text = "Left" + strength
        text_color = (0, 0, 255)
        down_timer = 0
        left = True
        
    elif (gaze < -1.5):
        gaze_text = "Right" + strength
        text_color = (0, 255, 0)
        down_timer = 0
        right = True
        
    else:
        gaze_text = "Center"
        text_color = (255, 0, 0)
        down_timer = 0
        
    if (drive_timer > drive_dwell and not down and car_enable):
        drive = True
        
    if (down_timer > down_dwell):
        gaze_text = "Stopping"
        drive_timer = 0
        
    if (down_timer > enable_dwell):
        car_enable = not car_enable

        if car_enable:
            playSound(0)
        else:
            playSound(1)

        down_timer = 0
    
    printScreen(gaze_text, text_color, drive)
    
#    if drive:
#        carOutput(gaze)
#    else:
#        resetCar()
    
#capture video
cap = cv2.VideoCapture(camera_index)

#initialize car
#GPIO.setup(12, GPIO.OUT)
#GPIO.setup(13, GPIO.OUT)
#drive = GPIO.PWM(12, 1000)
#steer = GPIO.PWM(13, 1000)

#resetCar()

while True:

        
    index_list = captureLandmarks()
    
    eye_data = findContours(index_list)
    
    gaze, down_data = findGaze(eye_data)
    
    gazeOutput(gaze, down_data)
                
    cv2.imshow("FRAME", frame)
    cv2.imshow("OVERLAY", overlay)
    if cv2.waitKey(1) & 0xFF == 27:
        break
cap.release()
cv2.destroyAllWindows()

