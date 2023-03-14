/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:35:00 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/14 19:17:39 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_for_efficiency(long long time, long long start, t_info *info)
{
	usleep(time * 0.8);
	while (!(get_is_dead(info)))
	{
		if ((ft_time() - start) >= time)
			break ;
		usleep(150);
	}
}

void	usleep_for_philo_control(t_philo *philo)
{
	if (philo->id % 2 == 1)
		usleep(500);
	else
		usleep(1000);
}

long long	ft_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_free(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
		pthread_mutex_destroy(&(info->fork[i++]));
	pthread_mutex_destroy(&(info->mutex_print));
	pthread_mutex_destroy(&(info->mutex_dead));
	pthread_mutex_destroy(&(info->mutex_lifecycle));
	free(info->fork);
	i = 0;
	while (i < info->philo_num)
		pthread_mutex_destroy(&(philo[i++].mutex_philo));
	free(philo);
}

int	ft_atoi(const char *str)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + (*str - '0');
		str++;
	}
	if (ret > 9223372036854775807 && sign == -1)
		return (-1);
	else if (ret > 9223372036854775807)
		return (-1);
	return (sign * ret);
}
