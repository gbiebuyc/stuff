# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/29 22:38:27 by gbiebuyc          #+#    #+#              #
#    Updated: 2020/02/29 22:38:27 by gbiebuyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
SRC = main.cpp
OBJ = $(addprefix ./obj/, $(SRC:.cpp=.o))
CXX	= clang++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98
.PHONY: all clean fclean re

all: ./obj $(NAME)

./obj:
	mkdir -p ./obj

./obj/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CXX) -o $@ $^

clean:
	rm -rf ./obj

fclean: clean
	rm -f $(NAME)

re: fclean all
