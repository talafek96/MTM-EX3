#include "IntMatrix.h"
using namespace mtm;
IntMatrix::IntMatrix(Dimensions dim, int init_number) :
dimensions(dim)
{
    elements = new int[dim.getRow() * dim.getCol()];
};