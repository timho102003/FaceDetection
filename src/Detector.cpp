#include "Detector.h"
#include <algorithm>

void Detector::forward(cv::Mat input){
    cv::Mat faces;
    model->detect(input, faces);
    for (int i = 0; i < faces.rows; i++){
        auto current = faces.rowRange(i, i+1);
        Pedestrian p(current);
        _pedestrian.emplace_back(p);
    }
}
void Detector::simulate(std::shared_ptr<cv::Mat> &frame){
    for (auto it = _pedestrian.begin(); it != _pedestrian.end(); it++)
    {
        it->simulate(frame);
        _pedestrian.erase(it--);
    }
}