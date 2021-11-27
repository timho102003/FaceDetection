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
        void setBoundingBox(double x1, double y1, double x2, double y2);
        void getBoundingBox(double &x1, double &y1, double &x2, double &y2);

    protected:
        ObjectType _type;                 
        int _id;                          
        double _posX1, _posY1, _posX2, _posY2;  // Bounding Box
        std::vector<std::thread> threads;
        static std::mutex _mtx;           
    private:
        static int _idCnt;
};

#endif // MOVEOBJECT_H