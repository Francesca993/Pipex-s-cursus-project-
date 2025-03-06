/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:03:28 by fmontini          #+#    #+#             */
/*   Updated: 2025/02/18 09:35:21 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	check_type(char str, va_list args);
int	ft_putnbr_hexa(unsigned int n, char type);
int	ft_print_pointer(void *ptr);
int	ft_putnbr_hexa_pointer(unsigned long long n);

#endif
