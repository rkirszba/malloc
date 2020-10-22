# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/20 16:46:57 by ezalos            #+#    #+#              #
#    Updated: 2020/10/22 17:30:33 by ldevelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra

#For developping purposes:
CFLAGS 		+= -fsanitize=address,undefined -g3

NAME=malloc

SRCS_DIR	= srcs/
HEAD_DIR	= includes/
OBJS_DIR	= objs/
OBJS_RBT_DIR	= objs/rbt/
$(shell mkdir -p $(OBJS_DIR))
$(shell mkdir -p $(OBJS_RBT_DIR))

INCS		= $(wildcard $(HEAD_DIR)*.h)
SRCS		= $(wildcard $(SRCS_DIR)*.c)
SRCS		+= $(wildcard $(SRCS_DIR)rbt/*.c)
OBJS		= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

HEADERS		= -I./$(HEAD_DIR)

##########################
##						##
##		  BASIC			##
##						##
##########################


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(HEADERS)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INCS) Makefile
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean
	$(MAKE) all

##########################
##						##
##		  PERSO			##
##						##
##########################

SUPPORTED_COMMANDS := run
SUPPORTS_MAKE_ARGS := $(findstring $(firstword $(MAKECMDGOALS)), $(SUPPORTED_COMMANDS))
ifneq "$(SUPPORTS_MAKE_ARGS)" ""
  COMMAND_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(COMMAND_ARGS):;@:)
endif

run: $(NAME)
	./$(NAME) $(COMMAND_ARGS)

prototypes:
	python3 .tmp/prototype_catcher.py srcs includes/prototypes_malloc.h malloc

REQUEST 		= 'read -p "Enter a commit message:	" pwd && echo $$pwd'
COMMIT_MESSAGE ?= $(shell bash -c $(REQUEST))
# $(GIT_VALID) || (echo -n "Are you sure? [y/N] " && read ans && [ $${ans:-N} = y ])
git :
		git add -A
		git status
		(echo -n "Are you sure? [y/N] " && read ans && [ $${ans:-N} = y ])
		git commit -m "$(COMMIT_MESSAGE)"
		git push

.PHONY: clean fclean
