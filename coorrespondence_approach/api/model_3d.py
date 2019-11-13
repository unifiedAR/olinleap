import numpy as np


class Model_3D:
    # TODO
    def __init__(self, model_file_path, estimated_pose):
        self.estimated_pose = estimated_pose
        self.model_file_path = model_file_path
        pass

    # TODO
    def return_model_xyz_pts(self, img_R_pts: np.ndarray) -> np.ndarray:
        pass

    # TODO
    def render(self) -> np.ndarray:
        # uses self.estimated_pose
        pass

    def set_estimated_pose(self, estimated_pose: np.ndarray):
        self.estimated_pose = estimated_pose