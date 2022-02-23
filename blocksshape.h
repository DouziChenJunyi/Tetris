#ifndef BLOCKSSHAPE_H
#define BLOCKSSHAPE_H

#include "blocksquare.h"

class blockSShape : public blockSquare
{
public:
    blockSShape();
    blockSShape(int board_rowNum, int board_colNum);
    void initialize() override;
};
#endif // BLOCKSSHAPE_H
