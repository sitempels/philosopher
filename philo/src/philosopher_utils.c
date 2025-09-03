/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 09:36:22 by stempels          #+#    #+#             */
/*   Updated: 2025/09/03 11:05:19 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_isspace(char c);

int	print_msg(t_ctrl *ctrl, char *msg, t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(&ctrl->m_print);
	pthread_mutex_lock(&ctrl->m_start);
	if (get_time(ctrl, &time, ctrl->time_start, 1))
		return (pthread_mutex_unlock(&ctrl->m_start), 1);
	if (ctrl->start == 1 && philo)
		printf("%ld	%d %s\n", time, philo->philo_id, msg);
	pthread_mutex_unlock(&ctrl->m_start);
	pthread_mutex_unlock(&ctrl->m_print);
	return (0);
}

int	get_time(t_ctrl *ctrl, long int *time, long int start, int lock)
{
	struct timeval	tmp;

	if (gettimeofday(&tmp, NULL))
	{
		if (!lock)
		{
			pthread_mutex_lock(&ctrl->m_print);
			pthread_mutex_lock(&ctrl->m_start);
		}
		ctrl->start = 0;
		printf("XXX	get_time: Time calculation failure !\n");
		pthread_mutex_unlock(&ctrl->m_print);
		return (1);
	}
	*time = ((tmp.tv_sec * 1000000 + tmp.tv_usec) / 1000) - start;
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t		i;
	int			sign;
	long int	res;

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
		if ((res > INT_MAX && sign == 1)
			|| ((-1) * res < INT_MIN && sign == -1))
			return (0);
		i++;
	}
	if (str[i])
		return (1);
	return ((int)sign * res);
}

int	check_ft_atoi(int res, char *str)
{
	int	i;

	if (res < 0)
		return (write(2, "Error: Negative value argument\n", 31), 0);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (res == 0 && (str[i] != '0' || str[i + 1]))
		return (write(2, "Error: Argument exceed integer limits\n", 38), 0);
	if (res == 1 && (str[i] != '1' || str[i + 1]))
		return (write(2, "Error: Argument not an integer\n", 31), 0);
	return (1);
}

static int	ft_isspace(char c)
{
	if (c == 32 || (9 <= c && c <= 13))
		return (1);
	return (0);
}
