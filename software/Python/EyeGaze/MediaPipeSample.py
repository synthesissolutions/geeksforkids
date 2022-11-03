import cv2
import mediapipe as mp

camera_index = 0

#mediapipe mesh variables
mp_face_mesh = mp.solutions.face_mesh
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
face_mesh = mp_face_mesh.FaceMesh(refine_landmarks=True)

frame = ()
overlay = ()
facial_landmarks = ()

cap = cv2.VideoCapture(camera_index)
while True:
    ret, frame = cap.read()
    overlay = frame.copy()
    frame = cv2.resize(frame, (640, 480))
    overlay = cv2.resize(overlay, (640, 480))
    rgb_frame = cv2.cvtColor(overlay, cv2.COLOR_BGR2RGB)
    results = face_mesh.process(rgb_frame)

    if results.multi_face_landmarks:
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

    cv2.imshow("FRAME", frame)
    cv2.imshow("OVERLAY", overlay)
    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
cv2.destroyAllWindows()