#include "IntMatrix.h"

namespace mtm
{
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

    IntMatrix::IntMatrix(const IntMatrix& matrix) :
    dimensions(matrix.height(),matrix.width())
    {
        elements = new int[matrix.size()];
        for (int i=0; i<matrix.size(); i++)
        {
            elements[i] = (matrix.elements)[i];
        }
    }

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

    int IntMatrix::height() const 
    {
        return dimensions.getRow();
    }
    
    int IntMatrix::size() const 
    {
        return (size() * width());
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
    IntMatrix IntMatrix::Identity(int dim)
    {
        Dimensions dimension(dim, dim);
        IntMatrix I(dimension, 0);
        for(int i = 0; i < dim; i++)
        {
            I(i, i) = 1;
        }
        return I;
    }
    bool any(const IntMatrix& matrix)
    {
        for(const int& val : matrix)
        {
            if (val != 0)
            {
                return true;
            }
        }
        return false;
    }

    bool all(const IntMatrix& matrix)
    {
        for(const int& val : matrix)
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

    IntMatrix IntMatrix::operator-() const
    {
        IntMatrix negative = *this;
        for(int& val : negative)
        {
            val = -val;
        }
        return negative;
    }

    int& IntMatrix::operator()(int row, int col)
    {
        return *(elements + row * IntMatrix::width() + col);
    }

    const int& IntMatrix::operator()(int row, int col) const
    {
        return (*this)(row, col);
    }

    IntMatrix operator-(const IntMatrix& matrix1, const IntMatrix& matrix2)
    {
        return matrix1 + (-matrix2);
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

    std::ostream& operator<<(std::ostream& out, const IntMatrix& matrix)
    {
        out << printMatrix(matrix.elements, matrix.dimensions);
        return out;
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
}