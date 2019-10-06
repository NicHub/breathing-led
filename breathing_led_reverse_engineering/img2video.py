#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""

http://tsaith.github.io/combine-images-into-a-video-with-python-3-and-opencv-3.html

MacOS
python img2video.py -e png -d "./out/" -o out.mp4

"""

import time
import cv2
import argparse
import os

# %%
TIC = time.time()

# %%
# Construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument(
    "-e",
    "--extension",
    required=False,
    default='jpg',
    help="extension name. default is 'jpg'.")
ap.add_argument(
    "-d",
    "--dir",
    required=True,
    help="Directory containing images")
ap.add_argument(
    "-o",
    "--output",
    required=False,
    default='output.mp4',
    help="output video file")
args = vars(ap.parse_args())

# %%
# Arguments
dir_path = args['dir']
ext = args['extension']
output = args['output']

images = []
for f in os.listdir(dir_path):
    if f.endswith(ext):
        images.append(f)

# %%
# Determine the width and height from the first image
image_path = os.path.join(dir_path, images[0])
frame = cv2.imread(image_path)
cv2.imshow('video', frame)
height, width, channels = frame.shape

# %%
# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'mp4v')  # Be sure to use lower case
out = cv2.VideoWriter(output, fourcc, 20.0, (width, height))

for image in images:

    image_path = os.path.join(dir_path, image)
    frame = cv2.imread(image_path)

    out.write(frame)  # Write out frame to video

    cv2.imshow('video', frame)
    if (cv2.waitKey(1) & 0xFF) == ord('q'):  # Hit `q` to exit
        break

# %%
# Release everything if job is finished
out.release()
cv2.destroyAllWindows()

print("The output video is {}".format(output))

# %%
print("\n######\n# Temps écoulé : %0.2f s\n###\n" % (time.time() - TIC))
