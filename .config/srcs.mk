# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 12:18:49 by mpitot            #+#    #+#              #
#    Updated: 2024/05/28 11:52:19 by cefuente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(MAIN)





DIR_MAIN	=	main/

SRC_MAIN	=	main.c	\
				exit_errors.c \
				construct_app.c \
				draw.c \
				key_events.c \
				moove.c \
				raycasting.c

MAIN	=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))

