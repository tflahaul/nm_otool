# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/26 16:19:12 by thflahau          #+#    #+#              #
#    Updated: 2020/11/26 16:31:18 by thflahau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM		=	../ft_nm
NM_SRCDIR	=	nm
NM_OBJS		=	objn

OTOOL		=	../ft_otool
OTOOL_SRCDIR	=	otool
OTOOL_OBJS	=	objo

all	: nm otool

stripped:
	@make stripped -C src NAME=$(NM) SRCDIR=$(NM_SRCDIR) OBJDIR=$(NM_OBJS)
	@make stripped -C src NAME=$(OTOOL) SRCDIR=$(OTOOL_SRCDIR) OBJDIR=$(OTOOL_OBJS)

nm	:
	@make -C src NAME=$(NM) SRCDIR=$(NM_SRCDIR) OBJDIR=$(NM_OBJS)

otool	:
	@make -C src NAME=$(OTOOL) SRCDIR=$(OTOOL_SRCDIR) OBJDIR=$(OTOOL_OBJS)

clean	:
	@make clean -C src NAME=$(NM) SRCDIR=$(NM_SRCDIR) OBJDIR=$(NM_OBJS)
	@make clean -C src NAME=$(OTOOL) SRCDIR=$(OTOOL_SRCDIR) OBJDIR=$(OTOOL_OBJS)

fclean	: clean
	@make fclean -C src NAME=$(NM) SRCDIR=$(NM_SRCDIR) OBJDIR=$(NM_OBJS)
	@make fclean -C src NAME=$(OTOOL) SRCDIR=$(OTOOL_SRCDIR) OBJDIR=$(OTOOL_OBJS)

re	: fclean all

.PHONY	: all nm otool clean fclean re
