#include"cameraOpen/include/MvCameraControl.h"

#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

#ifndef __GETIMAGE__
#define __GETIMAGE__
using cv::Mat;
using std::cout;
using std::endl;
using std::vector;

static void __stdcall ImageCallBackEx(unsigned char * pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser);
bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo);
void Grabbing();
void VideoGet();

#endif