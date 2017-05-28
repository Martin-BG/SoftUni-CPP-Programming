#include<iostream>
#include<string>
#include<sstream>
#include<vector>

#pragma GCC optimize ("O3")
using namespace std;

int convertToMinutes(int time)
{
	int min = time % 10;
	time /= 10;
	min += (time % 10) * 10;
	time /= 10;
	min += (time % 10) * 60;
	time /= 10;
	min += (time % 10) * 600;
	return min;
}

int main()
{
	// Tweaks for faster cin execution
	std::cin.sync_with_stdio(false);
	std::cin.tie(nullptr);

	vector<int> bus_arrival_times;

	int time;
	string input_line;
	getline(cin >> ws, input_line);

	istringstream input_stream(input_line);

	while (input_stream && (input_stream >> time))
	{
		bus_arrival_times.push_back(convertToMinutes(time));
	}

	int train_time;

	cin >> ws >> train_time;

	train_time = convertToMinutes(train_time);

	int min_wait_time = 100000;
	for (int min : bus_arrival_times)
	{
		if (train_time < min)
		{
			continue;
		}

		if (train_time - min < min_wait_time)
		{
			min_wait_time = train_time - min;
		}
	}

	cout << min_wait_time << endl;
	return 0;
}
