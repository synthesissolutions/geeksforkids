## Setting up Raspberry Pi 4 for Media Pipe
* Install Raspi 32-bit Buster (Legacy OS)
    * If you use the Raspberry Pi Imager, select Raspberry Pi OS (other) and then Raspberry Pi OS (Legacy)
* Make sure it fully updates software either through the startup wizard or with sudo apt update on the command line
* Turn on the USB camera by:
    * sudo raspi-config
    * Go to option 3 Interface Options
    * Choose option 1 USB Camera and answer Yes
    * You must restart after doing this
* Install OpenCV with sudo apt install python3-opencv
* Upgrade numpy with sudo pip3 install -U numpy
* Install MediaPipe library with sudo pip3 install mediapipe-rpi4 
    * It might be necessary to run this command twice (not sure why)
    * If you receive errors related to protobuf, downgrade protobuf with the command
        * sudo pip3 install -U protobuf==3.19.4
* Run the demo code from the video https://www.youtube.com/watch?v=B7fWq_U_ipw&t=320s
    * You can change the cv2.VideoCapture call to cv2.VideoCapture(0) instead of cv2.VideoCapture("path to mp4") to use the USB camera
## Setting up Rapsberry Pi 4 for PWM Output
* Install HardwarePWM - pip3 install rpi-hardware-pwm
* Follow the instructions for enabling Hardware PWM pins here - https://pypi.org/project/rpi-hardware-pwm/
## Setting up PC (Windows/Mac) for EyeGaze Software
* Install Python3
    * https://www.python.org/downloads/
* Install Pip if necessary
    * py -m ensurepip --upgrade
* Install Necessary Modules
    * python -m pip install numpy
    * python -m pip install opencv-python
    * python -m pip install MediaPipe
* Connect a USB Webcam
* Start the Eye Gaze software
    * NOTE: This software doesn't control anything, but instead reports on screen the eye position readings
    * python Eye_Tracking_Desktop.py
