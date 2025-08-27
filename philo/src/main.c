/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:21:34 by stempels          #+#    #+#             */
/*   Updated: 2025/08/27 13:50:32 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_ctrl_struct(t_ctrl *ctrl, int argc, char **argv);
static int	handle_arg(long int *target, char *content);
static int	set_table(t_ctrl *ctrl);
static int	init_flow_mutex(t_ctrl *ctrl);

int	main(int argc, char **argv)
{
	t_ctrl	ctrl;

	if (argc < 5 || argc > 6)
		return (write(2, "Error: wrong number of arguments\n", 32), 1);
	if (init_ctrl_struct(&ctrl, argc, argv))
		return (1);
	if (ctrl.nbr_philo == 1)
	{
		printf("=== 0 ===	philo 1: took a fork !\n");
		usleep(ctrl.time_die);
		printf("=== %ld ===	philo 1: died !\n", ctrl.time_die);
		return (0);
	}
	if (set_table(&ctrl))
		return (1);
	if (philosopher(&ctrl))
	{
		ft_free_array((void ***)&ctrl.philo);
		return (clean_mutex(&ctrl, 0), 1);
	}
	ft_free_array((void ***)&ctrl.philo);
	clean_mutex(&ctrl, 0);
	return (0);
}

static int	init_ctrl_struct(t_ctrl *ctrl, int argc, char **argv)
{
	if (handle_arg((long int *)&ctrl->nbr_philo, argv[1]))
		return (1);
	if (handle_arg(&ctrl->time_die, argv[2]))
		return (1);
	if (handle_arg(&ctrl->time_eat, argv[3]))
		return (1);
	if (handle_arg(&ctrl->time_sleep, argv[4]))
		return (1);
	ctrl->nbr_dinner = -1;
	if (argc == 6)
		if (handle_arg((long int *)&ctrl->nbr_dinner, argv[5]))
			return (1);
	ctrl->philo = NULL;
	ctrl->start = 1;
	if (init_flow_mutex(ctrl))
		return (write(2, "Error: flow mutex attribution failed !\n", 39), 1);
	return (0);
}

static int	init_flow_mutex(t_ctrl *ctrl)
{
	ctrl->m_start = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!ctrl->m_start)
		return (1);
	if (pthread_mutex_init(ctrl->m_start, NULL))
		return (free(ctrl->m_start), 1);
	ctrl->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!ctrl->print)
	{
		pthread_mutex_destroy(ctrl->m_start);
		free(ctrl->m_start);
		return (1);
	}
	if (pthread_mutex_init(ctrl->print, NULL))
	{
		free(ctrl->print);
		pthread_mutex_destroy(ctrl->m_start);
		free(ctrl->m_start);
		return (1);
	}
	return (0);
}

static int	set_table(t_ctrl *ctrl)
{
	int				i;
	pthread_mutex_t	**tmp;

	tmp = malloc(sizeof(pthread_mutex_t *) * (ctrl->nbr_philo + 1));
	ctrl->forks = tmp;
	if (!ctrl->forks)
		return (1);
	memset(ctrl->forks, 0, sizeof(pthread_mutex_t *) * (ctrl->nbr_philo + 1));
	i = 0;
	while (i < ctrl->nbr_philo)
	{
		ctrl->forks[i] = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		if (!ctrl->forks[i])
			return (clean_mutex(ctrl, 0), 1);
		if (pthread_mutex_init(ctrl->forks[i], NULL))
			return (clean_mutex(ctrl, i), 1);
		i++;
	}
	return (0);
}

static int	handle_arg(long int *target, char *content)
{
	long int	i;

	i = ft_atol(content);
	if (!check_ft_atol(i, content))
		return (1);
	*target = i;
	return (0);
}
