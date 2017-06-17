#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <functional>

using namespace std;

// Compiler optimizations
#pragma GCC optimize ("O3")

int main()
{
	// Tweaks for faster cin execution
	std::cin.sync_with_stdio(false);
	std::cin.tie(nullptr);

	string query;
	getline(cin >> ws, query);

	int page_size;
	cin >> page_size;


	multimap<int, string, greater<int> > mails;
	string message;
	getline(cin >> ws, message);

	while (message != ".")
	{
		string word;
		int hits = 0;
		istringstream input_stream(message);

		while (input_stream && (input_stream >> word))
		{
			if (word == query)
			{
				hits++;
			}
		}
		
		if (hits > 0)
		{
			mails.insert(make_pair(hits, message));
		}

		getline(cin >> ws, message);
	}

	int shown = 0;
	multimap<int, string, greater<int> >::iterator rit = mails.begin();

	while(rit != mails.end() && shown < page_size)
	{
		cout << rit->second << endl;
		++rit;
		shown++;
	}
	return 0;
}