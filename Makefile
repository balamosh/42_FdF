NAME		= fdf

SRCS_PATH	= srcs/
OBJS_PATH	= objs/
HEAD_PATH	= includes/

SRCS_FILES	= main.c
HEAD_FILES	= fdf.h
OBJS_FILES	= $(SRCS_FILES:.c=.o)

SRCS 		= $(addprefix $(SRCS_PATH), $(SRCS_FILES))
OBJS		= $(addprefix $(OBJS_PATH), $(OBJS_FILES))
HEAD		= $(addprefix $(HEAD_PATH), $(HEAD_FILES))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3

OS			= $(shell uname)
ifeq ($(OS), Linux)
	MLX			= ./mlx_linux/libmlx.a
	MLX_FLAGS	= -L $(dir $(MLX)) -l mlx -lXext -lX11 -lz 
else
	MLX			= ./mlx/libmlx.a
	MLX_FLAGS	= -L $(dir $(MLX)) -l mlx -framework OpenGL -framework AppKit
endif

all: $(NAME)
	
$(NAME): $(OBJS_PATH) $(OBJS) 
	$(CC) $(OBJS) $(MLX_FLAGS) -lm -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(MLX) $(HEAD)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(HEAD_PATH)

$(OBJS_PATH):
	mkdir $@

$(MLX):
	make -C $(dir $@) $(notdir $@)

clean: 
	rm -rf $(OBJS_PATH)
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re $(MLX)
