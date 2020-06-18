# To Do List
## Berko
### Methods
- [ ] IntMatrix(IntMatrix& matrix);

- [ ] int height();

- [ ] int size();

- [ ] iterator begin();

- [ ] const_iterator begin() const;

- [ ] _iterator& operator++();

- [ ] _iterator operator++(int);



### Operators
- [ ] IntMatrix& operator=(const IntMatrix& target_matrix);

- [ ] IntMatrix& operator+=(int number);

- [ ] IntMatrix operator+(const IntMatrix& matrix1, const IntMatrix& matrix2);

- [ ] IntMatrix operator+(const IntMatrix& matrix, int number);

- [ ] IntMatrix operator+(int number, const IntMatrix& matrix);


### Functions
- [ ] bool all(const IntMatrix& matrix);


### Iterators
- [ ] _iterator(ITERATOR_T* matrix, int index);




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
