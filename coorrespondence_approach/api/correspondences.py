from __future__ import print_function
import cv2  # make sure opencv-contrib-python is also installed
import numpy as np
import matplotlib.pyplot as plt
from api.find_roi import find_roi
import argparse


# TODO
def return_corresponding_pts(img_C: np.ndarray, img_R: np.ndarray) -> [np.ndarray, np.ndarray]:
    # will likely use find_roi here to find a region of interest that makes comparison between rendered and captured
    # image easier
    pass

def rescaleAndMakeU8(array: np.ndarray, ret_min=0, ret_max=255):
    ret = array.copy()
    return ((ret_max - ret_min) * (ret - np.min(ret)) / (np.max(ret) - np.min(ret)) + ret_min).astype(np.uint8)


if __name__ == "__main__":
    # # prototyping for return_corresponding_pts() is below:
    # 
    img1 = cv2.imread("../data/001_C.jpg")
    img2 = cv2.imread("../data/001_R.png")
    # 
    # # make images grayscale
    # if len(cam_img.shape) == 3:
    #     cam_img = cv2.cvtColor(cam_img, cv2.COLOR_BGR2GRAY)
    # if len(renderer_img.shape) == 3:
    #     renderer_img = cv2.cvtColor(renderer_img, cv2.COLOR_BGR2GRAY)
    # 
    # cam_img = cam_img.astype(np.float32)
    # renderer_img = renderer_img.astype(np.float32)
    # 
    # cam_img -= 1 / np.mean(cam_img)
    # cam_img *= 1 / np.std(cam_img)
    # cam_img = rescaleAndMakeU8(cam_img)
    # renderer_img -= 1 / np.mean(renderer_img)
    # renderer_img *= 1 / np.std(renderer_img)
    # renderer_img = rescaleAndMakeU8(renderer_img)
    # 
    # # Initiate ORB detector
    # orb = cv2.ORB_create()
    # # find the keypoints and descriptors with ORB
    # kp1, des1 = orb.detectAndCompute(cam_img, None)
    # kp2, des2 = orb.detectAndCompute(renderer_img, None)
    # 
    # # BFMatcher with default params
    # bf = cv2.BFMatcher()
    # matches = bf.knnMatch(des1, des2, k=2)
    # 
    # # Apply ratio test
    # good = []
    # for m, n in matches:
    #     if m.distance < 0.75 * n.distance:
    #         good.append([m])
    # 
    # # cv2.drawMatchesKnn expects list of lists as matches.
    # img3 = cv2.drawMatchesKnn(cam_img, kp1, renderer_img, kp2, good, None, cv2.DrawMatchesFlags_DRAW_RICH_KEYPOINTS)
    # plt.figure(dpi=400)
    # plt.imshow(img3)
    # plt.show()

    # parser = argparse.ArgumentParser(description='Code for Feature Matching with FLANN tutorial.')
    # parser.add_argument('--input1', help='Path to input image 1.', default='box.png')
    # parser.add_argument('--input2', help='Path to input image 2.', default='box_in_scene.png')
    # args = parser.parse_args()
    # img1 = cv2.imread(cv2.samples.findFile(args.input1), cv2.IMREAD_GRAYSCALE)
    # img2 = cv2.imread(cv2.samples.findFile(args.input2), cv2.IMREAD_GRAYSCALE)
    if img1 is None or img2 is None:
        print('Could not open or find the images!')
        exit(0)
    # -- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
    minHessian = 400
    detector = cv2.xfeatures2d_SURF.create(hessianThreshold=minHessian)
    keypoints1, descriptors1 = detector.detectAndCompute(img1, None)
    keypoints2, descriptors2 = detector.detectAndCompute(img2, None)
    # -- Step 2: Matching descriptor vectors with a FLANN based matcher
    # Since SURF is a floating-point descriptor NORM_L2 is used
    matcher = cv2.DescriptorMatcher_create(cv2.DescriptorMatcher_FLANNBASED)
    knn_matches = matcher.knnMatch(descriptors1, descriptors2, 2)
    # -- Filter matches using the Lowe's ratio test
    ratio_thresh = 0.7
    good_matches = []
    for m, n in knn_matches:
        if m.distance < ratio_thresh * n.distance:
            good_matches.append(m)
    # -- Draw matches
    img_matches = np.empty((max(img1.shape[0], img2.shape[0]), img1.shape[1] + img2.shape[1], 3), dtype=np.uint8)
    cv2.drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches,
                   flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
    # -- Show detected matches
    cv2.cvNamedWindow('Good Matches', cv2.WINDOW_NORMAL);
    cv2.imshow('Good Matches', img_matches)
    cv2.waitKey()
