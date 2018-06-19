# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/19 17:13:02 by pgritsen          #+#    #+#              #
#    Updated: 2018/06/19 17:23:22 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	avm

CC			=	g++

CFLAGS		=	-Wextra -Werror -Wall -g3

HDRSDIR		=	./includes

HDRS		=	$(addprefix $(HDRSDIR)/, avm.hpp)

SRCSDIR		=	./sources

SRCS		=	main.cpp

OBJDIR		=	./obj

CDIRS		=	./obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

INCLUDES	=	$(addprefix -I, $(HDRSDIR))

all: $(NAME)

$(NAME): $(CDIRS) $(OBJ) $(HDRS)
	@printf "\033[32m[Creating $(NAME)].......\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@printf "\033[32m[DONE]\033[0m\n"

$(CDIRS):
	@printf "\033[32m[Creating folder $@].......\033[0m"
	@mkdir -p $@
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : $(SRCSDIR)/%.cpp $(HDRS)
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "\033[32m[DONE]\033[0m\n"

clean:
	@printf "\033[31m[Cleaning $(NAME) object files].......\033[0m"
	@rm -rf $(OBJDIR)
	@printf "\033[31m[DONE]\033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[31m[Removing $(NAME)].......[DONE]\033[0m\n"

rebuild_message:
	@printf "\033[33m[Rebuild $(NAME)].......[START]\033[0m\n"

re:	rebuild_message fclean all
	@printf "\033[33m[Rebuild $(NAME)].......[END]\033[0m\n"

.NOTPARALLEL: all $(NAME) re
