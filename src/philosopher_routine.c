/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:20:09 by stempels          #+#    #+#             */
/*   Updated: 2025/08/26 16:36:46 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	eating(t_ctrl *ctrl, t_philo *philo);

void	*philo_routine(void *arg)
{
	t_ctrl		*ctrl;
	t_philo		*philo;

	philo = (t_philo *)arg;
	ctrl = philo->ctrl;
	pthread_mutex_lock(ctrl->m_start);
	while (ctrl->start != 0)
	{
		pthread_mutex_unlock(ctrl->m_start);
		if (eating(ctrl, philo))
			return (NULL);
		print_msg("is sleeping", philo);
		usleep(1000 * philo->ctrl->time_sleep);
		print_msg("is thinking", philo);
		usleep((ctrl->time_die - ctrl->time_eat - ctrl->time_sleep) * 1000 / 3);
		pthread_mutex_lock(ctrl->m_start);
	}
	pthread_mutex_unlock(ctrl->m_start);
	return (NULL);
}

static int	eating(t_ctrl *ctrl, t_philo *philo)
{
	if (pthread_mutex_lock(philo->forks[0]))
		return (1);
	if (print_msg("took a fork", philo))
		return (1);
	if (pthread_mutex_lock(philo->forks[1]))
		return (1);
	philo->last_meal = get_time(ctrl->time_start);
	print_msg("took is second fork and is eating !", philo);
	if (philo->dinner > 0)
		philo->dinner--;
	usleep(1000 * philo->ctrl->time_eat);
	if (pthread_mutex_unlock(philo->forks[0]))
		return (1);
	print_msg("let go of the fork", philo);
	if (pthread_mutex_unlock(philo->forks[1]))
		return (1);
	print_msg("let go of the second fork", philo);
	return (0);
}

int	print_msg(char *msg, t_philo *philo)
{
	long int	time;

	if (pthread_mutex_lock(philo->ctrl->print))
		return (1);
	time = get_time(philo->ctrl->time_start);
	if (philo->ctrl->start == 1)
		printf("=== %ld ===	philo %d: %s !\n", time, philo->philo_id, msg);
	if (pthread_mutex_unlock(philo->ctrl->print))
		return (1);
	return (0);
}

long int	get_time(long int start_time)
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL))
		return (-1);
	return (((tmp.tv_sec * 1000000 + tmp.tv_usec) / 1000) - start_time);
}
