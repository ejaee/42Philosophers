/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejachoi <ejachoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:01:30 by ejachoi           #+#    #+#             */
/*   Updated: 2023/03/12 16:59:49 by ejachoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "philo.h"

void	ft_free_mutex_fork(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(info->mutex_print));
	pthread_mutex_destroy(&(info->mutex_dead));
	pthread_mutex_destroy(&(info->mutex_lifecycle));
	while (i < info->philo_num && &(info->fork[i++]));
		pthread_mutex_destroy(&(info->fork[i++]));
	free(info->fork);
}

int	error_handler(char *message)
{
	write(2, "Error : ", 8);
	while (*message)
		write(2, message++, 1);
	return (1);
}

int	error_handler_mutex(t_info *info, char *message, int errno)
{
	write(2, "Error : ", 8);
	while (*message)
		write(2, message++, 1);
	if (errno == 1)
		pthread_mutex_destroy(&(info->mutex_print));
	else if (errno == 2)
	{
		pthread_mutex_destroy(&(info->mutex_print));
		pthread_mutex_destroy(&(info->mutex_dead));
	}
	else if (errno = 3)
	{
		pthread_mutex_destroy(&(info->mutex_print));
		pthread_mutex_destroy(&(info->mutex_dead));
		pthread_mutex_destroy(&(info->mutex_lifecycle));
	}
	else if (errno = 4)
		ft_free_mutex_fork(info);
	return (1);
}

long long	ft_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


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
		returm (1);
	returm (0);
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

 int	main(int argc, char **argv)
 {
	t_info info;

	if (argc != 5 && argc != 6)
		return (error_handler("invalid arguments\n"));
	if (!memset(&info, 0, sizeof(t_info)))
		return (error_handler("fail func memset\n"));
	if (init_info(argc, argv, &info))
		return (error_handler("fail info init\n"));
	if (init_mutex(&info))
		return (1);

 }