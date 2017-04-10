#ifndef SEQUENCE_GENERATORS_H_INCLUDED
#define SEQUENCE_GENERATORS_H_INCLUDED

#include<sstream>
#include<cmath>

class SequenceGenerator
{
public:
    // Constructor
    SequenceGenerator(const int & start_num, const int & end_num) :
        m_elements(end_num - start_num),
        m_start_num(start_num),
        m_end_num(end_num),
        m_values(new double[this->m_elements]()),
        m_names(new std::string[this->m_elements]()) {}

    // Destructor
    virtual ~SequenceGenerator()
    {
        delete [] this->m_values;
        delete [] this->m_names;
    }

    // Copy constructor
    SequenceGenerator(const SequenceGenerator & other) :
        m_elements(other.m_elements),
        m_start_num(other.m_start_num),
        m_end_num(other.m_end_num),
        m_values(new double[this->m_elements]()),
        m_names(new std::string[this->m_elements]())
    {
        for (int i = 0; i < this->m_elements; i++)
        {
            this->m_values[i] = other.m_values[i];
            this->m_names[i] = other.m_names[i];
        }
    }

    // Copy-assignment operator
    SequenceGenerator & operator= (const SequenceGenerator & other)
    {
        if (this != &other)
        {
            this->m_elements = other.m_elements;
            this->m_start_num = other.m_start_num;
            this->m_end_num = other.m_end_num;

            delete [] this->m_values;
            this->m_values = new double[this->m_elements]();

            delete [] this->m_names;
            this->m_names = new std::string[this->m_elements]();

            for (int i = 0; i < this->m_elements; i++)
            {
                this->m_values[i] = other.m_values[i];
                this->m_names[i] = other.m_names[i];
            }
        }

        return *this;
    }

    virtual void generateSequence() = 0;

    std::string & getName(const int & index) const
    {
        return this->m_names[index];
    }

    double & getValue(const int & index) const
    {
        return this->m_values[index];
    }

    int getElementsCount() const
    {
        return this->m_elements;
    }

    int getStartNum() const
    {
        return this->m_start_num;
    }

    int getEndNum() const
    {
        return this->m_end_num;
    }

    std::string getInfo() const
    {
        std::stringstream ss;

        for (int i = 0; i < getElementsCount(); i++)
        {
            ss << this->m_names[i] << " = " << this->m_values[i] << std::endl;
        }

        return ss.str();
    }
protected:
    int m_elements;
    int m_start_num;
    int m_end_num;
    double * m_values;
    std::string * m_names;
};

class FibonacciGenerator : public SequenceGenerator
{
// Note - Calculated Fibonacci numbers for big N will be incorrect because
// of the requirement to use double type in SequenceGenerator to store values
public:
    FibonacciGenerator(const int & start_num, const int & end_num) :
        SequenceGenerator(start_num, end_num)
    {
        generateSequence();
    }

    void generateSequence()
    {
        int index = 0;

        while (index < this->m_elements)
        {
            if (index < 2)
            {
                this->m_values[index] = getFibonacciNum(this->m_start_num + index);
            }
            else
            {
                this->m_values[index] = this->m_values[index - 2] + this->m_values[index - 1];
            }

            this->m_names[index] = "Fibonacci " + std::to_string(this->m_start_num + index);

            index++;
        }
    }

private:
    static double getFibonacciNum(const int & num, bool reset = true)
    {
        if (num == 0)
        {
            return 0.;
        }

        static double n1 = 0.;
        static double n2 = 1.;
        static double n3 = 0.;

        if (reset)
        {
            n1 = 0.;
            n2 = 1.;
            n3 = 0.;
        }

        n3 = n1 + n2;
        n1 = n2;
        n2 = n3;

        if(num > 2)
        {
            getFibonacciNum(num - 1, false);
        }

        return n3;
    }
};

class SqrtGenerator : public SequenceGenerator
{
public:
    SqrtGenerator(const int & start_num, const int & end_num) :
        SequenceGenerator(start_num, end_num)
    {
        generateSequence();
    }

    void generateSequence()
    {
        int index = 0;

        while (index < this->m_elements)
        {
            this->m_values[index] = std::sqrt(this->m_start_num + index);
            this->m_names[index] = "Sqrt(" + std::to_string(this->m_start_num + index) + ")";
            index++;
        }
    }
};

#endif // SEQUENCE_GENERATORS_H_INCLUDED
