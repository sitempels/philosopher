/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:56:55 by stempels          #+#    #+#             */
/*   Updated: 2025/08/13 10:55:19 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	get_fork(t_ctrl *ctrl, pthread_mutex *fork[2], char *fork_name[2]);
static time_t	get_time(int time_start);

void	philosopher(t_ctrl *ctrl)
{
	int	i;
	phtread	**thread_id;

	thread_id = (pthread **) malloc(sizeof(phtread *) * (ctrl->nbr_philo));
	i = 0;
	while (i < nbr_philo)
	{
		ctrl->philo_id = i;
		if (pthread_create(thread_id[i], NULL, &philo_routine, ctrl))
			return (problem);
		i++;
	}
	if (gettimeofday(ctrl->time_start, NULL))
		return (problem);
}

void	*philo_routine(void *arg)
l
	char			*fork_name[2];
	t_time			last_meal;
	t_ctrl			*ctrl;
	pthread_mutex	*fork[2];

	ctrl = (t_ctrl *)arg;
	get_fork(ctrl->philo_id, fork, fork_name);
	while (ctrl->start == 0)
		usleep(50);
	last_meal = ctrl->start->tv_sec;
	while (ctrl->start == 1)
	{
		if (ctrl->time_die )
		pthread_mutex_lock(forks[0]);
		if (check_dead(ctrl))
			return (died(ctrl));
		pthread_mutex_lock(forks[1]);
		if (check_dead(ctrl))
			return (died(ctrl));
		printf("philosopher %d is eating\n", ctrl->philo_id);
		usleep(ctrl->time_eat);
		pthread_mutex_unlock(forks[1]);
		pthread_mutex_unlock(forks[0]);
		if (check_dead(ctrl))
			return (died(ctrl));
		printf("philosopher %d is sleeping\n", ctrl->philo_id);
		usleep(ctrl->time_sleeping);
		if (check_dead(ctrl))
			return (died(ctrl));
		printf("philosopher %d is thinking\n", ctrl->philo_id);
	}
}

static void	get_fork(t_ctrl *ctrl, pthread_mutex *fork[2], char *fork_name[2])
{
	if (ctrt->philo_id == 0)
	{
		fork[0] = ctrl->forks[ctr->philo_id]; 
		fork[1] = ctrl->forks[ctr->nbr_philo - 1]; 
	}
	else
	{
		fork[ctrl->philo_id % 2] = ctrl->forks[ctr->philo_id]; 
		fork[(ctrl->philo_id + 1) % 2] = ctrl->forks[ctr->philo_id - 1]; 
	}
}

static int	check_dead(t_ctrl *ctrl)
{
	t_timeval	actual_time;

	if (gettimeofday(actual_time, NULL))
		return (problem);
	if (ctrl->time_die < (actual_time - ctrl->time_start))
		return (1);
	else
		return (0);
}

static time_t	get_time(int time_start)
{
	t_timeval	actual;

	gettimeofday(actual, NULL);
	return (actual->tv_sec);
}
