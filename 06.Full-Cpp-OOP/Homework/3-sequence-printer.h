#ifndef SEQUENCE_PRINTER_H_INCLUDED
#define SEQUENCE_PRINTER_H_INCLUDED

#include "2-sequence-generators.h" // Declaration and implementation of SequenceGenerator, FibonacciGenerator and SqrtGenerator classes
#include<fstream>

class SequencePrinter
{
public:
    // Constructor
    SequencePrinter(SequenceGenerator & sequence) :
        m_sequence(sequence) {}

    // Destructor
    virtual ~SequencePrinter() {}

    // Copy constructor
    SequencePrinter(const SequencePrinter & other) :
        m_sequence(other.m_sequence) {}

    // Copy-assignment operator
    SequencePrinter & operator= (const SequencePrinter & other)
    {
        if (this != &other)
        {
            this->m_sequence = other.m_sequence;
        }

        return *this;
    }

    virtual void print() = 0;
    virtual void setSequence(const SequenceGenerator & sequence) = 0;

    SequenceGenerator & getSequence() const
    {
        return this->m_sequence;
    }

    void changeSequence(const SequenceGenerator & sequence)
    {
        this->m_sequence = sequence;
    }
private:
    SequenceGenerator & m_sequence;
};

class SequencePrinterToString : public SequencePrinter
{
public:
    // Constructor
    SequencePrinterToString(SequenceGenerator & sequence) :
        SequencePrinter(sequence),
        m_string() {}

    // Destructor
    ~SequencePrinterToString() {}

    // Copy constructor
    SequencePrinterToString(const SequencePrinterToString & other) :
        SequencePrinter(other.getSequence()),
        m_string(other.m_string) {}

    // Copy-assignment operator
    SequencePrinterToString & operator= (const SequencePrinterToString & other)
    {
        if (this != &other)
        {
            this->setSequence(other.getSequence());
            this->m_string = other.m_string;
        }

        return *this;
    }

    void print()
    {
        std::stringstream ss;

        for (int i = 0; i < this->getSequence().getElementsCount(); i++)
        {
            if (i > 0 || this->m_string.size() > 0)
            {
                ss << " ";
            }

            ss << this->getSequence().getValue(i);
        }

        this->m_string += ss.str();
    }

    void setSequence(const SequenceGenerator & sequence)
    {
        changeSequence(sequence);
    }

    std::string getString() const
    {
        return this->m_string;
    }
private:
    std::string m_string;
};

class SequencePrinterToFile : public SequencePrinter
{
public:
    // Constructor
    SequencePrinterToFile(SequenceGenerator & sequence) :
        SequencePrinter(sequence) {}

    void print()
    {
        SequencePrinterToString sequence_printer_to_string(getSequence());
        sequence_printer_to_string.print();

        std::ofstream fs(this->m_file_name, this->m_file_mode);

        fs << sequence_printer_to_string.getString() << std::endl;

        fs.close();
    }

    void setSequence(const SequenceGenerator & sequence)
    {
        changeSequence(sequence);
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

class SequencePrinterToConsole : public SequencePrinter
{
public:
    // Constructor
    SequencePrinterToConsole(SequenceGenerator & sequence) :
        SequencePrinter(sequence) {}

    void print()
    {
        SequencePrinterToString sequence_printer_to_string(getSequence());
        sequence_printer_to_string.print();

        std::cout << sequence_printer_to_string.getString() << std::endl;
    }

    void setSequence(const SequenceGenerator & sequence)
    {
        changeSequence(sequence);
    }
private:
};
#endif // SEQUENCE_PRINTER_H_INCLUDED
