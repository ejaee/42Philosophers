/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:01:53 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/14 19:14:11 by ejachoi          ###   ########.fr       */
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

# define DEAD 1

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
	int				id;
	int				meals_count;
	int				left;
	int				right;
	long long		last_meal_time;
}	t_philo;

/* init.c */
int			init_info(int argc, char **argv, t_info *info);
int			init_mutex(t_info *info);
int			init_philo(t_philo *philo, t_info *info);
int			init_setting(int argc, char **argv, t_info *info, t_philo **philo);

/* error.c */
int			error_handler(char *message);
int			error_handler_mutex(t_info *info, char *message, int errno);
int			error_handler_philo(t_philo *philo, t_info *info, char *message);
void		free_mutex_fork(t_info *info);

/* philo.c */
void		*pattern(void *argv);
int			print_philo(t_info *info, long long time, int id, char *msg);
int			monitor_philo(t_philo *philo, t_info *info);

/* property.c */
void		set_is_dead(t_info *info);
void		set_meals_count_finish(t_info *info, t_philo *philo);
int			get_meals_count_finish(t_info *info);
int			get_is_dead(t_info *info);
long long	get_last_meal_time(t_philo *philo);

/* utils.c */
long long	ft_time(void);
void		usleep_for_efficiency(long long time, long long start, \
	t_info *info);
void		usleep_for_philo_control(t_philo *philo);
void		ft_free(t_philo *philo, t_info *info);
int			ft_atoi(const char *str);

#endif