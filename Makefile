NAME		= fdf

SRCS_DIR	= srcs/
HEAD_DIR	= includes/

BUILD_DIR		= build/
BUILD_SUBDIRS	= camera/	\
				  events/	\
				  fdf/		\
				  geometry/	\
				  gnl/		\
				  image/	\
				  libft/	\
				  qrot/		\
				  vector3/	\
				  window/
BUILD_SUBDIRS	:= $(addprefix $(BUILD_DIR), $(BUILD_SUBDIRS))

SRCS_FILES	= main.c					\
			  camera/controls.c			\
			  camera/projections.c	\
			  camera/update.c			\
			  events/button_pressed.c	\
			  events/button_released.c	\
			  events/close.c			\
			  events/cursor_moved.c		\
			  events/key_pressed.c		\
			  fdf/fdf_init.c			\
			  fdf/fdf.c					\
			  fdf/geo_init.c			\
			  fdf/geo_read.c			\
			  geometry/add.c			\
			  geometry/axis.c			\
			  geometry/bbox.c			\
			  geometry/free.c			\
			  geometry/geometry.c		\
			  geometry/modify.c			\
			  gnl/get_next_line.c		\
			  image/clear.c				\
			  image/color_lerp.c		\
			  image/image.c				\
			  image/pixel_put.c			\
			  image/plot_line.c			\
			  image/render_geo.c		\
			  libft/abs.c				\
			  libft/atoi.c				\
			  libft/fabs.c				\
			  libft/fmax.c				\
			  libft/fmin.c				\
			  libft/isdigit.c			\
			  libft/malloc.c			\
			  libft/max.c				\
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
			  qrot/qrot.c				\
			  vector3/vector3_func1.c	\
			  vector3/vector3_func2.c	\
			  window/window.c

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
