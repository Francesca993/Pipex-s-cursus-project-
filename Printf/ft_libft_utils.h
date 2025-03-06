#ifndef FT_LIBFT_UTILS_H
#define FT_LIBFT_UTILS_H

#include <unistd.h>
#include <stddef.h>

static inline int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static inline int	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

static inline int	ft_putnmbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		count += ft_putnmbr(n / 10);
	}
	count += ft_putchar((n % 10) + '0');
	return (count);
}

static inline int	ft_putnbr_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
	{
		count += ft_putnbr_unsigned(n / 10);
	}
	count += ft_putchar((n % 10) + '0');
	return (count);
}

#endif // FT_LIBFT_UTILS_H