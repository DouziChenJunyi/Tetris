#include "wall.h"
#include<QDebug>
Wall::Wall()
{

}


Wall::Wall(int wallPixelNum, int pixelWid, int board_rowNum, int board_colNum)
{
    this->wallPixelNum = wallPixelNum;
    this->pixelWid = pixelWid;
    this->board_rowNum = board_rowNum;
    this->board_colNum = board_colNum;
}

