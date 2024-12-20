NAME			:= fractol
CFLAGS			:= -Wextra -Wall -Werror -g3 -O0 -fsanitize=address
# CFLAGS			:= -g3

HEADERS			:= -I ./include

LIB_DIR			:= ./lib

# HB_MATH_DIR		:= $(abspath $(LIB_DIR)/hb_math_ext)
# HB_MATH			:= $(HB_MATH_DIR)/hb_math_ext.a

LIBFT_DIR		:= $(abspath $(LIB_DIR)/libft)
LIBFT			:= $(LIBFT_DIR)/libft.a

LIBMLX_DIR		:= $(abspath $(LIB_DIR)/MLX42)
LIBMLX			:= $(LIBMLX_DIR)/build/libmlx42.a
LIBFLAGS		:=  -ldl `pkg-config --libs glfw3` -pthread -lm

SRC_DIR			:= ./src
SRCS			:= $(SRC_DIR)/fract_util.c \
				$(SRC_DIR)/mousehooks.c \
				$(SRC_DIR)/cleanup.c \
				$(SRC_DIR)/sim_utils.c \
				$(SRC_DIR)/julia.c \
				$(SRC_DIR)/newton.c \
				$(SRC_DIR)/mandelbrot.c \
				$(SRC_DIR)/strtofloat.c \
				$(SRC_DIR)/input_handler.c \
				$(SRC_DIR)/mlx_get_pixel.c \
				$(SRC_DIR)/colour_defaults.c \
				$(SRC_DIR)/colour_get.c \
				$(SRC_DIR)/colour_math.c

OBJS			:= ${SRCS:.c=.o}

MAIN			:= $(SRC_DIR)/main.c

all: $(NAME)

$(LIBFT):
		$(MAKE) --directory $(LIBFT_DIR) all CFLAGS="$(CFLAGS)"

$(LIBMLX):
		cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make CFLAGS="$(CFLAGS)" -C $(LIBMLX_DIR)/build -j4

.c.o:
		$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)


$(NAME): $(MAIN) $(OBJS) $(LIBFT) $(LIBMLX)
		$(CC) $(CFLAGS) $(MAIN) $(OBJS) $(LIBFT) $(LIBMLX) $(LIBFLAGS) -o $(NAME)

clean:
		$(MAKE) --directory $(LIBFT_DIR) clean
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(LIBMLX_DIR)/build
		$(MAKE) --directory $(LIBFT_DIR) fclean
		rm -rf $(NAME)

rm:
		rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, test
