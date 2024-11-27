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
typedef std::vector<cv::Mat> Splited_images;

//定义颜色
const cv::Scalar blue=cv::Scalar(255,0,0);

// char image_dir[]="../Picture/mine_standard.png";
// char image_dir[]="../Picture/mine1.png";
// char image_dir[]="../Picture/mine2.png";
char image_dir[]="../Picture/mine3.png";


cv::Mat preprocess_image_exchange_slot(const cv::Mat& image){
    Splited_images channels;
    cv::split(image,channels);
    
}

void process_image_exchange_slot(){
    cv::Mat image=cv::imread(image_dir);
    
}