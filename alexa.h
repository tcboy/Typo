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

#define	HTTPPORT 80

using namespace std;

class Alexa
{
public:
	Alexa();
	bool GetRank(const string & Domain, int & Rank);
	bool GetData(const string & server, const string & url, string & Data);

private:
	bool GetIP(const string & Domain, string & IP);
	string url;
	string server;
};
