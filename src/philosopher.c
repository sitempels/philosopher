/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:56:55 by stempels          #+#    #+#             */
/*   Updated: 2025/08/21 16:26:05 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	actual_time(long int start_time, long int *time);
int	print_msg(long int time, char *msg, t_philo *philo);
//static time_t	get_time(int time_start);
static t_philo	*invite_philo(t_ctrl *ctrl, int philo_id);
void static		*philo_routine(void *arg);

int	philosopher(t_ctrl *ctrl)
{
	int			i;
	pthread_t	**thread_id;

	ctrl->start = 0;
	ctrl->time_start = 0;
	thread_id = (pthread_t **) malloc(sizeof(pthread_t *) * (ctrl->nbr_philo + 1));
	if (!thread_id)
		return (1);
	thread_id[ctrl->nbr_philo] = NULL;
	i = 0;
	while (i < ctrl->nbr_philo)
	{
		thread_id[i] = (pthread_t *) malloc(sizeof(pthread_t));
		ctrl->philo[i] = invite_philo(ctrl, i + 1);
		if (!ctrl->philo[i])
			return (1);
		if (pthread_create(thread_id[i], NULL, philo_routine, ctrl->philo[i]))
			return (1);
		printf("%d	philo_id: %d\n", ctrl->start, ctrl->philo[i]->philo_id);
		printf("	fork_1: %p	fork_2: %p\n", ctrl->philo[i]->forks[0], ctrl->philo[i]->forks[1]);
		i++;
	}
	if (actual_time(0, &ctrl->time_start))
		return (1);
	ctrl->start = 1;
	usleep(5000000);
	ctrl->start = 0;
	i = 0;
	while (thread_id[i])
	{
		pthread_join(*(thread_id[i]), NULL);
		i++;
	}
	return (0);
}

static t_philo	*invite_philo(t_ctrl *ctrl, int philo_id)
{
	t_philo	*philo;


	philo = (t_philo *) malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_id = philo_id;
	philo->ctrl = ctrl;
	philo->forks[philo_id % 2] = ctrl->forks[philo_id % ctrl->nbr_philo]; 
	philo->forks[(philo_id + 1) % 2] = ctrl->forks[philo_id - 1]; 
	return (philo);	
}

static void	*philo_routine(void *arg)
{
//	t_time			last_meal;
	long int	time;
	t_philo	*philo;

	time = 0;
	philo = (t_philo *)arg;
	while (philo->ctrl->start == 0)
		usleep(10);
	usleep(2000000);
	while (philo->ctrl->start != 0)
	{
		if (actual_time(philo->ctrl->time_start, &time))
			return (NULL);
		print_msg(time, "Alive !", philo);
	}
	return (NULL);
}

int	print_msg(long int time, char *msg, t_philo *philo)
{
		pthread_mutex_lock(philo->ctrl->print);
		printf("=== %ld ===	philo %d: Alive !\n", time, philo->philo_id);
		pthread_mutex_unlock(philo->ctrl->print);
		usleep(10);
}

int	actual_time(long int start_time, long int *time)
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL))
		return (1);
	else
		*time = ((tmp.tv_sec * 1000000 + tmp.tv_usec) / 1000) - start_time;
	return (0);
}

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
