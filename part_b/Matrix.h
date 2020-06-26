#ifndef MATRIX_INCLUDE
#define MATRIX_INCLUDE
#include <iostream>
#include "Array.h"
#include "Auxiliaries.h"

namespace mtm
{
    class Exception : public std::exception {};

    template<typename T>
    class Matrix
    {
    private:
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Instance variables */

        mtm::Dimensions dimensions;  /* The allocated size of the array   */
        Array<T> elements;           /* A dynamic array of the elements   */

        template<typename FUNCTOR>
        void determineCondition(Matrix<bool>& result, FUNCTOR condition) const
        {
            for(int i = 0; i < height(); i++)
            {
                for(int j = 0; j < width(); j++)
                {
                    if(condition((*this)(i, j)))
                    {
                        result(i, j) = true;
                    }
                }
            }            
        }
    public:
        /*
         * Constructor: Matrix<T>
         * Usage: Matrix<T> matrix(dim, init_value);
         *        Matrix<T> matrix(dim);
         * ---------------------------------------
         * Initializes a new Matrix<T>.  
         * Creates a matrix with the dimension of dim.
         * Each element in the matrix is initialized to init_value.
         * If init_value is missing, the elements are initialized with the
         * default constructor of T.
         * 
         * Possible Exceptions:
         * Matrix::IllegalInitialization, std::bad_alloc
         * 
         * Assumptions on T:
         * • Has an assignment operator. (=)
         * • Has a default/no argument constructor.
         */ 
        explicit Matrix(const mtm::Dimensions dim, const T& init_value = T()) :
        dimensions(dim)
        {
            if(dim.getCol() <= 0 || dim.getRow() <= 0)
            {
                throw IllegalInitialization();
            }
            int size = dim.getCol() * dim.getRow();
            elements = Array<T>(size);
            for(int i = 0; i < size; i++)
            {
                elements[i] = init_value;
            }
        }

        /*
         * Copy Constructor: Matrix<T>
         * Usage: Matrix<T> new_matrix(matrix);
         *        Matrix<T> new_matrix = matrix;
         * ---------------------------------------
         * Initializes a new Matrix.  
         * Creates a new matrix that is a copy of matrix.
         * 
         * Assumptions on T:
         * • Has an assignment operator. (=)
         * • Has a default/no argument constructor.
         * 
         * Possible exceptions:
         * std::bad_aloc if allocation fail.
         */ 
        Matrix(const Matrix<T>& matrix) :
        dimensions(matrix.dimensions) , elements(matrix.elements) { }

                
        /*
         * Destructor: ~Matrix
         * -------------------
         * Frees any heap storage allocated by this matrix.
         * Make this a virtual dtor in case we want to derive from this 
         * class in the future.
         */
        virtual ~Matrix() { }

        /*
         * Method: Diagonal
         * Usage: Matrix<t> diagonal_matrix = Matrix<T>::Diagonal(dim, diagonal_value);
         * -----------------------------------
         * Creates a new Matrix<T> of dimensions (dim x dim) with diagonal_value
         * elements initialized in the diagonal.
         * 
         * Possible Exceptions:
         * Matrix::IllegalInitialization, std::bad_alloc
         * 
         * Assumptions on T:
         * • Has an assignment operator. (=)
         * • Has a default/no argument constructor
         */
        static Matrix Diagonal(int dim, const T& diagonal_value)
        {
            if(dim <= 0)
            {
                throw IllegalInitialization();
            }
            mtm::Dimensions diag_dim(dim, dim);
            Matrix diag(diag_dim);
            for(int i = 0; i < dim; i++)
            {
                diag(i, i) = diagonal_value;
            }
            return diag;
        }

        /*
         * Method: height
         * Usage: int rows = matrix.height();
         * -----------------------------------
         * Returns the number of rows (height) of the matrix.
         */
        int height() const noexcept
        {
            return dimensions.getRow();
        }

        /*
         * Method: width
         * Usage: int columns = matrix.width();
         * -----------------------------------
         * Returns the number of columns (width) of the matrix.
         */
        int width() const noexcept
        {
            return dimensions.getCol();
        }
        
        /*
         * Method: size
         * Usage: int size = matrix.size();
         * -----------------------------------
         * Returns the number of elements in the matrix.
         */
        int size() const noexcept
        {
            return height() * width();
        }

        /*
         * Method: transpose
         * Usage: Matrix<T> matrix_trans = matrix.transpose();
         * -----------------------------------
         * Returns a new transposed Matrix<T> derived from matrix.
         * 
         * Possible Exceptions:
         * std::bad_alloc
         * 
         * Assumptions on T:
         * • Has an assignment operator. (=)
         * • Has a default/no argument constructor
         */
        Matrix transpose() const
        {
            Dimensions transpose_dim(width(), height());
            Matrix transpose(transpose_dim);
            for(int i = 0; i < height(); i++)
            {
                for(int j = 0; j < width(); j++)
                {
                    transpose(j, i) = (*this)(i, j);
                }
            }
            return transpose;
        }

        /*
         * Method: apply
         * Usage: matrix.apply(<function_pointer>);
         *        matrix.apply(<function_object>);
         * -----------------------------------
         * Returns a new Matrix<T> copy of matrix after applying <function_pointer>
         *  to each element of matrix.
         * 
         * Assumptions on T:
         * • Has an assignment operator. (=)
         * • Has a copy ctor.
         * 
         * Possible exceptions:
         * std::bad_aloc if allocation fail.
         */
        template<typename FUNCTOR>
        Matrix apply(FUNCTOR function) const
        {
            Matrix new_matrix = *this;
            for(T& element : new_matrix)
            {
                element = function(element);
            }
            return new_matrix;
        }

        /*
         * Operator: <, >, <=, >=, ==, !=
         * Usage: matrix < T_value   matrix <= T_value
         *        matrix > T_value   matrix >= T_value
         *        matrix == T_value  matrix != T_value
         * ----------------------
         * Returns a matrix with binary values in its cells, according to the evaluated result.
         * 
         * Possible Exceptions:
         * std::bad_alloc
         * 
         * Assumptions on T:
         * • T can be compared using the <bool operator> the client wishes to use.
         * • Has a copy ctor.
         */
        Matrix<bool> operator<(const T& value) const
        {
            class LowerThan
            {
                T val;
            public:
                LowerThan(const T& val) : val(val) { }
                bool operator()(const T& to_compare)
                {
                    return to_compare < val;
                }
            };
            Matrix<bool> bool_result(dimensions, false);
            this->determineCondition(bool_result, LowerThan(value));
            return bool_result;
        }
        Matrix<bool> operator<=(const T& value) const
        {
            Matrix<bool> bool_result(dimensions, false);
            for(int i = 0; i < height(); i++)
            {
                for(int j = 0; j < width(); j++)
                {
                    if((*this)(i, j) <= value)
                    {
                        bool_result(i, j) = true;
                    }
                }
            }
            return bool_result;
        }

        Matrix<bool> operator>(const T& value) const
        {
            Matrix<bool> bool_result(dimensions, false);
            for(int i = 0; i < height(); i++)
            {
                for(int j = 0; j < width(); j++)
                {
                    if((*this)(i, j) > value)
                    {
                        bool_result(i, j) = true;
                    }
                }
            }
            return bool_result;
        }

        Matrix<bool> operator>=(const T& value) const
        {
            Matrix<bool> bool_result(dimensions, false);
            for(int i = 0; i < height(); i++)
            {
                for(int j = 0; j < width(); j++)
                {
                    if((*this)(i, j) >= value)
                    {
                        bool_result(i, j) = true;
                    }
                }
            }
            return bool_result;
        }

        Matrix<bool> operator==(const T& value) const
        {
            Matrix<bool> bool_result(dimensions, false);
            for (int i = 0; i < height(); i++)
            {
                for (int j = 0 ; j < width(); j++)
                {
                    if ((*this)(i,j) == value)
                    {
                        bool_result(i, j) = true;
                    }
                }
            }
            return bool_result;
        }

        Matrix<bool> operator!=(const T& value) const
        {
            Matrix<bool> bool_result(dimensions, false);
            for (int i = 0; i < height(); i++)
            {
                for (int j = 0 ; j < width(); j++)
                {
                    if ((*this)(i,j) != value)
                    {
                        bool_result(i, j) = true;
                    }
                }
            }
            return bool_result;
        }

        /**************************************/
        /*    Operator definition section     */
        /**************************************/
        /*
         * Operator: =
         * Usage: matrix = target_matrix
         * ----------------------
         * Replaces every single element in the matrix to be equal
         * to the target_matrix's elements.
         * 
         * Possible Exceptions:
         * std::bad_alloc
         * 
         * Assumptions on T:
         * • Has an assignment operator. (=)
         * • Has a default/no argument constructor
         */
        Matrix& operator=(const Matrix<T>& target_matrix)
        {
            if (this == &target_matrix)
            {
                return *this;
            }
            dimensions = target_matrix.dimensions;
            Array<T> tmp_arr = target_matrix.elements;
            elements = tmp_arr;
            return *this;
        }

        /*
         * Operator: +=
         * Usage: matrix += value.
         * ----------------------
         * Adds number to every single element in the matrix and returns the matrix' reference.
         * Assumptions on T:
         * • Has an + operator. 
         * 
         * Possible exceptions:
         * std::bad_aloc if allocation fail.
         */
        Matrix& operator+=(const T& value)
        {
            Matrix add_matrix(dimensions, value);
            *this = *this + add_matrix;
            return *this;
        }

        /*
         * Operator: -
         * Usage: -matrix
         * ----------------------
         * -matrix: Returns a negative copy of the matrix.
         * matrix1 - matrix2: performs a substraction of both matrices
         * ----------------------
         * Assumptions on T:
         * • Has an assignment operator. (=)
         * • Has a unary - operator.
         * 
         * Possible exceptions:
         * std::bad_aloc if the allocation fails.
         */
        Matrix operator-() const 
        {
            Matrix negative(*this);
            for(T& element : negative)
            {
                element = -element;
            }
            return negative;
        }

        /*
         * Operator: ()
         * Usage: matrix(row, column)
         * ----------------------
         * Returns a reference to the element of the matrix in the (row, column) index.
         * 
         * Possible Exceptions:
         * Matrix::AccessIllegalElement
         */
        T& operator()(int row, int col)
        {
            if(row >= height() || col >= width() || row < 0 || col < 0)
            {
                throw AccessIllegalElement();
            }
            return elements[row * width() + col];
        }

        const T& operator()(int row, int col) const
        {
            if(row >= height() || col >= width() || row < 0 || col < 0)
            {
                throw AccessIllegalElement();
            }
            return elements[row * width() + col];
        }

        /*
         * Iterator support
         */
        template<typename MATRIX_T, typename TYPE> 
        class _iterator // THIS IS A TEMPLATE ITERATOR CLASS WHICH WILL NOT BE DIRECTLY REACHABLE TO THE USER!
        {
            /*********************************/
            /*        Private Section        */
            /*********************************/
            /* Instance variables */
            MATRIX_T* matrix;
            int index;
            
            
            _iterator(MATRIX_T* matrix, int index) : matrix(matrix), index(index) {};
            friend class Matrix<T>;
            /*
             * Access to the ctor of this template iterator class should be
             * limited to the Matrix<T> class.            
             */

            /*********************************/
            /*         Public Section        */
            /*********************************/
            public:
            /*
             * Copy Constructor: _iterator 
             * Usage: iterator new_iterator(it);
             *        const_iterator new_iterator = it;
             * ---------------------------------------
             * Copies an existing iterator.
             */
            _iterator(const _iterator& it) : matrix(it.matrix), index(it.index) { }
            
            /*
             * Operator: =
             * Usage: it1 = it2;
             * ----------------------
             * Replaces the instance variables of it1 to the 
             * instance variables of it2
             */
            _iterator& operator=(const _iterator& it)
            {
                _iterator copy(it);
                matrix = copy.matrix;
                index = copy.index;
                return *this;
            }

            /*
             * Operator: ++
             * Usage: it++;
             *        ++it;
             * ----------------------
             * Increments the iterator by 1. (According to ++ conventions)
             */
            _iterator& operator++()
            {
                index++;
                return *this;
            }

            _iterator operator++(int)
            {
                _iterator temp_iterator = *this;
                index++;
                return temp_iterator;
            }
            
            /*
             * Operator: *
             * Usage: *it;
             * ----------------------
             * Returns the value of the Matrix<T> that is currently being pointed at.
             * 
             * Possible exceptions:
             * AccessIllegalElement if trying to access an illegal area in the array.
             * 
             */
            TYPE& operator*()
            {
                if((index >= matrix->size()) || (index < 0) || (*this == matrix->end()))
                {
                    throw AccessIllegalElement();
                }
                return (matrix->elements)[index];
            }
            
            /*
             * Operator: ==, !=
             * Usage: it1 == it2
             *        it1 != it2
             * ----------------------
             * Returns a bool value that determines whether it1 is equal to it2 (true or false
             * according to the used operator).
             */
            bool operator==(const _iterator& it) const noexcept
            {
                return (index == it.index) && (matrix == it.matrix);
            }
            
            bool operator!=(const _iterator& it) const noexcept
            {
                return !(*this == it);
            }
        };
        
        /* For the clarity of the code and prevent code duplication */
        typedef _iterator<Matrix<T>, T> iterator;
        typedef _iterator<const Matrix<T>, const T> const_iterator;

        iterator begin()
        {
            iterator it(this, 0);
            return it;
        }

        const_iterator begin() const
        {
            const_iterator it(this, 0);
            return it;
        }

        iterator end() noexcept
        {
            iterator new_it(this, size());
            return new_it;
        }

        const_iterator end() const noexcept
        {
            const_iterator new_it(this, size());
            return new_it;
        }

        /*********************************/
        /*       Exception Section       */
        /*********************************/
        class AccessIllegalElement : public Exception
        {
        private:
            const char* description = "Mtm matrix error: An attempt to access an illegal element";
        public:
            AccessIllegalElement() = default;
            virtual ~AccessIllegalElement() = default;
            const char* what() const noexcept override
            {
                return description;
            }
        };

        class IllegalInitialization : public Exception
        {
        private:
            const char* description = "Mtm matrix error: Illegal initialization values";
        public:
            IllegalInitialization() = default;
            virtual ~IllegalInitialization() = default;
            const char* what() const noexcept override
            {
                return description;
            }
        };

        class DimensionMismatch : public Exception
        {
        private:
            std::string message;
            const std::string description;
        public:
            explicit DimensionMismatch(const Matrix& mat1, const Matrix& mat2) : description("Mtm matrix error: Dimension mismatch: ")
            {
                message = description + "(" + std::to_string(mat1.height()) + "," + std::to_string(mat1.width()) + ") "
                + "(" + std::to_string(mat2.height()) + "," + std::to_string(mat2.width()) + ")";
            }
            virtual ~DimensionMismatch() = default;
            const char* what() const noexcept override
            {
                return message.c_str();
            }
        };
    };
    
    /**************************************/
    /*    Operator definition section     */
    /**************************************/
    /*
     * Operator: +
     * Usage: matrix + type_T (interchangeable)
     *        matrix1 + matrix2
     * ----------------------
     * Adds type_T to every single element in the matrix.
     * The other form performs addition between every two elements in both matrices
     * and returns a new Matrix<T> result.
     * 
     * Possible Exceptions:
     * Matrix::DimensionMismatch if matrix1 and matrix2 have different dimensions.
     * std::bad_aloc if allocation fail.
     * 
     * Assumptions on T:
     * • Has a + operator between two T's.
     * • Has an assignment operator. (=)
     */
    template<typename T>
    Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2)
    {
        if(matrix1.width() != matrix2.width() || matrix1.height() != matrix2.height())
        {
            throw typename Matrix<T>::DimensionMismatch(matrix1, matrix2);
        }
        Matrix<T> result(matrix1);
        for(int i = 0; i < result.height(); i++)
        {
            for(int j = 0; j < result.width(); j++)
            {
                result(i, j) = result(i, j) + matrix2(i, j);
            }
        }
        return result;
    }
    
    template<typename T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T& value)
    {
        return typename Matrix<T>::Matrix(matrix) += value;
    }

    template<typename T>
    Matrix<T> operator+(const T& value, const Matrix<T>& matrix)
    {
        Dimensions copy_dim(matrix.height(),matrix.width());
        Matrix<T> value_matrix(copy_dim, value);
        Matrix<T> result = (value_matrix + matrix); 
        return result;
    }

    /*
     * Operator: -
     * Usage: matrix1 - matrix2
     * ------------------------
     * Performs a substraction for every two elements of the matrices and
     * returns a copy of the result.
     * 
     * Assumptions on T:
     * • Has an assignment operator. (=)
     * • Has a binary + operator and an unary - operator.
     * 
     * Possible exceptions:
     * Matrix::DimensionMismatch if matrix1 and matrix2 have different dimensions.
     * std::bad_aloc if allocation fail.
     */
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2) //Assumes operator+ throws Matrix::DimensionMismatch
    {
        return matrix1 + (-matrix2);
    }

    /*
     * Operator: <<
     * Usage: std::ostream& out << matrix
     * ----------------------------------
     * Prints the matrix in a formatted template to the output channel.
     * 
     * Assumptions on T:
     * • Has a << operator.
     * • Has a copy ctor.
     */
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) noexcept
    {
        return printMatrix(out, matrix.begin(), matrix.end(), matrix.width());
    }

    /**************************************/
    /*    Function definition section     */
    /**************************************/
    
    /*
     * Function: all
     * Usage:  bool res = all(matrix)
     * --------------------------------------
     * Returns true if and only if all the elements of the matrix
     * are true when converted to bool type.
     * 
     * Assumptions on T:
     * • Has a conversion to bool type.
     */
    template<typename T>
    bool all(const Matrix<T>& matrix) noexcept
    {
        for(const T& val : matrix)
        {
            if(!static_cast<bool>(val))
            {
                return false;
            }
        }
        return true;
    }

    /*
     * Function: any
     * Usage:  bool res = any(matrix)
     * --------------------------------------
     * Returns true if and only if exists atleast one element
     * in the matrix that is true when converted to bool type.
     * 
     * Assumptions on T:
     * • Has casting to bool.
     */
    template<typename T>
    bool any(const Matrix<T>& matrix) noexcept
    {
        for(const T& val : matrix)
        {
            if (static_cast<bool>(val))
            {
                return true;
            }
        }
        return false;
    }
}

#endif