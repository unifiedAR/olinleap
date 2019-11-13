import cv2
import os
from api.correspondences import return_corresponding_pts
from api.data_load import load_camera_img
from api.model_3d import Model_3D
from api.pnp import estimate_pose
from api.error import calculate_error
from api.ml_model import predict_model_pose

MODEL_FILE_PATH = "data/model.stl"  # placeholder
THRESHOLD = 0.1  # arbitrary placeholder value
MAX_ITER = 100

if __name__ == "__main__":
    img_C = load_camera_img("001", os.getcwd())
    estimated_pose = predict_model_pose(img_C)

    model = Model_3D(MODEL_FILE_PATH, estimated_pose)

    error = 1000  # arbitrarily large initial value
    iter = 0
    while True:
        img_R = model.render()
        img_C_pts, img_R_pts = return_corresponding_pts(img_C, img_R)
        error = calculate_error(img_C, img_R, img_C_pts, img_R_pts)
        if error < THRESHOLD or iter == MAX_ITER:
            break
        model_xyz_points = model.return_model_xyz_pts(img_R_pts)
        estimated_pose = estimate_pose(img_C_pts, model_xyz_points)
        model.set_estimated_pose(estimated_pose)

        iter += 1

    cv2.imshow("Model aligned on world!", img_R)

