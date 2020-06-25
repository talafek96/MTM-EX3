#ifndef MATRIX_INCLUDE
#define MATRIX_INCLUDE
#include <iostream>
#include "Array.h"
#include "Auxiliaries.h"

namespace mtm
{
    template<typename T>
    class Matrix
    {
    private:
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Instance variables */

        Array<T> elements;           /* A dynamic array of the elements   */
        mtm::Dimensions dimensions;  /* The allocated size of the array   */
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
         * IllegalInitialization, std::bad_alloc
         * 
         * Assumptions on T:
         * • Has an assignment operator. (=)
         * • Has a default/no argument constructor
         */ 
        explicit Matrix(const mtm::Dimensions dim, const T& init_value = T())
        {
            if (dim.getCol() <= 0 || dim.getRow() <= 0)
            {
                throw IllegalInitialization();
            }
            elements = Array<T>(size);
            int size = dim.getCol() * dim.getRow();
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
         */
        Matrix(const Matrix<T>& matrix);
                
        /*
         * Destructor: ~Matrix
         * -------------------
         * Frees any heap storage allocated by this matrix.
         */
        virtual ~Matrix();

        /*
         * Method: Diagonal
         * Usage: Matrix<t> diagonal_matrix = Matrix<T>::Diagonal(dim, diagonal_value);
         * -----------------------------------
         * Creates a new Matrix<T> of dimensions (dim x dim) with diagonal_value
         * elements initialized in the diagonal.
         */
        static Matrix Diagonal(const int dim, const T& diagonal_value) const;

        /*
         * Method: height
         * Usage: int rows = matrix.height();
         * -----------------------------------
         * Returns the number of rows (height) of the matrix.
         */
        int height() const;

        /*
         * Method: width
         * Usage: int columns = matrix.width();
         * -----------------------------------
         * Returns the number of columns (width) of the matrix.
         */
        int width() const;
        
        /*
         * Method: size
         * Usage: int size = matrix.size();
         * -----------------------------------
         * Returns the number of elements in the matrix.
         */
        int size() const;

        /*
         * Method: transpose
         * Usage: Matrix<T> matrix_trans = matrix.transpose();
         * -----------------------------------
         * Returns a new transposed Matrix<T> derived from matrix.
         */
        Matrix transpose() const;

        /*
         * Method: apply
         * Usage: matrix.apply(<function_pointer>);
         *        matrix.apply(<function_object>);
         * -----------------------------------
         * Returns a new Matrix<T> copy of matrix after applying <function_pointer>
         *  to each element of matrix.
         */
        template<typename FUNCTOR>
        Matrix apply(FUNCTOR function);

        /*
         * Operator: <, >, <=, >=, ==, !=
         * Usage: matrix < T_value   matrix <= T_value
         *        matrix > T_value   matrix >= T_value
         *        matrix == T_value  matrix != T_value
         * ----------------------
         * Returns a matrix with binary values in its cells, according to the evaluated result.
         */
        Matrix<bool> operator<(const T& value) const;
        Matrix<bool> operator<=(const T& value) const;
        Matrix<bool> operator>(const T& value) const;
        Matrix<bool> operator>=(const T& value) const;
        Matrix<bool> operator==(const T& value) const;
        Matrix<bool> operator!=(const T& value) const;

        /**************************************/
        /*    Operator definition section     */
        /**************************************/
        /*
         * Operator: =
         * Usage: matrix = target_matrix
         * ----------------------
         * Replaces every single element in the matrix to be equal
         * to the target_matrix's elements.
         */
        Matrix& operator=(const Matrix<T>& target_matrix);

        /*
         * Operator: +=
         * Usage: matrix += value.
         * ----------------------
         * Adds number to every single element in the matrix and returns the matrix' reference.
         */
        Matrix& operator+=(T& value);

        /*
         * Operator: -
         * Usage: -matrix
         * ----------------------
         * -matrix: Returns a negative copy of the matrix.
         * matrix1 - matrix2: performs a substraction of both matrices
         */
        Matrix operator-() const;

        /*
         * Operator: ()
         * Usage: matrix(row, column)
         * ----------------------
         * Returns a reference to the element of the matrix in the (row, column) index.
         */
        T& operator()(int row, int col);
        const T& operator()(int row, int col) const;

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
            _iterator(_iterator& it) : matrix(it.matrix), index(it.index) { }
            
            /*
             * Operator: =
             * Usage: it1 = it2;
             * ----------------------
             * Replaces the instance variables of it1 to the 
             * instance variables of it2
             */
            _iterator& operator=(_iterator& it)
            {
                *this = _iterator(it);
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
             */
            TYPE& operator*()
            {
                if(index >= matrix->size())
                {
                    return *(matrix->elements + matrix->size() - 1); //Return the last element of the matrix
                }
                if(index < 0)
                {
                    return *(matrix->elements);
                }
                return *(matrix->elements + index);
            }
            
            /*
             * Operator: ==, !=
             * Usage: it1 == it2
             *        it1 != it2
             * ----------------------
             * Returns a bool value that determines whether it1 is equal to it2 (true or false
             * according to the used operator).
             */
            bool operator==(_iterator& it)
            {
                return (index == it.index) && (matrix == it.matrix);
            }
            
            bool operator!=(_iterator& it)
            {
                return !(*this == it);
            }
        };
        
        /* For the clarity of the code and prevent code duplication */
        typedef _iterator<Matrix<T>, T> iterator;
        typedef _iterator<const Matrix<T>, const T> const_iterator;

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        /*********************************/
        /*       Exception Section       */
        /*********************************/
        class AccessIllegalElement : public Exception
        {
        private:
            static const char* description[] = "Mtm matrix error: An attempt to access an illegal element\n";
        public:
            AccessIllegalElement() = default;
            virtual ~AccessIllegalElement() = default;
            const char* what() const noexcept
            {
                return description;
            }
        }

        class IllegalInitialization : public Exception
        {
        private:
            static const char* description[] = "Mtm matrix error: Illegal initialization values\n";
        public:
            IllegalInitialization() = default;
            virtual ~IllegalInitialization() = default;
            const char* what() const noexcept
            {
                return description;
            }
        }

        class DimensionMismatch : public Exception
        {
        private:
            std::string message;
            static const std::string description = "Mtm matrix error: Dimension mismatch: ";
        public:
            explicit DimensionMismatch(const Matrix& mat1, const Matrix& mat2)
            {
                message = description + "(" + std::string(mat1.height()) + "," + std::string(mat1.width()) + ") "
                + "(" + std::string(mat2.height()) + "," + std::string(mat2.width()) + ")";
            }
            virtual ~DimensionMismatch() = default;
            const char* what() const noexcept override
            {
                return message.c_str();
            }
        }
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
     * Or performs addition between every two elements in both matrixes
     * and returns a new Matrix<T> result.
     */
    template<typename T>
    Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2);
    
    template<typename T>
    Matrix<T> operator+(const Matrix<T>& matrix, const T& value);

    template<typename T>
    Matrix<T> operator+(const T& value, const Matrix<T>& matrix);

    /*
     * Operator: -
     * Usage: matrix1 - matrix2
     * ------------------------
     * Performs a substraction for every two elements of the matrices and
     * returns a copy of the result.
     */
    template<typename T>
    Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

    /*
     * Operator: <<
     * Usage: std::ostream& out << matrix
     * ----------------------------------
     * Prints the matrix in a formatted template to the output channel.
     */
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);

    /**************************************/
    /*    Function definition section     */
    /**************************************/
    
    /*
     * Function: all
     * Usage:  bool res = all(matrix)
     * --------------------------------------
     * Returns true if and only if all the elements of the matrix
     * are all true when converted to bool type.
     */
    template<typename T>
    bool all(const Matrix<T>& matrix);

    /*
     * Function: any
     * Usage:  bool res = any(matrix)
     * --------------------------------------
     * Returns true if and only if exists atleast one element
     * in the matrix that is true when converted to bool type.
     */
    template<typename T>
    bool any(const Matrix<T>& matrix);

    class Exception : public std::exception {};
};

#endif