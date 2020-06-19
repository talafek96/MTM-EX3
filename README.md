# To Do List
## Berko
### Methods
- [ ] IntMatrix(IntMatrix& matrix);

- [ ] int height();

- [ ] int size();

- [x] iterator begin();

- [x] const_iterator begin() const;



### Operators
- [x] IntMatrix& operator=(const IntMatrix& target_matrix);

- [x] IntMatrix& operator+=(int number);

- [x] IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);

- [x] IntMatrix operator+(const IntMatrix& matrix, int number);

- [x] IntMatrix operator+(int number, const IntMatrix& matrix);


### Functions
- [x] bool all(const IntMatrix& matrix);


### Iterators
- [x] _iterator(ITERATOR_T* matrix, int index);

- [x] _iterator& operator++();

- [x] _iterator operator++(int);





## ______________________________
## Tal
### Methods
- [x] explicit IntMatrix(mtm::Dimensions dim, int init_number = 0);

- [x] virtual ~IntMatrix();

- [x] int width();

- [x] IntMatrix transpose();

- [x] iterator end();

- [x] const_iterator end() const;



### Operators
- [ ] IntMatrix operator-() const;

- [ ] int& operator()(int row, int col);

- [ ] const int& operator()(int row, int col) const;

- [ ] IntMatrix operator-(const IntMatrix& matrix1, const IntMatrix& matrix2);

- [ ] std::ostream& operator<<(std::ostream& out, const IntMatrix& matrix);


### Functions
- [ ] static IntMatrix Identity(int dim);

- [ ] bool any(const IntMatrix& matrix);


### Iterators
- [x] _iterator(_iterator& it);

- [ ] _iterator& operator=(_iterator it);

- [ ] TYPE operator*();

- [ ] bool operator==(_iterator it);

- [ ] bool operator!=(_iterator it);


## ______________________________
## Together
### Operators
- [ ] IntMatrix operator<(int number) const;

- [ ] IntMatrix operator<=(int number) const;

- [ ] IntMatrix operator>(int number) const;

- [ ] IntMatrix operator>=(int number) const;

- [ ] IntMatrix operator==(int number) const;

- [ ] IntMatrix operator!=(int number) const;
