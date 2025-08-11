/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:49:06 by stempels          #+#    #+#             */
/*   Updated: 2025/03/24 15:13:05 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t			i;
	int				sign;
	long long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -sign;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res + (str[i] - 48);
		if ('0' <= str[i + 1] && str[i + 1] <= '9')
			res = res * 10;
		if (res > INT_MAX && sign == 1)
			return (-1);
		if ((-1) * res < INT_MIN && sign == -1)
			return (0);
		i++;
	}
	return (sign * res);
}
