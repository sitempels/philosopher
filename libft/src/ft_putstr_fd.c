/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:38:20 by stempels          #+#    #+#             */
/*   Updated: 2025/01/13 16:06:13 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr_fd(char *s, int fd)
{
	int		i;
	size_t	writed;

	i = 0;
	writed = 0;
	if (!s || fd < 0)
		return (-1);
	while (s[i])
	{
		writed += write(fd, &s[i], 1);
		i++;
	}
	return (writed);
}
