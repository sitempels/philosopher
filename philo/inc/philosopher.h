/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:22:36 by stempels          #+#    #+#             */
/*   Updated: 2025/09/03 11:04:42 by stempels         ###   ########.fr       */
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
# include <string.h>
/**/
/*________________________________STRUCT______________________________________*/
typedef struct s_philo
{
	int				philo_id;
	int				dinner;
	long int		last_meal;
	struct s_ctrl	*ctrl;
	pthread_mutex_t	m_meal;
	pthread_mutex_t	*forks[2];
}				t_philo;

typedef struct s_ctrl
{
	int					nbr_philo;
	int					nbr_dinner;
	int					start;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	long int			time_start;
	t_philo				*philo;
	pthread_mutex_t		m_start;
	pthread_mutex_t		m_print;
	pthread_mutex_t		*forks;
}						t_ctrl;
/**/
/*________________________________PHILO______________________________________*/
int			philosopher(t_ctrl *ctrl);
void		*rout(void *arg);
/**/
/*________________________________UTILS______________________________________*/
int			ft_atoi(const char *str);
int			check_ft_atoi(int res, char *str);
int			get_time(t_ctrl *ctrl, long *time, long int start, int unlock);
int			print_msg(t_ctrl *ctrl, char *msg, t_philo *philo);
void		clean_mutex(t_ctrl *ctrl, int pos);
#endif
