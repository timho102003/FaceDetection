#include "MoveObject.h"
#include <algorithm>
#include <iostream>

int MoveObject::_idCnt = 0;
// std::mutex MoveObject::_mtx;

MoveObject::MoveObject()
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}

void MoveObject::setBoundingBox(cv::Mat bboxs){
    cv::Point2f _top_left = cv::Point2f(bboxs.at<float>(0, 0), bboxs.at<float>(0, 1));
    cv::Point2f _buttom_right = cv::Point2f(bboxs.at<float>(0, 2), bboxs.at<float>(0, 3));
}

void MoveObject::getBoundingBox(cv::Point2f &top_left, cv::Point2f &buttom_right){
    top_left = _top_left;
    buttom_right = _buttom_right;
}