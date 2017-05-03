#include<queue>
#include<vector>
#include<iostream>
#include<sstream>

int M, X, Y, N, P, Q;

int calcTime()
{
    return (std::abs(X - P) + std::abs(Y-Q)) * 2;
}

int main()
{
    std::cin >> M >> X >> Y >> N;

    std::priority_queue<int, std::vector<int>, std::greater<int> > times;

    for (int i = 0; i < N; i++)
    {
        std::cin >> P >> Q;

        times.push(calcTime());
    }

    int time_needed = 0;

    while(M > 0 && !times.empty())
    {
        M--;
        time_needed += times.top();
        times.pop();
    }

    std::cout << time_needed;

    return 0;
}
