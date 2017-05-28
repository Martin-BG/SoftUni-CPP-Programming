#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<vector>
#include<unordered_map>

#pragma GCC optimize ("O3")

using namespace std;

int main()
{
	// Tweaks for faster cin execution
	std::cin.sync_with_stdio(false);
	std::cout.sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::map<string, int> players_list;
	std::unordered_map<string, vector<string> > teams_list;
	size_t teams;

	cin >> ws >> teams;

	for (size_t team = 0; team < teams; team++)
	{
		string input_line;
		getline(cin >> ws, input_line);

		istringstream input_stream(input_line);

		string team_id;
		input_stream >> team_id;

		size_t players_in_team;
		input_stream >> players_in_team;

		for (size_t player = 0; player < players_in_team; player++)
		{
			string player_id;
			input_stream >> player_id;
			players_list[player_id];
			teams_list[team_id].push_back(player_id);
		}
	}

	size_t games;

	cin >> games;

	string winner;
	map<string, int> victories;
	for (size_t game = 0; game < games; game++)
	{
		cin >> winner;
		victories[winner]++;
	}

	for (auto team : victories)
	{
		for (auto player : teams_list[team.first])
		{
			players_list[player]+= team.second;
		}
	}

	ostringstream os;
	for (auto player : players_list)
	{
		os << player.second << " ";
	}

	cout << os.str();
	return 0;
}
