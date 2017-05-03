#include<queue>
#include<vector>
#include<iostream>
#include<sstream>

int main()
{
	int M, X, Y, N, P, Q;
	
    std::cin >> M >> X >> Y >> N;

    std::priority_queue<int, std::vector<int>, std::greater<int> > times;

    for (int i = 0; i < N; i++)
    {
        std::cin >> P >> Q;

        times.push((std::abs(X - P) + std::abs(Y-Q)) * 2);
    }

    int time_needed = 0;

    while (M > 0 && !times.empty())
    {
        time_needed += times.top();
        times.pop();
        M--;
    }

    std::cout << time_needed;

    return 0;
}
