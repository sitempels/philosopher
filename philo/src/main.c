/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:21:34 by stempels          #+#    #+#             */
/*   Updated: 2025/09/01 09:58:15 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_ctrl_struct(t_ctrl *ctrl, int argc, char **argv);
static int	handle_arg(int *target, char *content);
static int	set_table(t_ctrl *ctrl);

int	main(int argc, char **argv)
{
	int		status;
	t_ctrl	ctrl;

	if (argc < 5 || argc > 6)
		return (write(2, "Error: wrong number of arguments\n", 32), 1);
	if (init_ctrl_struct(&ctrl, argc, argv))
		return (1);
	if (ctrl.nbr_philo == 0)
		return (write(2, "Error: at least one philosopher needed\n", 39), 1);
	if (ctrl.nbr_philo == 1)
	{
		printf("0	1 took a fork !\n");
		usleep(ctrl.time_die * 1000);
		printf("%d	1 died !\n", ctrl.time_die);
		return (0);
	}
	if (set_table(&ctrl))
		return (1);
	status = philosopher(&ctrl);
	free(ctrl.philo);
	clean_mutex(&ctrl, 0);
	return (status);
}

static int	init_ctrl_struct(t_ctrl *ctrl, int argc, char **argv)
{
	if (handle_arg(&ctrl->nbr_philo, argv[1])
		|| handle_arg(&ctrl->time_die, argv[2])
		|| handle_arg(&ctrl->time_eat, argv[3])
		|| handle_arg(&ctrl->time_sleep, argv[4]))
		return (1);
	ctrl->nbr_dinner = -1;
	if (argc == 6)
		if (handle_arg(&ctrl->nbr_dinner, argv[5]))
			return (1);
	ctrl->philo = NULL;
	ctrl->start = 1;
	if (pthread_mutex_init(&ctrl->m_start, NULL))
		return (1);
	if (pthread_mutex_init(&ctrl->m_print, NULL))
		return (1);
	return (0);
}

static int	set_table(t_ctrl *ctrl)
{
	int				i;
	pthread_mutex_t	*tmp;

	tmp = malloc(sizeof(pthread_mutex_t) * (ctrl->nbr_philo + 1));
	ctrl->forks = tmp;
	if (!ctrl->forks)
		return (1);
	memset(ctrl->forks, 0, sizeof(pthread_mutex_t) * (ctrl->nbr_philo + 1));
	i = 0;
	while (i < ctrl->nbr_philo)
	{
		if (pthread_mutex_init(&ctrl->forks[i], NULL))
			return (clean_mutex(ctrl, i), 1);
		i++;
	}
	return (0);
}

static int	handle_arg(int *target, char *content)
{
	int	i;

	i = ft_atoi(content);
	if (!check_ft_atoi(i, content))
		return (1);
	*target = i;
	return (0);
}
