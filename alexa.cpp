#include "alexa.h"

Alexa::Alexa()
{
	server = "data.alexa.com";
	url = "/data/+wQ411en8000lA?cli=10&dat=snba&ver=7.0&cdt=alx_vw=20&wid=12206&act=00000000000&ss=1680x1050&bw=964&t=0&ttl=35371&vis=1&rq=4&url=";
}

bool Alexa::GetIP(const string & Domain, string & IP)
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

bool Alexa::GetData(const string & server, const string & url, string & Data)
{
	const int BUFSIZE = 1024;
	int bytes;
	char buf[BUFSIZE];

	string Dest;

	if ( !GetIP(server, Dest) )
		return false;

	string result = "";

	struct sockaddr_in addr;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(HTTPPORT);
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

	string header = "";
	header += "GET " + url + " ";
	header += "HTTP/1.1\r\n";
	header += "Accept: */*\r\n";
	header += "Accept-Language: zh-cn\r\n";
	header += "User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022; InfoPath.2)\r\n";
	header += "Host: " + server + "\r\n";
	header += "Connection: close\r\n";
	header += "\r\n\r\n";

	sprintf(buf, "%s", header.c_str());

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

	Data = result;

	return true;
}

bool Alexa::GetRank(const string & Domain, int & Rank)
{
	string Data;
	if ( !GetData(server, url + Domain, Data) )
		return false;
	
	int rl = Data.find("200 OK");
	if ( rl == -1 )
		return false;
	
	rl = Data.find("POPULARITY");
	if ( rl == -1 )
	{
		Rank = -1;
		return true;
	}
	
	rl = Data.find("TEXT=\"", rl);
	if ( rl == -1 )
	{
		Rank = -1;
		return true;
	}
	rl = rl + 6;
	if ( rl >= Data.size() )
	{
		Rank = -1;
		return true;
	}

	int pos = Data.find("\"", rl) - 1;
	if ( pos >= Data.size() )
	{
		Rank = -1;
		return true;
	}

	string num = Data.substr(rl, pos - rl + 1);
	Rank = atoi(num.c_str());
	
	if ( Rank > 0 )
	{
		return true;
	}
	return false;
}
