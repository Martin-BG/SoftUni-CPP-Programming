#include<iostream>
#include<string>
#include<array>
#include <algorithm>
#include<fstream>

const int CITIES = 6342;
typedef unsigned int u_int;
std::array<u_int, CITIES> populations;

void parsePopulations();

int main()
{
    parsePopulations();

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

void parsePopulations()
{
    std::ofstream of("extracted.txt");
    std::ifstream fs("populations.txt");

    std::string line;
    getline(fs, line); // Header

    int index = 0;
    while (getline(fs,line))
    {
      std::string::size_type found = line.find_last_of("\t");
      populations[index++] = (atoi(line.substr(found+1).c_str()));
    }

    std::sort(populations.begin(), populations.end());

    for (u_int entry : populations)
    {
        of << entry << ", ";
    }
    fs.close();
    of.close();
}
