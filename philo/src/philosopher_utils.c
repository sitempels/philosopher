/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 09:36:22 by stempels          #+#    #+#             */
/*   Updated: 2025/08/27 13:19:57 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	clean_mutex(t_ctrl *ctrl, int pos)
{
	int	i;

	i = 0;
	if (ctrl->forks)
	{
		while (ctrl->forks[i])
		{
			if (i < pos)
				pthread_mutex_destroy(ctrl->forks[i]);
			free(ctrl->forks[i]);
			ctrl->forks[i] = NULL;
			i++;
		}
		free(ctrl->forks);
		ctrl->forks = NULL;
	}
	pthread_mutex_destroy(ctrl->m_start);
	free(ctrl->m_start);
	pthread_mutex_destroy(ctrl->print);
	free(ctrl->print);
}

void	ft_free_array(void ***array)
{
	int	i;

	i = 0;
	while (array[0][i])
	{
		if (array[0][i])
		{
			free(array[0][i]);
			array[0][i] = NULL;
		}
		i++;
	}
	free(*array);
	*array = NULL;
}
