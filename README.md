# Face Detection Project: Start from Capstone Hello World Repo

This project starts from the starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

https://user-images.githubusercontent.com/13211302/147681313-c0a0f6c8-4dee-4f10-81e0-9f2fc705e009.mov

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

## Rubrics
1. Loop, Function, I/O:
   - user input and process input: [user input](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/FaceDetection.cpp#L17), [process input](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/FaceDetection.cpp#L35)
   - read data from file: [read data](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/Detector.h#L36)
2. Object Oriented Programming: 
   - [constructor with initialization](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/Pedestrian.h#L10)
   - [inheritance](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/Pedestrian.h#L7)
   - [encapsulate](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/Detector.h)
3. Memory Management:
   - [reference in function declaraion](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/FaceDetection.cpp#L128)
   - [smart pointer](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/Pedestrian.cpp#L24)
4. Concurrency:
   - [thread](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/FaceDetection.cpp#L135)
   - [mutex or lock](https://github.com/timho102003/FaceDetection/blob/9a56259624709324d759168102e47262f6941a9e/src/FaceDetection.cpp#L135) 
