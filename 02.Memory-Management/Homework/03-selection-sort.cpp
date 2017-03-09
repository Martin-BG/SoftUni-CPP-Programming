/* Write a void selectionSort(int a[], int start, int end)
function that uses the selection sort algorithm to sort the elements from
arr[start] to arr[end – 1] in increasing order (the elements outside
the [start, end) range shouldn't be sorted). This function modifies the
array, so that the elements between start and end are sorted.

Selection sort: in this case it would just find the smallest element between start and end,
and place it at the start, then find the next smallest between the remaining (aka start + 1
and end) and place it at the next position (aka start + 1) and so on */

#include<iostream>

using namespace std;

void selectionSort(int[], int, int);
void printArray(int[], int);
int getIndexOfSmallestElement(int[], int, int);

int main()
{
    int array_elements = 0;
    int start_index = 0;
    int end_index = 0;

    cout << "Enter array size (elements): ";
    cin >> array_elements;

    cout << "Enter start element for selection sort (1 - " << array_elements - 1 << "): ";
    cin >> start_index;

    cout << "Enter end index for selection sort (" << start_index + 1 << " - " << array_elements << "): ";
    cin >> end_index;

    start_index--; //Index in arrays starts from 0

    if (array_elements < 1 || start_index < 0 || start_index >= end_index || end_index > array_elements)
    {
        cout << endl << "Invalid input parameters!" << endl;
        return 1;
    }

    int arr[array_elements];

    cout << endl << "Enter " << array_elements << " integer number(s): ";

    for (int i = 0; i < array_elements; i++)
    {
        cin >> arr[i];
    }

    cout << endl << "Input array : ";
    printArray(arr, array_elements);

    selectionSort(arr, start_index, end_index);

    cout << "Sorted array: ";
    printArray(arr, array_elements);

    return 0;
}

void selectionSort(int arr[], int start_index, int end_index)
{
    bool not_sorted_yet = true;
    int temp_number;
    int temp_index;
    for (int i = start_index; i < end_index; i++)
    {
        temp_index = getIndexOfSmallestElement(arr, i, end_index);

        if (i != temp_index)
        {
            temp_number = arr[i];
            arr[i] = arr[temp_index];
            arr[temp_index] = temp_number;
        }

    }
}

void printArray(int arr[], int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int getIndexOfSmallestElement(int arr[], int start_index, int end_index)
{
    int index_to_smallest_num = start_index;

    for (int i = start_index; i < end_index; i++)
    {
        if (arr[i] < arr[index_to_smallest_num])
        {
            index_to_smallest_num = i;
        }
    }

    return index_to_smallest_num;
}
