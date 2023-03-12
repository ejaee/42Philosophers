/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choiejae <choiejae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:01:30 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/12 20:25:18 by choiejae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher(t_philo *philo, t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (pthread_create(&philo[i].thread, NULL, philo_lifecycle, \
			&(philo[i])))
			return (1);
	}
	philo_monitoring(philo, info);
	i = 0;
	while (i < info->philo_num)
		pthread_join(philo[i++].thread, NULL);
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
	if (init_info(argc, argv, &info))
		return (error_handler("fail info init\n"));
	if (init_mutex(&info))
		return (1);
	philo = malloc(sizeof(t_philo) * info.philo_num);
	if (!philo)
		return (error_handler_mutex(&info, "fail func mallot\n", 4));
	if (init_philo(philo, &info))
		return (error_handler_philo(philo, &info, "fail func mallot\n"));
	if (philosopher(philo, &info))
		return (error_handler_philo(philo, &info, "fail func pthread_create\n"));
	ft_free(philo, &info);
	return (0);
}
