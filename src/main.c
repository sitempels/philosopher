/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 07:21:34 by stempels          #+#    #+#             */
/*   Updated: 2025/08/13 10:10:43 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_ctrl_struct(t_ctrl *ctrl, int argc, char **argv);
static void	set_table(t_ctrl *ctrl);

int	main(int argc, char **argv)
{
	t_ctrl	*ctrl;

	if (argc < 5 || argc > 6)
		return (write(2, "Error: wrong number of arguments\n", 32));
//	if (check_argument(&argv[1]))
//		return (1);
	init_ctrl_struct(ctrl, argc, argv);
	set_table(ctrl);
	philosopher(ctrl);
	return (0);
}

static void	init_ctrl_struct(t_ctrl *ctrl, int argc, char **argv)
{
	ctrl->start = 0;
	ctrl->nbr_philo = ft_atoi(argv[1]);
	ctrl->time_die = ft_atoi(argv[2]);
	ctrl->time_eat = ft_atoi(argv[3]);
	ctrl->time_sleep = ft_atoi(argv[4]);
	ctrl->nbr_dinner = -1;
	if (argc == 5)
		ctrl->nbr_dinner = ft_atoi(argv[5]);
}

static void	set_table(t_ctrl *ctrl)
{
	int	i;

	ctrl->forks = (pthread_mutex t **) malloc(sizeof(pthread_muttex_t *) * ctrl->nbr_philo);
	i = 0;
	while (i < ctrl->nbr_philo)
	{
		ctrl->forks[i] = (pthread *) malloc(sizeof(pthread));
		if (pthread_mutex_init(forks[i], NULL))
			return (problems);
		i++;
	}
}
