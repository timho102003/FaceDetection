#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include <thread>
#include <vector>
#include <mutex>
#include <opencv2/opencv.hpp>

enum class ObjectType{
    noObject,
    objPedestrian,
};

class MoveObject{
    public:
        MoveObject();
        ~MoveObject();
        // getter and setter
        int getID() { return _id; }
        ObjectType getType() { return _type; }
        void setBoundingBox(cv::Mat bboxs);
        void getBoundingBox(cv::Point2f &top_left, cv::Point2f &buttom_right);

    protected:
        ObjectType _type;                 
        int _id;                          
        cv::Point2f _top_left; 
        cv::Point2f _buttom_right;  // Bounding Box
        std::vector<std::thread> threads;
        static std::mutex _mtx;           
    private:
        static int _idCnt;
};

#endif // MOVEOBJECT_H