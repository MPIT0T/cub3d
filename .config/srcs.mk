# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesar <cesar@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 12:18:49 by mpitot            #+#    #+#              #
#    Updated: 2024/06/05 09:47:46 by cesar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(MAIN)		\
			$(MINIMAP)	\
			$(PARSING)	\
			$(GHOSTS)	\
			$(EXIT)


DIR_MAIN	=	main/
SRC_MAIN	=	main.c	\
				exit_errors.c \
				construct_app.c \
				draw.c \
				key_events.c \
				moove.c \
				raycasting.c \
				wall_textures.c \
				horizontal_textures.c

MAIN	=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))

DIR_MINI	=	minimap/
SRC_MINI	=	minimap.c	\
				minimap_utils.c
MINIMAP	=	$(addprefix $(DIR_MINI), $(SRC_MINI))

DIR_GHOSTS	=	ghosts/
SRC_GHOSTS	=	spawn.c \
				create.c \
				pathfinding.c \
				target_player.c \
				spritecasting.c \
				sort.c
GHOSTS	=	$(addprefix $(DIR_GHOSTS), $(SRC_GHOSTS)) \

DIR_PARS	=	parsing/
SRC_PARS	=	parsing.c			\
				read_map_file.c		\
				info_extract.c		\
				info_verif.c		\
				map_parsing.c		\
				map_verif.c			\
				parsing_utils.c
PARSING		=	$(addprefix $(DIR_PARS), $(SRC_PARS))

DIR_EXIT	=	exit-management/
SRC_EXIT	=	exit.c	\
				free.c
EXIT		=	$(addprefix $(DIR_EXIT), $(SRC_EXIT))