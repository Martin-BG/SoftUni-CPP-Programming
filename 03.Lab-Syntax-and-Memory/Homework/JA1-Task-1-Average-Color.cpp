#include<iostream>
#include<string>
#include <iomanip>

using namespace std;

int main()
{
	string color_one, color_two;

	cin >> color_one >> color_two;

	cout << "#";

	for (int i = 0; i < 3; i++)
	{
		cout << std::setw(2) << setfill('0') << hex
		<< ((stoi(color_one.substr(i * 2 + 1, 2), nullptr, 16)
            + stoi(color_two.substr(i * 2 + 1, 2), nullptr, 16)) / 2);
	}

	cout << endl;

	return 0;
}
