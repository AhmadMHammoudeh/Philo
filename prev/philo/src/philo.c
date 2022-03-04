/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:41:01 by anifanto          #+#    #+#             */
/*   Updated: 2022/03/03 16:53:04 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_create_philos(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->size)
	{
		info->philos[i].nb = i + 1;
		info->philos[i].start_eat = 0;
		info->philos[i].t_last_meal = info->time_start;
		info->philos[i].nb_meal = 0;
		info->philos[i].left_fork = &info->forks[i];
		info->philos[i].right_fork = &info->forks[i + 1];
		if (i == info->size - 1)
			info->philos[i].right_fork = &info->forks[0];
		info->philos[i].info = info;
		i++;
	}
}

void	ft_init_forks(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->size)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
		{
			printf("error: init mutex error\n");
			return ;
		}
		i++;
	}
}

void	ft_init_info(int argc, char **argv, t_info *info)
{
	info->size = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_eat = ft_atoi(argv[5]);
	else
		info->max_eat = MAX_INT;
	info->flag_die = 0;
	info->full_nb = 0;
	info->forks = malloc(info->size * sizeof(pthread_mutex_t));
	info->philos = malloc(info->size * sizeof(t_philo));
	if (!info->forks || !info->philos)
	{
		printf("error: allocated memmory error\n");
		ft_free(info);
		return ;
	}
	pthread_mutex_init(&info->print, NULL);
	info->time_start = ft_time();
	ft_create_philos(info);
	ft_init_forks(info);
}

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	if (ft_atoi(argv[1]) > 250)
	{
		printf("too much philosophers\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_arg(argc, argv))
	{
		ft_init_info(argc, argv, &info);
		ft_run_philo(&info);
		ft_monitor(&info);
		usleep(1000000);
		ft_free(&info);
		return (0);
	}
	printf("error: check input\n");
	return (0);
}
