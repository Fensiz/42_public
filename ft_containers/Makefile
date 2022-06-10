# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgreenbl <bgreenbl@student.21-school.      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 00:42:18 by bgreenbl          #+#    #+#              #
#    Updated: 2022/01/07 23:50:24 by bgreenbl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft.out
	
CC			=	clang++
CXXFLAGS	=	-Wall -Werror -Wextra -MMD -pedantic

SRC			=	main.cpp

all			:	ft

ft			:	ft.out

std			:	std.out
	
ft.out		:	ft.obj
	$(CC) ft.obj -o ft.out
	
std.out		:	std.obj
	$(CC) std.obj -o std.out
	
ft.obj		:	main.cpp
	$(CC) $(CXXFLAGS) -c $(SRC) -o ft.obj -D lib=ft
	
std.obj		:	main.cpp
	$(CC) $(CXXFLAGS) -c $(SRC) -o std.obj -D lib=std
	
clean		:
	rm -f ft.obj ft.dep std.obj std.dep
	
fclean		:	clean
	rm -f ft.out std.out
	
re			:	fclean all

test_ft		:
	./ft.out
	
test_std	:
	./std.out

.PHONY		:	all clean fclean re ft std

-include $(DEP)
