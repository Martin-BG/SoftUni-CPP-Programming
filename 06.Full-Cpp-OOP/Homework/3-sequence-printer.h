#ifndef SEQUENCE_PRINTER_H_INCLUDED
#define SEQUENCE_PRINTER_H_INCLUDED

#include "2-sequence-generator.h" // Declaration and implementation of SequenceGenerator, FibonacciGenerator and SqrtGenerator classes
#include<fstream>

class SequencePrinter
{
public:
    virtual ~SequencePrinter() {};
    virtual void print() = 0;
    virtual void setSequence(const SequenceGenerator & sequence) = 0;
};

class SequencePrinterBase : private SequencePrinter
{
public:
    // Destructor
    virtual ~SequencePrinterBase()
    {
        if (this->m_sequence != nullptr)
        {
            delete this->m_sequence;
        }
    }

    // Default constructor
    SequencePrinterBase() :
        m_sequence(nullptr) {}

    // Constructor
    SequencePrinterBase(const SequenceGenerator & sequence) :
        m_sequence(sequence.getClone()) {}

    // Copy constructor
    SequencePrinterBase(const SequencePrinterBase & other) :
        m_sequence(nullptr)
    {
        if (other.m_sequence != nullptr)
        {
            m_sequence = other.m_sequence->getClone();
        }
    }

    // Copy-assignment operator
    SequencePrinterBase & operator= (const SequencePrinterBase & other)
    {
        if (this != &other)
        {
            if (this->m_sequence != nullptr)
            {
                delete this->m_sequence;
            }

            this->m_sequence = other.m_sequence->getClone();
        }

        return *this;
    }

    void setSequence(const SequenceGenerator & sequence)
    {
        if (this->m_sequence != nullptr)
        {
            delete this->m_sequence;
        }

        this->m_sequence = sequence.getClone();
    }

protected:
    const SequenceGenerator * m_sequence;

    static std::string generateString(const SequenceGenerator * sequence)
    {
        std::stringstream ss;

        for (int i = 0; i < sequence->getElementsCount(); i++)
        {
            if (i > 0)
            {
                ss << " ";
            }

            ss << sequence->getValue(i);
        }

        return ss.str();
    }
};

class SequencePrinterToString : public SequencePrinterBase
{
public:
    // Constructor
    SequencePrinterToString(const SequenceGenerator & sequence) :
        SequencePrinterBase(sequence),
        m_string() {}

    // Destructor
    ~SequencePrinterToString() {}

    // Copy constructor
    SequencePrinterToString(const SequencePrinterToString & other) :
        SequencePrinterBase(other),
        m_string(other.m_string) {}

    // Copy-assignment operator
    SequencePrinterToString & operator= (const SequencePrinterToString & other)
    {
        if (this != &other)
        {
            SequencePrinterBase::operator=(other);
            this->m_string = other.m_string;
        }

        return *this;
    }

    void print()
    {
        std::string str = generateString(this->m_sequence);
        if (str.size() > 0)
        {
            if (this->m_string.size() > 0)
            {
                this->m_string += " ";
            }

            this->m_string += str;
        }
    }

    std::string getString() const
    {
        return this->m_string;
    }
private:
    std::string m_string;
};

class SequencePrinterToFile : public SequencePrinterBase
{
public:
    // Constructor
    SequencePrinterToFile(const SequenceGenerator & sequence) :
        SequencePrinterBase(sequence) {}

    // Destructor
    ~SequencePrinterToFile() {}

    // Copy constructor
    SequencePrinterToFile(const SequencePrinterToFile & other) :
        SequencePrinterBase(other) {}

    // Copy-assignment operator
    SequencePrinterToFile & operator= (const SequencePrinterToFile & other)
    {
        if (this != &other)
        {
            SequencePrinterBase::operator=(other);
        }

        return *this;
    }

    void print()
    {
        std::ofstream fs(this->m_file_name, this->m_file_mode);

        fs << generateString(this->m_sequence) << std::endl;

        fs.close();
    }

    static void setAppendMode(const bool & new_mode = false)
    {
        if (new_mode)
        {
            m_file_mode = (std::ofstream::out | std::ofstream::app);
        }
        else
        {
            m_file_mode = std::ofstream::out;
        }
    }

    static void setFileName(const std::string & file_name)
    {
        m_file_name = file_name;
    }

    static std::string getFileName()
    {
        return m_file_name;
    }
private:
    static std::string m_file_name;
    static std::ios_base::openmode m_file_mode;
};
std::string SequencePrinterToFile::m_file_name = "file.txt";
std::ios_base::openmode SequencePrinterToFile::m_file_mode = std::ofstream::out;

class SequencePrinterToConsole : public SequencePrinterBase
{
public:
    // Constructor
    SequencePrinterToConsole(const SequenceGenerator & sequence) :
        SequencePrinterBase(sequence) {}

    // Destructor
    ~SequencePrinterToConsole() {}

    // Copy constructor
    SequencePrinterToConsole(const SequencePrinterToConsole & other) :
        SequencePrinterBase(other) {}

    // Copy-assignment operator
    SequencePrinterToConsole & operator= (const SequencePrinterToConsole & other)
    {
        if (this != &other)
        {
            SequencePrinterBase::operator=(other);
        }

        return *this;
    }

    void print()
    {
        std::cout << generateString(this->m_sequence) << std::endl;
    }
private:
};
#endif // SEQUENCE_PRINTER_H_INCLUDED
