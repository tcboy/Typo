#include <algorithm>
#include "typos.h"

void Typos::GetTypos(const string & Domain, vector<string> & result)
{
	string prev;
	string suf;
	if ( !Prev(Domain, prev) || !Suffix(Domain, suf) )
		return;
	int len = prev.size();	

	//缺字
	for ( int i = 0 ; i < len ; i++ )
	{
		string st;
		st = prev.substr(0, i);
		st += prev.substr(i + 1, len - i);
		st += suf;
		result.push_back(st);
	}
	
	//交换
	for ( int i = 0 ; i < len - 1 ; i++ )
	{
		string st = prev;
		char tmp;
		tmp = st[i];
		st[i] = st[i + 1];
		st[i + 1] = tmp;
		st += suf;
		result.push_back(st);
	}

	//去重
	result.erase(unique(result.begin(), result.end()), result.end());
}

bool Typos::Prev(const string & Domain, string & prev)
{
	int index = Domain.find_first_of(".");
	if ( index == -1 )
		return false;
	prev = Domain.substr(0, index);
	return true;
}

bool Typos::Suffix(const string & Domain, string & suf)
{
	int index = Domain.find_first_of(".");
	if ( index == -1 )
		return false;
	suf = Domain.substr(index, Domain.size() - index + 1);
	return true;
}
