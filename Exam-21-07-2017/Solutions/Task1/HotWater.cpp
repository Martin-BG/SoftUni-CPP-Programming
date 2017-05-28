#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Compiler optimizations
#pragma GCC optimize ("O3")

int main()
{
	// Tweaks for faster cin execution
	std::cin.sync_with_stdio(false);
	std::cin.tie(nullptr);

	int num;
	vector<int> measurements1;
	vector<int> measurements2;

	string input_line;
	getline(cin >> ws, input_line);

	istringstream input_stream(input_line);

	while (input_stream && (input_stream >> num))
	{
		measurements1.push_back(num);
	}
	
	getline(cin >> ws, input_line);
	stringstream input_stream2(input_line);

	while (input_stream2 && (input_stream2 >> num))
	{
		measurements2.push_back(num);
	}

	for (size_t i = 0; i < measurements1.size(); i++)
	{
		cout << measurements2[i] / (measurements1[i] - measurements2[i]) << " ";
	}
	return 0;
}