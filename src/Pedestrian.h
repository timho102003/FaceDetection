#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H
#include <vector>
#include <memory>
#include "MoveObject.h"

class Pedestrian : public MoveObject{
    public:
        // Pedestrian();
        Pedestrian(cv::Mat data);
        ~Pedestrian(){}
        void setLandMark(cv::Mat landmarks);
        void getLandMark(std::vector<cv::Point2f> &landmarks);
        void simulate(std::shared_ptr<cv::Mat> &frame);
        void draw(std::shared_ptr<cv::Mat> &frame);
    private:
        int pt_thickness = 2;
        int num_lm_pt = 10; // 5 landmark (x, y), total 10 points
        std::vector<cv::Point2f> _landmark;
};

#endif // PEDESTRIAN_H