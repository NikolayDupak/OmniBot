import cv2
from math import *
import UartComm
from aruco_robot_navigation import ArucoRobotNavigation

l = 0.5
route = [[-l, -l, 0],
         [-l, l, 0],
         [l, l, 0],
         [l, -l, 0],
         [-l, -l, 0],
         [-l, l, 0],
         [l, l, 0],
         [l, -l, 0],
         [-l, -l, 0]]

aruco_pos_last = None
bot_x = bot_y = bot_phi = 100000

def fix_range(val, lim):
    if val > lim:
        val = lim
    if val < -lim:
        val = -lim
    return val

def rotate(x, y, phi):
    x1 = x*cos(phi) - y*sin(phi)
    y1 = x*sin(phi) + y*cos(phi)
    return x1, y1

if __name__ == '__main__':
    comm = UartComm.UartComm("/dev/ttyUSB0", 9600)
    aruco_nav = ArucoRobotNavigation()

    cap = cv2.VideoCapture(1)
    if not cap.isOpened():
        print("no video")
        exit()
    
    for des_x, des_y, des_phi in route:
        int_x = 0
        int_y = 0
        int_phi = 0
        while (abs(des_x - bot_x) > 0.07) or (abs(des_y - bot_y) > 0.07) or (abs(des_phi - bot_phi*180/pi) > 7):
            ret, img = cap.read()
            if img is None:
                break

            aruco_pos, img = aruco_nav.get_robot_position(img)
            cv2.imshow('img', img)
            key = cv2.waitKey(33)
            if (key == ord("q")) or (key == 27):
                break

            if aruco_pos is None:
                aruco_pos = aruco_pos_last
                #comm.send_package([55, 128, 128, 128])
                continue
            aruco_pos_last = aruco_pos
            bot_x, bot_y, bot_phi = aruco_pos

            err_x = des_x - bot_x
            err_y = des_y - bot_y
            err_phi = des_phi*pi/180 - bot_phi
            int_x += err_x
            int_x += err_y
            int_phi += err_phi
            int_x = fix_range(int_x, 20)
            int_y = fix_range(int_y, 20)
            int_phi = fix_range(int_phi, 20)

            vx = 300*err_x #+ 5*int_x
            vy = 300*err_y #+ 5*int_y
            w = 100*err_phi #+ 5*int_phi
            print(err_x, err_y, err_phi)

            vx, vy = rotate(vx, vy, -bot_phi)

            vx = fix_range(vx, 100)
            vy = fix_range(vy, 100)
            w = fix_range(w, 100)
            comm.send_package([55, int(vy) + 128, int(-vx) + 128, int(-w) + 128])
        print("next")

    comm.send_package([55, 128, 128, 128])
    cap.release()
    cv2.destroyAllWindows()
