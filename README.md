# RayTracer
A RayTracer, written in C++ with Phong Shading and Physical Based Rendering Support
## Table of Contents
+ [Cloning](#Cloning)
+ [Setup](#Setup)
+ [Examples](#Examples)
    + [Phong](#Phong)
    + [PBR](#PBR)

## <a name="Cloning"></a> Cloning
This repository contains an additional Windows Library WxWidgets which have to build separatly

```
git clone https://github.com/dekorlp/RayTracer.git
```

To Build the additional Windows Library WxWidgets, follow these steps:

1: Run RayTracer\lib\loadLibraries.bat

2: Open RayTracer\lib\wxWidgets/build/msw/wx_vc12.sln

3: Compile solution for both Release and Debug (x68 and x64)

## <a name="Setup"></a> Setup
1: Change to folder RayTracer\build\premake

2: Execute: premake5 vs2015 in the terminal

3: Change to folder RayTracer\TaytracingPull\RayTracer\build\solutions\vs2015

4: Open Solution with MS Visual Studio: RayTracerProject.sln

5: Change in config.h between Phong Shading and PBR Shading (optional: default is Phong Shading)

6: Run and Build

## <a name="Examples"></a> Examples
### <a name="Phong"></a> Phong 
![Phong](https://github.com/dekorlp/RayTracer/blob/master/images/raytracingPhong_demo.png)

### <a name="PBR"></a> PBR 
![PBR](https://github.com/dekorlp/RayTracer/blob/master/images/raytracingPBR_demo.png)
