#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import os
import numpy as np


def create_output_dir(dir_name):
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)


def crop(image, video_name):
    if video_name in ["breathing_led_001.mp4"]:
        image = crop_video_001(image)
    elif video_name in ["breathing_led_002.mp4"]:
        image = crop_video_002(image)
    return image


def crop_video_001(img):
    x = 872
    w = 50
    y = 432
    h = 4
    crop_img = img[y:y+h, x:x+w]
    return crop_img


def crop_video_002(img):
    offset = 10
    x = 550
    w = 100
    y = 500
    h = 70
    crop_img = img[y:y+h, x:x+w]
    return crop_img


def mean_val_with_masking(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    ret, gray = cv2.threshold(gray, 127, 255, 0)

    print(img.shape)
    mask = np.zeros(gray.shape, np.uint8)
    print(mask.shape)
    # img[:, :, 0] = img[:, :, 0] * mask
    # img[:, :, 1] = img[:, :, 1] * mask
    # img[:, :, 2] = img[:, :, 2] * mask

    contours, hier = cv2.findContours(
        gray, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
    for cnt in contours:
        if 200 < cv2.contourArea(cnt) < 5000:
            cv2.drawContours(img, [cnt], 0, (0, 255, 0), 2)
            cv2.drawContours(mask, [cnt], 0, 255, -1)

    return img


def mean_val(image):
    img_mean = cv2.mean(image)
    blank_image = np.zeros(shape=[500, 1000, 3], dtype=np.uint8)
    blank_image[:, :] = img_mean[0], img_mean[1], img_mean[2]
    gray_img = cv2.cvtColor(blank_image, cv2.COLOR_BGR2GRAY)
    gray_img_mean = cv2.mean(image)
    with open('brightness.csv', 'a+') as file:
        file.write(f"{gray_img_mean[0]:1.0f}, ")
    return gray_img


def extract_image(out_dir, video_name, px_coord):
    vidcap = cv2.VideoCapture(video_name)
    nb_images = 0
    while True:
        success, image = vidcap.read()
        if not success:
            break
        img_name = f"{out_dir}/frame_{nb_images}.png"
        image = crop(image, video_name)
        if video_name in ["breathing_led_001.mp4"]:
            image = mean_val(image)
        if video_name in ["breathing_led_002.mp4"]:
            image = mean_val_with_masking(image)
        if not (video_name in ["breathing_led_002.mp4"] and nb_images < 76):
            if not (video_name in ["breathing_led_002.mp4"] and nb_images > 574):
                cv2.imwrite(img_name, image)
        print(img_name)
        nb_images += 1

    print(f"{nb_images} images saved")


if __name__ == "__main__":
    if os.path.exists("brightness.csv"):
        os.remove("brightness.csv")
    out_dir = "out"
    video_name = "breathing_led_002.mp4"
    create_output_dir(out_dir)
    extract_image(out_dir, video_name, [0, 0])
