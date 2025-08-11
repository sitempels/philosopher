/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:22:39 by stempels          #+#    #+#             */
/*   Updated: 2025/01/27 10:25:33 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_s(char *arg, int fd)
{
	if (arg == NULL)
		return (write(fd, "(null)", 6));
	return (ft_putstr_fd(arg, fd));
}

int	get_p(unsigned long long arg, char *base, int fd)
{
	size_t	writed;

	writed = 0;
	if (arg == 0)
		return (write(fd, "(nil)", 5));
	writed += write(fd, "0x", 2);
	return (writed += ft_putunbr_bfd(arg, base, fd));
}
