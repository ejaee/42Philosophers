/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:58:02 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/14 19:17:18 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_handler(char *message)
{
	while (*message)
		write(2, message++, 1);
	return (1);
}

int	error_handler_mutex(t_info *info, char *message, int errno)
{
	while (*message)
		write(2, message++, 1);
	if (errno == 1)
		pthread_mutex_destroy(&(info->mutex_print));
	else if (errno == 2)
	{
		pthread_mutex_destroy(&(info->mutex_print));
		pthread_mutex_destroy(&(info->mutex_dead));
	}
	else if (errno == 3)
	{
		pthread_mutex_destroy(&(info->mutex_print));
		pthread_mutex_destroy(&(info->mutex_dead));
		pthread_mutex_destroy(&(info->mutex_lifecycle));
	}
	else if (errno == 4)
		free_mutex_fork(info);
	return (1);
}

int	error_handler_philo(t_philo *philo, t_info *info, char *message)
{
	while (*message)
		write(2, message++, 1);
	ft_free(philo, info);
	return (1);
}

void	free_mutex_fork(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(info->mutex_print));
	pthread_mutex_destroy(&(info->mutex_dead));
	pthread_mutex_destroy(&(info->mutex_lifecycle));
	while (i < info->philo_num && &(info->fork[i++]))
		pthread_mutex_destroy(&(info->fork[i++]));
	free(info->fork);
}
