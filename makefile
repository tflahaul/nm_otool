# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 22:08:10 by abrunet           #+#    #+#              #
#    Updated: 2020/09/08 19:26:48 by thflahau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_nm

#######   DIRECTORIES   #######
HDR		=	include
SRCDIR		=	src/new_nm
OBJDIR		=	obj

DIRS := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(shell find $(SRCDIR) -type d))

##########   FLAGS   ##########
CFLAGS		=	-Wall					\
			-Wextra					\
			-Werror					\
			-Wpadded				\
			-pedantic

INCFLAG		=	-I $(HDR)

#########   SOURCES   #########
SRCS		=	$(shell find $(SRCDIR) -type f -name "*.c")

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
	@$(CC) $(CFLAGS) $(INCFLAG) $(OBJS) -o $@
	@echo "$(GREEN)DONE$(STD)"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(DIRS)
	@printf "%-45s" " > Compiling $* ..."
	@$(CC) $(CFLAGS) -MMD $(INCFLAG) -c $< -o $@
	@echo '✓'

clean	:
	@/bin/rm -rf $(OBJDIR)

fclean	: clean
	@/bin/rm -rf $(NAME)

re	: fclean all

.PHONY	: all $(LIBFT) clean fclean re
