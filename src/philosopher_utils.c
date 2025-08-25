/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 09:36:22 by stempels          #+#    #+#             */
/*   Updated: 2025/08/25 17:11:05 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_isspace(char c);

long int	ft_atol(const char *str)
{
	size_t			i;
	int				sign;
	long long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -sign;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res + (str[i] - 48);
		if ('0' <= str[i + 1] && str[i + 1] <= '9')
			res = res * 10;
		if (res > LONG_MAX && sign == 1)
			return (-1);
		if ((-1) * res < LONG_MIN && sign == -1)
			return (0);
		i++;
	}
	return (sign * res);
}

int	check_ft_atol(long int res, char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (res == 0 && str[i] != 0)
		return (0);
	if (res == -1 && str[i] != 1)
		return (0);
	return (1);
}

static int	ft_isspace(char c)
{
	if (c == 32 || (9 <= c && c <= 13))
		return (1);
	return (0);
}

void	clean_mutex_pos(t_ctrl *ctrl, int pos)
{
	int	i;

	i = 0;
	while (i < pos && ctrl->forks[i])
	{
		pthread_mutex_destroy(ctrl->forks[i]);
//		free(ctrl->forks[i]);
		ctrl->forks[i] = NULL;
		i++;
	}
//	while (ctrl->forks[i])
//	{
//		free(ctrl->forks[i]);
//		ctrl->forks[i] = NULL;
//		i++;
//	}
}

int	print_msg(char *msg, t_philo *philo)
{
	long int	time;

	if (pthread_mutex_lock(philo->ctrl->print))
		return (1);
	time = get_time(philo->ctrl->time_start);
	if (philo->ctrl->start == 1)
		printf("=== %ld ===	philo %d: %s !\n", time, philo->philo_id, msg);
	if (pthread_mutex_unlock(philo->ctrl->print))
		return (1);
	return (0);
}

long int	get_time(long int start_time)
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL))
		return (-1);
	return (((tmp.tv_sec * 1000000 + tmp.tv_usec) / 1000) - start_time);
}
