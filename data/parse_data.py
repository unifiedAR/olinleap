import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def parse(filename):
    f = open(filename, 'r').read()
    f_lines = f.split('\n')
    x = []
    y = []
    z = []
    print(f_lines)
    for l, line in enumerate(f_lines):

        if line.__contains__("C:X="):
            new_line = line.split(':')[2:]
            # print("New line:", new_line)
            try:
                new_line[0] = float(new_line[0][2:])
                new_line[1] = float(new_line[1][2:])
                new_line[2] = float(new_line[2][2:])
            except:
                print("failed with :", new_line)
                continue

            if abs(new_line[0]) < 100 and abs(new_line[1]) < 100 and abs(new_line[2]) < 100:
                x.append(new_line[0])
                y.append(new_line[1])
                z.append(new_line[2])
    return [x, y, z]

if __name__ == "__main__":
    coords = parse("messages.txt")

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # plt.tricontourf(coords[0], coords[1], coords[2])

    ax.scatter(coords[0], coords[1], coords[2])
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()
