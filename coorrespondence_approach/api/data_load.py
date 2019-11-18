import numpy as np
import os
import cv2

IMG_TYPES = (".png", ".jpg")
CAMERA_IMG_SUFFIX = "_C"
DATA_DIR = "data"

class UnableToLoadImg(Exception):
    pass

def load_camera_img(id: str, parent_of_data_dir: str) -> np.ndarray:
    for img_type in IMG_TYPES:
        img_C = cv2.imread(os.path.join(parent_of_data_dir, DATA_DIR, id) + "_C" + img_type)
        if img_C is not None:
            break

    if img_C is None:
        print("Unable to load: " + os.path.join(parent_of_data_dir, DATA_DIR, id) + "_C" + "{.jpg or .png}")
        raise UnableToLoadImg()

    return img_C