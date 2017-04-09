/* Write a SequenceGenerator class, which has a pure-virtual method generateSequence(),
 contains a pointer to a dynamically allocated array of numbers (new double[…]), has a
 name for each of those numbers, and has a getName(int index) and a getValue(int index)
 method, both NOT virtual (Note: you can any other fields you need). Extend
 SequenceGenerator by FibonacciGenerator & SqrtGenerator.
The FibonacciGenerator should have a Fibonacci(int startFibonacciNumber, int
 endFibonacciNumber) constructor and generate the sequence of Fibonacci numbers from
 startFibonacciNumber (inclusive) to endFibonacciNumber (exclusive). The Nth Fibonacci
 number should have the name "Fibonacci N" (e.g. the 5th Fibonacci number should have
 the name "Fibonacci 5"). So, if we initialize a FibonacciGenerator(3, 6), it should
 generate the Fibonacci numbers from "Fibonacci 3" to "Fibonacci 5" (inclusive), i.e.
 the numbers 2, 3, 5
 (check here for reference: https://en.wikipedia.org/wiki/Fibonacci_number#List_of_Fibonacci_numbers)
The SqrtGenerator should have a SqrtGenerator(int startInteger, int endInteger) and
 should generate the square roots of the numbers from startInteger (inclusive) to
 endInteger (exclusive). The square root of the number N should have the name "Sqrt(N)"
 (e.g. the square root of the number 49 would be named "Sqrt(49)"). So, if we initialize
 SqrtGenerator(4, 10), it should generate "Sqrt(4)", "Sqrt(5)", "Sqrt(6)", "Sqrt(7)",
 "Sqrt(8)", "Sqrt(9)", i.e. 2, 2.236, 2.449, 2.64575, 2.828, 3
 (note: the values here are approximated for the example).
Make sure that your code has no memory problems (SequenceGenerator creates a
 new double[…], so it needs a destructor, which means it needs Rule of Three).
One way to test the if your class has memory problems would be to do something like:

for(int ind1 = 0; ind1 < BIG_NUMBER; ind1++) {
  for(int ind2 = 0; ind2 < BIG_NUMBER; ind2++) {
    FibonacciGenerator g(1, 100);
    FibonacciGenerator copyConstructed(g);
    FibonacciGenerator copyAssigned(1, 5);
    copyAssigned = g;
    // print copyAssigned and copyConstructed to see they are correct
    // or just have a function which checks each of their values
  }
}
This code will call copy-constructors, copy-assignment operators, and destructors a lot
 of times, and you can track if your program's memory usage increases (if you define a
 large enough BIG_NUMBER) - if it keeps increasing, then you've got something wrong*/

#include<iostream>
#include "2-sequence-generators.h" // Declaration and implementation of SequenceGenerator, FibonacciGenerator and SqrtGenerator classes

struct // Demo helper class
{
public:
    void stressTests() const
    {
        std::cout << "FibonacciGenerator - Validate copy constructor and copy assignment... ";

        FibonacciGenerator fg(1, 100);
        FibonacciGenerator copyConstructedF(fg);
        FibonacciGenerator copyAssignedF(1, 5);
        copyAssignedF = fg;

        if (copyConstructedF.getInfo() == copyAssignedF.getInfo() &&
            fg.getInfo() == copyAssignedF.getInfo())
        {
            std::cout << " OK" << std::endl << std::endl;
        }
        else
        {
            std::cout << " Failed" << std::endl << std::endl;
        }

        std::cout << "SqrtGenerator - Validate copy constructor and copy assignment... ";
        SqrtGenerator sg(1, 100);
        SqrtGenerator copyConstructedS(sg);
        SqrtGenerator copyAssignedS(1, 5);
        copyAssignedS = sg;

        if (copyConstructedS.getInfo() == copyAssignedS.getInfo() &&
            sg.getInfo() == copyAssignedS.getInfo())
        {
            std::cout << "OK" << std::endl << std::endl;
        }
        else
        {
            std::cout << "Failed" << std::endl << std::endl;
        }

        std::cout << "Load test - check program for memory leaks, Ctrl-C to stop";

        int const BIG_NUMBER = 1000000;
        for (int ind1 = 0; ind1 < BIG_NUMBER; ind1++)
        {
            for (int ind2 = 0; ind2 < BIG_NUMBER; ind2++)
            {
                FibonacciGenerator g(1, 100);
                FibonacciGenerator copyConstructed(g);
                FibonacciGenerator copyAssigned(1, 5);
                copyAssigned = g;
                SqrtGenerator sgt(1, 100);
                SqrtGenerator copyConstructedSqrt(sgt);
                SqrtGenerator copyAssignedSqrt(1, 5);
                copyAssignedSqrt = sgt;
            }
        }
    }

    void runDemo() const
    {
        std::cout << "FibonacciGenerator (3, 6)" << std::endl;
        FibonacciGenerator fibo_seq(3, 6);
        std::cout << fibo_seq.getInfo() << std::endl;

        std::cout << "SqrtGenerator (4, 10)" << std::endl;
        SqrtGenerator sqrt_seq(4, 10);
        std::cout << sqrt_seq.getInfo() << std::endl;
    }

}Demo;

int main()
{
    Demo.runDemo();

    Demo.stressTests();

    return 0;
}
