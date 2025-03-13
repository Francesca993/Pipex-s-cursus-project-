# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 11:35:34 by fmontini          #+#    #+#              #
#    Updated: 2025/03/13 11:39:31 by fmontini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# 🎨 Colori ANSI
RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
CYAN    = \033[36m
BOLD    = \033[1m

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_isalpha.c \
       ft_isdigit.c \
       ft_isalnum.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_strlen.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_memset.c \
       ft_bzero.c \
       ft_strlcpy.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_atoi.c \
       ft_calloc.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_strlcat.c \
       ft_strdup.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_split.c \
       ft_itoa.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_strmapi.c \
       ft_striteri.c \
       get_next_line.c \

BONUS_SRCS = ft_lstnew.c \
             ft_lstadd_front.c \
             ft_lstsize.c \
             ft_lstlast.c \
             ft_lstadd_back.c \
             ft_lstdelone.c \
             ft_lstclear.c \
             ft_lstiter.c \
             ft_lstmap.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "$(GREEN)✅ Compilation successful!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔨 Creating archive: $(NAME)$(RESET)"
	@ar rcs $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	@echo "$(BLUE)➕ Adding bonus functions$(RESET)"
	@ar rcs $(NAME) $(BONUS_OBJS)

%.o: %.c
	@echo "$(CYAN)🛠️  Compiling: $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)🗑️  Removing object files$(RESET)"
	@rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	@echo "$(RED)🗑️  Removing archive: $(NAME)$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus


