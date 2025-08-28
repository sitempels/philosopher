/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:46:31 by stempels          #+#    #+#             */
/*   Updated: 2025/08/28 11:19:29 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_isspace(char c);

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long int	res;

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
		if ((res > INT_MAX && sign == 1)
			|| ((-1) * res < INT_MIN && sign == -1))
			return (0);
		i++;
	}
	if (str[i])
		return (1);
	return ((int)sign * res);
}

int	check_ft_atoi(int res, char *str)
{
	int	i;

	if (res < 0)
		return (write(2, "Error: Negative value argument\n", 31), 0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (res == 0 && (str[i] != '0' || str[i + 1]))
		return (write(2, "Error: Argument exceed integer limits\n", 38), 0);
	if (res == 1 && (str[i] != '1' || str[i + 1]))
		return (write(2, "Error: Argument not an integer\n", 31), 0);
	return (1);
}

static int	ft_isspace(char c)
{
	if (c == 32 || (9 <= c && c <= 13))
		return (1);
	return (0);
}
