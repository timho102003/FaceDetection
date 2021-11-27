#include "MoveObject.h"
#include <algorithm>
#include <iostream>

int MoveObject::_idCnt = 0;
std::mutex MoveObject::_mtx;

MoveObject::MoveObject()
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}

void MoveObject::setBoundingBox(double x1, double y1, double x2, double y2){
    _posX1 = x1;
    _posY1 = y1;
    _posX2 = x2;
    _posY2 = y2;
}

void MoveObject::getBoundingBox(double &x1, double &y1, double &x2, double &y2){
    x1 = _posX1;
    x2 = _posX2;
    y1 = _posY1;
    y2 = _posY2;
}

MoveObject::~MoveObject()
{
    // set up thread barrier before this object is destroyed
    std::for_each(threads.begin(), threads.end(), [](std::thread &t)
                  { t.join(); });
}
