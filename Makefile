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
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
GLFW3 = MLX42/build/_deps/glfw-build/src/libglfw3.a
LIBMLX42 = MLX42/build/libmlx42.a
LIBFT = libft/libft.a
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit

MANDATORY_SRC = source/mandatory/input_check.c \
				source/mandatory/cub3d.c
# source/mandatory/map_check.c \
# source/mandatory/get_map.c \

BONUS_SRC =

MANDATORY_OBJS = $(MANDATORY_SRC:.c=.o)

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
	@$(CC) $(LIBFT) $(MANDATORY_OBJS) $(LIBMLX42) $(GLFW3) $(FRAMEWORK) -o $(NAME)
	@echo "$(NAME) created."

clean:
	@echo "Cleaning."
	@rm -rf source/mandatory/*.o
	@rm -rf source/bonus/*.o
	@make clean -C libft
ifneq (,$(wildcard ./MLX42/build))
	@make clean -C ./MLX42/build/_deps/glfw-build
	@make clean -C ./MLX42/build
else
	
endif

fclean: clean
	@echo "Removing executable."
	@rm -rf source/mandatory/*.o
	@rm -rf source/bonus/*.o
	@make fclean -C libft
	@rm -rf ./MLX42/build $(GLFW3) $(LIBMLX42) $(NAME)

re: fclean all

.PHONY: all clean fclean re run


# MLX42/TOOLS/CMAKELISTS.TXT line 129 CHANGE AND TO OR