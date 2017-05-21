#ifndef MATRIX_H
#define MATRIX_H

#include<string>
#include<stdexcept>

typedef int DataType;
typedef DataType * Row;
typedef Row * RowsCols;
class Matrix {
    unsigned int rows;
    unsigned int columns;

    RowsCols data;
public:
    Matrix(unsigned int rows, unsigned int columns);
    Matrix(const Matrix& other);

    unsigned int getRows() const;
    unsigned int getColumns() const;

    void changeSize(unsigned int rows, unsigned int columns);
    DataType get(unsigned int row, unsigned int column) const;
    void set(unsigned int row, unsigned int column, DataType value);

    std::string toString() const;

    Matrix& operator=(const Matrix& other);

    ~Matrix();
private:
    void ensureInBounds(unsigned int row, unsigned int column) const;
    static void freeRowsCols(RowsCols data, unsigned int rows);
    static RowsCols initRowsCols(unsigned int rows, unsigned int columns);
    static void copyData(RowsCols source, unsigned int sourceRows, unsigned int sourceColumns, RowsCols dest, unsigned int destRows, unsigned int destColumns);
};

#endif //MATRIX_H
