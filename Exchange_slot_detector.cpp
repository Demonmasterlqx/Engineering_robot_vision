#include "detector.hpp"

/*
由于没有相机，所以没有对于画面的畸变矫正

这里完成了通道分离，二值化

注意坑在于 split mixChannels merge 函数
*/
cv::Mat preprocess_image_exchange(const cv::Mat& image){
    Splited_images channels;
    Mat image_binary;
    //通道顺序为 BGR
    cv::split(image,channels);
    Mat image_BR(channels[0].size(),channels[0].type());

    const vector<int> from_to={
        0,0,
        1,0
    };

    cv::mixChannels(vector<cv::Mat>{channels[0],channels[2]},vector<cv::Mat>{image_BR},from_to);

    cv::threshold(image_BR,image_binary,100,200,cv::THRESH_BINARY);

    std::cout<<image_BR.channels()<<std::endl;

    cv::namedWindow("1");
    cv::namedWindow("2");
    cv::namedWindow("3");
    cv::imshow("1",image);
    cv::imshow("2",image_BR);
    cv::imshow("3",image_binary);
    cv::waitKey(0);
    return image_binary;
}

Triangle_arrow find_triangle_arrow(const Mat& image_pre,const Mat& image){
    Counters counter_triangle_1,counter_triangle_2;
    cv::findContours(image_pre,counter_triangle_1,cv::RETR_LIST,cv::CHAIN_APPROX_SIMPLE);
    // cv::drawContours(image,counter_triangle,-1,blue,4);
    // cv::imshow("4",image);
    // cv::waitKey(0);
    // cv::cornerHarris
    for(auto counter : counter_triangle_1){
        cv::RotatedRect rect=cv::minAreaRect(counter);
    }

    return Triangle_arrow();
}

int get_counter_size(const Counter & counter,const int & rows,const int & cols){
    int pixel_num=0;
    for(int i=0;i<rows;i++) for(int e=0;e<cols;e++){
        if(cv::pointPolygonTest(counter,cv::Point2f(i,e),0)>=0) pixel_num++;
    }
    return pixel_num;
}

bool find_front_exchange_slot(const Mat& image_pre,Mat& image){
    Counters counter_1,counter_2;
    vector<int> counter_size;
    cv::findContours(image_pre,counter_1,cv::RETR_LIST,cv::CHAIN_APPROX_SIMPLE);
    
    Counter result;
    cv::RotatedRect rect;
    cv::Size siz;
    for(const Counter &counter : counter_1){
        //这里的epsilon的值是没有确定的，要看之后怎么调；
        cv::approxPolyDP(counter,result,10,1);
        rect=cv::minAreaRect(counter);
        siz=rect.size;
        int pixel_num=get_counter_size(counter,image.rows,image.cols);
        //参数全部等待确定，和相机与工作距离有关
        bool height_to_width=(siz.height/siz.width<4.5 && siz.width/siz.height<4.5);
        bool siz_counter=(pixel_num>400 && pixel_num<12000);
        bool approxPolyDP_counters=(result.size()>5 && result.size()<9);
        if(height_to_width&&siz_counter&&approxPolyDP_counters) counter_2.push_back(counter),counter_size.push_back(pixel_num);
    }
    sort(counter_size.begin(),counter_size.end());
    if(counter_2.size()!=4||(counter_size[0]*10<=counter_size[3])) return 0;
    //找到了四个角

    cv::drawContours(image,counter_2,-1,blue,5);
    cv::imshow("1",image);
    cv::waitKey(0);
    return 1;
}

void process_image_exchange_slot(cv::Mat &image){
    cv::Mat image_binary=preprocess_image_exchange(image);
    find_triangle_arrow(image_binary,image);
}

void process_image_front(cv::Mat& image){
    cv::Mat image_binary=preprocess_image_exchange(image);
    find_front_exchange_slot(image_binary,image);
}