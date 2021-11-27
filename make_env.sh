## Build Opencv 4.5.4
cd lib
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd opencv
git checkout 4.5.4
cd ..
cd opencv_contrib
git checkout 4.5.4
cd ..
mkdir build
cd build
cmake CMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=ON -DOPENCV_GENERATE_PKGCONFIG=ON -DCMAKE_INSTALL_PREFIX=/usr/local/ -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules ../opencv
make 
sudo make install