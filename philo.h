/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:01:53 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/12 19:33:19 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_info
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_lifecycle;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	int				finished_eat;
	int				is_dead;
	long long		start_time;
}	t_info;

typedef struct s_philo
{
	pthread_mutex_t	mutex_philo;
	pthread_t		thread;
	t_info			*info;
	int				p_id;
	int				count_eat;
	int				left;
	int				right;
	long long		time_eat_last;
}	t_philo;

/* init.c */
int	init_info(int argc, char **argv, t_info *info);
int	init_mutex(t_info *info);
int	init_philo(t_philo *philo, t_info *info);

/* error.c */
int		error_handler(char *message);
int		error_handler_mutex(t_info *info, char *message, int errno);
int		error_handler_philo(t_philo *philo, t_info *info, char *message);
void	ft_free_mutex_fork(t_info *info);

/* philo.c */
void	*philo_lifecycle(void *argv);
void	philo_monitoring(t_philo *philo, t_info *info);

/* property.c */
void		set_info_isdead(t_info *info, int flag);
void		set_info_count_eat_finish(t_info *info, t_philo *philo);
int			get_info_count_eat_finish(t_info *info);
int			get_info_isdead(t_info *info);
long long		get_philo_time_eat_last(t_philo *philo);

/* utils.c */
long long	ft_time(void);
void		ft_usleep(long long time, long long start, t_info *info);
void		ft_philo_usleep(t_philo *philo);
void		ft_free(t_philo *philo, t_info *info);
int			ft_atoi(const char *str);


#endif