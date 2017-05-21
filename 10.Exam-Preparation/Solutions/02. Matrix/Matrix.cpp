#include<sstream>
#include "Matrix.h"

Matrix::Matrix(unsigned int rows, unsigned int columns) :
    rows(rows),
    columns(columns),
    data(new Row[rows]())
{
    for (unsigned int i = 0; i < rows; i++)
    {
        this->data[i] = new DataType[columns]();
    }
}

Matrix::Matrix(const Matrix& other) :
    rows(other.rows),
    columns(other.columns),
    data(new Row[rows]())
{
    for (unsigned int i = 0; i < this->rows; i++)
    {
        this->data[i] = new DataType[this->columns]();
        for (unsigned int j = 0; j < this->columns; j++)
        {
            this->data[i][j] = other.data[i][j];
        }
    }
}

unsigned int Matrix::getRows() const
{
    return this->rows;
}

unsigned int Matrix::getColumns() const
{
    return this->columns;
}

void Matrix::changeSize(unsigned int rows, unsigned int columns)
{
    RowsCols new_data = new Row[rows]();

    for (unsigned int i = 0; i < rows; i++)
    {
        new_data[i] = new DataType[columns]();
    }

    unsigned int rows_to_copy = (this->rows < rows)?this->rows:rows;
    unsigned int columns_to_copy = (this->columns < columns)?this->columns:columns;

    for (unsigned int i = 0; i < rows_to_copy; i++)
    {

        for (unsigned int j = 0; j < columns_to_copy; j++)
        {
            new_data[i][j] = this->data[i][j];
        }
    }

    for (unsigned int i = 0; i < this->rows; i++)
    {
        delete [] this->data[i];
    }

    delete [] this->data;

    this->rows = rows;
    this->columns = columns;
    this->data = new_data;
}

DataType Matrix::get(unsigned int row, unsigned int column) const
{
    ensureInBounds(row, column);

    return this->data[row][column];
}

void Matrix::set(unsigned int row, unsigned int column, DataType value)
{
    ensureInBounds(row, column);

    this->data[row][column] = value;
}

std::string Matrix::toString() const
{
    std::stringstream ss;
    for (unsigned int i = 0; i < this->rows; i++)
    {
        for (unsigned int j = 0; j < this->columns; j++)
        {
            ss << this->data[i][j] << " ";
        }
        ss << std::endl;
    }

    return ss.str();
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        for (unsigned int i = 0; i < this->rows; i++)
        {
            delete [] this->data[i];
        }

        delete [] this->data;

        this->rows = other.rows;
        this->columns = other.columns;
        this->data = new Row[this->rows]();

        for (unsigned int i = 0; i < this->rows; i++)
        {
            this->data[i] = new DataType[this->columns]();

            for (unsigned int j = 0; j < this->columns; j++)
            {
                this->data[i][j] = other.data[i][j];
            }
        }
    }

    return *this;
}

Matrix::~Matrix()
{
    for (unsigned int i = 0; i < this->rows; i++)
    {
        delete [] this->data[i];
    }

    delete [] this->data;
    this->data = nullptr;
    this->rows = 0;
    this->columns = 0;
}

void Matrix::ensureInBounds(unsigned int row, unsigned int column) const
{
    if (this->rows < row || this->columns < column || this->rows == 0 || this->columns == 0)
    {
        throw std::range_error("Out of bounds");
    }
}

void Matrix::freeRowsCols(RowsCols data, unsigned int rows)
{

}

RowsCols Matrix::initRowsCols(unsigned int rows, unsigned int columns)
{
    RowsCols m;
    return m;
}

void Matrix::copyData(RowsCols source, unsigned int sourceRows, unsigned int sourceColumns, RowsCols dest, unsigned int destRows, unsigned int destColumns)
{

}
