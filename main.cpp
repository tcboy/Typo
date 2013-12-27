#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include "whois.h"
#include "typos.h"
#include "alexa.h"

using namespace std;

int main(int argc, char *argv[])
{
	int i;
	string st;
	Typos typos;
	Whois whois;
	Alexa alexa;
	while ( cin >> st )
	{
		cout << st << endl;
		
		if ( st.size() > 15 )
		{
			cout << endl;
			continue;
		}
		
		vector<string> domains;
		vector<string> result;
		typos.GetTypos(st, domains);
		for ( i = 0 ; i < domains.size() ; i++ )
		{
			bool isReg;
			printf("%cLoading Whois : %s", 13, domains[i].c_str());
			fflush(stdout);
			if ( whois.isRegistered(domains[i], isReg) )
			{
				if ( !isReg )
					result.push_back(domains[i]);
			}
			sleep(1);
		}

		for ( i = 0 ; i < result.size() ; i++ )
		{
			int Rank;
			printf("%cLoading Alexa : %s", 13, result[i].c_str());
			fflush(stdout);
			if ( alexa.GetRank(result[i], Rank) )
				cout << result[i] << " " << Rank << endl;
			sleep(1);
		}
		printf("%c\n", 13);
		fflush(stdout);
	}	
	return 0;
}
