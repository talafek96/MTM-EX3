#include "IntMatrix.h"
using namespace mtm;
IntMatrix::IntMatrix(Dimensions dim, int init_number) :  
dimensions(dim)
{
    elements = new int[dim.getRow() * dim.getCol()];
    for (int i=0 ; i<(dim.getRow() * dim.getCol()); i++)    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ You didn't init the vlues, I added it 
    {
        elements[i] = init_number;
    }
};


/*******************/
/* Berko's methods */
/*******************/
IntMatrix::IntMatrix(const IntMatrix& matrix) :
dimensions(matrix.height(),matrix.width())
{
    elements = new int[matrix.size()];
    for (int i=0; i<matrix.size(); i++)
    {
        elements[i] = (matrix.elements)[i];
    }
}

int IntMatrix::height() const 
{
    return dimensions.getRow();
}

int IntMatrix::width() const
{
    return dimensions.getCol();
}

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



/*********************/
/* Berko's operators */
/*********************/
bool operator==(const IntMatrix& matrix1, const IntMatrix& matrix2)
{
    if ((matrix1.height() != matrix2.height()) || (matrix1.width() != matrix2.width()))
    {
        return false;

    }
    for(int row = 0; row < matrix1.height(); row++)
    {
        for(int col = 0; col<matrix1.width(); col++)
        {
            if(matrix1(row, col) != matrix2(row, col))
            {
                return false;
            }
        }
    }
    return true;
}

IntMatrix& IntMatrix::operator=(const IntMatrix& target_matrix)
{
    if (*this == target_matrix)
    {
        return *this;
    }
    dimensions = target_matrix.dimensions;
    delete[] elements;
    elements = new int[target_matrix.size()];
    for (int i=0; i<target_matrix.size(); i++)
    {
        elements[i] = target_matrix.elements[i];
    }
    return *this;
}

IntMatrix& IntMatrix::operator+=(int number)
{
    for (IntMatrix::iterator it = this->begin(); it != this->end(); it++)
    {
        *it += number;
    }
    return *this;
}

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

IntMatrix operator+(const IntMatrix& matrix, int number)
{
    IntMatrix result_matrix = matrix;
    result_matrix += number;
    return(result_matrix);
}

IntMatrix operator+(int number, const IntMatrix& matrix)
{
    IntMatrix result_matrix =matrix; 
    result_matrix += number;
    return (result_matrix);
}


/*********************/
/* Berko's Functions */
/*********************/
bool all(const IntMatrix& matrix)
{
    for (IntMatrix::const_iterator it = matrix.begin(); it != matrix.end(); it++)
    {
        if (*it == 0)
        {
            return false;
        }
    }
    return true;
}