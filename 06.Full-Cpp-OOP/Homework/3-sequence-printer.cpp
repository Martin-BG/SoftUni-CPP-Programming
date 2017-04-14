/* Write a SequencePrinter class, which has a pure-virtual print() method
 and a pure-virtual setSequence(const SequenceGenerator& sequence) method.
 Derive a SequencePrinterToString, SequencePrinterToFile, SequencePrinterToConsole
 class. Any class implementing setSequence(const SequenceGenerator& sequence)
 should change the sequence the current object work with, with the sequence
 passed-in from the method. Any class implementing print() should write the
 sequence to whatever target it prints to, the numbers in the sequence should
 be separated by spaces.
The SequencePrinterToString should be able to print a sequence to a string (by appending)
The SequencePrinterToFile should be able to print a sequence to a file (by overwriting
 the file with the sequence string equivalent). NOTE: you can use SequencePrinterToString,
 but NOT by inheriting it - SequencePrinterToFile isn't a kind of SequencePrinterToString
The SequencePrinterToConsole class should be able to print a sequence to the console.*/

#include<iostream>
#include "3-sequence-printer.h"

struct   // Demo helper class
{
    void runDemo() const
    {
        std::cout << "SqrtGenerator sqrt_gen(0, 10)" << std::endl;
        SqrtGenerator * sqrt_gen = new SqrtGenerator(0, 10);
        std::cout << sqrt_gen->getInfo() << std::endl;

        std::cout << "FibonacciGenerator fibo_gen(0, 10)" << std::endl;
        FibonacciGenerator * fibo_gen = new FibonacciGenerator(0, 10);
        std::cout << fibo_gen->getInfo() << std::endl;

        std::cout << std::endl << "Demo SequencePrinterToConsole" << std::endl;

        std::cout << std::endl << "SequencePrinterToConsole print_to_console(*sqrt_gen)" << std::endl;
        SequencePrinterToConsole print_to_console(*sqrt_gen);
        print_to_console.print();

        std::cout << std::endl << "print_to_console.setSequence(SqrtGenerator(10, 15))" << std::endl;
        print_to_console.setSequence(SqrtGenerator(10, 15));
        print_to_console.print();

        std::cout << std::endl << "print_to_console.setSequence(*fibo_gen)" << std::endl;
        print_to_console.setSequence(*fibo_gen);
        print_to_console.print();

        std::cout << std::endl << "print_to_console.setSequence(FibonacciGenerator(10, 15))" << std::endl;
        print_to_console.setSequence(FibonacciGenerator(10, 15));
        print_to_console.print();

        std::cout << std::endl << "SequencePrinterToConsole print_to_console2(*sqrt_gen)" << std::endl;
        SequencePrinterToConsole print_to_console2(*sqrt_gen);
        print_to_console2.print();

        std::cout << std::endl << "SequencePrinterToConsole print_to_console3(print_to_console2)" << std::endl;
        SequencePrinterToConsole print_to_console3(print_to_console2);
        print_to_console3.print();

        std::cout << std::endl << "print_to_console2 = print_to_console" << std::endl;
        print_to_console2 = print_to_console;
        print_to_console2.print();

        std::cout << std::endl << "Demo SequencePrinterToString" << std::endl;

        std::cout << std::endl << "SequencePrinterToString print_to_string(SqrtGenerator(0, 10))" << std::endl;
        SequencePrinterToString print_to_string(*sqrt_gen);
        print_to_string.print();
        std::cout << print_to_string.getString() << std::endl;

        std::cout << std::endl << "print_to_string.setSequence(SqrtGenerator(10, 15))" << std::endl;
        print_to_string.setSequence(SqrtGenerator(10, 15));
        print_to_string.print();
        std::cout << print_to_string.getString() << std::endl;

        std::cout << std::endl << "print_to_string.setSequence(*fibo_gen)" << std::endl;
        print_to_string.setSequence(*fibo_gen);
        print_to_string.print();
        std::cout << print_to_string.getString() << std::endl;

        std::cout << std::endl << "print_to_string.setSequence(FibonacciGenerator(10, 15))" << std::endl;
        print_to_string.setSequence(FibonacciGenerator(10, 15));
        print_to_string.print();
        std::cout << print_to_string.getString() << std::endl;

        std::cout << std::endl << "SequencePrinterToString print_to_string2(*sqrt_gen)" << std::endl;
        SequencePrinterToString print_to_string2(*sqrt_gen);
        print_to_string2.print();
        std::cout << print_to_string2.getString() << std::endl;

        std::cout << std::endl << "SequencePrinterToString print_to_string3(print_to_string2)" << std::endl;
        SequencePrinterToString print_to_string3(print_to_string2);
        std::cout << print_to_string3.getString() << std::endl;

        std::cout << std::endl << "print_to_string2 = print_to_string" << std::endl;
        print_to_string2 = print_to_string;
        std::cout << print_to_string2.getString() << std::endl;

        std::cout << std::endl << "Demo SequencePrinterToFile" << std::endl;

        std::cout << std::endl << "Changed file name from " << SequencePrinterToFile::getFileName() << " to ";
        SequencePrinterToFile::setFileName("3-sequence-printer-file.txt");
        std::cout << SequencePrinterToFile::getFileName() << std::endl;

        std::cout << std::endl << "SequencePrinterToFile print_to_file(*sqrt_gen)" << std::endl;
        SequencePrinterToFile print_to_file(*sqrt_gen);
        print_to_file.print();
        std::cout << "Saved to " << SequencePrinterToFile::getFileName() << std::endl;

        std::cout << std::endl << "Change file access mode from overwrite to append" << std::endl;
        SequencePrinterToFile::setAppendMode(true); // Enable append mode for write to file

        std::cout << std::endl << "print_to_file.setSequence(SqrtGenerator(10, 15))" << std::endl;
        print_to_file.setSequence(SqrtGenerator(10, 15));
        print_to_file.print();
        std::cout << "Saved to " << SequencePrinterToFile::getFileName() << std::endl;

        std::cout << std::endl << "print_to_file.setSequence(*fibo_gen)" << std::endl;
        print_to_file.setSequence(*fibo_gen);
        print_to_file.print();
        std::cout << "Saved to " << SequencePrinterToFile::getFileName() << std::endl;

        std::cout << std::endl << "print_to_file.setSequence(FibonacciGenerator(10, 15))" << std::endl;
        print_to_file.setSequence(FibonacciGenerator(10, 15));
        print_to_file.print();
        std::cout << "Saved to " << SequencePrinterToFile::getFileName() << std::endl;

        std::cout << std::endl << "SequencePrinterToFile print_to_file2(*sqrt_gen)" << std::endl;
        SequencePrinterToFile print_to_file2(*sqrt_gen);
        print_to_file2.print();
        std::cout << "Saved to " << SequencePrinterToFile::getFileName() << std::endl;

        std::cout << std::endl << "SequencePrinterToFile print_to_file3(print_to_file2)" << std::endl;
        SequencePrinterToFile print_to_file3(print_to_file2);
        print_to_file3.print();
        std::cout << "Saved to " << SequencePrinterToFile::getFileName() << std::endl;

        std::cout << std::endl << "print_to_file2 = print_to_file" << std::endl;
        print_to_file2 = print_to_file;
        print_to_file2.print();
        std::cout << "Saved to " << SequencePrinterToFile::getFileName() << std::endl;

        std::cout << std::endl  << "SequencePrinterToFile demo completed." << std::endl
            << "Changes saved to " << SequencePrinterToFile::getFileName() << std::endl
            << std::endl;
    }

    void stressTests() const
    {
        std::cout << "Load test - check program for memory leaks."
            << std::endl << "Press <Enter> to start. Use Ctrl-C to terminate at any time...";

        std::cin.get();

        SequencePrinterToFile::setAppendMode(false); // Disable append mode for write to file
        SequencePrinterToFile::setFileName("3-load-test.txt");

        SqrtGenerator * sqrt_gen = new SqrtGenerator(0, 100);
        FibonacciGenerator * fibo_gen = new FibonacciGenerator(1, 100);

        int const BIG_NUMBER = 1000000;
        for (int i = 0; i < BIG_NUMBER; i++)
        {
            for (int j = 0; j < BIG_NUMBER; j++)
            {
                SequencePrinterToFile seq_file(*sqrt_gen);
                SequencePrinterToString seq_str(*sqrt_gen);
                SequencePrinterToConsole seq_con(*sqrt_gen);
                seq_file.print();
                seq_str.print();
                seq_con.print();

                seq_file.setSequence(FibonacciGenerator(0, 10));
                seq_str.setSequence(SqrtGenerator(0,10));
                seq_con.setSequence(FibonacciGenerator(0, 10));
                seq_file.print();
                seq_str.print();
                seq_con.print();

                SequencePrinterToFile seq_file2(seq_file);
                SequencePrinterToString seq_str2(seq_str);
                SequencePrinterToConsole seq_con2(seq_con);
                seq_file2.print();
                seq_str2.print();
                seq_con2.print();

                seq_file.setSequence(FibonacciGenerator(*fibo_gen));
                seq_str.setSequence(FibonacciGenerator(*fibo_gen));
                seq_con.setSequence(FibonacciGenerator(*fibo_gen));
                seq_file.print();
                seq_str.print();
                seq_con.print();

                seq_file2 = seq_file;
                seq_str2 = seq_str;
                seq_con2 = seq_con;
                seq_file2.print();
                seq_str2.print();
                seq_con2.print();
            }
        }
    }
}Demo;

int main()
{
    Demo.runDemo();

    Demo.stressTests();

    return 0;
}
