/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:22:36 by stempels          #+#    #+#             */
/*   Updated: 2025/08/26 16:54:17 by stempels         ###   ########.fr       */
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
	pthread_mutex_t	*forks[2];
}				t_philo;

typedef struct s_ctrl
{
	int					nbr_philo;
	int					nbr_dinner;
	int					start;
	long int			time_start;
	long int			time_die;
	long int			time_eat;
	long int			time_sleep;
	t_philo				**philo;
	pthread_mutex_t		*m_start;
	pthread_mutex_t		*print;
	pthread_mutex_t		**forks;
}						t_ctrl;
/**/
/*________________________________PHILO______________________________________*/
int			philosopher(t_ctrl *ctrl);
void		*philo_routine(void *arg);
/**/
/*________________________________UTILS______________________________________*/
int			check_ft_atol(long int res, char *str);
int			print_msg(char *msg, t_philo *philo);
void		ft_free_array(void ***array);
void		clean_mutex(t_ctrl *ctrl, int pos);
long int	ft_atol(const char *str);
long int	get_time(long int start_time);
#endif
