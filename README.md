# CUDA-and-Computer-Vision

# 基于小波域局部高斯模型的图像复原
## GaussianBlur.cpp 
    通过高斯滤波（模糊）生成实验用的降析图像，其中源图像是512*512的Lena图像，高斯卷积核的σ(x)=σ(y)=1.0

## preprocessing.cpp
    图像预处理。通过σ(x)=σ(y)=1.0的高斯卷积核处理源图像，然后添加高斯白噪声。得到的降析图像即为最终要复原的图像。

## OpenCV.props
    基于OpenCV-3.4.0、VS2015和X64的项目属性表

## Haar.h
    基于N=2的哈尔小波基的小波变换函数