#ifndef OPERATION_H
#define OPERATION_H

class Operation {
public:
    virtual void addOperand(int operand) = 0;
    virtual int getResult() = 0;
    virtual bool isCompleted() = 0;

    virtual ~Operation() = default;
};

#endif // OPERATION_H
