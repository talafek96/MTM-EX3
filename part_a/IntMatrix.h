#ifndef _INT_MATRIX
#define _INT_MATRIX
#include <iostream>
#include "Auxiliaries.h"

namespace mtm {
    class IntMatrix
    {
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Instance variables */

        int* elements;        /* A dynamic array of the elements   */
        mtm::Dimensions dimensions;  /* The allocated size of the array   */

    public:
        /*
         * Constructor: IntMatrix
         * Usage: IntMatrix matrix(dim, init_number);
         *        IntMatrix matrix(dim);
         * ---------------------------------------
         * Initializes a new IntMatrix.  
         * Creates a matrix with the dimension of dim.
         * Each element in the matrix is initialized to init_number.
         * If init_number is missing, the elements are initialized to 0.
         */ 
        explicit IntMatrix(mtm::Dimensions dim, int init_number = 0);
        
        /*
         * Copy Constructor: IntMatrix
         * Usage: IntMatrix new_matrix(matrix);
         *        IntMatrix new_matrix = matrix;
         * ---------------------------------------
         * Initializes a new IntMatrix.  
         * Creates a new matrix that is a copy of matrix.
         */
        IntMatrix(IntMatrix& matrix);

        /*
         * Destructor: ~IntMatrix
         * -------------------
         * Frees any heap storage allocated by this matrix.
         */
        virtual ~IntMatrix();

        /*
         * Function: Identity
         * Usage: IntMatrix I = Identity(dim);
         * -----------------------------------
         * Returns an identity matrix of dimension (dim x dim).
         */
        static IntMatrix Identity(int dim);

        /*
         * Method: height
         * Usage: int rows = matrix.height();
         * -----------------------------------
         * Returns the number of rows (height) of the matrix.
         */
        int height();
        
        /*
         * Method: width
         * Usage: int columns = matrix.width();
         * -----------------------------------
         * Returns the number of columns (width) of the matrix.
         */
        int width();
        
        /*
         * Method: size
         * Usage: int size = matrix.size();
         * -----------------------------------
         * Returns the number of elements in the matrix.
         */
        int size();

        /*
         * Method: transpose
         * Usage: IntMatrix matrix_trans = matrix.transpose();
         * -----------------------------------
         * Returns the number of elements in the matrix.
         */
        IntMatrix transpose();
        
        /**************************************/
        /*    Operator definition section     */
        /**************************************/
        /*
         * Operator: =
         * Usage: matrix = matrix
         * ----------------------
         * Replaces every single element in the matrix to be equal
         * to the target_matrix's elements.
         */
        IntMatrix& operator=(const IntMatrix& target_matrix);
        
        /*
         * Operator: -
         * Usage: -matrix
         * ----------------------
         * -matrix: Returns a negative copy of the matrix.
         * matrix1 - matrix2: performs a substraction of both matrices
         */
        IntMatrix operator-() const;

        /*
         * Operator: +=
         * Usage: matrix += number.
         * ----------------------
         * Adds number to every single element in the matrix and returns the matrix' reference.
         */

        IntMatrix& operator+=(int number);
        
        /*
         * Operator: ()
         * Usage: matrix(row, column)
         * ----------------------
         * Returns a reference to the element of the matrix in the (row, column) index.
         */
        int& operator()(int row, int col);
        const int& operator()(int row, int col) const;

        /*
         * Operator: <, >, <=, >=, ==, !=
         * Usage: matrix < number   matrix <= number
         *        matrix > number   matrix >= number
         *        matrix == number  matrix != number
         * ----------------------
         * Returns a matrix with binary values in it's cells, according to the evaluated result.
         */
        IntMatrix operator<(int number) const;
        IntMatrix operator<=(int number) const;
        IntMatrix operator>(int number) const;
        IntMatrix operator>=(int number) const;
        IntMatrix operator==(int number) const;
        IntMatrix operator!=(int number) const;

        /*
         * Iterator support
         */
        template<typename ITERATOR_T, typename TYPE>
        class _iterator
        {
        /*********************************/
        /*        Private Section        */
        /*********************************/
        /* Instance variables */
        ITERATOR_T* matrix;
        int index;
        
        
        _iterator(ITERATOR_T* matrix, int index);
        /*
         Access to the ctor of this template iterator class should be
         limited to the IntMatrix class.
         */
        friend class IntMatrix;
        
        public:
          /*
         * Copy Constructor: _iterator 
         * Usage: iterator new_iterator(it);
         *        const_iterator new_iterator = it;
         * ---------------------------------------
         * Copies an existing iterator.
         */
        _iterator(_iterator& it);
        // mtm::IntMatrix::_iterator<HAHA, noob> it = it1; @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        
        /*
         * Operator: =
         * Usage: it1 = it2;
         * ----------------------
         * Replaces the instance variables of it1 to the 
         * instance variables of it2
         */
        _iterator& operator=(_iterator it);
        /*
         * Operator: ++
         * Usage: it++;
         *        ++it;
         * ----------------------
         * Increments the iterator by 1. (According to ++ conventions)
         */
        _iterator& operator++();
        _iterator operator++(int);
        
        /*
         * Operator: *
         * Usage: *it;
         * ----------------------
         * Returns the value of the IntMatrix that is currently being pointed at.
         */
        TYPE operator*();
        

        /*
         * Operator: ==, !=
         * Usage: it1 == it2
         *        it1 != it2
         * ----------------------
         * Returns a bool value that determines whether it1 is equal to it2 (true or false
         * according to the used operator).
         */
        bool operator==(_iterator it);
        bool operator!=(_iterator it);

        };

        /* For the clarity of the code and prevent code duplication */
        typedef _iterator<IntMatrix, int> iterator;
        typedef _iterator<const IntMatrix, const int> const_iterator;

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
    };
    /**************************************/
    /*    Operator definition section     */
    /**************************************/
    /*
     * Operator: +
     * Usage: matrix + number (interchangeable)
     *        matrix1 + matrix2
     * ----------------------
     * Adds number to every single element in the matrix.
     * Or, performs a classic matrix addition.
     */
    IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);
    IntMatrix operator+(const IntMatrix& matrix, int number);
    IntMatrix operator+(int number, const IntMatrix& matrix);

    /*
     * Operator: -
     * Usage: matrix1 - matrix2
     * ------------------------
     * Performs a substraction of both matrices and returns a copy of the result.
     */
    IntMatrix operator-(const IntMatrix& matrix1, const IntMatrix& matrix2);
    
    /*
     * Operator: <<
     * Usage: ostream& out << IntMatrix matrix
     * ------------------------
     * Prints the matrix in a formatted template to the output channel.
     */
    std::ostream& operator<<(std::ostream& out, const IntMatrix& matrix);


    /**************************************/
    /*    Function definition section     */
    /**************************************/
    
    /*
     * Function: all
     * Usage:  bool res = all(matrix)
     * --------------------------------------
     * Returns true if and only if all the elements of the matrix
     * do not equal 0.
     */
    bool all(const IntMatrix& matrix);

    /*
     * Function: any
     * Usage:  bool res = any(matrix)
     * --------------------------------------
     * Returns true if and only if exists atleast one element
     * in the matrix that is different than 0.
     */
    bool any(const IntMatrix& matrix);
}
#endif