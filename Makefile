# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksoto <ksoto@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/26 00:08:57 by ksoto             #+#    #+#              #
#    Updated: 2021/08/26 14:10:46 by ksoto            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SERVER		=	server
CLIENT		=	client

#***************** LIB ********************#
# General
INC			=	./includes/

# Lib
LIB			=	./libft/
INCFT		=	./libft/include/

INCLUDE		=	-I $(INC) -I $(INCFT)

#***************** DIR ********************#

DIRSRC		=	./srcs/
DIRFT		=	$(LIB)/src/

#***************** SRC ********************#

SRC			=	client.c server.c

SRCS		=	$(SRC)

#***************** DEPS *******************#

DIROBJ		=	./depo/

OAUX		=	$(SRCS:%=$(DIROBJ)%)
DEPS		=	$(OAUX:.c=.d)
OBJS		=	$(OAUX:.c=.o)

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e
BOLD		=	"\e[1m"
BLINK		=	"\e[5m"
RED			=	"\e[38;2;255;0;0m"
GREEN		=	"\e[92m"
BLUE		=	"\e[34m"
YELLOW		=	"\e[33m"
E0M			=	"\e[0m"

#************************ DEPS COMPILATION *************************

%.o		:		../$(DIRSRC)/%.c
				@printf $(GREEN)"Generating libftprintf objects... %-33.33s\r" $@
				@$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

#************************ MAIN COMPILATION *************************

$(SERVER)	:	ftlib $(OBJS)
				@$(ECHO)
				@mv libft.a $(SERVER)
				@ar rcs $(SERVER) $(OBJS)
				@ranlib $(SERVER)
				@$(ECHO) $(BOLD)$(GREEN)'> server compiled'$(E0M)

$(CLIENT)	:	ftlib $(OBJS)
				@$(ECHO)
				@mv libft.a $(CLIENT)
				@ar rcs $(CLIENT) $(OBJS)
				@ranlib $(CLIENT)
				@$(ECHO) $(BOLD)$(GREEN)'> client compiled'$(E0M)

clean	:
				@($(RM) $(OBJS)) 
				@($(RM) $(DEPS))
				@(cd $(LIB) && $(MAKE) clean)
				@$(ECHO) $(BOLD)$(RED)'> directory cleaned'$(E0M)

all		:		ftlib $(OBJS)
				@$(CC) $(CFLAGS) ./srcs/server.c libft/libft.a -o $(SERVER)
				@$(CC) $(CFLAGS) ./srcs/client.c libft/libft.a -o $(CLIENT)
				@$(ECHO) $(BOLD)$(GREEN)'> server compiled'$(E0M)
				@$(ECHO) $(BOLD)$(GREEN)'> client compiled'$(E0M)

bonus	:		$(NAME)

fclean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@$(RM) $(SERVER)
				@$(RM) $(CLIENT)
				@(cd $(LIB) && $(MAKE) fclean)
				@$(ECHO) $(BOLD)$(RED)'> executable removed'$(E0M)

re		:		fclean all

bonus	: 		all

ftlib	:
				@(cd $(LIB) && $(MAKE))

.PHONY	:		all bonus clean fclean re ftlib


-include $(DEPS)
