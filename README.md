# To Do List
## Tal
### Methods
- [x] Matrix(const mtm::Dimensions dim, const T init_value = T());

- [x] int height() const;

- [x] int size() const;

- [ ] Matrix transpose() const;

- [ ] iterator begin();

- [ ] const_iterator begin() const;


### Operators
- [ ] Matrix& operator=(const Matrix<T>& target_matrix);

- [ ] T& operator()(int row, int col);

- [ ] const T& operator()(int row, int col) const;

- [ ] Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

- [ ] Matrix<bool> operator<(const T& value) const;

- [ ] Matrix<bool> operator<=(const T& value) const;

- [ ] Matrix<bool> operator>(const T& value) const;

- [ ] Matrix<bool> operator>=(const T& value) const;


### Functions
- [ ] static Matrix Diagonal(const int dim, const T& diagonal_value) const;

- [ ] bool all(const Matrix<T>& matrix);


### Iterators
- [ ] _iterator(_iterator& it)

- [ ] _iterator& operator++()

- [ ] _iterator operator++(int)

## ______________________________

## Berko
### Methods
- [ ] Matrix(const Matrix<T>& matrix);

- [ ] virtual ~Matrix();

- [ ] int width() const;

- [ ] Matrix apply(FUNCTOR function);

- [ ] iterator end();

- [ ] const_iterator end() const;


### Operators
- [ ] Matrix operator-() const;

- [ ] Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2);

- [ ] std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix);

- [ ] Matrix& operator+=(T& value);

- [ ] Matrix<T> operator+(const Matrix<T>& matrix, const T& value);

- [ ] Matrix<T> operator+(const T& value, const Matrix<T>& matrix);

- [ ] Matrix<bool> operator==(const T& value) const;

- [ ] Matrix<bool> operator!=(const T& value) const;


### Functions
- [ ] bool any(const Matrix<T>& matrix);


### Iterators
- [ ] _iterator(MATRIX_T* matrix, int index)

- [ ] _iterator& operator=(_iterator& it)

- [ ] TYPE& operator*()

- [ ] bool operator==(_iterator& it)

- [ ] bool operator!=(_iterator& it)
