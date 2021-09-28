# ClayEngine

A 3D Rendering Engine for Real-time Visualization of Complex Geometry and Robotic Perception Maps.


![](Images/PointCloud_MapSense.png) 


## Installation

### Build from Source
Clone the repository, build the code and install at `/usr/local/include`.
```
git clone https://github.com/BhavyanshM/ClayEngine.git
cd ClayEngine
mkdir build
cd build
cmake ..
sudo make install (requires privileged access)
```

## Usage
### Cmake
Link `ClayEngine` as a static library into your CMake project. Use `src/ClayEditor/EditorLayer.cpp` as a guide to use the engine in your application.

## Development
Developed by Bhavyansh Mishra