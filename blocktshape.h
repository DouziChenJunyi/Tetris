#ifndef BLOCKTSHAPE_H
#define BLOCKTSHAPE_H
#include "blocksquare.h"

class blockTShape : public blockSquare
{
public:
    blockTShape();
    blockTShape(int board_rowNum, int board_colNum);
    void initialize() override;
};

#endif // BLOCKTSHAPE_H
