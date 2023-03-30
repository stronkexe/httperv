
#include "webserv.hpp"

typedef struct s_server
{
	std::string port;
	std::string host;
	struct s_server *next;
}	t_server;

void _get_ports( t_server *_server, std::string* _servers, int c )
{
	for (int i=0; i< c; i++)
	{
		std::string port="";
		int port_index = _servers[i].find("listen");
		int x=port_index+6;
		while (_servers[i][x] == ' ')
			x++;
		while (_servers[i][x] != ';')
		{
			port+=_servers[i][x++];
			// x++;
		}
		_server[i].port = port;
	}
}

void _get_hosts( t_server *_server, std::string* _servers, int c )
{
	for (int i=0; i< c; i++)
	{
		std::string host="";
		int host_index = _servers[i].find("server_name");
		int x=host_index+11;
		while (_servers[i][x] == ' ')
			x++;
		while (_servers[i][x] != ';')
		{
			host+=_servers[i][x++];
			// y++;
		}
		_server[i].host = host;
	}
}

void _parser( std::string s )
{
	int count = 0;
	std::string str= "server {";
    size_t nPos = s.find(str, 0); 
	while (nPos != std::string::npos)
	{
		count++;
		nPos = s.find(str, nPos + str.size());
	}

	std::string _servers[count];
	int i=0;
	int c=0;

	while (s[i])
	{
		int index = (s.substr(i, s.length())).find("server {")+9;
		i += index;
		while (s[i] && s[i] != '}')
		{
			if (s[i] == '{')
			{
				i++;
				while (s[i] != '}' && s[i])
				{
					_servers[c] += s[i];
					i++;
				}
				i++;
			}
			else
			{
				_servers[c] += s[i];
				i++;
			}
		}
		c++;
		if (c == count)
			break;
	}


	// allocating and constracting the servers
	t_server _server[count];

	_get_ports(_server, _servers, c);
	_get_hosts(_server, _servers, c);
	// for (int i=0; i< c; i++)
	// {
	// 	// std::string port="";
	// 	// int port_index = _servers[i].find("listen");
	// 	// int x=port_index+6;
	// 	// while (_servers[i][x] == ' ')
	// 	// 	x++;
	// 	// while (_servers[i][x] != ';')
	// 	// {
	// 	// 	port+=_servers[i][x];
	// 	// 	x++;
	// 	// }


	// 	// std::string host="";
	// 	// int host_index = _servers[i].find("server_name");
	// 	// int y=host_index+11;
	// 	// while (_servers[i][y] == ' ')
	// 	// 	y++;
	// 	// while (_servers[i][y] != ';')
	// 	// {
	// 	// 	host+=_servers[i][y];
	// 	// 	y++;
	// 	// }
		
	// 	// std::cout << i << " - " << _servers[i]  << std::endl;
	// 	// _server[i].port = port;
	// 	_server[i].host = host;
	// 	// std::cerr << "port " << _server[i].port << std::endl;
	// 	// std::cerr << "host " << _server[i].host << std::endl;
	// }
	for (int i=0; i<count; i++)
	{
		std::cout << _server[i].host << std::endl;
		std::cout << _server[i].port << std::endl;
	}

	// while (s[i])
	// {
	// 	// if (s[i] == '{')
	// 	// {
	// 	// 	while (s[i] && s[i] != '}')
	// 	// 	{
	// 	// 		std::cout << s[i];
	// 	// 		i++;
	// 	// 	}
	// 	// }
	// 	std::cout << s[i];
	// 	i++;
	// }
	// and the parsing begins!!
	// if (strcmp())
}