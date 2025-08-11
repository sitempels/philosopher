/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:46:09 by stempels          #+#    #+#             */
/*   Updated: 2024/12/15 13:38:12 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*csrc;
	unsigned char	*cdst;

	csrc = (unsigned char *) src;
	cdst = (unsigned char *) dst;
	if (cdst > csrc)
		while (len-- > 0)
			cdst[len] = csrc[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
