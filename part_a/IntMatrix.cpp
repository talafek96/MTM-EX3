#include "IntMatrix.h"
using namespace mtm;

IntMatrix::IntMatrix(Dimensions dim, int init_number) :
dimensions(dim)
{
    elements = new int[dim.getRow() * dim.getCol()];
};

IntMatrix::~IntMatrix()
{
    delete[] elements;
}

int IntMatrix::width() const
{
    return this->dimensions.getCol();
}

IntMatrix IntMatrix::transpose()
{
    Dimensions transpose_dim(this->width(), this->height());
    IntMatrix transpose(transpose_dim);
    for(int i = 0; i < this->height(); i++)
    {
        for(int j = 0; j < this->width(); j++)
        {
            transpose(j, i) = (*this)(i, j);
        }
    }
    return transpose;
}

IntMatrix::iterator IntMatrix::end()
{
    IntMatrix::iterator new_it(this, this->size() - 1);
    return new_it;
}

IntMatrix::const_iterator IntMatrix::end() const
{ 
    IntMatrix::const_iterator new_it(this, this->size() - 1);
    return new_it;
}