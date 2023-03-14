/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:54:52 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/14 19:16:24 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_a_meal(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&(info->fork[philo->left]));
	if (print_philo(info, ft_time(), philo->id, "has taken a fork"))
		return (0);
	if (info->philo_num > 1)
	{
		pthread_mutex_lock(&(info->fork[philo->right]));
		if (print_philo(info, ft_time(), philo->id, "has taken a fork"))
			return (0);
		pthread_mutex_lock(&(philo->mutex_philo));
		philo->last_meal_time = ft_time();
		philo->meals_count++;
		pthread_mutex_unlock(&(philo->mutex_philo));
		if (print_philo(info, ft_time(), philo->id, "is eating"))
			return (0);
		usleep_for_efficiency((long long)info->time_to_eat, ft_time(), info);
		pthread_mutex_unlock(&(info->fork[philo->right]));
		pthread_mutex_unlock(&(info->fork[philo->left]));
		return (1);
	}
	else
	{
		usleep_for_efficiency((long long)info->time_to_die, ft_time(), info);
		pthread_mutex_unlock(&(info->fork[philo->left]));
		return (0);
	}
}

int	print_philo(t_info *info, long long time, int id, char *msg)
{
	if (time == -1)
		return (-1);
	pthread_mutex_lock(&(info->mutex_print));
	if (!(get_is_dead(info)))
		printf("%lld %d %s\n", ft_time() - info->start_time, id, msg);
	pthread_mutex_unlock(&(info->mutex_print));
	return (0);
}

int	monitor_philo(t_philo *philo, t_info *info)
{
	int			i;

	while (!get_is_dead(info))
	{
		if (info->eat_times != 0 && info->philo_num
			== get_meals_count_finish(info))
		{
			set_is_dead(info);
			break ;
		}
		i = -1;
		while (++i < info->philo_num)
		{
			if ((ft_time() - get_last_meal_time(&(philo[i])))
				> info->time_to_die)
			{
				if (print_philo(info, ft_time(), philo[i].id, "died"))
					return (1);
				set_is_dead(info);
				break ;
			}
		}
	}
	return (0);
}

void	*pattern(void *argv)
{
	t_info	*info;
	t_philo	*philo;

	philo = argv;
	info = philo->info;
	usleep_for_philo_control(philo);
	while (!get_is_dead(info))
	{
		if (eat_a_meal(philo, info))
		{
			set_meals_count_finish(info, philo);
			if (print_philo(info, ft_time(), philo->id, "is sleeping"))
				return ((void *)1);
			usleep_for_efficiency((long long)info->time_to_sleep, \
				ft_time(), info);
			if (print_philo(info, ft_time(), philo->id, "is thinking"))
				return ((void *)1);
		}
	}
	return (0);
}
