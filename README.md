# To Do List
### Methods
- [ ] Matrix(const Matrix<T>& matrix);

- [ ] Matrix(const mtm::Dimensions dim, const T init_value = T());

- [ ] virtual ~Matrix();

- [ ] int height() const;

- [ ] int width() const;

- [ ] int size() const;

- [ ] Matrix transpose() const;

- [ ] Matrix apply(FUNCTOR function);

- [ ] iterator end();

- [ ] const_iterator end() const;

- [ ] iterator begin();

- [ ] const_iterator begin() const;



### Operators
- [ ] Matrix& operator=(const Matrix<T>& target_matrix);

- [ ] Matrix operator-() const;

- [ ] T& operator()(int row, int col);

- [ ] const T& operator()(int row, int col) const;

- [ ] Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

- [ ] std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);

- [ ] Matrix& operator+=(T& value);

- [ ] Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

- [ ] Matrix<T> operator+(const Matrix<T>& matrix, const T& value);

- [ ] Matrix<T> operator+(const T& value, const Matrix<T>& matrix);


### Functions
- [ ] static Matrix Diagonal(const int dim, const T& diagonal_value) const;

- [ ] bool any(const Matrix<T>& matrix);

- [ ] bool all(const Matrix<T>& matrix);


### Iterators
- [ ] _iterator(MATRIX_T* matrix, int index)

- [ ] _iterator(_iterator& it)

- [ ] _iterator& operator=(_iterator& it)

- [ ] TYPE& operator*()

- [ ] bool operator==(_iterator& it)

- [ ] bool operator!=(_iterator& it)

- [ ] _iterator& operator++()

- [ ] _iterator operator++(int)



## ______________________________
## Tal

## Berko
### Methods


### Operators


### Functions



### Iterators


## ______________________________
## Together
### Operators
- [ ] Matrix<bool> operator<(const T& value) const;

- [ ] Matrix<bool> operator<=(const T& value) const;

- [ ] Matrix<bool> operator>(const T& value) const;

- [ ] Matrix<bool> operator>=(const T& value) const;

- [ ] Matrix<bool> operator==(const T& value) const;

- [ ] Matrix<bool> operator!=(const T& value) const;
