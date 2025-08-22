/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:56:55 by stempels          #+#    #+#             */
/*   Updated: 2025/08/22 16:59:27 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	get_time(long int start_time);
int	print_msg(long int time, char *msg, t_philo *philo);
//static time_t	get_time(int time_start);
static t_philo	*invite_philo(t_ctrl *ctrl, int philo_id);
void static		*philo_routine(void *arg);
int	check_dead(t_philo *philo);
int	eating(t_ctrl *ctrl, t_philo *philo);

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
		printf("philo %d join the table !\n", ctrl->philo[i]->philo_id);
		printf("	fork_1: %p	fork_2: %p\n", ctrl->philo[i]->forks[0], ctrl->philo[i]->forks[1]);
		i++;
	}
	printf("%ld	All set, starting simulation !\n", ctrl->time_start);
	ctrl->time_start = get_time(0);
	if (ctrl->time_start < 0)
		return (1);
	ctrl->start = 1;
	i = 0;
	while (ctrl->start == 1)
	{
		if (check_dead(ctrl->philo[i]))
			break ;
		if (i == ctrl->nbr_philo - 1)	
			i = 0;
	}
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
	philo->dinner = ctrl->nbr_dinner;
	philo->last_meal = 0;
	philo->ctrl = ctrl;
	philo->forks[philo_id % 2] = ctrl->forks[philo_id % ctrl->nbr_philo]; 
	philo->forks[(philo_id + 1) % 2] = ctrl->forks[philo_id - 1]; 
	return (philo);	
}

static void	*philo_routine(void *arg)
{
	int			status;
	long int	new_time;
	t_ctrl		*ctrl;
	t_philo		*philo;

	philo = (t_philo *)arg;
	ctrl = philo->ctrl;
	while (ctrl->start == 0)
		usleep(1);
	philo->last_meal = get_time(ctrl->time_start);
	if (philo->last_meal < 0)
		return (NULL);
	while (ctrl->start != 0)
	{
		status = eating(ctrl, philo);
		if (status < 0)
			return (NULL);
		else if (status == 1)
		{
			new_time = get_time(philo->ctrl->time_start);
			print_msg(new_time, "is sleeping !", philo);
			usleep(1000 * philo->ctrl->time_sleep);
			new_time = get_time(philo->ctrl->time_start);
			print_msg(new_time, "is thinking !", philo);
		}
	}
	return (NULL);
}

int	eating(t_ctrl *ctrl, t_philo *philo)
{
	long int	time;

	time = get_time(ctrl->time_start);
	if (time < 0)
		return (-1);
	if ((time - philo->last_meal) * 100 / (ctrl->time_die - (ctrl->time_eat + ctrl->time_sleep)) > 50)
	{
		pthread_mutex_lock(philo->forks[0]);
		time = get_time(philo->ctrl->time_start);
		print_msg(time, "took a fork", philo);
		pthread_mutex_lock(philo->forks[1]);
		philo->last_meal = get_time(philo->ctrl->time_start);
		print_msg(philo->last_meal, "took is second fork and is eating !", philo);
		usleep(1000 * philo->ctrl->time_eat);
		pthread_mutex_unlock(philo->forks[0]);
		time = get_time(philo->ctrl->time_start);
		print_msg(time, "let go of the fork", philo);
		pthread_mutex_unlock(philo->forks[1]);
		print_msg(time, "let go of the second fork", philo);
		return (1);
	}
	return (0);
}

int	check_dead(t_philo *philo)
{
	long int	actual_time;

	actual_time = get_time(philo->ctrl->time_start);
	if (actual_time < 0)
		return (-1);
	if (actual_time - philo->last_meal >= philo->ctrl->time_die)
	{
		print_msg(actual_time, "died !", philo);
		philo->ctrl->start = 0;
		return (1);
	}
	return (0);
}

int	print_msg(long int time, char *msg, t_philo *philo)
{
		pthread_mutex_lock(philo->ctrl->print);
		if (philo->ctrl->start == 1)
			printf("=== %ld ===	philo %d: %s !\n", time, philo->philo_id, msg);
		pthread_mutex_unlock(philo->ctrl->print);
}

long int	get_time(long int start_time)
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL))
		return (-1);
	return (((tmp.tv_sec * 1000000 + tmp.tv_usec) / 1000) - start_time);
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
