/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:00:06 by fmontini          #+#    #+#             */
/*   Updated: 2025/02/18 09:32:53 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_libft_utils.h"

int	ft_putnbr_hexa(unsigned int n, char type)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_putnbr_hexa((n / 16), type);
	}
	if ((n % 16) > 9)
	{
		if (type == 'x')
			count += ft_putchar(((n % 16) - 10) + 'a');
		else
			count += ft_putchar(((n % 16) - 10) + 'A');
	}
	else
		count += ft_putchar((n % 16) + '0');
	return (count);
}

int	ft_putnbr_hexa_pointer(unsigned long long n)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_putnbr_hexa_pointer(n / 16);
	}
	if ((n % 16) > 9)
	{
		count += ft_putchar(((n % 16) - 10) + 'a');
	}
	else
		count += ft_putchar((n % 16) + '0');
	return (count);
}

int	ft_print_pointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_putstr("(nil)"));
	count += ft_putstr("0x");
	count += ft_putnbr_hexa_pointer((unsigned long long)ptr);
	return (count);
}
