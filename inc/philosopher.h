/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:22:36 by stempels          #+#    #+#             */
/*   Updated: 2025/08/22 15:10:00 by stempels         ###   ########.fr       */
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
	int				dinner;
	long int		last_meal;
	struct s_ctrl	*ctrl;
	pthread_mutex_t	*forks[2];
	
}				t_philo;

typedef struct	s_ctrl
{
	int					nbr_philo;
	int					nbr_dinner;
	int					start;
	long int			time_start;
	long int			time_die;
	long int			time_eat;
	long int			time_sleep;
	t_philo				**philo;
	pthread_mutex_t		*print;
	pthread_mutex_t		**forks;
}						t_ctrl;

/**/
/*________________________________PHILO______________________________________*/
int		philosopher(t_ctrl *ctrl);
//void	*philo_routine(void *arg);
/**/
/*________________________________UTILS______________________________________*/
int				check_ft_atol(long int res, char *str);
void			clean_mutex_pos(t_ctrl *ctrl, int pos);
long int		ft_atol(const char *str);
#endif
