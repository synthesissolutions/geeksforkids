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
* Run the demo code from the video https://www.youtube.com/watch?v=B7fWq_U_ipw&t=320s
    * You can change the cv2.VideoCapture call to cv2.VideoCapture(0) instead of cv2.VideoCapture("path to mp4") to use the USB camera