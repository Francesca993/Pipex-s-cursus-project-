/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:09:19 by fmontini          #+#    #+#             */
/*   Updated: 2025/02/18 09:25:02 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_libft_utils.h"

int	check_type(char str, va_list args)
{
	char	c;

	if (str == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	if (str == 'c')
	{
		c = (char) va_arg(args, int);
		return (ft_putchar(c));
	}
	if (str == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (str == 'd' || str == 'i')
		return (ft_putnmbr(va_arg(args, int)));
	if (str == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	if (str == 'x' || str == 'X')
		return (ft_putnbr_hexa(va_arg(args, unsigned int), str));
	if (str == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;
	int		i;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if ((str[i] == '%') && (str[i + 1]))
		{
			i++;
			count += check_type(str[i], args);
		}
		else
		{
			ft_putchar(str[i]);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
