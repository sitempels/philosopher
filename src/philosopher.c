/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:56:55 by stempels          #+#    #+#             */
/*   Updated: 2025/08/12 13:25:48 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	if (argc < 4 || argc > 5)
		return (write(2, "Error: wrong number of arguments\n", 32));
	if (check_argument(&argv[1]))
		return (1);
	philosopher(&argv[1]);
	return (0);
}
