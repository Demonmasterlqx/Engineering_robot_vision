
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <opencv2/imgproc.hpp>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <bits/stdc++.h>

typedef std::vector<std::vector<cv::Point>> Counters;
typedef std::vector<cv::Point> Counter;

//定义颜色
const cv::Scalar blue=cv::Scalar(255,0,0);


cv::Mat preprocessImage(const cv::Mat & image);
// cv::Mat preprocessImage_debug(const cv::Mat & image);
cv::Mat get_threshold_val(const cv::Mat & image);


// char image_dir[]="../Picture/mine_standard.png";
// char image_dir[]="../Picture/mine1.png";
// char image_dir[]="../Picture/mine2.png";
char image_dir[]="../Picture/mine3.png";

// cv::Mat preprocessImage(const cv::Mat & image){
//     cv::Mat imgae_gray,image_binary;
//     cv::cvtColor(image,imgae_gray,cv::COLOR_RGB2GRAY);
//     //得到灰化的图片
//     double minval,maxval;
//     cv::minMaxLoc(imgae_gray,&minval,&maxval);
//     double thresholdval=(maxval-minval)*0.27+minval;
//     //动态得到阈值
//     //这里的阈值先挖一个坑,没有找到合适的方法来确定
//     cv::threshold(imgae_gray,image_binary,thresholdval,300,cv::THRESH_BINARY_INV);
//     //得到二值化图片
//     return image_binary;
// }

//得到动态阈值的值
cv::Mat get_threshold_val(const cv::Mat & image){
    cv::Mat imgae_gray,image_binary;
    cv::cvtColor(image,imgae_gray,cv::COLOR_RGB2GRAY);

    int track_val=0;
    cv::namedWindow("trackw");
    //这里会有个bug value的值必须为nullptr
    cv::createTrackbar("track","rtrackw",nullptr,100);
    //得到灰化的图片
    while(1){
        double minval,maxval;
        cv::minMaxLoc(imgae_gray,&minval,&maxval);
        double thresholdval=(maxval-minval)*cv::getTrackbarPos("track","trackw")/100.0+minval;
        //动态得到阈值
        cv::threshold(imgae_gray,image_binary,thresholdval,300,cv::THRESH_BINARY_INV);
        cv::imshow("111",image_binary);
        cv::waitKey(10);
    }
    return image_binary;
    //得到二值化图片
}

/*
1. 将图像平滑处理
    可以用均值滤波，方框滤波，高斯滤波，中值滤波，双边滤波，以及自定义2D卷积
    具体使用哪一种还不太清楚，卷积核的大小也不确定，先写着吧
2. 查找轮廓 canny
3. 得到灰度图
*/
cv::Mat preprocessImage(const cv::Mat & image){
    cv::Mat image_count,image_median,image_gray,image_canny;
    Counters counters;

    //灰度图
    cv::cvtColor(image,image_gray,cv::COLOR_BGR2GRAY);

    //中值滤波
    cv::medianBlur(image_gray,image_median,5);
    
    //找边缘
    cv::Canny(image_median,image_canny,60,150,3);

    // cv::cvtColor(image,image_gray,cv::COLOR_RGB2GRAY);
    cv::imshow("1",image_gray);
    cv::imshow("2",image_median);
    cv::imshow("3",image_canny);
    cv::waitKey(0);
    return image_count;
}

int main(){
    cv::Mat originFrame=cv::imread(image_dir);
    cv::Mat binaryFrame=preprocessImage(originFrame);
}