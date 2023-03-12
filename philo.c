/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:54:52 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/12 19:17:04 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_print(t_info *info, long long time, int p_id, char *msg)
{
	if (time == -1)
		return (-1);
	pthread_mutex_lock(&(info->mutex_print));
	if (!(get_info_isdead(info)))
		printf("%lld %d %s\n", ft_time() - info->start_time, p_id, msg);
	pthread_mutex_unlock(&(info->mutex_print));
	return (0);
}

int	philo_eat(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&(info->fork[philo->left]));
	philo_print(info, ft_time(), philo->p_id, "has taken a fork");
	if (info->philo_num > 1)
	{
		pthread_mutex_lock(&(info->fork[philo->right]));
		philo_print(info, ft_time(), philo->p_id, "has taken a fork");
		pthread_mutex_lock(&(philo->mutex_philo));
		philo->time_eat_last = ft_time();
		philo->count_eat++;
		pthread_mutex_unlock(&(philo->mutex_philo));
		philo_print(info, ft_time(), philo->p_id, "is eating");
		ft_usleep((long long)info->time_to_eat, ft_time(), info);
		pthread_mutex_unlock(&(info->fork[philo->right]));
		pthread_mutex_unlock(&(info->fork[philo->left]));
		return (1);
	}
	else
	{
		ft_usleep((long long)info->time_to_die, ft_time(), info);
		pthread_mutex_unlock(&(info->fork[philo->left]));
		return (0);
	}
}

void	*philo_lifecycle(void *argv)
{
	t_info	*info;
	t_philo	*philo;
	int		eat;

	philo = argv;
	info = philo->info;
	ft_philo_usleep(philo);
	while (!get_info_isdead(info))
	{
		eat = philo_eat(philo, info);
		if (eat)
		{
			set_info_count_eat_finish(info, philo);
			philo_print(info, ft_time(), philo->p_id, "is sleeping");
			ft_usleep((long long)info->time_to_sleep, ft_time(), info);
			philo_print(info, ft_time(), philo->p_id, "is thinking");
		}
	}
	return (0);
}

void	philo_monitoring(t_philo *philo, t_info *info)
{
	int			i;
	long long	time;

	while (!get_info_isdead(info))
	{
		if (info->eat_times != 0 && info->philo_num
			== get_info_count_eat_finish(info))
		{
			set_info_isdead(info, 1);
			break ;
		}
		i = -1;
		while (++i < info->philo_num)
		{
			time = ft_time();
			if ((time - get_philo_time_eat_last(&(philo[i]))) > info->time_to_die)
			{
				philo_print(info, ft_time(), philo[i].p_id, "died");
				set_info_isdead(info, 1);
				break ;
			}
		}
	}
}