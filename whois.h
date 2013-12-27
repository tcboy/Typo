#include <netinet/in.h>		// for sockaddr_in
#include <sys/types.h>		// for socket
#include <sys/socket.h>		// for socket
#include <arpa/inet.h>
#include <unistd.h> 
#include <netdb.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>

#define	WHOISPORT 43

using namespace std;

class Whois
{
public:
	Whois();
	bool isRegistered(const string & Domain, bool & isReg);
	bool GetWhois(const string & Domain, string & WhoisInfo);

private:
	map<string, string> Server;
	bool GetIP(const string & Domain, string & IP);
	bool Suffix(const string & Domain, string & suf);
};
