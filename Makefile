# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 17:25:21 by vvaucoul          #+#    #+#              #
#    Updated: 2022/05/27 12:43:06 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lemipc
NAME_VISUALIZER = lemipc-visualizer
NAME_PROCESSUS = lemipc-processus

LIBFT = libft
OWN_LIBFT_NAME = 42_PCC_LIBFT

MLX = libmlx
LIBMLX = libmlx

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror
IFLAGS = -I ./$(INCLUDE_PATH) -I ./$(LIBFT_PATH)/$(INCLUDE_PATH)
LIBFLAGS = -I ./$(LIBFT)/$(INCLUDE_PATH)/ -L ./$(LIB_DIR) ./$(LIB_DIR)/$(LIBFT_PATH).a 
MLX_FLAGS = ./$(MLX_DIR)/$(LIBMLX).a -lglfw  -lmlx -lXext -lX11 -lXft -lglfw

SRCS =		srcs/game/game_handler.c \
			srcs/game/game_display_board.c \
			srcs/game/game.c \
			srcs/ia/ia_movements.c \
			srcs/ia/ia_death.c \
			srcs/ia/ia.c \
			srcs/meta_host/meta_host.c \
			srcs/meta_host/meta_host_init_map.c \
			srcs/main.c \
			srcs/signals/signals.c \
			srcs/utils/utils.c \
			srcs/arguments/check_arguments.c \
			srcs/meta_client/meta_client.c

SRCS_P =	utils/processus/create_processus.c
SRCS_V =	srcs-visualizer/mlx_mode.c \
			srcs-visualizer/main.c \
			srcs-visualizer/bash_mode.c \
			srcs-visualizer/init.c \
			srcs-visualizer/utils.c

SRCS_PATH = srcs
SRCS_PROCESSUS_PATH = utils/processus 
SRCS_VISUALIZER_PATH = srcs-visualizer
INCLUDE_PATH = includes
OBJS_DIR = objs
LIBFT_PATH = libft
LIB_DIR = lib
MLX_DIR = minilibx-linux

OBJS = $(SRCS:.c=.o)
OBJS_P = $(SRCS_P:.c=.o)
OBJS_V = $(SRCS_V:.c=.o)

PRINT_COMP		=	printf "\r$(_BOLD)$(_WHITE)$(_BOLD)$(_LCYAN)%s\r\t\t\t\t\t\t\t $(_BOLD)$(_LWHITE)[$(_LGREEN)✓$(_LWHITE)]"

%.o : %.c
	@printf "\r$(_CLEAR_LINE)"
	@$(PRINT_COMP) $@
	@$(CC) $(CFLAGS) $(IFLAGS) -I. -c $< -o ${<:.c=.o}

#*******************************************************************************
#*                                   COLORS                                    *
#*******************************************************************************

# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

# Inverted, i.e. colored backgrounds
_IGREY=$'\033[40m
_IRED=$'\033[41m
_IGREEN=$'\033[42m
_IYELLOW=$'\033[43m
_IBLUE=$'\033[44m
_IPURPLE=$'\033[45m
_ICYAN=$'\033[46m
_IWHITE=$'\033[47m

# Light colors
_LGREY=$'\033[90m
_LRED=$'\033[91m
_LGREEN=$'\033[92m
_LYELLOW=$'\033[93m
_LBLUE=$'\033[94m
_LPURPLE=$'\033[95m
_LCYAN=$'\033[96m
_LWHITE=$'\033[97m

# Others
_DIM=$'\033[2m
_CLEAR_LINE=$'\033[K

RM = rm -rf

#*******************************************************************************
#*                                    RULES                                    *
#*******************************************************************************

$(NAME):
	@printf "$(_LGREEN)"
	@printf " _    ___ __  __    ___ ___  ___ \n"
	@printf "| |  | __|  \/  |__|_ _| _ \/ __|\n"
	@printf "| |__| _|| |\/| |___| ||  _| (__ \n"
	@printf "|____|___|_|  |_|  |___|_|  \___|\n"
	@printf "                                 \n"
	@printf "$(_END)"

	@# LIBFT
	@printf "$(_LWHITE)Compiling $(LIBFT) ...$(_END)\n"
	@make -C ./$(LIBFT_PATH) -s
	@mkdir -p $(LIB_DIR) $(LIB_DIR)/$(INCLUDE_PATH)
	@cp $(LIBFT_PATH)/$(OWN_LIBFT_NAME).a ./$(LIB_DIR)/$(LIBFT).a
	@cp -r $(LIBFT_PATH)/$(INCLUDE_PATH)/* ./$(LIB_DIR)/$(INCLUDE_PATH)/

	@# MLX
	@printf "$(_END)\n\n$(_LWHITE)Compiling $(MLX) ...$(_END)\n"
	@cd $(MLX_DIR) && ./configure > /dev/null 2>&1 && make -s > /dev/null 2>&1 && cd ..
	@cp $(MLX_DIR)/$(LIBMLX).a ./$(LIB_DIR)/$(LIBMLX).a
	@cp -r $(MLX_DIR)/$(includes)/* ./$(LIB_DIR)/$(INCLUDE_PATH)/
	@printf "$(_BOLD)$(_LCYAN)$(LIBMLX) compiled !\t\t\t\t\t $(_BOLD)$(_LWHITE)[$(_LGREEN)✓$(_LWHITE)]\n"

	@# IPC
	@printf "$(_END)\n$(_LWHITE)Compiling $(NAME) ...$(_END)\n"
	@make -s $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(IFLAGS) $(LIBFLAGS) -o $@

$(NAME_PROCESSUS):
	@printf "$(_LWHITE)\n\nCompiling $(NAME_PROCESSUS) ...$(_END)\n"
	@make -s $(OBJS_P)
	@$(CC) $(OBJS_P) $(CFLAGS) $(IFLAGS) -o $(NAME_PROCESSUS)
	@# printf "$(_WHITE)$(NAME_PROCESSUS) Compiled ! $(_END)\n"

$(NAME_VISUALIZER):
	@printf "$(_LWHITE)\n\nCompiling $(NAME_VISUALIZER) ...$(_END)\n"
	@make -s $(OBJS_V)
	@$(CC) $(OBJS_V) $(IFLAGS) $(MLX_FLAGS) $(LIBFLAGS) -lglfw -o $(NAME_VISUALIZER)
	@# printf "$(_WHITE)$(NAME_VISUALIZER) Compiled ! $(_END)\n"

all: $(NAME) $(NAME_PROCESSUS) $(NAME_VISUALIZER) 

processus: $(NAME_PROCESSUS)

visualizer: $(NAME_VISUALIZER)

clean:
	@printf "$(_LYELLOW)Cleaning...$(_END)\n"
	@make -C ./$(LIBFT_PATH) clean -s > /dev/null 2>&1
	@make -C ./$(MLX_DIR) clean -s > /dev/null 2>&1
	@$(RM) $(OBJS) $(OBJS_P) $(OBJS_V)

fclean: clean
	@printf "$(_LYELLOW)Fcleaning...$(_END)\n"
	@make -C ./$(LIBFT_PATH) fclean -s > /dev/null 2>&1
	@$(RM) $(LIB_DIR)
	@$(RM) $(NAME) $(NAME_PROCESSUS) $(NAME_VISUALIZER)

re: fclean all

re-fast:
	@$(RM) $(OBJS) $(OBJS_P) $(OBJS_V)
	@$(RM) $(NAME) $(NAME_PROCESSUS) $(NAME_VISUALIZER)
	@make all -s

leaks: all
	@x-terminal-emulator -x "valgrind --leak-check=full --show-reachable=yes ./$(NAME) 1 --pts:200"
	sleep 1
	@x-terminal-emulator -x "valgrind --leak-check=full --show-reachable=yes ./$(NAME_VISUALIZER) -m"
	sleep 1
	@x-terminal-emulator -x "valgrind --leak-check=full --show-reachable=yes ./$(NAME_PROCESSUS) 199 2"

.PHONY: all clean fclean re re-fast processus visualizer leaks