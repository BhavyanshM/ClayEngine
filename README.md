

![](Images/ClayLogo.jpeg)

Clay is a C++ 3D Rendering Engine for Robotics and Computer Vision. It supports structures such as Point Clouds, Meshes, Polynomial Surfaces, Implicit
Surfaces, and arbitrary Two-Dimensional Manifolds.

[comment]: <> (![alt text]&#40;Images/Bunny.gif&#41; ![alt text]&#40;Images/Cylinder.gif&#41; ![alt text]&#40;Images/Surface.gif&#41;)


<p float="left">
    <img src="https://github.com/BhavyanshM/ClayEngine/blob/master/Images/Bunny.gif" width="250" height="250" />
    <img src="https://github.com/BhavyanshM/ClayEngine/blob/master/Images/Cylinder.gif" width="250" height="250" />
    <img src="https://github.com/BhavyanshM/ClayEngine/blob/master/Images/Surface.gif" width="250" height="250" />
    <img src="https://github.com/BhavyanshM/ClayEngine/blob/master/Images/Cup.gif" width="250" height="250" />
    <img src="https://github.com/BhavyanshM/ClayEngine/blob/master/Images/Manifold.gif" width="250" height="250" />
</p>



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

To initialize the submodules:
```
git submodule update --init --recursive
```

## Usage
### Cmake
Link `ClayEngine` as a static library into your CMake project. Use `src/ClayEditor/EditorLayer.cpp` as a guide to use the engine in your application.

Add the CMake arg `-DBUILD_LOCAL=true` to set the asset paths correctly for running locally.

## Development
Developed by Bhavyansh Mishra