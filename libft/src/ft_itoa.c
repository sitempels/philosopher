/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:24:25 by stempels          #+#    #+#             */
/*   Updated: 2024/11/05 14:21:21 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_count(long nbr);
static char	*int_conv(char *res, long nbr);

char	*ft_itoa(int n)
{
	char	*res;
	long	nbr;
	int		i;

	nbr = (long) n;
	i = int_count(nbr);
	res = (char *) malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[i] = '\0';
	return (int_conv(res, nbr));
}

static char	*int_conv(char *res, long nbr)
{
	int	i;

	i = int_count(nbr) - 1;
	if (nbr < 0)
	{
		nbr = nbr * -1;
		res[0] = '-';
	}
	while (nbr > 9)
	{
		res[i] = (nbr % 10) + 48;
		nbr = nbr / 10;
		i--;
	}
	res[i] = (nbr % 10) + 48;
	return (res);
}

static int	int_count(long nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr = nbr * -1;
		count++;
	}
	while (nbr != 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}
