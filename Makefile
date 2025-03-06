# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 12:17:48 by fmontini          #+#    #+#              #
#    Updated: 2025/03/06 15:31:22 by fmontini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Executable name
NAME	=	pipex

SRC		=	pipex.c \
			pipex_utils.c \

# .c to .o compilation
OBJ	=	$(SRC:.c=.o)
OBJ_BONUS =	$(SRC_BONUS:.c=.o)

CFLAGS	= -Wall -Werror -Wextra -g -gdwarf-4

SRC	:= $(addprefix src/, $(SRC))
SRC_BONUS := $(addprefix bonus/src/, $(SRC_BONUS))

#Libft
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

#Printf
PRINTF_DIR = Printf
FT_PRINTF = $(PRINTF_DIR)/ft_printf.a

#Rules
$(NAME): $(OBJ) $(LIBFT) $(FT_PRINTF)
	@make -C $(PRINTF_DIR)
	@make -C $(LIBFT_DIR)
	cc -o $(NAME) $(OBJ) $(LIBFT) $(CFLAGS) $(FT_PRINTF)

#Esegui il Makefile di libft e ft_printf
$(LIBFT):
	@male -C $(LIBFT_DIR)
$(FT_PRINTF):
	@make -C $(FT_PRINTF)

all: $(NAME)

clean:
	rm -rf $(OBJ)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)

re: fclean all

.PHONY: all clean fclean all