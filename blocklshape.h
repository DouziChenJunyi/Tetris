#ifndef BLOCKLSHAPE_H
#define BLOCKLSHAPE_H

#include "blocksquare.h"

class blockLShape : public blockSquare
{
public:
    blockLShape();
    blockLShape(int board_rowNum, int board_colNum);
    void initialize() override;
};

#endif // BLOCKLSHAPE_H
