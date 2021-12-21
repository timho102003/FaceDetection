#ifndef DETECTOR_H
#define DETECTOR_H

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include "Pedestrian.h"

using namespace std;

class Detector
{
public:
    Detector() {}
    ~Detector() {}
    cv::Ptr<cv::FaceDetectorYN> model;
    void setConfig(cv::String model_path, string config, cv::Size input_size, float score_thresh, float nms_thresh, int topK, int backend_id, int target_id)
    {
        _model_path = model_path;
        _config = config;
        _in_size = input_size;
        _score_threshold = score_thresh;
        _nms_threshold = nms_thresh;
        _top_k = topK;
        _backend_id = backend_id;
        _target_id = target_id;
    }
    void build()
    {
        model = cv::FaceDetectorYN::create(
            _model_path,
            _config,
            _in_size,
            _score_threshold,
            _nms_threshold,
            _top_k,
            _backend_id,
            _target_id);
    }
    void forward(cv::Mat input);
    void simulate(std::shared_ptr<cv::Mat> &frame);

private:
    cv::String _model_path;
    cv::String _config;
    cv::Size _in_size;
    float _score_threshold;
    float _nms_threshold;
    int _top_k;
    int _backend_id;
    int _target_id;
    std::vector<Pedestrian> _pedestrian;
};
#endif // DETECTOR_H