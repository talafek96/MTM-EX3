#include "IntMatrix.h"
using namespace mtm;

/*****************************************/
/*   Ctor/Dtor implementation section    */
/*****************************************/
IntMatrix::IntMatrix(Dimensions dim, int init_number) :
dimensions(dim)
{
    elements = new int[dim.getRow() * dim.getCol()];
    for (int i=0 ; i<(dim.getRow() * dim.getCol()); i++) 
    {
        elements[i] = init_number;
    }
};

IntMatrix::~IntMatrix()
{
    delete[] elements;
}
/*****************************************/
/*    Methods implementation section     */
/*****************************************/
int IntMatrix::width() const
{
    return this->dimensions.getCol();
}

IntMatrix IntMatrix::transpose()
{
    Dimensions transpose_dim(width(), height());
    IntMatrix transpose(transpose_dim);
    for(int i = 0; i < height(); i++)
    {
        for(int j = 0; j < width(); j++)
        {
            transpose(j, i) = (*this)(i, j);
        }
    }
    return transpose;
}

/*****************************************/
/*   Functions implementation section    */
/*****************************************/
bool all(const IntMatrix& matrix)
{
    for(const int val : matrix)
    {
        if (val == 0)
        {
            return false;
        }
    }
    return true;
}
/*****************************************/
/*   Operators implementation section    */
/*****************************************/
IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2)
{
    Dimensions new_dim(matrix1.height(), matrix1.width());
    IntMatrix result_matrix(new_dim);
    for(int row = 0; row < matrix1.height(); row++)
    {
        for(int col = 0; col<matrix1.width(); col++)
        {
            result_matrix(row, col) = matrix1(row, col) + matrix2(row, col);
        }
    }
    return result_matrix;
}

IntMatrix& IntMatrix::operator+=(int number)
{
    for (IntMatrix::iterator it = begin(); it != end(); it++)
    {
        *it += number;
    }
    return *this;
}

IntMatrix operator+(const IntMatrix& matrix, int number)
{
    IntMatrix result_matrix = matrix;
    result_matrix += number;
    return(result_matrix);
}

IntMatrix operator+(int number, const IntMatrix& matrix)
{
    IntMatrix result_matrix = matrix; 
    result_matrix += number;
    return result_matrix;
}

/*****************************************/
/*   Iterators implementation section    */
/*****************************************/
IntMatrix::iterator IntMatrix::begin() 
{
    IntMatrix::iterator it(this, 0);
    return it;
}

IntMatrix::const_iterator IntMatrix::begin() const
{
    IntMatrix::const_iterator it(this, 0);
    return it;
}

IntMatrix::iterator IntMatrix::end()
{
    IntMatrix::iterator it(this, size() - 1);
    return it;
}

IntMatrix::const_iterator IntMatrix::end() const
{ 
    IntMatrix::const_iterator it(this, size() - 1);
    return it;
}

IntMatrix& IntMatrix::operator=(const IntMatrix& target_matrix)
{
    if (this == &target_matrix)
    {
        return *this;
    }
    dimensions = target_matrix.dimensions;
    delete[] elements;
    elements = new int[target_matrix.size()];
    for (int i = 0; i < target_matrix.size(); i++)
    {
        elements[i] = target_matrix.elements[i];
    }
    return *this;
}