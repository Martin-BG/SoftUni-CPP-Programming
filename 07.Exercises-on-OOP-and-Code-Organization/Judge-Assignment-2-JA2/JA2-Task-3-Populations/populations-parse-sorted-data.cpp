#include<iostream>
#include<string>
#include<array>
#include <algorithm>
#include<fstream>

const int CITIES = 6342;
typedef unsigned int u_int;

int main()
{
    std::ifstream fs("sorted.txt");

    std::array<u_int, CITIES> populations;

    for (int i = 0; i < CITIES; i++)
    {
        fs >> populations[i];
    }

    fs.close();

    int L, H, M;
    std::cin >> L >> H >> M;

    u_int low_limit, high_limit;
    std::array<u_int, CITIES>::iterator low,up;

    int result = 0;
    for(u_int entry : populations)
    {
        low_limit = entry * L;
        high_limit = entry * H;

        low = std::lower_bound(populations.begin(), populations.end(), low_limit);
        up = std::upper_bound(low, populations.end(), high_limit);

        if (up - low >= M)
        {
            result++;
        }
    }

    std::cout << result;

    return 0;
}
