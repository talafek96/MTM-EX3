# To Do List
## Tal
### Methods
- [x] Matrix(const mtm::Dimensions dim, const T init_value = T());

- [x] int height() const;

- [x] int size() const;

- [x] Matrix transpose() const;

- [x] iterator begin();

- [x] const_iterator begin() const;

### Operators
- [x] Matrix& operator=(const Matrix<T>& target_matrix);

- [x] T& operator()(int row, int col);

- [x] const T& operator()(int row, int col) const;

- [x] Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

- [x] Matrix<bool> operator<(const T& value) const;

- [x] Matrix<bool> operator<=(const T& value) const;

- [x] Matrix<bool> operator>(const T& value) const;

- [x] Matrix<bool> operator>=(const T& value) const;


### Functions
- [x] static Matrix Diagonal(const int dim, const T& diagonal_value) const;

- [x] bool all(const Matrix<T>& matrix);


### Iterators
- [x] _iterator(_iterator& it)

- [x] _iterator& operator++()

- [x] _iterator operator++(int)

## ______________________________

## Berko
### Methods
- [x] Matrix(const Matrix<T>& matrix);

- [x] virtual ~Matrix();

- [x] int width() const;

- [x] Matrix apply(FUNCTOR function);

- [x] iterator end();

- [x] const_iterator end() const;


### Operators
- [x] Matrix operator-() const;

- [x] Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

- [x] std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);

- [x] Matrix& operator+=(T& value);

- [x] Matrix<T> operator+(const Matrix<T>& matrix, const T& value);

- [x] Matrix<T> operator+(const T& value, const Matrix<T>& matrix);

- [x] Matrix<bool> operator==(const T& value) const;

- [x] Matrix<bool> operator!=(const T& value) const;

- [x] Matrix<bool> operator==(const T& value) const;

### Functions
- [x] bool any(const Matrix<T>& matrix);


### Iterators
- [x] _iterator(MATRIX_T* matrix, int index)

- [x] _iterator& operator=(_iterator& it)

- [x] TYPE& operator*()

- [x] bool operator==(_iterator& it)

- [x] bool operator!=(_iterator& it)
