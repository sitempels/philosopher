/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:47:15 by stempels          #+#    #+#             */
/*   Updated: 2024/11/05 14:26:05 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*res;

	if (!s)
		return (NULL);
	res = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (!f)
	{
		ft_strlcpy(res, s, ft_strlen(s) + 1);
		return (res);
	}
	i = 0;
	while (s[i])
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
