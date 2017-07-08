#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Player {
    int score;
public:
    const string name;

    Player(string name) : name(name), score(0) {}

    int getScore() const {
        return this->score;
    }

    void increaseScore() {
        this->score++;
    }
};

class PlayerNameComp {
public:
    bool operator()(Player* p1, Player* p2) const {
        return p1->name < p2->name;
    }
};

int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    set<Player*, PlayerNameComp> players;
    map<string, vector<Player*> > teamPlayers;

    int numTeams;
    cin >> numTeams;
    for (int i = 0; i < numTeams; i++) {
        string teamName;
        cin >> teamName;
        int numPlayers;
        cin >> numPlayers;
        vector<Player*> & currTeamPlayers = teamPlayers[teamName];
        for (int teammateInd = 0; teammateInd < numPlayers; teammateInd++) {
            string playerName;
            cin >> playerName;
            Player playerFilter(playerName);
            auto playerIter = players.find(&playerFilter);

            Player* player;
            if (playerIter == players.end()) {
                player = new Player(playerName);
                players.insert(player);
            } else {
                player = *playerIter;
            }

            currTeamPlayers.push_back(player);
        }
    }

    int numGames;
    cin >> numGames;
    for (int i = 0; i < numGames; i++) {
        string winningTeam;
        cin >> winningTeam;

        auto winningPlayers = teamPlayers[winningTeam];
        for (Player* player : winningPlayers) {
            player->increaseScore();
        }
    }

    for (Player* player : players) {
        cout << player->getScore() << " ";
        delete player;
    }

    return 0;
}
/*
3
A 2 a b
B 3 b c d
C 1 a
4
A
B
A
C

3 3 1 1
*/
