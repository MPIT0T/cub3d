# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 16:12:25 by mpitot            #+#    #+#              #
#    Updated: 2024/05/23 14:17:52 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .config/srcs.mk
include .config/display.mk

OBJS	=	$(SRCS:%.c=${OBJ_D}%.o)

SRC_D	=	srcs/

OBJ_D	=	.objs/

HEAD	=	includes/

NAME	=	cub3d

CC		=	cc

FLAGS	=	-Wall -Wextra -Werror #-g3

all		:	mlx libft .internal_separate2 ${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.c Makefile includes/cub3d.h mlx_linux/mlx.h mlx_linux/mlx_int.h
	@$(call print_progress,$<)
	@${CC} ${FLAGS} -I/usr/include -Imlx_linux -I${HEAD} -c $< -o $@
	@$(call update_progress,$<)

${NAME}	:	${OBJ_D} ${OBJS} libft/libft.a
	@$(call print_progress,$(NAME))
	@${CC} ${FLAGS} ${OBJS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -L./libft -lft -Imlx_linux -I${HEAD} -o ${NAME}
	@$(eval CHANGED=1)
	@$(call erase)
	@$(call done_and_dusted,$(NAME))

${OBJ_D}:
	@mkdir -p ${OBJ_D}
	@mkdir -p ${OBJ_D}main

libft	:
	@make --no-print-directory -C ./libft

mlx		:
	@make --no-print-directory -C ./mlx_linux

clean	:
	@echo "Cleaning $(WHITE)[$(RED)libft$(WHITE)]...$(DEFAULT)"
	@make --no-print-directory -C ./libft clean
	@$(call separator)
	@echo "Cleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"

fclean	:
	@echo "F***ing-Cleaning $(WHITE)[$(RED)libft$(WHITE)]...$(DEFAULT)"
	@make --no-print-directory -C ./libft fclean
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

leak: all .internal_separate3
	@echo "$(MAGENTA)Valgrind $(WHITE)~ $(YELLOW)Flags:$(DEFAULT)"
	@echo "   $(YELLOW)-$(DEFAULT)Suppressed Readline Lib"
	@echo "   $(YELLOW)-$(DEFAULT)Show Leak Kinds"
	@echo "   $(YELLOW)-$(DEFAULT)Track FDs"
	@echo "   $(YELLOW)-$(DEFAULT)Show Mismatched Frees"
	@echo "   $(YELLOW)-$(DEFAULT)Read Variable Information"
	@echo "   $(YELLOW)-$(DEFAULT)Leak check"
	@echo "   $(YELLOW)-$(DEFAULT)Trace children"
	@$(call separator)
	@valgrind	--suppressions=.config/valgrind_ignore_rl.txt \
				--show-leak-kinds=all \
				--track-fds=yes \
				--show-mismatched-frees=yes \
				--read-var-info=yes \
				--leak-check=full \
				--trace-children=yes \
				./$(NAME)

re		:	fclean .internal_separate1 all

.PHONY	:	all clean fclean re libft leak

.NOTPARALLEL all:
	@if [ $(CHANGED) -eq 0 ]; then \
		echo "$(YELLOW)Nothing to be done for $(WHITE)[$(CYAN)$(NAME)$(WHITE)].$(DEFAULT)"; \
	fi

.internal_announce	:
	@echo "$(YELLOW)Compiling $(WHITE)[$(CYAN)minishell$(WHITE)]...$(DEFAULT)"
