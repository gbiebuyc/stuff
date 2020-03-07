# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/21 15:08:28 by gbiebuyc          #+#    #+#              #
#    Updated: 2020/01/21 17:03:26 by gbiebuyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean re

CXXFLAGS = -Wall -Wextra

snake: ./src/*
	g++ $(CXXFLAGS) -o $@ $^

clean:
	rm -rf snake

re: clean snake
