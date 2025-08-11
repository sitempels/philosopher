/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:00:12 by stempels          #+#    #+#             */
/*   Updated: 2024/11/05 14:25:20 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;

	lensrc = ft_strlen(src);
	lendst = ft_strlen(dst);
	if (!dst && !src)
		return (0);
	if (lendst > dstsize)
		return (dstsize + lensrc);
	i = 0;
	while (src[i] && i < (dstsize - lendst - 1) && (dstsize - lendst) >= 1)
	{
		dst[lendst + i] = src[i];
		i++;
	}
	dst[lendst + i] = '\0';
	return (lendst + lensrc);
}
