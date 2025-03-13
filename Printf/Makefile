# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 14:01:51 by fmontini          #+#    #+#              #
#    Updated: 2025/03/13 11:44:34 by fmontini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colori ANSI
RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
CYAN    = \033[36m
BOLD    = \033[1m

NAME = ft_printf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf.c \
       ft_printf_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "$(GREEN)✅ Compilation successful!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔨 Creating archive: $(NAME)$(RESET)"
	ar rcs $(NAME) $(OBJS)
%.o: %.c
	@echo "$(CYAN)🛠️  Compiling: $<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@
#indica esplicitamente come compilare i .c in .o. Senza questa regola, il Makefile si affida alle 
#regole implicite di make, che di solito fanno la stessa cosa, ma è sempre una buona 
#pratica esplicitarla per evitare problemi di compatibilità.

clean:
	@echo "$(RED)🗑️  Removing object files$(RESET)"
	rm -f $(OBJS)
fclean: clean
	@echo "$(RED)🗑️  Removing archive: $(NAME)$(RESET)"
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re bonus
