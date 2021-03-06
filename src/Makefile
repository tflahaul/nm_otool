# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 22:08:10 by abrunet           #+#    #+#              #
#    Updated: 2020/11/26 16:16:50 by thflahau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=

#######   DIRECTORIES   #######
SRCDIR		=
OBJDIR		=
HEADERS		=	../include

DIRS		=	$(patsubst $(SRCDIR)%, $(OBJDIR)%, $(shell find $(SRCDIR) -type d))

##########   FLAGS   ##########
CCFLAGS		=	-Wall					\
			-Wextra					\
			-Werror					\
			-Wpadded				\
			-Wno-unused-result			\
			-Wsign-compare				\
			-Wunreachable-code			\
			-pedantic

INCFLAG		=	-I $(HEADERS)

#########   SOURCES   #########
SRCS		=	$(shell find $(SRCDIR) -type f -o -type l -name "*.c")
OBJS		=	$(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))
DEPENDS		=	${OBJS:.o=.d}

#########   COLORS   ##########
STD		=	\033[0m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m

##########   RULES   ##########
all	: $(NAME)

$(NAME)	: $(OBJS)
	@printf "$(YELLOW)%-45s$(STD)" "Building executable $@ ..."
	@$(CC) $(CCFLAGS) $(INCFLAG) $(OBJS) -o $@
	@echo "$(GREEN)DONE$(STD)"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(DIRS)
	@printf "%-45s" " > Compiling $* ..."
	@$(CC) $(CCFLAGS) -MMD $(INCFLAG) -c $< -o $@
	@echo '✓'

stripped: $(NAME)
	@printf "$(YELLOW)%-45s$(STD)" "Stripping executable $(NAME) ..."
	@strip $(NAME)
	@echo "$(GREEN)DONE$(STD)"

clean	:
	@if [ -d $(OBJDIR) ]; then \
		printf "$(YELLOW)%-45s$(STD)" "Removing objects ...";\
		/bin/rm -rf $(OBJDIR);\
		echo "$(GREEN)DONE$(STD)";\
	fi;

fclean	: clean
	@if [ -f $(NAME) ]; then \
		printf "$(YELLOW)%-45s$(STD)" "Removing $(NAME) ...";\
		/bin/rm -f $(NAME);\
		echo "$(GREEN)DONE$(STD)";\
	fi;

re	: fclean all

.PHONY	: all stripped clean fclean re
