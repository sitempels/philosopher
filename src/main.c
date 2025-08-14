/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:21:34 by stempels          #+#    #+#             */
/*   Updated: 2025/08/14 16:29:05 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_ctrl_struct(t_ctrl *ctrl, int argc, char **argv);
static int	handle_arg(int *target, char *content);
static int	set_table(t_ctrl *ctrl);

int	main(int argc, char **argv)
{
	t_ctrl	ctrl;

	if (argc < 5 || argc > 6)
		return (write(2, "Error: wrong number of arguments\n", 32));
	if (init_ctrl_struct(&ctrl, argc, argv))
		return (write(2, "Error: wrong argument value", 27), 1);
	printf("nbr_philo: %d   die: %d   eat: %d   sleep: %d   nbr_dinner: %d\n", ctrl.nbr_philo, ctrl.time_eat, ctrl.time_eat, ctrl.time_sleep, ctrl.nbr_dinner);
	if (set_table(&ctrl))
		return (clean_mutex_pos(&ctrl, ctrl.nbr_philo + 1), free(ctrl.forks), 1);
	if (philosopher(&ctrl))
		return (clean_mutex_pos(&ctrl, ctrl.nbr_philo + 1), free(ctrl.forks), 1);
	clean_mutex_pos(&ctrl, ctrl.nbr_philo + 1);
	free(ctrl.forks);
	return (0);
}

static int	init_ctrl_struct(t_ctrl *ctrl, int argc, char **argv)
{
	ctrl->start.tv_sec = 0;
	if (handle_arg(&ctrl->nbr_philo, argv[1]))
		return (1);
	if (handle_arg(&ctrl->time_die, argv[2]))
		return (1);
	if (handle_arg(&ctrl->time_eat, argv[3]))
		return (1);
	if (handle_arg(&ctrl->time_sleep, argv[4]))
		return (1);
	ctrl->nbr_dinner = -1;
	if (argc == 6)
	{
		if (handle_arg(&ctrl->nbr_dinner, argv[5]))
			return (1);
	}
	ctrl->philo = (t_philo **)malloc(sizeof(t_philo *) * ctrl->nbr_philo);
	if (!ctrl->philo)
		return (1);
	if (pthread_mutex_init(&ctrl->print, NULL))
		return (1);
	return (0);
}

static int	set_table(t_ctrl *ctrl)
{
	int	i;
	pthread_mutex_t	**tmp;

	tmp = (pthread_mutex_t **) malloc(sizeof(pthread_mutex_t *) * (ctrl->nbr_philo + 1));
	ctrl->forks = tmp;
	if (!ctrl->forks)
		return (1);
	ctrl->forks[ctrl->nbr_philo] = NULL;
	i = 0;
	while (i < ctrl->nbr_philo)
	{
		ctrl->forks[i] = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(ctrl->forks[i], NULL))
			return (clean_mutex_pos(ctrl, i), 1);
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
