/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:20:09 by stempels          #+#    #+#             */
/*   Updated: 2025/09/03 11:04:14 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	eating(t_ctrl *ctrl, t_philo *philo);
static int	do_usleep(t_ctrl *ctrl, int sleep);
static void	unlock_forks(t_philo *philo, int unlock_to);

void	*rout(void *arg)
{
	int			think;
	t_ctrl		*ctrl;
	t_philo		*philo;

	philo = (t_philo *)arg;
	ctrl = philo->ctrl;
	think = (ctrl->time_die - ctrl->time_eat - ctrl->time_sleep) * 1000 / 2;
	if (think < 0)
		think = 0;
	pthread_mutex_lock(&ctrl->m_start);
	while (ctrl->start != 0)
	{
		pthread_mutex_unlock(&ctrl->m_start);
		if (eating(ctrl, philo))
			return (NULL);
		print_msg(ctrl, "is sleeping", philo);
		if (do_usleep(ctrl, ctrl->time_sleep * 1000))
			return (NULL);
		print_msg(ctrl, "is thinking", philo);
		if (do_usleep(ctrl, think))
			return (NULL);
		pthread_mutex_lock(&ctrl->m_start);
	}
	pthread_mutex_unlock(&ctrl->m_start);
	return (NULL);
}

static int	eating(t_ctrl *ctrl, t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->forks[0]);
	if (print_msg(ctrl, "has taken a fork", philo))
		return (unlock_forks(philo, 0), 1);
	pthread_mutex_lock(philo->forks[1]);
	if (print_msg(ctrl, "has taken a fork", philo))
		return (unlock_forks(philo, 1), 1);
	pthread_mutex_lock(&philo->m_meal);
	if (get_time(ctrl, &philo->last_meal, ctrl->time_start, 0))
		return (unlock_forks(philo, 1), 1);
	pthread_mutex_unlock(&philo->m_meal);
	status = print_msg(ctrl, "is eating", philo);
	pthread_mutex_lock(&philo->m_meal);
	if (philo->dinner > 0)
		philo->dinner--;
	pthread_mutex_unlock(&philo->m_meal);
	if (status == 0)
		status = do_usleep(ctrl, ctrl->time_eat * 1000);
	unlock_forks(philo, 1);
	return (status);
}

static int	do_usleep(t_ctrl *ctrl, int sleep)
{
	int	i;
	int	time;

	time = sleep / 1000000;
	i = 0;
	pthread_mutex_lock(&ctrl->m_start);
	while (i < time && ctrl->start != 0)
	{
		pthread_mutex_unlock(&ctrl->m_start);
		usleep(1000000);
		i++;
		pthread_mutex_lock(&ctrl->m_start);
	}
	if (ctrl->start != 0)
	{
		pthread_mutex_unlock(&ctrl->m_start);
		usleep((sleep % 1000000));
		return (0);
	}
	pthread_mutex_unlock(&ctrl->m_start);
	return (1);
}

static void	unlock_forks(t_philo *philo, int unlock_to)
{
	int	i;

	i = 0;
	while (i < unlock_to + 1)
	{
		pthread_mutex_unlock(philo->forks[i]);
		i++;
	}
}

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
