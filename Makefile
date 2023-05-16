# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 11:16:24 by ael-asri          #+#    #+#              #
#    Updated: 2023/05/11 11:16:25 by ael-asri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRCS =  main.cpp \
		_config_parser/parsing.cpp\
		_socket/socket.cpp\
		_methodes/methods.cpp\
		_cgi/cgi.cpp\
		_request/request.cpp\
		_response/response.cpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	c++ $(FLAGS) $^ -o $@

# %.o : %.cpp
# 	@	c++ $(FLAGS) -c $(SRCS)

clean:
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re