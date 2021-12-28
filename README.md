# Face Detection Project: Start from Capstone Hello World Repo

This project starts from the starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

## Dependencies for Running Locally
* macos: 12.0.1 (apple silicon: m1 pro)
* cmake == 3.22.1
* gnu make == 3.81 (macos)
* gcc/g++ == 11.2.0
* opencv == 4.5.4

## Data:
* checkpoints: yunet.onnx (face detection and landmark predictor)
* example video: data/videos/demo_video.mov

## Basic Build Instructions

1. Clone this repo.
2. Make a lib directory in the top level directory: `mkdir lib`
3. Build opencv: `bash ./make_env.sh`
4. Make a build directory in the top level directory: `mkdir build && cd build`
5. Compile: `cmake .. && make`
6. Run it: `./FaceDetection -m=../data/checkpoints/yunet.onnx -v=../data/videos/demo_video.mov`
7. Press `Q / q` to quit