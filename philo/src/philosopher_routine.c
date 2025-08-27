/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:20:09 by stempels          #+#    #+#             */
/*   Updated: 2025/08/27 13:58:26 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	eating(t_ctrl *ctrl, t_philo *philo);

void	*philo_routine(void *arg)
{
	long int	think;
	t_ctrl		*ctrl;
	t_philo		*philo;

	philo = (t_philo *)arg;
	ctrl = philo->ctrl;
	think = (ctrl->time_die - ctrl->time_eat - ctrl->time_sleep) * 1000 / 3;
	if (think < 0)
		think = 0;
	pthread_mutex_lock(ctrl->m_start);
	while (ctrl->start != 0)
	{
		pthread_mutex_unlock(ctrl->m_start);
		if (eating(ctrl, philo))
			return (NULL);
		print_msg(ctrl, "is sleeping", philo);
		usleep(1000 * philo->ctrl->time_sleep);
		print_msg(ctrl, "is thinking", philo);
		usleep(think);
		pthread_mutex_lock(ctrl->m_start);
	}
	pthread_mutex_unlock(ctrl->m_start);
	return (NULL);
}

static int	eating(t_ctrl *ctrl, t_philo *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	if (print_msg(ctrl, "has taken a fork", philo))
		return (pthread_mutex_unlock(philo->forks[0]), 1);
	pthread_mutex_lock(philo->forks[1]);
	philo->last_meal = get_time(ctrl, ctrl->time_start);
	if (print_msg(ctrl, "has taken a fork", philo))
	{
		pthread_mutex_unlock(philo->forks[0]);
		pthread_mutex_unlock(philo->forks[1]);
		return (1);
	}
	if (print_msg(ctrl, "is eating !", philo))
	{
		pthread_mutex_unlock(philo->forks[0]);
		pthread_mutex_unlock(philo->forks[1]);
		return (1);
	}
	if (philo->dinner > 0)
		philo->dinner--;
	usleep(1000 * philo->ctrl->time_eat);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
	return (0);
}

int	print_msg(t_ctrl *ctrl, char *msg, t_philo *philo)
{
	long int	time;

	time = get_time(ctrl, ctrl->time_start);
	if (time < 0)
		return (1);
	pthread_mutex_lock(ctrl->print);
	if (ctrl->start == 1)
		printf("=== %ld ===	philo %d: %s !\n", time, philo->philo_id, msg);
	pthread_mutex_unlock(ctrl->print);
	return (0);
}

long int	get_time(t_ctrl *ctrl, long int start_time)
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL))
	{
		if (start_time != 0)
			pthread_mutex_lock(ctrl->m_start);
		pthread_mutex_lock(ctrl->print);
		ctrl->start = 0;
		printf("=== XXX ===	get_time: Time calculation failure !\n");
		if (start_time != 0)
			pthread_mutex_unlock(ctrl->m_start);
		pthread_mutex_unlock(ctrl->print);
		return (-1);
	}
	return (((tmp.tv_sec * 1000000 + tmp.tv_usec) / 1000) - start_time);
}
