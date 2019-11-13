import numpy as np
import os
import cv2

IMG_TYPES = ("png", "jpg")
CAMERA_IMG_SUFFIX = "_C"
DATA_DIR = "data"

class UnableToLoadImg(Exception):
    def __init__(self, filename):
        Exception.__init__(self)
        print("Unable to load {}".format(filename))

def load_camera_img(id: str, parent_of_data_dir: str) -> np.ndarray:
    for img_type in IMG_TYPES:
        img_C = cv2.imread(os.path.join(parent_of_data_dir, DATA_DIR, id) + "_C" + img_type)
        if img_C is not None:
            break

    if img_C is None:
        raise UnableToLoadImg(os.path.join(parent_of_data_dir, id) + "_C" + "{.jpg or .png}")

    return img_C