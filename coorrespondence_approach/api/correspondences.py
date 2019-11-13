import cv2  # make sure opencv-contrib-python is also installed
import numpy as np
import matplotlib.pyplot as plt
from api.find_roi import find_roi


# TODO
def return_corresponding_pts(img_C: np.ndarray, img_R: np.ndarray) -> [np.ndarray, np.ndarray]:
    # will likely use find_roi here to find a region of interest that makes comparison between rendered and captured
    # image easier
    pass


if __name__ == "__main__":
    # prototyping for return_corresponding_pts() is below:

    cam_img = cv2.imread("../data/001_C.jpg")
    renderer_img = cv2.imread("../data/001_R.png")

    # make images grayscale
    if len(cam_img.shape) == 3:
        cam_img = cv2.cvtColor(cam_img, cv2.COLOR_BGR2GRAY)
    if len(renderer_img.shape) == 3:
        renderer_img = cv2.cvtColor(renderer_img, cv2.COLOR_BGR2GRAY)

    cam_img = cam_img.astype(np.float32)
    renderer_img = renderer_img.astype(np.float32)

    cam_img -= 1 / np.mean(cam_img)
    cam_img *= 1 / np.std(cam_img)

    renderer_img -= 1 / np.mean(renderer_img)
    renderer_img *= 1 / np.std(renderer_img)

    # Initiate ORB detector
    orb = cv2.ORB_create()
    # find the keypoints and descriptors with ORB
    kp1, des1 = orb.detectAndCompute(cam_img, None)
    kp2, des2 = orb.detectAndCompute(renderer_img, None)

    # BFMatcher with default params
    bf = cv2.BFMatcher()
    matches = bf.knnMatch(des1, des2, k=2)

    # Apply ratio test
    good = []
    for m, n in matches:
        if m.distance < 0.75 * n.distance:
            good.append([m])

    # cv2.drawMatchesKnn expects list of lists as matches.
    img3 = cv2.drawMatchesKnn(cam_img, kp1, renderer_img, kp2, good, None,
                              flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
    plt.figure(dpi=400)
    plt.imshow(img3)
    plt.show()
