# RayTracer

## Table of Contents
+ [Cloning](#Cloning)

## <a name="Cloning"></a> Cloning
This repository contains an additional Windows Library WxWidgets which have to build separatly

```
git clone https://github.com/dekorlp/RayTracer.git
```

To Build the additional Windows Library WxWidgets, follow these steps:

1: Run RayTracer\lib\loadLibraries.bat

2: Open RayTracer\lib\wxWidgets/build/msw/wx_vc12.sln

3: Compile solution for both Release and Debug (x68 and x64)

4: Change to folder RayTracer\build\premake

## Phong 
![Phong](https://github.com/dekorlp/RayTracer/blob/master/images/raytracingPhong_demo.png)

## PBR
![PBR](https://github.com/dekorlp/RayTracer/blob/master/images/raytracingPBR_demo.png)

## Project Setup
1: git clone https://github.com/dekorlp/RayTracer.git
2: Run RayTracer\lib\loadLibraries.bat
3: Open RayTracer\lib\wxWidgets/build/msw/wx_vc12.sln
4: Compile solution for both Release and Debug (x68 and x64)
5: Change to folder RayTracer\build\premake
5: Execute: premake5 vs2015 in the terminal
6: Change to folder RayTracer\TaytracingPull\RayTracer\build\solutions\vs2015
7: Open Solution with MS Visual Studio: RayTracerProject.sln
8: Change in config.h between Phong Shading and PBR Shading (optional: default is Phong Shading)
9: Run and Build
