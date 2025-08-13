/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:22:36 by stempels          #+#    #+#             */
/*   Updated: 2025/08/13 10:55:37 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_timeval
{
	time_t		tv_sec;
	suseconds_t	tv_usec;
}				t_timeval;

typedef struct	s_ctrl
{
	t_timeval		start;
	int				nbr_philo;
	int				philo_id;
	int				time_start;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_dinner;
	pthread_mutex_t	print;
	pthread_mutex_t	**forks;
}				t_ctrl;

void	philosopher(t_ctrl *ctrl);
void	*philo_routine(void *arg);
#endif
