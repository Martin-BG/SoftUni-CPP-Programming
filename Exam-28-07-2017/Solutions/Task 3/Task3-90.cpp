#include<iostream>
#include<string>
#include<sstream>
#include<map>
#include<vector>

#pragma GCC optimize ("O3")

using namespace std;

int main()
{
	// Tweaks for faster cin execution
	std::cin.sync_with_stdio(false);
	std::cout.sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::map<string, int> players_list;
	std::map<string, vector<string> > teams_list;
	int teams;

	cin >> ws >> teams;

//	cout << "Teams: " << teams << endl;

	for (size_t team = 0; team < teams; team++)
	{
		string input_line;
		getline(cin >> ws, input_line);

		istringstream input_stream(input_line);

		string team_id;
		input_stream >> team_id;

//		cout << "Team ID: " << team_id << endl;

		int players_in_team;
		input_stream >> players_in_team;

//		cout << "Players in team: " << players_in_team << endl;

		for (size_t player = 0; player < players_in_team; player++)
		{
			string player_id;
			input_stream >> player_id;
//			cout << "Player ID: " << player_id << endl;
			players_list[player_id];
		//	players_list.insert(make_pair(player_id, 0));

			teams_list[team_id].push_back(player_id);
		}
	}
	//for (auto player : players_list)
	//{
	//	cout << player.first << " : " << player.second << endl;
	//}

	//for (auto team : teams_list)
	//{
	//	cout << team.first << " : ";
	//	for(auto player : team.second)
	//	{
	//		cout << player << " ";
	//	}
	//	cout << endl;
	//}
	int games;

	cin >> games;
//	cout << "Games " << games << endl;

	for (size_t game = 0; game < games; game++)
	{
		string winner;
		cin >> winner;

		for (auto player : teams_list[winner])
		{
			players_list[player]++;
		}
//		cout << "Winner is " << winner << endl;
	}

	for (auto player : players_list)
	{
		cout << player.second << " ";
	}
	return 0;
}