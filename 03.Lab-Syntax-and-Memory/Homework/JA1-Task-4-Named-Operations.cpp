// https://judge.softuni.bg/Contests/Compete/Index/502#3

#include<iostream>
#include<string>
#include<sstream>
#include<climits>

using namespace std;

int* getArray(int&);
int operationZero(const int[], const int&, const int&); // Sum
int operationOne(const int[], const int&, const int&); // Avg
int operationTwo(const int[], const int&, const int&); // Min
int operationThree(const int[], const int&, const int&); // Max

int main()
{
    // Get array
    int array_array_size = 0;
    int * pArr = getArray(array_array_size);

    // Initialize operators
    int operators_count;
    cin >> operators_count;

    string operator_names[operators_count];
    int (*functptr[operators_count])(const int[], const int&, const int&) = {NULL};

    int function_index;

    for (int i = 0; i < operators_count; i++)
    {
        cin >> operator_names[i];
        cin >> function_index;

        switch (function_index)
        {
            case 0: functptr[i] = &operationZero;   break;
            case 1: functptr[i] = &operationOne;   break;
            case 2: functptr[i] = &operationTwo;   break;
            case 3: functptr[i] = &operationThree;   break;
            default : break;
        }
    }

    // Perform operations
    std::ostringstream operations_stream;
    string operation;
    int start_index, end_index;
    int operations = 0;

    cin >> operation;

    while (operation.compare("end") != 0)
    {
        cin >> start_index >> end_index;

        for (int i = 0; i < operators_count; i++)
        {
            if(operator_names[i].compare(operation) == 0)
            {
                if (operations > 0)
                {
                    operations_stream << ",";
                }

                operations_stream << operation << "(" << start_index << "," << end_index << ")=";
                operations_stream << functptr[i](pArr, start_index, end_index);
                operations++;
            }
        }

        cin >> operation;
    }

    // Print result, release memory and exit
    cout << "[" << operations << "]{" << operations_stream.str() << "}";

    delete [] pArr;

    return 0;
}

int* getArray(int &array_array_size)
{
    string input_array;

    getline(cin, input_array);

    istringstream input_stream(input_array);
    int number;

    while (input_stream >> number)
    {
        array_array_size++;
    }

    int * pArr = new int[array_array_size];
    istringstream input_stream_get(input_array);

    for (int i = 0; i < array_array_size; i++)
    {
        input_stream_get >> pArr[i];
    }

    return pArr;
}

int operationZero(const int arr[], const int& startIndex, const int& endIndex)
{
    int result = 0;

    for (int i = startIndex; i < endIndex; i++)
    {
        result += arr[i];
    }

    return result;
}

int operationOne(const int arr[], const int& startIndex, const int& endIndex)
{
    int result = 0;

    for (int i = startIndex; i < endIndex; i++)
    {
        result += arr[i];
    }

    return result / (endIndex - startIndex);
}

int operationTwo(const int arr[], const int& startIndex, const int& endIndex)
{
    int result = INT_MAX;

    for (int i = startIndex; i < endIndex; i++)
    {
        if (result > arr[i])
        {
            result = arr[i];
        }
    }

    return result;
}

int operationThree(const int arr[], const int& startIndex, const int& endIndex)
{
    int result = INT_MIN;

    for (int i = startIndex; i < endIndex; i++)
    {
        if (result < arr[i])
        {
            result = arr[i];
        }
    }

    return result;
}
