# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 16:42:11 by zstenger          #+#    #+#              #
#    Updated: 2023/02/16 17:30:07 by zstenger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BONUS_NAME = cub3d_bonus
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
GLFW3 = MLX42/build/_deps/glfw-build/src/libglfw3.a
LIBMLX42 = MLX42/build/libmlx42.a
LIBFT = libft/libft.a
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit

MANDATORY_SRC = source/mandatory/input_check.c \
				source/mandatory/cub3d.c
# source/mandatory/map_check.c \
# source/mandatory/get_map.c \

MANDATORY_OBJS = $(MANDATORY_SRC:.c=.o)

BONUS_SRC =

BONUS_OBJS = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(LIBMLX42):
	@if [ -d ./MLX42/glfw_lib ]; \
    then echo "glfw3 already Exists"; \
    else \
	echo "Creating Makefiles." && \
	sleep 1 && \
	cmake -S MLX42/ -B MLX42/build -DGLFW_FETCH=1 && \
	echo "Building glfw3 and MLX42." && \
	sleep 1; \
	make -C MLX42/build; \
	fi

$(LIBFT):
	@git submodule update --init --recursive --remote
	@make -C libft

$(NAME): $(LIBFT) $(LIBMLX42) $(MANDATORY_OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Mandatory part By:$(DEF_COLOR) $(RED)zstenger$(DEF_COLOR)"
	@$(CC) $(LIBFT) $(MANDATORY_OBJS) $(LIBMLX42) $(GLFW3) $(FRAMEWORK) -o $(NAME)
	@echo "$(NAME) has been compiled."
	echo "$(RED)   ▓███▓░░░██▒░░▒██░▒█████░░░█████░░██████"
	echo " ▓██▓░▒██░░██▒░░▒██░░██▒░▒█░░░░▒██░░██▒░▒██"
	echo " █▓░░░░░░░░██▒░░▒██░░█████▒░░░▒███░░██▒░░▒██"
	echo " ▓██▓░▒██░░██▒░░▒██░░██▒░▒█░░░░▒██░░██▒░▒██"
	echo "   ▓███▓░ ░░██████░░░█████▒░▒█████░░██████"
	echo "   ▒▓▒░ ░  ░░▒▓▓▒░░ ░▒▓▒ ░░░▒▓▓▓▓▒░░▒▓▓▒▒"
	echo "   ░░     ░▒▒░ ░▒ ░  ░ ░  ░▒▒░   ░▒▒░ ░▒░"
	echo "    ░      ░░  ░░      ░   ░░     ░░   ░"
	echo "           ░   ░            ░     ░"

$(BONUS_NAME): $(LIBFT) $(LIBMLX42) $(BONUS_OBJS)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(BONUS_NAME) Bonus part By:$(DEF_COLOR) $(RED)zstenger$(DEF_COLOR)"

	@echo "$(BONUS_NAME) has been compiled."
	echo "$(RED)   ▓███▓░░░██▒░░▒██░▒█████░░░█████░░██████"
	echo " ▓██▓░▒██░░██▒░░▒██░░██▒░▒█░░░░▒██░░██▒░▒██"
	echo " █▓░░░░░░░░██▒░░▒██░░█████▒░░░▒███░░██▒░░▒██"
	echo " ▓██▓░▒██░░██▒░░▒██░░██▒░▒█░░░░▒██░░██▒░▒██"
	echo "   ▓███▓░ ░░██████░░░█████▒░▒█████░░██████"
	echo "   ▒▓▒░ ░  ░░▒▓▓▒░░ ░▒▓▒ ░░░▒▓▓▓▓▒░░▒▓▓▒▒"
	echo "   ░░     ░▒▒░ ░▒ ░  ░ ░  ░▒▒░   ░▒▒░ ░▒░"
	echo "    ░      ░░  ░░      ░   ░░     ░░   ░"
	echo "           ░   ░            ░     ░"

clean:
	@echo "Cleaning object files."
	@$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)
	@make clean -C libft
ifneq (,$(wildcard ./MLX42/build))
	@make clean -C ./MLX42/build/_deps/glfw-build
	@make clean -C ./MLX42/build
else
	
endif
	@echo "Objects have been removed."

fclean: clean
	@echo "Removing executables."
	@$(RM) $(NAME) $(BONUS_NAME)
	@make fclean -C libft
	@$(RM) ./MLX42/build $(GLFW3) $(LIBMLX42)
	@echo "Executables and objects have been romved."

#RUN WITH DIFFERENT MAPS
t1:

t2:

t3:

t4:

t5:

re:
	@echo "Rebuilding the project."
	fclean all
	@echo "The project has been rebuilt."

DEF_COLOR = \033[0;39m
RED = \033[1;4;91m
GREEN = \033[4;92m
CYAN = \033[1;96m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
CYAN2 = \x1B[1;36m

.PHONY: all clean fclean re run


# MLX42/TOOLS/CMAKELISTS.TXT line 129 CHANGE AND TO OR