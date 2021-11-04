NAME		= fdf

SRCS_DIR	= srcs/
OBJS_DIR	= objs/
HEAD_DIR	= includes/

SRCS_FILES	= main.c				\
			  fdf_init.c			\
			  libft_func1.c			\
			  malloc.c				\
			  matrix3.c				\
			  mlx_pixel_put.c		\
			  plot_line.c			\
			  vector3_func1.c		\
			  vector3_func2.c

OBJS_FILES	= $(SRCS_FILES:.c=.o)

SRCS 		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_FILES))
DEP			= $(OBJS:.o=.d)

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3

OS			= $(shell uname)
ifeq ($(OS), Linux)
	MLX			= mlx_linux/libmlx.a
	MLX_FLAGS	= -L $(dir $(MLX)) -l mlx -lXext -lX11 -lz
else
	MLX			= mlx/libmlx.a
	MLX_FLAGS	= -L $(dir $(MLX)) -l mlx -framework OpenGL -framework AppKit
endif

all: $(NAME)
	
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -lm -o $(NAME)

-include $(DEP)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) $(MLX)
	$(CC) $(CFLAGS) -MMD -I $(HEAD_DIR) -o $@ -c $<

$(OBJS_DIR):
	mkdir $@

$(MLX):
	make -C $(dir $(MLX))

clean: 
	rm -rf $(OBJS_DIR)
	-rm $(DEP)
	make -C $(dir $(MLX)) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all mlx clean fclean re
