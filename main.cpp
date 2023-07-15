/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:14:48 by ael-asri          #+#    #+#             */
/*   Updated: 2023/06/11 20:30:15 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

std::string _webserv_loc;

void f(int ac, char **av)
{
    
    std::string  str;
    Parsing _server;
    
    if (ac == 2)
    {
        _webserv_loc = getcwd(NULL, 0);
        _server.file = av[1];
        std::ifstream file(_server.file.c_str());
        while (std::getline(file, str))
            split_conf(_server.data, str);

        if (_server.data.empty())
            error("Nothing in configFile.conf");
        // 1- Config File:
        parss_info(_server);
        // print_data(_server);

        // 2- Socket connection
        _socket(_server);
    }
    else
        std::cerr << "invalid number of arguments!" << std::endl;
}

int main(int ac, char **av)
{
    f(ac, av);
    return 0;
}
