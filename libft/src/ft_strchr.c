/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:28:48 by stempels          #+#    #+#             */
/*   Updated: 2024/11/05 14:23:24 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	sep;

	i = 0;
	sep = (char) c;
	while (s[i])
	{
		if (s[i] == sep)
			return ((char *) &s[i]);
		i++;
	}
	if (sep == '\0')
		return ((char *) &s[i]);
	return (NULL);
}
