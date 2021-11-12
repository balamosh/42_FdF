NAME		= fdf

SRCS_DIR	= srcs/
HEAD_DIR	= includes/

BUILD_DIR		= build/
BUILD_SUBDIRS	= events/	\
				  image/	\
				  gnl/		\
				  libft/	\
				  qrot/		\
				  vector3/
BUILD_SUBDIRS	:= $(addprefix $(BUILD_DIR), $(BUILD_SUBDIRS))

SRCS_FILES	= main.c					\
			  fdf_init.c				\
			  vector3/vector3_func1.c	\
			  vector3/vector3_func2.c	\
			  events/button_pressed.c	\
			  gnl/get_next_line.c		\
			  image/clear_image.c		\
			  image/mlx_image_swap.c	\
			  image/mlx_pixel_put.c		\
			  image/pixel.c				\
			  image/plot_line.c			\
			  libft/abs.c				\
			  libft/atoi.c				\
			  libft/fabs.c				\
			  libft/isdigit.c			\
			  libft/malloc.c			\
			  libft/memcpy.c			\
			  libft/min.c				\
			  libft/putchar_fd.c		\
			  libft/putstr_fd.c			\
			  libft/split.c				\
			  libft/strdup.c			\
			  libft/strlen.c			\
			  libft/substr.c			\
			  libft/swap.c				\
			  qrot/qrot_mult.c			\
			  qrot/qrot_rotate.c		\
			  qrot/qrot.c				

OBJS_FILES	= $(SRCS_FILES:.c=.o)

SRCS 		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS		= $(addprefix $(BUILD_DIR), $(OBJS_FILES))
DEPS		= $(OBJS:.o=.d)

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -O3

OS			= $(shell uname)
ifeq ($(OS), Linux)
	MLX			= mlx_linux/libmlx.a
	MLX_DIR		= $(dir $(MLX))
	MLX_FLAGS	= -L $(MLX_DIR) -l mlx -lm -lXext -lX11 -lz
else
	MLX			= mlx/libmlx.a
	MLX_DIR		= $(dir $(MLX))
	MLX_FLAGS	= -L $(MLX_DIR) -l mlx -lm -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

-include $(DEPS)

$(BUILD_DIR)%.o: $(SRCS_DIR)%.c $(BUILD_DIR)%.d | $(BUILD_SUBDIRS)
	$(CC) $(CFLAGS) -MMD -I $(HEAD_DIR) -I $(MLX_DIR) -o $@ -c $<

$(BUILD_DIR)%.d: $(SRCS_DIR)%.c | $(BUILD_SUBDIRS)
	$(CC) $(CFLAGS) -MMD -I $(HEAD_DIR) -I $(MLX_DIR) -o $(@:.d=.o) -c $<

$(BUILD_SUBDIRS): | $(BUILD_DIR)
	mkdir $@

$(BUILD_DIR):
	mkdir $@

$(MLX):
	make -C $(MLX_DIR)

clean: 
	rm -rf $(BUILD_DIR)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)

re:
	make fclean
	make all

.PHONY: all mlx clean fclean re
