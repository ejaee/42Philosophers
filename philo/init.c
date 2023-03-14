/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:55:13 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/14 19:12:15 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_info(int argc, char **argv, t_info *info)
{
	info->start_time = ft_time();
	if (info->start_time == -1)
		return (1);
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->eat_times = ft_atoi(argv[5]);
		if (info->eat_times <= 0)
			return (1);
	}
	else
		info->eat_times = 0;
	info->finished_eat = 0;
	info->is_dead = 0;
	if (info->philo_num <= 0 || info->time_to_die < 0
		|| info->time_to_eat < 0 || info->time_to_sleep < 0)
		return (1);
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;

	if (pthread_mutex_init(&(info->mutex_print), NULL))
		return (error_handler("fail mutex init\n"));
	if (pthread_mutex_init(&(info->mutex_dead), NULL))
		return (error_handler_mutex(info, "fail mutex init\n", 1));
	if (pthread_mutex_init(&(info->mutex_lifecycle), NULL))
		return (error_handler_mutex(info, "fail mutex init\n", 2));
	info->fork = malloc(sizeof(pthread_mutex_t) * info->philo_num);
	if (!(info->fork))
		return (error_handler_mutex(info, "fail malloc", 3));
	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL))
			return (error_handler_mutex(info, "fail mutex init\n", 4));
	}
	return (0);
}

int	init_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		philo[i].id = i + 1;
		philo[i].info = info;
		philo[i].meals_count = 0;
		philo[i].left = i;
		philo[i].right = (i + 1) % info->philo_num;
		philo[i].last_meal_time = ft_time();
		if (pthread_mutex_init(&(philo[i].mutex_philo), NULL))
			return (1);
	}
	return (0);
}

int	init_setting(int argc, char **argv, t_info *info, t_philo **philo)
{
	if (init_info(argc, argv, info))
		return (error_handler("fail info init\n"));
	if (init_mutex(info))
		return (1);
	*philo = malloc(sizeof(t_philo) * info->philo_num);
	if (!philo)
		return (error_handler_mutex(info, "fail func mallot\n", 4));
	if (init_philo(*philo, info))
		return (error_handler_philo(*philo, info, "fail func mallot\n"));
	return (0);
}
