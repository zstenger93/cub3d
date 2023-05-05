# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zstenger <zstenger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 16:42:11 by zstenger          #+#    #+#              #
#    Updated: 2023/05/05 01:47:10 by zstenger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
DN = > /dev/null
CC = cc
RM = rm -rf
CFLAGS =  -Wall -Wextra -Werror -g
GLFW3 = MLX42/build/_deps/glfw-build/src/libglfw3.a
LIBMLX42 = MLX42/build/libmlx42.a
LIBFT = libft/libft.a
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit
SRC_DIR = source/mandatory/
OBJ_DIR = objects/

SOURCE = cub3d \
		 utils \
		 init_minimap \
		 draw_minimap \
		 hooks \
		 input_check \

SRC				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SOURCE)))
OBJ				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SOURCE)))

all: $(NAME)
	make run

# $(LIBMLX42):
# 	@if [ -d ./MLX42/glfw_lib ]; \
#     then echo "glfw3 already Exists"; \
#     else \
# 	echo "Creating Makefiles." && \
# 	sleep 1 && \
# 	cmake -S MLX42/ -B MLX42/build -DGLFW_FETCH=1 && \
# 	echo "Building glfw3 and MLX42." && \
# 	sleep 1; \
# 	make -C MLX42/build; \
# 	fi

$(LIBFT):
	@git submodule update --init --recursive --remote
	@make -C libft

$(NAME): $(LIBFT) $(LIBMLX42) $(OBJ)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Mandatory part By:$(DEF_COLOR) $(RED)zstenger$(DEF_COLOR)"
	@$(CC) $(LIBFT) $(OBJ) $(LIBMLX42) $(GLFW3) $(FRAMEWORK) -o $(NAME)
	@echo "$(NAME) has been compiled."
# @echo "$(RED)   ▓███▓░░░██▒░░▒██░▒█████░░░█████░░██████"
# @echo " ▓██▓░▒██░░██▒░░▒██░░██▒░▒█░░░░▒██░░██▒░▒██"
# @echo " █▓░░░░░░░░██▒░░▒██░░█████▒░░░▒███░░██▒░░▒██"
# @echo " ▓██▓░▒██░░██▒░░▒██░░██▒░▒█░░░░▒██░░██▒░▒██"
# @echo "   ▓███▓░ ░░██████░░░█████▒░▒█████░░██████"
# @echo "   ▒▓▒░ ░  ░░▒▓▓▒░░ ░▒▓▒ ░░░▒▓▓▓▓▒░░▒▓▓▒▒"
# @echo "   ░░     ░▒▒░ ░▒ ░  ░ ░  ░▒▒░   ░▒▒░ ░▒░"
# @echo "    ░      ░░  ░░      ░   ░░     ░░   ░"
# @echo "           ░   ░            ░     ░"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(INCL_RDL_HEADER) -c $< -o $@ $(DN)

clean:
	@echo "Cleaning object files."
	@$(RM) objects
# 	@make clean -C libft
# ifneq (,$(wildcard ./MLX42/build))
# 	# @make clean -C ./MLX42/build/_deps/glfw-build
# 	@make clean -C ./MLX42/build
# else
	
# endif
	@echo "Objects have been removed."

fclean: clean
	@echo "Removing executables."
	@$(RM) $(NAME)
# @make fclean -C libft
# @$(RM) ./MLX42/build $(GLFW3) $(LIBMLX42)
	@echo "Executables and objects have been romved."

re:
	@echo "Rebuilding the project."
	@make fclean
	@make
	@echo "The project has been rebuilt."

#RUN WITH DIFFERENT MAPS
run:
	./cub3d maps/valid/firstmap.cub
vf:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-limit=no --tool=memcheck ./cub3d
t1:

t2:

t3:

t4:

t5:

.PHONY: all clean fclean re run

DEF_COLOR = \033[0;39m
RED = \033[1;4;91m
GREEN = \033[4;92m
CYAN = \033[1;96m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
CYAN2 = \x1B[1;36m

# MLX42/TOOLS/CMAKELISTS.TXT line 129 CHANGE AND TO OR