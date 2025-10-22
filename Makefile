# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 09:35:18 by hermarti          #+#    #+#              #
#    Updated: 2025/10/22 16:45:06 by hermarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

LIBFT_DIR := libft/
LIBFT := $(LIBFT_DIR)libft.a
LIBFT_INC := $(LIBFT_DIR)inc/

INC_DIR := inc/
INC_BONUS_DIR := inc_bonus/

SRC_DIR := src/
SRC_BONUS_DIR := src_bonus/

OBJ_DIR := obj/

INC := $(INC_DIR)pipex.h
INC_BONUS := $(INC_BONUS_DIR)pipex_bonus.h

SRCS := $(SRC_DIR)main.c \
		$(SRC_DIR)pipe.c \
		$(SRC_DIR)pipe_util.c \
		$(SRC_DIR)check.c \
		$(SRC_DIR)read_write_pipe.c \
		$(SRC_DIR)read_write_pipe_utils.c \
		$(SRC_DIR)check_util.c \
		$(SRC_DIR)check_util2.c \
		$(SRC_DIR)split_args.c \
		$(SRC_DIR)split_args_util.c \
		$(SRC_DIR)util.c

SRCS_BONUS :=	$(SRC_BONUS_DIR)main_bonus.c \
				$(SRC_BONUS_DIR)pipe_bonus.c \
				$(SRC_BONUS_DIR)pipe_util_bonus.c \
				$(SRC_BONUS_DIR)check_bonus.c \
				$(SRC_BONUS_DIR)read_write_pipe_bonus.c \
				$(SRC_BONUS_DIR)read_write_pipe_utils_bonus.c \
				$(SRC_BONUS_DIR)check_util_bonus.c \
				$(SRC_BONUS_DIR)check_util2_bonus.c \
				$(SRC_BONUS_DIR)split_args_bonus.c \
				$(SRC_BONUS_DIR)split_args_util_bonus.c \
				$(SRC_BONUS_DIR)util_bonus.c

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
OBJS_BONUS := $(patsubst $(SRC_BONUS_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS_BONUS))

CC := cc
CFLAGS := -I$(LIBFT_INC) -Wall -Wextra -Werror

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g2 -O0
endif

RM = rm -f

.PHONY: all bonus clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_BONUS_DIR)%.c $(INC_BONUS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_BONUS_DIR) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I$(INC_DIR) -o $@

bonus: $(LIBFT) .bonus
	@:

.bonus: $(LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -I$(INC_BONUS_DIR) -o $(NAME)
	@touch .bonus

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) .bonus
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
rebonus: fclean bonus
