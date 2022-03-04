/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:41:01 by anifanto          #+#    #+#             */
/*   Updated: 2021/12/17 10:21:33 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	ft_create_philos(t_info *info)
{
	pid_t	*tmp_pid;
	t_philo	*philo;

	tmp_pid = malloc(info->size * sizeof(pid_t));
	if (!tmp_pid)
		return (0);
	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
	{
		free (tmp_pid);
		return (0);
	}
	info->philos = philo;
	info->pid = tmp_pid;
	info->philos->nb = 1;
	info->philos->start_eat = 0;
	info->philos->t_last_meal = info->time_start;
	info->philos->nb_meal = 0;
	info->philos->info = info;
	return (1);
}

int	ft_init_forks(t_info *info)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	info->forks = sem_open("/forks", O_CREAT, 0644, info->size);
	info->print = sem_open("/print", O_CREAT, 0644, 1);
	if (info->forks == SEM_FAILED || info->print == SEM_FAILED)
	{
		printf("error opening semaphore\n");
		return (0);
	}
	return (1);
}

int	ft_init_info(int argc, char **argv, t_info *info)
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
	info->time_start = ft_time();
	if (!ft_create_philos(info) || !ft_init_forks(info))
		return (0);
	return (1);
}

int	ft_check_arg(int argc, char **argv)
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

	if (ft_check_arg(argc, argv))
	{
		if (ft_init_info(argc, argv, &info))
		{
			ft_start_philo(&info);
			ft_check_meal(&info);
		}
		else
			printf("Error : Wrong Arguments\n");
		usleep(1000000);
		ft_free(&info);
		sem_post(info.print);
		sem_close(info.print);
		return (0);
	}
	printf("error: check input\n");
	return (0);
}
