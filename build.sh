sudo rm -rf /usr/local/include/ClayEngine
mkdir build
cd build
cmake ..
make -j32
sudo make install
cd ..
rm -rf build
