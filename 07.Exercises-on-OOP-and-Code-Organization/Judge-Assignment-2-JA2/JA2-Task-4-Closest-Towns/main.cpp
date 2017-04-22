#include<iostream>
#include<vector>
#include<string>
#include<limits>
#include<cmath>

double calculateDistance(const int & x, const int & y)
{
    return std::sqrt(x * x + y * y);
}

int main()
{
    int entries, shortest_x, shortest_y;
    double shortest_dist = std::numeric_limits<double>::max();
    double current_dist;

    std::cin >> entries;

    std::vector<std::string> cities(entries);
    std::vector<int> x_coord(entries);
    std::vector<int> y_coord(entries);

    for (int i = 0; i < entries; i++)
    {
        std::cin >> cities[i] >> x_coord[i] >> y_coord[i];
    }

    for (int i = 0; i < entries; i++)
    {
        for (int j = i + 1; j < entries; j++)
        {
            current_dist = calculateDistance(x_coord[i] - x_coord[j], y_coord[i] - y_coord[j]);

            if (current_dist < shortest_dist)
            {
                shortest_dist = current_dist;
                shortest_x = i;
                shortest_y = j;
            }
        }
    }

    std::cout << cities[shortest_x] << "-" << cities[shortest_y];

    return 0;
}
