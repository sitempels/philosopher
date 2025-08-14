/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:56:55 by stempels          #+#    #+#             */
/*   Updated: 2025/08/14 16:35:21 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

//static void	get_fork(t_ctrl *ctrl, pthread_mutex *fork[2], char *fork_name[2]);
//static time_t	get_time(int time_start);
static t_philo	*invite_philo(t_ctrl *ctrl, int philo_id);
void static		*philo_routine(void *arg);

int	philosopher(t_ctrl *ctrl)
{
	int			i;
	pthread_t	**thread_id;

	ctrl->start.tv_sec = 0;
	thread_id = (pthread_t **) malloc(sizeof(pthread_t *) * (ctrl->nbr_philo + 1));
	if (!thread_id)
		return (1);
	thread_id[ctrl->nbr_philo] = NULL;
	i = 0;
	while (i < ctrl->nbr_philo)
	{
		thread_id[i] = (pthread_t *) malloc(sizeof(pthread_t));
		ctrl->philo[i] = invite_philo(ctrl, i);
		if (!ctrl->philo[i])
			return (1);
		if (pthread_create(thread_id[i], NULL, philo_routine, &ctrl->philo[i]))
			return (1);
		i++;
	}
//	if (gettimeofday(ctrl->time_start, NULL))
//		return (1);
	ctrl->start.tv_sec = 1;
	pthread_join(*thread_id[0], NULL);
	return (0);
}

static t_philo	*invite_philo(t_ctrl *ctrl, int philo_id)
{
	t_philo	*philo;


	philo = (t_philo *) malloc(sizeof(t_philo) * 1);
	if (!philo)
		return (NULL);
	philo->start = ctrl->start;
	philo->philo_id = philo_id;
	philo->print = ctrl->print;
	philo->time = &ctrl->start.tv_sec;
	return (philo);	
}

static void	*philo_routine(void *arg)
{
//	int				philo_id;
//	char			*fork_name[2];
//	t_time			last_meal;
//	pthread_mutex	*fork[2];
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->time == 0)
		usleep(50);
//	get_fork(ctrl, fork, fork_name);
	pthread_mutex_lock(&philo->print);
	printf("philo_id: %d\n", philo->philo_id);
	pthread_mutex_unlock(&philo->print);
	while (philo->time == 0)
		usleep(50);
//	last_meal = ctrl->start->tv_sec;
	return (NULL);
}

/*
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
*/
/*
static void	print_msg(t_ctrl *ctrl, time_t time, int philo_id, char *msg)
{
	pthread_mutex_lock(ctrl->print);
	if (t_ctrl->start == 1)
		printf("%d philosopher %d %s\n", time, philo_id, msg);
	pthread_mutex_unlock(ctrl->print);
}
*/
/*
static int	check_dead(t_ctrl *ctrl)
{
	t_timeval	actual_time;

	if (gettimeofday(actual_time, NULL))
		return (problem);
	if (ctrl->time_die < (actual_time - ctrl->time_start))
	{
		ctrl->start = 0;
		printf("philosopher %d died\n", ctrl->philo_id);
		return (1);
	}
	else
		return (0);
}
*/
/*
static time_t	get_time(int time_start)
{
	t_timeval	actual;

	gettimeofday(actual, NULL);
	return (actual->tv_sec);
}
*/
