/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 09:36:22 by stempels          #+#    #+#             */
/*   Updated: 2025/08/28 10:51:58 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	clean_mutex(t_ctrl *ctrl, int pos)
{
	int	i;

	i = 0;
	if (ctrl->forks)
	{
		while (i < pos)
		{
			pthread_mutex_destroy(&ctrl->forks[i]);
			i++;
		}
		free(ctrl->forks);
		ctrl->forks = NULL;
	}
	pthread_mutex_destroy(&ctrl->m_start);
	pthread_mutex_destroy(&ctrl->m_print);
}

int	print_msg(t_ctrl *ctrl, char *msg, t_philo *philo)
{
	int	time;

	time = get_time(ctrl, ctrl->time_start);
	if (time < 0)
		return (1);
	pthread_mutex_lock(&ctrl->m_print);
	pthread_mutex_lock(&ctrl->m_start);
	if (ctrl->start == 1 && philo)
		printf("%d	philo %d: %s\n", time, philo->philo_id, msg);
	pthread_mutex_unlock(&ctrl->m_start);
	if (!philo)
		printf("%d	%s !\n", time, msg);
	pthread_mutex_unlock(&ctrl->m_print);
	return (0);
}

long int	get_time(t_ctrl *ctrl, long int start_time)
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL))
	{
		if (start_time != 0)
			pthread_mutex_lock(&ctrl->m_start);
		pthread_mutex_lock(&ctrl->m_print);
		ctrl->start = 0;
		printf("XXX	get_time: Time calculation failure !\n");
		if (start_time != 0)
			pthread_mutex_unlock(&ctrl->m_start);
		pthread_mutex_unlock(&ctrl->m_print);
		return (-1);
	}
	return (((tmp.tv_sec * 1000000 + tmp.tv_usec) / 1000) - start_time);
}
