#include "Pedestrian.h"

Pedestrian::Pedestrian(cv::Mat data)
{
    _type = ObjectType::objPedestrian;
    auto bbox = data.colRange(0, 4);
    setBoundingBox(bbox);
    auto lm = data.colRange(4, num_lm_pt);
    setLandMark(lm);
}

void Pedestrian::setLandMark(cv::Mat landmarks)
{
    for (int j = 0; j < num_lm_pt; j += 2)
    {
        _landmark.emplace_back(cv::Point2f(landmarks.at<float>(0, j), landmarks.at<float>(0, j + 1)));
    }
}
void Pedestrian::getLandMark(std::vector<cv::Point2f> &landmarks)
{
    landmarks = _landmark;
}

void Pedestrian::draw(std::shared_ptr<cv::Mat> &frame){
    for (cv::Point2f &pts: this->_landmark){
        cv::circle(*frame, pts,  2, cv::Scalar(255, 0, 0), pt_thickness);
    }
}

void Pedestrian::simulate(std::shared_ptr<cv::Mat> &frame){
    draw(frame);
}