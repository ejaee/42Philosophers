/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:47:28 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/12 19:47:37 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_info_isdead(t_info *info, int flag)
{
	pthread_mutex_lock(&(info->mutex_dead));
	info->is_dead = flag;
	pthread_mutex_unlock(&(info->mutex_dead));
}

void	set_info_count_eat_finish(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->mutex_lifecycle));
	if (info->eat_times != 0 && philo->count_eat == info->eat_times)
		info->finished_eat++;
	pthread_mutex_unlock(&(info->mutex_lifecycle));
}

int	get_info_count_eat_finish(t_info *info)
{
	int	count;

	pthread_mutex_lock(&(info->mutex_lifecycle));
	count = info->finished_eat;
	pthread_mutex_unlock(&(info->mutex_lifecycle));
	return (count);
}

int	get_info_isdead(t_info *info)
{
	pthread_mutex_lock(&(info->mutex_dead));
	if (info->is_dead)
	{
		pthread_mutex_unlock(&(info->mutex_dead));
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&(info->mutex_dead));
		return (0);
	}
}

long long	get_philo_time_eat_last(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(&(philo->mutex_philo));
	time = philo->time_eat_last;
	pthread_mutex_unlock(&(philo->mutex_philo));
	return (time);
}