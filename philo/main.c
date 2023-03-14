/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:01:30 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/14 19:16:39 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	run_philo(t_philo *philo, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_create(&philo[i].thread, NULL, pattern, \
			&(philo[i])))
			return (1);
	}
	if (monitor_philo(philo, info))
		return (1);
	i = -1;
	while (++i < info->philo_num)
		pthread_join(philo[i].thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		return (error_handler("invalid arguments\n"));
	if (!memset(&info, 0, sizeof(t_info)))
		return (error_handler("fail func memset\n"));
	if (init_setting(argc, argv, &info, &philo))
		return (1);
	if (run_philo(philo, &info))
		return (error_handler_philo(philo, &info, "fail func pthread_create\n"));
	ft_free(philo, &info);
	return (0);
}
