# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 12:18:49 by mpitot            #+#    #+#              #
#    Updated: 2024/06/13 10:39:03 by cefuente         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	$(MAIN)					\
				$(MLXX)					\
				$(GUI)					\
				$(PARSING)				\
				$(RAYCASTING)			\
				$(GHOSTS)				\
				$(EXIT)

SRC_MAIN	=	main.c

SRC_MLXX	=	construct_app.c			\
				draw.c					\
				key_events.c			\
				mlx_things.c

SRC_GUI		=	minimap.c				\
				minimap_utils.c			\
				doors.c

SRC_GHOSTS	=	spawn.c					\
				create.c				\
				pathfinding.c			\
				spritecasting.c			\
				sort.c

SRC_PARS	=	parsing.c				\
				read_map_file.c			\
				info_extract.c			\
				info_verif.c			\
				map_parsing.c			\
				map_verif.c				\
				parsing_utils.c			\
				set_start_vars.c

SRC_RAY		=	horizontal_textures.c	\
				moove.c					\
				rotate.c				\
				raycasting.c			\
				wall_textures.c			\
				rotation.c

SRC_EXIT	=	exit.c					\
				free.c

DIR_MAIN	=	main/
DIR_MLXX	=	mlx/
DIR_GUI		=	gui/
DIR_DOORS	=	doors/
DIR_GHOSTS	=	ghosts/
DIR_PARS	=	parsing/
DIR_RAY		=	raycasting/
DIR_EXIT	=	exit-management/

MAIN		=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))
MLXX			=	$(addprefix $(DIR_MLXX), $(SRC_MLXX))
GUI			=	$(addprefix $(DIR_GUI), $(SRC_GUI))
DOORS		=	$(addprefix $(DIR_DOORS), $(SRC_DOORS))
GHOSTS		=	$(addprefix $(DIR_GHOSTS), $(SRC_GHOSTS))
PARSING		=	$(addprefix $(DIR_PARS), $(SRC_PARS))
RAYCASTING	=	$(addprefix $(DIR_RAY), $(SRC_RAY))
EXIT		=	$(addprefix $(DIR_EXIT), $(SRC_EXIT))
