/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:12:39 by stempels          #+#    #+#             */
/*   Updated: 2025/01/27 10:19:38 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_prs(va_list arg, char *str, int fd);
static int	is_format(char *str, size_t *place);
static int	get_print(va_list arg, char type, int fd);

int	ft_printf_fd(int fd, const char *str, ...)
{
	int		printed;
	va_list	arg;

	fd = 1;
	va_start(arg, str);
	printed = 0;
	if (!str)
		return (-1);
	printed = str_prs(arg, (char *)str, fd);
	va_end (arg);
	return (printed);
}

static int	str_prs(va_list arg, char *str, int fd)
{
	int		buffer;
	int		printed;
	char	*res;
	size_t	i;

	i = 0;
	printed = 0;
	while (str[i])
	{
		buffer = 1;
		res = &str[i];
		if (str[i] == '%' && is_format(str, &i))
		{
			buffer = get_print(arg, str[i], fd);
			if (buffer < 0)
				return (-1);
		}
		else
			write (1, res, buffer);
		printed = printed + buffer;
		i++;
	}
	return (printed);
}

static int	is_format(char *str, size_t *place)
{
	size_t		j;

	j = 0;
	while (FORMAT[j])
	{
		if (FORMAT[j] == str[*place + 1])
		{
			*place = *place + 1;
			return (1);
		}
		j++;
	}
	return (0);
}

static int	get_print(va_list arg, char type, int fd)
{
	int	b;

	b = 0;
	if (type == 'c')
		b = ft_putchar_fd(va_arg(arg, int), fd);
	else if (type == 's')
		b = get_s(va_arg(arg, char *), fd);
	else if (type == 'd' || type == 'i')
		b = ft_putnbr_bfd((long long)va_arg(arg, int), BA_10, fd);
	else if (type == 'u')
		b = ft_putnbr_bfd((long long)va_arg(arg, unsigned), BA_10, fd);
	else if (type == 'x')
		b = ft_putnbr_bfd((long long)va_arg(arg, unsigned), BA_16, fd);
	else if (type == 'X')
		b = ft_putnbr_bfd((long long)va_arg(arg, unsigned), BA_X16, fd);
	else if (type == 'p')
		b = get_p(va_arg(arg, unsigned long long), BA_16, fd);
	else
		b = write(fd, "%", 1);
	return (b);
}
