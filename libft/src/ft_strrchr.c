/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:35:21 by stempels          #+#    #+#             */
/*   Updated: 2024/11/05 15:25:21 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	sep;
	char	*ptr;

	i = ft_strlen(s);
	sep = (char) c;
	ptr = NULL;
	if (s[i] == sep)
		return ((char *) &s[i]);
	while (--i >= 0)
	{
		if (s[i] == sep)
		{
			ptr = (char *) &s[i];
			break ;
		}
	}
	return (ptr);
}
