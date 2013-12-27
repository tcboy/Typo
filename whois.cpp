#include "whois.h"

Whois::Whois()
{
	Server[".com"]		=	"whois.internic.net";
	Server[".net"]		=	"whois.internic.net";
	Server[".cn"]		=	"whois.cnnic.net.cn";
	Server[".com.cn"]	=	"whois.cnnic.net.cn";
}

bool Whois::isRegistered(const string & Domain, bool & isReg)
{
	string result;
	if ( !GetWhois(Domain, result) )
		return false;
	//for .com .net
	int rl = result.find("No match for");
	if ( rl > 0 )
	{
		isReg = false;
		return true;
	}
	
	//for .cn .com.cn
	rl = result.find("no matching record.");
	if ( rl > 0 )
	{
		isReg = false;
		return true;
	}

	isReg = true;
	return true;
}


bool Whois::GetWhois(const string & Domain, string & WhoisInfo)
{
	const int BUFSIZE = 1024;
	int bytes;
	char buf[BUFSIZE];
	string suf;
	if ( !Suffix(Domain, suf) )
		return false;

	string Dest;
	if ( Server.find(suf) == Server.end() )
		return false;

	if ( !GetIP(Server[suf], Dest) )
		return false;

	string result = "";

	struct sockaddr_in addr;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(WHOISPORT);
	addr.sin_addr.s_addr = inet_addr(Dest.c_str());

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if ( sockfd == -1 )
	{
		return false;
	}

	if(connect(sockfd,(struct sockaddr *)(&addr), sizeof(struct sockaddr)) == -1)
	{
		return false;
	}
	sprintf(buf, "%s\r\n", Domain.c_str() );
	if ( write(sockfd, buf, strlen(buf)) == -1)
	{
		return false;
	}
	

	while ( bytes = read(sockfd, buf, BUFSIZE - 1) )
	{
		buf[bytes] = '\0';
		result += buf;
	}
	close(sockfd);

	WhoisInfo = result;

	return true;

}

bool Whois::GetIP(const string & Domain, string & IP)
{
	struct hostent *hptr;
	struct in_addr in;
	struct sockaddr_in local_addr;

	if( (hptr = gethostbyname(Domain.c_str()) ) == NULL )
		return false;

	memcpy(&local_addr.sin_addr.s_addr, hptr->h_addr,4);
	in.s_addr = local_addr.sin_addr.s_addr;
	IP = inet_ntoa(in);
	return true;
}

bool Whois::Suffix(const string & Domain, string & suf)
{
	int index = Domain.find_first_of(".");
	if ( index == -1 )
		return false;
	suf = Domain.substr(index, Domain.size() - index + 1);
	return true;
}
