/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_bfd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:58:10 by stempels          #+#    #+#             */
/*   Updated: 2025/01/27 10:44:26 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wnbr_fd(unsigned long long nbr, char *base, size_t b_len, int fd);

int	ft_putunbr_bfd(unsigned long long nbr, char *base, int fd)
{
	int		writed;
	size_t	base_len;

	writed = 0;
	base_len = 0;
	base_len = ft_strlen(base);
	writed += wnbr_fd(nbr, base, base_len, fd);
	return (writed);
}

static int	wnbr_fd(unsigned long long nbr, char *base, size_t b_len, int fd)
{
	int	writed;
	int	printed;

	writed = 0;
	printed = 0;
	if (nbr > b_len - 1)
		printed += wnbr_fd(nbr / b_len, base, b_len, fd);
	if (printed == -1)
		return (-1);
	writed = ft_putchar_fd(base[nbr % b_len], fd);
	if (writed == -1)
		return (-1);
	printed = printed + writed;
	return (printed);
}
