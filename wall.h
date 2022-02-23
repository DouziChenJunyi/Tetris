#ifndef WALL_H
#define WALL_H

#include<QPainter>
#include<QWidget>

class Wall : public QWidget
{
public:
    Wall();
    Wall(int wallPixelNum, int pixelWid, int board_rowNum, int board_colNum);
    int wallPixelNum;
    int pixelWid;
    int board_rowNum, board_colNum;
};

#endif // WALL_H
