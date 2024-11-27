
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

#include "detector.hpp"

int main(){
    std::fstream in;
    in.open("../in");
    char *dir;
    in>>dir;
    auto image=cv::imread(dir);
    process_image_front(image);
}