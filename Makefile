# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jergashe <jergashe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 16:42:11 by zstenger          #+#    #+#              #
#    Updated: 2023/05/18 14:14:46 by jergashe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
NAME		= cub3D
B_NAME		= Cub3D
RM			= rm -rf
DN			= > /dev/null
LIBFT		= libft/libft.a
B_SRC_DIR	= source/bonus/
B_OBJ_DIR	= objects/bonus/
SRC_DIR		= source/mandatory/
OBJ_DIR		= objects/mandatory/
# CFLAGS		= -Wall -Wextra -Werror
LIBMLX42	= MLX42/build/libmlx42.a
CFLAGS		= -Wno-gnu-include-next -I/LeakSanitizer/include -L./LeakSanitizer/ -llsan -lc++
GLFW3		= MLX42/build/_deps/glfw-build/src/libglfw3.a
FRAMEWORK	= -framework Cocoa -framework OpenGL -framework IOKit

SOURCE		= main/cub3d \
			  main/utils \
			  main/hooks \
			  minimap/draw \
			  movement/move \
			  movement/turn \
			  init_data/init \
			  free_data/free \
			  input_handling/dfs \
			  init_data/init_map \
			  movement/move_utils \
			  minimap/draw_minimap \
			  init_data/init_utils \
			  raycasting/raycasting \
			  raycasting/print_texture \
			  input_handling/save_data \
			  input_handling/input_check \
			  input_handling/map_validating \
			  input_handling/validating_utils \
			  input_handling/color_validating \
			  input_handling/object_validating \

B_SOURCE	= door/door \
			  main/cub3d \
			  main/utils \
			  main/hooks \
			  minimap/draw \
			  movement/move \
			  movement/turn \
			  init_data/init \
			  free_data/free \
			  input_handling/dfs \
			  init_data/init_map \
			  movement/move_utils \
			  minimap/draw_minimap \
			  init_data/init_utils \
			  raycasting/raycasting \
			  raycasting/print_texture \
			  input_handling/save_data \
			  draw_sprites/draw_sprites \
			  draw_f_and_c/draw_f_and_c \
			  input_handling/input_check \
			  input_handling/map_validating \
			  input_handling/validating_utils \
			  input_handling/color_validating \
			  input_handling/object_validating \

SRC			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SOURCE)))
OBJ			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SOURCE)))

B_SRC		= $(addprefix $(B_SRC_DIR), $(addsuffix .c, $(B_SOURCE)))
B_OBJ		= $(addprefix $(B_OBJ_DIR), $(addsuffix .o, $(B_SOURCE)))

all: $(NAME)
	make run

bonus: $(B_NAME)
	make brun

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
	$(CC) $(CFLAGS) $(LIBFT) $(OBJ) $(LIBMLX42) $(GLFW3) $(FRAMEWORK) -o $(NAME)
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

$(B_NAME): $(LIBFT) $(LIBMLX42) $(B_OBJ)
	@echo "$(YELLOW)Compiling: $(DEF_COLOR)$(PURPLE)$(NAME) Mandatory part By:$(DEF_COLOR) $(RED)zstenger$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(LIBFT) $(B_OBJ) $(LIBMLX42) $(GLFW3) $(FRAMEWORK) -o $(NAME)
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

$(B_OBJ_DIR)%.o : $(B_SRC_DIR)%.c
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
	@$(RM) $(NAME) $(B_NAME) cub3D.dSYM/
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
	./cub3d maps/valid/input.cub

brun:
	./cub3d maps/valid/bonus.cub

# WITH BONUS
t1:
	./cub3d maps/valid/crazy.cub

t3:
	./cub3d maps/valid/randomshit.cub

t4:
	./cub3d maps/valid/bonus_big.cub

# WITH MANDATORY
t2:
	./cub3d maps/valid/dfs.cub

# MAPS WITH ERROR
t5:
	./cub3d maps/valid/empty.cub

t6:
	./cub3d maps/valid/bad_file.cub

t7:
	./cub3d maps/valid/hole.cub

t8:
	./cub3d maps/valid/line_inside.cub

t9:
	./cub3d maps/valid/bad_rgb.cub

t10:
	./cub3d maps/valid/bad_extension.cub

.PHONY: all clean fclean re run

DEF_COLOR	= \033[0;39m
RED			= \033[1;4;91m
GREEN		= \033[4;92m
CYAN		= \033[1;96m
CYAN3		= \033[1;4;96m
YELLOW		= \033[1;33m
PURPLE		= \033[1;35m
BWhite		= \033[1;37m
CYAN2		= \x1B[1;36m

# MLX42/TOOLS/CMAKELISTS.TXT line 129 CHANGE AND TO OR