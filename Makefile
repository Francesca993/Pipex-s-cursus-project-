# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 12:17:48 by fmontini          #+#    #+#              #
#    Updated: 2025/03/13 11:31:07 by fmontini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colori ANSI
GREEN=\033[1;32m
YELLOW=\033[1;33m
CYAN=\033[1;36m
RED=\033[1;31m
RESET=\033[0m

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
	@echo "$(CYAN)[Compilazione] 🚀 Creazione dell'eseguibile...$(RESET)"
	@make -C $(PRINTF_DIR)
	@make -C $(LIBFT_DIR)
	cc -o $(NAME) $(OBJ) $(LIBFT) $(CFLAGS) $(FT_PRINTF)
	@echo "$(GREEN)[OK] ✅ pipex compilato con successo!$(RESET)"

#Esegui il Makefile di libft e ft_printf
$(LIBFT):
	@make -C $(LIBFT_DIR)
$(FT_PRINTF):
	@make -C $(PRINTF_DIR)

all: $(NAME)
	@echo "$(GREEN)🎉 pipex è pronto per l'uso!$(RESET)"

clean:
	@echo "$(YELLOW)[Pulizia] 🧹 Rimozione file oggetto...$(RESET)"
	rm -rf $(OBJ)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)
	@echo "$(GREEN)[OK] ✅ File oggetto rimossi!$(RESET)"

fclean: clean
	@echo "$(YELLOW)[Pulizia Completa] 🗑 Rimozione binari...$(RESET)"
	rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
	@echo "$(GREEN)✅ $(BOLD)Tutti i file sono stati rimossi!$(RESET)"

re: fclean all

.PHONY: all clean fclean all