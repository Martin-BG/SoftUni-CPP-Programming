#include <iostream>
#include <vector>

using namespace std;

int main()
{
    size_t arrays, elements;
    cin >> arrays >> elements;

    typedef vector<int> numbers;
    std::vector<numbers> arr(arrays);

    for (int i = 0; i < arrays; ++i)
    {
        numbers curr(elements);
        for (int j = 0; j < elements; ++j)
        {
            cin >> curr[j];
        }
        arr[i] = curr;
    }

    vector<int> weights(arrays);

    for (int k = 0; k < arrays; ++k)
    {
        cin >> weights[k];
    }

    for (int l = 0; l < elements; ++l)
    {
        int res = 0;
        for (int i = 0; i < arrays; ++i)
        {
            res += arr[i][l] * weights[i];
        }

        cout << res << " ";
    }

    return 0;
}