#include "detector.hpp"

class PnPsolver{
    public:
    PnPsolver(
    const std::vector<double> & camera_matrix,
    const std::vector<double> & distortion_coefficients);
    
    bool solvePnP(const Slot & slot, cv::Mat & rvec, cv::Mat & tvec);

    float calculateDistanceToCenter(const cv::Point2f & image_point);

    private:
    //Unit m
    //the corner of light
    static const float slot_lenght=275/1000.0;
    static const float slot_half_lenght=slot_lenght/2;
    Mat camera_matrix;
    Mat distortion_coefficients;
    vector<cv::Point3f> slot_3d_points;
};

PnPsolver::PnPsolver(const std::vector<double> & in_camera_matrix,const std::vector<double> & in_distortion_coefficients){
    camera_matrix=cv::Mat(1,9,CV_64F,const_cast<double *>(in_camera_matrix.data())).clone();
    distortion_coefficients=cv::Mat(1,5,CV_64F,const_cast<double *>(in_distortion_coefficients.data())).clone();

    // when you in the front of slot, the order is left_up right_up right_down left_down
    // in clockwise order
    // Model coordinate: x forward, y left, z up
    // last one is center of the slot
    slot_3d_points.push_back(cv::Point3f(0,-slot_half_lenght,slot_half_lenght));
    slot_3d_points.push_back(cv::Point3f(0,slot_half_lenght,slot_half_lenght));
    slot_3d_points.push_back(cv::Point3f(0,slot_half_lenght,-slot_half_lenght));
    slot_3d_points.push_back(cv::Point3f(0,-slot_half_lenght,-slot_half_lenght));
    slot_3d_points.push_back(cv::Point3f(0,0,0));
}

bool PnPsolver::solvePnP(const Slot & slot, cv::Mat & rvec, cv::Mat & tvec){
    std::vector<cv::Point2f> image_slot_points;

    for(auto &i : slot.corners) image_slot_points.push_back(i);
    image_slot_points.push_back(slot.center);

    return cv::solvePnP(image_slot_points,slot_3d_points,camera_matrix,distortion_coefficients,rvec,tvec,false,cv::SOLVEPNP_IPPE);
}

