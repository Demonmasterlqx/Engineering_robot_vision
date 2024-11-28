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

#ifndef __EXCHANGE__SLOT__DETECTOR__
#define __EXCHANGE__SLOT__DETECTOR__

class Triangle_arrow;
struct Circle;

using cv::Mat;
using std::cout;
using std::endl;
using std::vector;
typedef std::vector<std::vector<cv::Point>> Counters;
typedef std::vector<cv::Point> Counter;
typedef std::vector<cv::Mat> Splited_images;
typedef vector<Circle> Circles;

const float eps=1e-9;

//奇怪的问题，为啥把这个定义放在后面会报重载出问题，而不是这个类没有定义？
class Triangle_arrow:Mat{
};
class Front_exchange_slot:Mat{
    public:

    private:

};
struct Circle{
    cv::Point2f center;
    float radius;
    Circle(){}
    Circle(const cv::Point2f & po,float ra):center(po),radius(ra){}
};

//定义颜色
const cv::Scalar blue=cv::Scalar(255,0,0);
const cv::Scalar green=cv::Scalar(0,255,0);


cv::Mat preprocess_image_exchange(const cv::Mat& image);
Triangle_arrow find_triangle_arrow(const Mat& image_pre,const Mat& image);
bool find_front_exchange_slot(const Mat& image_pre,const Mat& image);
// void process_image_front();
// void process_image_exchange_slot();
void process_image_exchange_slot(cv::Mat &image);
void process_image_front(cv::Mat& image);
vector<float> get_trangle_angle(const Counter& trangle);
float angleBetweenVectors(const cv::Point2f& v1, const cv::Point2f& v2);
float distanceBetweenPoint(const cv::Point2f& v1, const cv::Point2f& v2);

#endif