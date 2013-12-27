#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Typos
{
public:
	void GetTypos(const string & Domain, vector<string> & result);	

private:
	bool Prev(const string & Domain, string & prev);
	bool Suffix(const string & Domain, string & suf);
};

