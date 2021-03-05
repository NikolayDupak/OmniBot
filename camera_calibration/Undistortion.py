import numpy as np
import cv2
import json
from json import JSONEncoder

with open("camera_param1.json", "r") as read_file:
    decodedArray = json.load(read_file)
    ret = np.asarray(decodedArray["ret"])
    mtx = np.asarray(decodedArray["mtx"])
    dist = np.asarray(decodedArray["dist"])
    rvecs = np.asarray(decodedArray["rvecs"])
    tvecs = np.asarray(decodedArray["tvecs"])

img = cv2.imread('chessboard/chess_13.jpg')
h,  w = img.shape[:2]
newcameramtx, roi=cv2.getOptimalNewCameraMatrix(mtx,dist,(w,h),1,(w,h))

# 1
# undistort
dst = cv2.undistort(img, mtx, dist, None, newcameramtx)

# crop the image
x,y,w,h = roi
dst = dst[y:y+h, x:x+w]
cv2.imwrite('undistorted1.png',dst)

# 2
# undistort
mapx,mapy = cv2.initUndistortRectifyMap(mtx,dist,None,newcameramtx,(w,h),5)
dst = cv2.remap(img,mapx,mapy,cv2.INTER_LINEAR)

# crop the image
x,y,w,h = roi
dst = dst[y:y+h, x:x+w]
cv2.imwrite('undistorted2.png',dst)
orig = img[y:y+h, x:x+w]
cv2.imwrite('original_cropped.png', orig)
