#include <iostream>
#include <vector>
#include <algorithm>

#pragma GCC optimize ("O3")

int main()
{
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    int D, N, income;
    std::vector<int> numbers;

    std::cin >> D >> N;

    while (N-- > 0)
    {
        std::cin >> income;
        numbers.push_back(income);
    }

    std::sort(numbers.begin(), numbers.end());

    int low_bound = numbers.front() + D;
    int high_bound = numbers.back() - D;
    double sum = 0.0;
    int items_count = 0;
    for (auto item : numbers)
    {
        if (item <= low_bound)
        {
            continue;
        }

        if (item >= high_bound)
        {
            break;
        }

        sum += item;
        items_count++;
    }

    std::cout << sum / items_count << std::endl;

    return 0;
}
