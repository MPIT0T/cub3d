# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 12:18:49 by mpitot            #+#    #+#              #
#    Updated: 2024/05/23 15:31:29 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(MAIN)		\
			$(PARSING)	\
			$(EXIT)


DIR_MAIN	=	main/
SRC_MAIN	=	main.c
MAIN	=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))

DIR_PARS	=	parsing/
SRC_PARS	=	parsing.c
PARSING		=	$(addprefix $(DIR_PARS), $(SRC_PARS))

DIR_EXIT	=	exit-management/
SRC_EXIT	=	exit.c	\
				free.c
EXIT		=	$(addprefix $(DIR_EXIT), $(SRC_EXIT))