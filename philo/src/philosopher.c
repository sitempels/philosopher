/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:56:55 by stempels          #+#    #+#             */
/*   Updated: 2025/08/27 11:35:25 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	invite_philo(t_ctrl *ctrl, pthread_t ***thread_id);
static int	create_thread(t_ctrl *ctrl, pthread_t ***thread_id);
static int	check_dead(t_ctrl *ctrl, t_philo *philo);
static int	check_eaten(t_ctrl *ctrl, t_philo **philo);

int	philosopher(t_ctrl *ctrl)
{
	int			i;
	pthread_t	**thread_id;

	pthread_mutex_lock(ctrl->m_start);
	if (invite_philo(ctrl, &thread_id))
		return (1);
	ctrl->time_start = get_time(ctrl, 0);
	if (ctrl->time_start < 0)
		ctrl->start = 0;
	i = 0;
	while (ctrl->start == 1)
	{
		pthread_mutex_unlock(ctrl->m_start);
		if (check_dead(ctrl, ctrl->philo[i])
			|| (ctrl->nbr_dinner > 0 && check_eaten(ctrl, ctrl->philo)))
			break ;
		if (++i == ctrl->nbr_philo - 1)
			i = 0;
		pthread_mutex_lock(ctrl->m_start);
	}
	pthread_mutex_unlock(ctrl->m_start);
	i = -1;
	while (thread_id[++i])
		pthread_join(*(thread_id[i]), NULL);
	return (ft_free_array((void ***)&thread_id), 0);
}

static int	invite_philo(t_ctrl *ctrl, pthread_t ***thread_id)
{
	int		i;
	t_philo	**philo;

	ctrl->philo = (t_philo **)malloc(sizeof(t_philo *) * (ctrl->nbr_philo + 1));
	if (!ctrl->philo)
		return (1);
	memset(ctrl->philo, 0, sizeof(t_philo *) * (ctrl->nbr_philo + 1));
	i = 0;
	while (i < ctrl->nbr_philo)
	{
		philo = &ctrl->philo[i];
		*philo = (t_philo *) malloc(sizeof(t_philo));
		if (!philo)
			return (1);
		(*philo)->philo_id = i + 1;
		(*philo)->dinner = ctrl->nbr_dinner;
		(*philo)->last_meal = 0;
		(*philo)->ctrl = ctrl;
		(*philo)->forks[(i + 1) % 2] = ctrl->forks[(i + 1) % ctrl->nbr_philo];
		(*philo)->forks[(i + 2) % 2] = ctrl->forks[i];
		i++;
	}
	if (create_thread(ctrl, thread_id))
		ctrl->start = 0;
	return (0);
}

static int	create_thread(t_ctrl *ctrl, pthread_t ***thread)
{
	int			i;

	*thread = malloc(sizeof(pthread_t *) * (ctrl->nbr_philo + 1));
	if (!*thread)
		return (1);
	memset(*thread, 0, sizeof(pthread_t *) * (ctrl->nbr_philo + 1));
	i = 0;
	while (i < ctrl->nbr_philo)
	{
		(*thread)[i] = (pthread_t *) malloc(sizeof(pthread_t));
		if (!(*thread)[i])
			return (1);
		if (pthread_create((*thread)[i], NULL, philo_routine, ctrl->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	check_dead(t_ctrl *ctrl, t_philo *philo)
{
	long int	time;

	time = get_time(ctrl, ctrl->time_start);
	if (time < 0)
		return (1);
	pthread_mutex_lock(philo->forks[1]);
	if (time - philo->last_meal >= ctrl->time_die)
	{
		pthread_mutex_lock(ctrl->m_start);
		ctrl->start = 0;
		printf("=== %ld ===	philo %d: died !\n", time, philo->philo_id);
		pthread_mutex_unlock(philo->forks[1]);
		return (1);
	}
	pthread_mutex_unlock(philo->forks[1]);
	return (0);
}

static int	check_eaten(t_ctrl *ctrl, t_philo **philo)
{
	int			i;
	int			eaten;
	long int	actual_time;

	i = -1;
	eaten = 0;
	while (++i < ctrl->nbr_philo)
	{
		if (philo[i]->dinner == 0)
			eaten++;
	}
	if (eaten == ctrl->nbr_philo)
	{
		actual_time = get_time(ctrl, ctrl->time_start);
		if (actual_time < 0)
			return (1);
		pthread_mutex_lock(ctrl->m_start);
		pthread_mutex_lock(ctrl->print);
		ctrl->start = 0;
		printf("=== %ld ===	Everybody has eaten !\n", actual_time);
		pthread_mutex_unlock(ctrl->print);
		return (1);
	}
	return (0);
}
