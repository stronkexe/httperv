/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:14:33 by ael-asri          #+#    #+#             */
/*   Updated: 2023/06/11 20:39:05 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../webserv.hpp"

std::string	generate_response_str(Response &_response)
{
	// std::cerr << "HALWA: [" << _response.content_length << "] - [" << num_to_str(_response.content_length) << "]" << std::endl;
	// std::cerr << "HTTP/1.1 "+ std::to_string(_response.status)+" "+_response.status_message+\
	// 				"\nContent-Type: "+_response.content_type+\
	// 				"\nContent-Length: "+num_to_str(_response.content_length)+\
	// 				"\nLocation: "+_response.location << std::endl;
	return "HTTP/1.1 "+ std::to_string(_response.status)+" "+_response.status_message+\
					"\nContent-Type: "+_response.content_type+\
					"\nContent-Length: "+num_to_str(_response.content_length)+\
					"\nLocation: "+_response.location+\
					"\n\n"+_response.body;
}


// size_t modifyFile(int fd, off_t offset, std::string newData) {
    
//     if (fd == -1) {
//         perror("open");
//         return;
//     }

//     // Move the file pointer to the desired position
//     off_t result = lseek(fd, offset, SEEK_SET);
//     if (result == -1) {
//         perror("lseek");
//         close(fd);
//         return;
//     }

//     // Write the new data at the specified position
//     size_t bytesWritten = write(fd, newData.c_str(), newData.size());
//     if (bytesWritten == -1) {
//         perror("write");
//         // close(fd);
//         return 0;
//     }

//     // Close the file
//     // close(fd);
// 	return bytesWritten;
// }


std::vector<int>	_get_ports( Parsing &_server )
{
    std::vector<int>    _ports;

	for (size_t i=0; i < _server.servers.size(); i++)
		_ports.push_back(_server.servers[i].listen_port);
	return _ports;
}

void	_init_l3alam( Request &_request, Response &_response)
{
	// Request
	// if (!_request.path.size())
	// {
		// char buffer[9999];
		// if (getcwd(buffer, sizeof(buffer)) != nullptr)
		// 	_request.path = std::string(buffer)+"/public";
		// else
		// 	_request.path = "";
	// }// char c[9999];
	// _request.path = std::string(getcwd(c, 9999));
	_request.body = "";
	_request.root = "";
	_request.method = "";
	_request.type = "";
	_request.uri = "";
	_request.autoindex = 0;
	_request.is_method_allowed = 0;
	_request.index.clear();
	_request.error_pages.clear();
	_request.cgi.clear();
	_request.redirection.clear();
	_request.headers.clear();

	// Response
	_response.status = 0;
	_response.content_length = 0;
	_response.body = "";
	_response.location = "";
	_response.status_message = "";

}

void	print_shit( Request &_request, Response &_response )
{
	std::cerr << "****************************************" << std::endl << "Request: " << std::endl;
	// std::cerr << "fd: " << _request.fd << std::endl;
	std::cerr << "uri: " << _request.uri << std::endl;
	std::cerr << "method: " << _request.method << std::endl;
	std::cerr << "type: " << _request.type << std::endl;
	std::cerr << "autoindex: " << _request.autoindex << std::endl;
	std::cerr << "path: " << _request.path << std::endl;
	for (size_t i=0; i<_request.index.size(); i++)
		std::cerr << "index[" << i << "]: " << _request.index[i] << std::endl;
	std::cerr << "root: " << _request.root << std::endl;
	for (size_t i=0; i<_request.redirection.size(); i++)
		std::cerr << "redirection[" << i << "]: " << _request.redirection[i] << std::endl;
	// for (size_t i=0; i<_request.cgi.size(); i++)
	// 	std::cerr << "cgi[" << i << "]: " << _request.cgi[i] << std::endl;
	// std::cerr << "client_body_upload: " << _request.client_body_upload << std::endl;
	// std::cerr << "headers: " << _request.headers << std::endl;
	std::cerr << "body: " << _request.body << std::endl;
	// for (size_t i=0; i<_request.error_pages.size(); i++)
	// 	std::cerr << "error_pages[" << i << "]: " << _request.error_pages[i] << std::endl;
	std::cerr << "is_method_allowed: " << _request.is_method_allowed << std::endl;
	std::cerr << "upload_path: " << _request.upload_path << std::endl;
	std::cerr << "upload_name: " << _request.upload_name << std::endl;
	std::cerr << "upload_content_type: " << _request.upload_content_type << std::endl;
	std::cerr << "upload_file_name: " << _request.upload_file_name << std::endl;
	std::cerr << "upload_data: " << _request.upload_data << std::endl;
	std::cerr << "boundary: " << _request.boundary << std::endl;

	std::cerr << "****************************************" << std::endl << "Response: " << std::endl;
	std::cerr << "status: " << _response.status << std::endl;
	std::cerr << "status_message: " << _response.status_message << std::endl;
	std::cerr << "content_length: " << _response.content_length << std::endl;
	std::cerr << "content_type: " << _response.content_type << std::endl;
	std::cerr << "path: " << _response.path << std::endl;
	std::cerr << "data: " << _response.data << std::endl;
	std::cerr << "body: " << _response.body << std::endl;
	std::cerr << "location: " << _response.location << std::endl;
	// std::cerr << "mims: " << _response.mims << std::endl;


}

// std::string replaceSubstring(std::string s, std::string new_str, int _pos, int wld7mida ) {
//     // std::string::size_type pos = 0;
//     // while ((pos = str.find(oldSubstr, pos)) != std::string::npos) {
//     //     str.replace(pos, oldSubstr.length(), newSubstr);
//     //     pos += newSubstr.length();
//     // }
// 	std::string t = s.substr(0, _pos);
// 	t+= "3231655\n";
// 	// std::cerr << ";;;;;;;;" << s.substr(0, _pos+new_str.size()+1) << ";;;;;;;;" << std::endl;
// 	t += s.substr(wld7mida, s.size());
// 	return t;
// }

std::string getSubstring(const std::string str, std::string::size_type startPos, std::string::size_type length) {
	std::cerr << "s.size : " << str.size()  << std::endl;

    if (startPos > str.length())
        return "";

    return str.substr(startPos, length);
}

void	_socket( Parsing &_server )
{
    int					_socket_fd;
    struct sockaddr_in	address;
    int					addrlen;
    int					default_port;
	// Request		request;
	// Response	response;
	std::vector<int>	_socket_fds;
	std::vector<Client> Clients;
	// struct timeval timeout;

	// timeout.tv_sec = 2;  // Set a timeout value (in seconds)
    // timeout.tv_usec = 0;
	
	// std::string			s;
	
	fd_set				_sockets, _current_sockets, _readfds, _writefds;
	

    
	addrlen = sizeof(address);
	default_port = _get_ports(_server)[0];

	// Initializing the sockets
	FD_ZERO(&_sockets);
	FD_ZERO(&_current_sockets);
	FD_ZERO(&_readfds);
	FD_ZERO(&_writefds);
	for (size_t i=0; i < _server.servers.size(); i++)
	{
		// Creating a socket for each server
		if ((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			print_error("socket creation failed!");
		
		// Binding the sockets of each server
		memset((char *)&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = htonl(INADDR_ANY);
		address.sin_port = htons(_server.servers[i].listen_port);

		int on = 1;
		if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)) < 0)
			print_error("port in use!");
		int v = fcntl(_socket_fd, F_SETFL, O_NONBLOCK);

		if ((bind(_socket_fd, (struct sockaddr *)&address, sizeof(address))) < 0)
			print_error("binding failed!");
		
		// Start listining..
		if ((listen(_socket_fd, SOMAXCONN)) < 0)
			print_error("listining failed!");
		
		
		FD_SET(_socket_fd, &_readfds);
		_socket_fds.push_back(_socket_fd);
		std::cerr << "fds: " << _socket_fd << std::endl;
		// _socket_fds.push_back(_socket_fd);
		// _socket_fds.push_back(_socket_fd);

	}
	int fd_size = _socket_fds[_socket_fds.size() - 1];
	int read_again = 0;
	int					_reading_lock=0, _writing_lock=0;
	std::string _test_buffer;
	// std::string s;
	// int					_wr = 0;
	// _init_l3alam(request, response);
	int old_data=0;
	int _first_time=0;
	int a_key=0;
	std::vector<int> accepted_shit;
    while (1)
    {
        std::cout << "listening ..." << std::endl;
		
		_sockets = _readfds;
		_current_sockets = _writefds;
		// std::cerr << "fd_size: " << fd_size << std::endl;
		if (select(fd_size + 1, &_sockets, &_current_sockets, NULL, NULL) < 0)
			print_error("error in select");
		
		// int x=0;
		int coming_socket;
		
		
		
		// _first_time=0;
		// while (x <= fd_size)
		
		for (int x=0; x <= fd_size; x++)
		{
			
			// std::cerr << "check return value of FD_ISSET: " << FD_ISSET(x, &_sockets) << ", at: " << x << std::endl;
			// std::cerr << "check return value of FD_ISSET current: " << FD_ISSET(x, &_current_sockets) << ", at: " << x << std::endl;
			if (FD_ISSET(x, &_sockets) || FD_ISSET(x, &_current_sockets))
			{
				// for (size_t f=0; f<_socket_fds.size(); f++)
				// 	std::cerr << "_socket_fds[" << f << "]: " << _socket_fds[f] << std::endl;
				// for (size_t f=0; f<accepted_shit.size(); f++)
				// 	std::cerr << "accepted_shit[" << f << "]: " << accepted_shit[f] << std::endl;
				// std::cerr << "hola mista: " << x << std::endl;

				if (std::find(_socket_fds.begin(), _socket_fds.end(), x) != _socket_fds.end() && !a_key)
				{
					// if (std::find(accepted_shit.begin(), accepted_shit.end(), x) != accepted_shit.end())
					// 	std::cerr << "----------------------------------------------------------" <<std::endl;
					std::cerr << "ACCEPTINGGGGGGGGGGGGGG" << x << std::endl;
					if ((coming_socket = accept(x, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
						print_error("acception failed!");
					// std::cerr << "coming_socket ::: " << coming_socket << std::endl;
					int d = fcntl(coming_socket, F_SETFL, O_NONBLOCK);
					FD_SET(coming_socket, &_readfds);
					if (coming_socket > fd_size)
						fd_size = coming_socket;
					// _first_time = 1;
					// _test_buffer = "";
					std::cerr << "x : " << x << " - coming_socket : " << coming_socket  << std::endl;
					accepted_shit.push_back(coming_socket);
					// std::cerr << "ggggg" << Clients.size() << std::endl;
					
					Clients.push_back(Client(coming_socket));
					// std::cerr << "\e[95msssssssssssssssssssssss: \e[0m" << Clients.size() << std::endl;
					// std::cerr << "x: " << x << std::endl;
					// x++;
					a_key=1;
					
					break ;
				}
				// std::cerr << "\e[94mClintes size : \e[0m" << Clients.size() << std::endl;
				for (size_t e=0; e<Clients.size(); e++)
				{
					
					// else if (std::find(_socket_fds.begin(), _socket_fds.end(), x) == _socket_fds.end() && _reading_lock)
					// std::cerr << "client[" << e << "]: " << Clients[e]._id << " - " << Clients[e]._read_status << " - " << Clients[e]._write_status << std::endl;
					if ((std::find(_socket_fds.begin(), _socket_fds.end(), Clients[e]._id) == _socket_fds.end()) &&  Clients[e]._read_status)
					{
						std::cerr << "READINGGGGGGGGGGGGGG" << std::endl;
						
						char				buffer[999999] = {0};
						// int data;

						if ((Clients[e].data = read(Clients[e]._id, buffer, 999999)) > 0)
						{
							for (int i=0; i<Clients[e].data; i++)
								Clients[e].buffer += buffer[i];
							Clients[e]._done_reading = 0;
							// std::cerr << "yyyyy" << Clients[e].data << std::endl;
							// break ;
						}
						else
						{
							Clients[e]._read_status = 0;
							Clients[e]._done_reading = 1;
						}
						FD_SET(Clients[e]._id, &_writefds);
					}
					// Request parsing
					std::cerr << Clients[e]._read_status << " ~ " << Clients[e]._read_status << " ~ " << Clients[e]._write_status << std::endl;
					if (Clients[e]._done_reading && !Clients[e]._read_status && !Clients[e]._write_status)
					{
						std::cerr << "PARSINGGGGGGGGGGGGGG" << std::endl;
						Server _s;
						_request(_server, _s, Clients[e]._request, Clients[e]._response, Clients[e].buffer);
	
						// Checking the method
						if (Clients[e]._request.is_method_allowed)
						{
							if (Clients[e]._request.method == "GET")
								_get(Clients[e], _s);
							else if (Clients[e]._request.method == "POST")
								_post(Clients[e], _s);
							else if (Clients[e]._request.method == "DELETE")
								_delete(Clients[e], _s);
						}
						else
							Clients[e]._response.status = 405;
						
						_response(Clients[e]);
						// std::cerr << "response type: " << Clients[e]._response.content_type << " response length: " << Clients[e]._response.content_length << std::endl;
						Clients[e].s = generate_response_str(Clients[e]._response);
						// FD_SET(Clients[e]._id, &_writefds);
						Clients[e]._write_status = 1;
						// std::cerr << "rddddddddddddddddddddd" << Clients[e].data << " - " << Clients[e]._done_reading << std::endl;
							// std::cerr << "status: " << Clients[e]._response.status << std::endl;
							
							
							// else
							// 	Clients[e]._read_status = 0;
							
							// _reading_lock = 0;
							// _writing_lock = 1;
							// std::cerr << "PATH: " << request.path << std::endl;
							// x++;
							// break;
							// FD_CLR(x, &_readfds);
							// std::cerr << "buffer: " << _test_buffer << std::endl;
							// break;
						// }
						// else
						// _get_res_body(Clients[e]);
						// old_data = data;
						

							// std::cerr << " Clients[e]._response.content_length : " << Clients[e]._response.content_type << std::endl;
						
						// std::cerr << "Clients[" << e << "]: " << Clients[e]._id << " - done_reading: " << Clients[e]._done_reading << " - file fd: " << Clients[e].fd_file << std::endl;
						// if (Clients[e]._done_reading)
						// 	Clients[e]._read_status = 0;
						
						
						
						
						// break;
						// request.fd = x;
						// FD_SET(x, &_readfds);
						// x++;
					}
					// else if (std::find(_socket_fds.begin(), _socket_fds.end(), x) == _socket_fds.end() && _writing_lock)
					if (std::find(_socket_fds.begin(), _socket_fds.end(), Clients[e]._id) == _socket_fds.end() && Clients[e]._write_status/* && !Clients[e]._done_writing*/)
					{
						std::cerr << "WRITINGGGGGGGGGGGGGG" << std::endl;
						if (Clients[e]._cgi_pid == waitpid(Clients[e]._cgi_pid, NULL, WNOHANG))
						{
							///// time to exit child for 30second
							std::cerr << "noooooooo" << std::endl;
							if (remove(Clients[e].file.c_str()))
               					 perror("remove file");
							Clients[e]._kill_pid = true;
							// std::cerr << "---------------------Clients[e]._kill_pid : " << Clients[e]._kill_pid << std::endl;	
							parent_process( Clients[e].body, Clients[e].pipe_fd);
							get_body(Clients[e]._response, Clients[e].body);
							// _get_res_body(Clients[e]);
							// std::cerr << " Body : " << Clients[e].body << std::endl;
        					Clients[e]._response.content_type = Clients[e]._response.mims[_get_ex(Clients[e]._request.path)];
							Clients[e].s = generate_response_str(Clients[e]._response);
						}
						if (Clients[e]._kill_pid)
						{
							// if (!Clients[e]._done_writing)
							// 	_get_res_body(Clients[e]);
							// }
							// else
							// {

							// }
							// long return_write = 0;
							// std::cerr << "wrrrrrrrrrrrrrrrrrrrrr: " << Clients[e]._response.content_length << std::endl;
							// if (Clisize of res_bodyents[e]._done_reading)
							// {
								// size_t _ctPos = s.find("Content-Length: ")+16, wld7mida=0, temp=_ctPos;
								
								// while (s[temp] != '\n' && s[temp] != '\0')
								// {
								// 	wld7mida++;
								// 	temp++;
								// }

								// s = replaceSubstring(s, std::to_string(Clients[e]._response.content_length), _ctPos, wld7mida);
								// std::cerr << ";;;;;;;;" << s.substr(0, _ctPos+wld7mida+1) << ";;;;;;;;" << std::endl;
								// std::cerr << "v: " << v << std::endl;
								// s=v;
								// _wr += return_write;
							// }
							// std::cerr << "response type: " << Clients[e]._response.content_type << std::endl;
							Clients[e].substring.clear();
							Clients[e].substring = getSubstring(Clients[e].s, Clients[e]._wr, Clients[e].s.length());
							std::cerr << "substring.size : " << Clients[e].substring.size()  << std::endl;
							// std::cerr << "s.size() : " << Clients[e].s.size() << " - substring.size() : " << Clients[e].substring.size() << std::endl;
							Clients[e].return_write=0;
							std::cerr << "Whyyy: " << Clients[e].substring.size() << std::endl;
							Clients[e].return_write = write(Clients[e]._id, Clients[e].substring.c_str(), Clients[e].substring.size());
							std::cerr <<"size of res_body: " << Clients[e]._response.body.size() << std::endl;

							////////////////////////////////
							// if (errno != 0) {
							// 	perror("Error"); // Print a descriptive error message
							// 	// Handle the error
							// }
							////////////////////////////////
							
							// std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
							// std::cerr << "response type: " << Clients[e].substring << std::endl;
							if (Clients[e].return_write > 0)
								Clients[e]._wr = Clients[e].return_write;
							std::cerr << "Clients[e]._wr : " <<  Clients[e]._wr << std::endl;
							// std::cerr << request.uri << " - Response: " << s.size() << " - Write return: " << _wr << " - reminds: " << s.size()-_wr << std::endl;
							if (Clients[e]._done_writing)
							{
							// std::cerr << "hlwaaaaaaaaaaaaaaaaaaaaaaaaa" << std::endl;
								std::cerr << "\e[96m###############\e[0m : fd_file : " << Clients[e]._id << std::endl;
								close(Clients[e]._id);
								FD_CLR(Clients[e]._id, &_readfds);
								FD_CLR(Clients[e]._id, &_writefds);
								// _writing_lock = 0;
								// Clients[e].init();
								std::vector<Client>::iterator it = Clients.begin();
								std::advance(it, e);
								Clients.erase(it);
								a_key = 0;
								// Clients[e]._write_status = 0;
								// Clients[e]._wr=0;
								// std::cerr << "l3zz: " << response.content_type << " - " << response.content_length << std::endl;
								// Clients[e].buffer = "";
								// _init_l3alam(Clients[e]._request, Clients[e]._response);
								// _first_time= 0;
								// print_shit(request, response);
								// x++;
							}
							else
							{
								_get_res_body(Clients[e]);
								Clients[e].s = generate_response_str(Clients[e]._response);
								std::cerr << "lblan dyal s: " << Clients[e].s.size() << std::endl;
							}
						// x++;
						}

					}
					// else
					// 	x++;

				}
				// x++;
				
			}
			// else
			// 	x++;
		}
	}
}
