# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cesar <cesar@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 16:12:25 by mpitot            #+#    #+#              #
#    Updated: 2024/06/05 01:21:58 by cesar            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .config/srcs.mk
include .config/display.mk

OBJS	=	$(SRCS:%.c=${OBJ_D}%.o)

SRC_D	=	srcs/

OBJ_D	=	.objs/

HEAD	=	includes/

NAME	=	cub3D

CC		=	cc

FLAGS	=	-Wall -Wextra -Werror -g3

MLX				= 	mlx_linux/libmlx_Linux.a
MLX_DIR			=	mlx_linux/
MLX_LINKS		=	mlx_Linux

USRLIB_DIR		=	/usr/lib/
USRLIB_LINKS	=	-lXext -lX11 -lm -lz

all		:	mlx libft .internal_separate2 ${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.c Makefile includes/cub3D.h mlx_linux/mlx.h mlx_linux/mlx_int.h
	@$(call print_progress,$<)
	@${CC} ${FLAGS} -I${HEAD} -I${MLX_DIR} -I${USRLIB_DIR} -c $< -o $@
	@$(call update_progress,$<)

${NAME}	:	${OBJ_D} ${OBJS} libft/libft.a
	@$(call print_progress,$(NAME))
	@${CC} ${FLAGS} ${OBJS} -L./libft -lft -I${HEAD} -L${MLX_DIR} -l${MLX_LINKS} -I${USRLIB_DIR} ${USRLIB_LINKS} -o ${NAME}
	@$(eval CHANGED=1)
	@$(call erase)
	@$(call done_and_dusted,$(NAME))

${OBJ_D}:
	@mkdir -p ${OBJ_D}
	@mkdir -p ${OBJ_D}main
	@mkdir -p ${OBJ_D}ghosts
	@mkdir -p ${OBJ_D}ghosts/sort
	@mkdir -p ${OBJ_D}minimap
	@mkdir -p ${OBJ_D}doors
	@mkdir -p ${OBJ_D}parsing
	@mkdir -p ${OBJ_D}exit-management

mlx		:
	@make --no-print-directory -C $(MLX_DIR)

libft	:
	@make --no-print-directory -C ./libft

clean	:
	@echo "Cleaning $(WHITE)[$(RED)libft$(WHITE)]...$(DEFAULT)"
	@make --no-print-directory -C ./libft clean
	@make --no-print-directory -C ${MLX_DIR} clean
	@$(call separator)
	@echo "Cleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"

fclean	:
	@echo "F***ing-Cleaning $(WHITE)[$(RED)libft$(WHITE)]...$(DEFAULT)"
	@make --no-print-directory -C ./libft fclean
	@make --no-print-directory -C ${MLX_DIR} clean
	@$(call separator)
	@echo "F***ing-Cleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"
	@rm -f ${NAME}
	@echo "$(WHITE)[$(RED)$(NAME)$(WHITE)] $(RED)deleted.$(DEFAULT)"

sanitize	: fclean mlx libft .internal_separate2 ${OBJ_D} ${OBJS} libft/libft.a
	@$(call print_progress,$(NAME))
	@${CC} ${FLAGS} ${OBJS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L./libft -lft -I${HEAD} -o ${NAME} -fsanitize=address -g3
	@$(eval CHANGED=1)
	@$(call erase)
	@$(call done_and_dusted,$(NAME))

ARGS = "maps/map_subject.cub"

leak: all .internal_separate3
	@echo "$(MAGENTA)Valgrind $(WHITE)~ $(YELLOW)Flags:$(DEFAULT)"
	@echo "   $(YELLOW)-$(DEFAULT)Show Leak Kinds"
	@echo "   $(YELLOW)-$(DEFAULT)Track FDs"
	@echo "   $(YELLOW)-$(DEFAULT)Show Mismatched Frees"
	@echo "   $(YELLOW)-$(DEFAULT)Read Variable Information"
	@echo "   $(YELLOW)-$(DEFAULT)Leak check"
	@echo "   $(YELLOW)-$(DEFAULT)Trace children"
	@$(call separator)
	@valgrind	--show-leak-kinds=all \
				--track-fds=yes \
				--show-mismatched-frees=yes \
				--read-var-info=yes \
				--leak-check=full \
				--trace-children=yes \
				./$(NAME) $(ARGS)

re		:	fclean .internal_separate1 all

.PHONY	:	all clean fclean re libft mlx leak

.NOTPARALLEL all:
	@if [ $(CHANGED) -eq 0 ]; then \
		echo "$(YELLOW)Nothing to be done for $(WHITE)[$(CYAN)$(NAME)$(WHITE)].$(DEFAULT)"; \
	fi

.internal_announce	:
	@echo "$(YELLOW)Compiling $(WHITE)[$(CYAN)minishell$(WHITE)]...$(DEFAULT)"
