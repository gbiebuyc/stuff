# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/25 11:10:20 by gbiebuyc          #+#    #+#              #
#    Updated: 2020/02/25 11:10:21 by gbiebuyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = megaphone
OBJ = megaphone.o
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	clang++ -o $@ $^

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all