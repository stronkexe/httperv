/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:15:55 by ael-asri          #+#    #+#             */
/*   Updated: 2023/06/11 20:29:24 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fstream>
#include <map>
#include <fcntl.h>
#include <sstream>
#include <vector>
#include <iterator>
#include <map>
#include <sys/stat.h>

#define _POSIX_SOURCE
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#undef _POSIX_SOURCE
#include <stdio.h>

struct error_page
{
    std::vector<int>  error_status;
    std::string       path;

	error_page &operator= (const error_page & err)
	{
		this->path = err.path;
		this->error_status = err.error_status;
		return *this;
	}
};

struct CGI
{
    std::string		extension;
    std::string     path;

	CGI &operator= (const CGI & _cgi)
	{
		this->path = _cgi.path;
		this->extension = _cgi.extension;
		return *this;
	}
};

struct Redirection
{
    size_t            return_status;
    std::string       path;

	Redirection& operator=(const Redirection& red)
	{
		this->return_status = red.return_status;
		this->path = red.path;
		return *this;
	}
};

struct Location
{
    bool						autoindex;
    std::string					root_location, name, uploadDir;
    std::vector<std::string> 	index;
    std::vector<std::string>	allows_methods;
	Redirection					redirection;
    std::vector<CGI>			cgi_pass;

	Location& operator=(const Location& loc)
	{
		this->name = loc.name;
		this->root_location = loc.root_location;
		this->autoindex = loc.autoindex;
		this->index = loc.index;
		this->allows_methods = loc.allows_methods;
		this->redirection = loc.redirection;
		this->cgi_pass = loc.cgi_pass;
		this->uploadDir = loc.uploadDir;
		return *this;
	}
};
    

struct Server
{
    std::string					name, root_location, client_max_body_size;
    std::vector<std::string>	index;
    std::vector<Location>		locations;
    std::vector<error_page>		errors;
	Redirection					redirection;
    size_t						listen_port;

	Server& operator=(const Server& serv) {
		this->name = serv.name;
		this->root_location = serv.root_location;
		this->client_max_body_size = serv.client_max_body_size;
		this->listen_port = serv.listen_port;
		this->index = serv.index;
		this->locations = serv.locations;
		this->redirection = serv.redirection;
		this->errors = serv.errors;
    return *this;
  }
};

struct Parsing
{
	std::string					file;
	std::vector<std::string>	data;
	std::vector<Server>			servers;
};

class Request
{
	public :

		int									fd;
		std::string							uri;
		std::string							method;
		std::string 						type;
		int									autoindex;
		std::string							path;
		std::map<std::string, std::string>	paths;
		std::vector<std::string>			index;
		std::string							root;
		std::vector<std::string>			redirection;
		std::vector<CGI>					cgi;
		char								**env;
		int									client_body_upload;
		std::map<std::string, std::string>	headers;
		std::string							body;
		std::vector<error_page>				error_pages;
		int									is_method_allowed;
		std::string							upload_path;

		// Uploads
		std::string	upload_name;
		std::string	upload_content_type;
		std::string	upload_file_name;
		std::string	upload_data;
		std::string	boundary;

		Request() {
			std::cerr << "Constructor Request" << std::endl;
			fd = 0;
			autoindex = 0;
			client_body_upload = 0;
			is_method_allowed = 0;
			
			env = new char*[11];
			for (int i = 0; i < 10; i++)
				env[i] = NULL;
		};
		Request(const Request & req) { *this = req;};

		Request& operator=(  const  Request & req) {
			fd = req.fd;
			uri = req.uri;
			method = req.method;
			type = req.type;
			autoindex = req.autoindex;
			path = req.path;
			paths = req.paths;
			index = req.index;
			root = req.root;
			redirection = req.redirection;
			cgi = req.cgi;
			client_body_upload = req.client_body_upload;
			headers = req.headers;
			body = req.body;
			error_pages = req.error_pages;
			is_method_allowed = req.is_method_allowed;
			upload_path = req.upload_path;

		// Uploads
			upload_name = req.upload_name;
			upload_content_type = req.upload_content_type;
			upload_file_name = req.upload_file_name;
			upload_data = req.upload_data;
			boundary = req.boundary;

			for (int i = 0; i < 10; i++)
			{
				// std::cerr<< "^^^^^^^^^^^^^" << std::endl;
				if (env[i])
					delete env[i];
				if (req.env[i])
					env[i] = strdup(req.env[i]);
				else
					env[i] = NULL;
			}

			return *this;
		};
		~Request() {
			std::cerr << "Destructor Request" << std::endl;
			for (int i = 0; i < 10; i++)
			{
				if (env[i])
					delete env[i];
			}
			delete[] env;
		};

};

class Response
{
	public:

		int			status;
		std::string status_message;
		int			content_length;
		std::string content_type;
		std::string path;
		std::string data;
		std::string body;
		std::string	location;
		std::map<std::string, std::string>	mims;
		Response() {
			std::cerr << "constructor Response" << std::endl;

			status = 0;
			content_length = 0;
		};
		Response(const Response & res) { *this = res; };

		Response& operator=(  const Response & res) { 
			status = res.status;
			status_message = res.status_message;
			content_length = res.content_length;
			content_type = res.content_type;
			path = res.path;
			data = res.data;
			body = res.body;
			location = res.location;
			mims = res.mims;
			return *this; 
		};

		~Response() {std::cerr << "Destructor Response" << std::endl;};

};


class Client {

	public:

		int		_id;
		pid_t	_cgi_pid;
		bool	_kill_pid;
		int		pipe_fd[2];
		std::string		file, body;
		int		_read_status;
		int		_write_status;
		std::string	buffer;

		Request		_request;
		Response	_response;

		Client( ) {std::cerr << "constructor Client" << std::endl;};

		Client(const int id ) {
			std::cerr << "constructor Client" << std::endl;
			_id = id;
			_read_status = 1;
			_write_status = 0;
			_cgi_pid = -2;
			_kill_pid = true;
		};

		Client(const Client & client) { *this = client; };

		Client& operator= (const Client & client) { 
			_id = client._id;
			_read_status = client._read_status;
			_write_status = client._write_status;
			_cgi_pid = client._cgi_pid;
			_kill_pid = client._kill_pid;
			std::cerr << "++++++++++" << std::endl;
			_request = client._request;
			_response = client._response;
			return *this; 
		};
		~Client() {std::cerr << "Destructor Client" << std::endl;};

		bool operator ==(Client &b ) { return _id == b._id; }

		// void init( void ) {

		// 	_read_status = 0;
		// 	_write_status = 0;
		// 	_cgi_pid = -2;
		// 	_kill_pid = true;
		// 	buffer = "";

		// };

};

// Socket
void	_socket( Parsing &_server );

//cgi
std::string generateRandomString(int length);
void parent_process(std::string &result, int *pipe_fd);
void get_body(Response & _response, std::string & result);

// Methodes
void	_get( Client & _client, Server &_server );
void	_post( Client & _client, Server &_server );
void	_delete( Client & _client ,Server &_server );

// CGI
void	_cgi( Client & _client , Server &_server );

// Request
void	_request( Parsing &_server, Server &_s, Request &_request, Response &_response, std::string s );

// Response
void		_response( Client & _client );
int			_get_res_body( Client & _client );
void    	get_indexed_file_data( Request &_request, Response &_response, std::string path );
std::string	_get_ex( std::string _file_name );

// Utils
void	print_error(std::string s);

// Parsing
void	error(std::string err);
int		str_to_num(std::string str);
void	parss_info(Parsing &parss);
void	info_autoindex(Location &loc, std::string &str);
void	split_conf(std::vector<std::string> &data, std::string str);
void	info_err_status(std::vector<error_page> &errors, std::vector<std::string>::iterator &it);
void	info_location(std::vector<Location> &locations, std::vector<std::string>::iterator &it);
void	print_data(Parsing &parss);
std::vector<std::string>	info_(std::vector<std::string>::iterator &it);

#endif