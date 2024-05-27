# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesar <cesar@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 12:18:49 by mpitot            #+#    #+#              #
#    Updated: 2024/05/25 08:59:48 by cesar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(MAIN)





DIR_MAIN	=	main/

SRC_MAIN	=	main.c	\
				exit_errors.c \
				construct_app.c \
				draw.c \

MAIN	=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))

