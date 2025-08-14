/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:22:36 by stempels          #+#    #+#             */
/*   Updated: 2025/08/14 16:22:49 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
/*________________________________INC_________________________________________*/
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <stdarg.h>
# include <pthread.h>
# include <sys/time.h>
/**/
/*________________________________MACRO_______________________________________*/
/**/
/*________________________________STRUCT______________________________________*/
typedef struct	s_timeval
{
	time_t		tv_sec;
	suseconds_t	tv_usec;
}				t_timeval;
/*
typedef struct	s_msg
{
	time_t	time;
	int		philo_id;
	e_state	state;
}
*/
typedef struct	s_philo
{
	int				philo_id;
	time_t			*time;
	t_timeval		start;
	pthread_mutex_t	print;
	
}				t_philo;

typedef struct	s_ctrl
{
	t_timeval		start;
	int				nbr_philo;
	int				time_start;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_dinner;
	t_philo			**philo;
	pthread_mutex_t	print;
	pthread_mutex_t	**forks;
}				t_ctrl;

/**/
/*________________________________PHILO______________________________________*/
int		philosopher(t_ctrl *ctrl);
//void	*philo_routine(void *arg);
/**/
/*________________________________UTILS______________________________________*/
int		ft_atoi(const char *str);
int		check_ft_atoi(int res, char *str);
void	clean_mutex_pos(t_ctrl *ctrl, int pos);
#endif
