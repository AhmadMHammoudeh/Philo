/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philos_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:50:37 by anifanto          #+#    #+#             */
/*   Updated: 2021/12/16 21:13:15 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	ft_monitor(t_philo *philo)
{
	long	time;

	time = ft_time();
	if (time - philo->t_last_meal > philo->info->time_die)
	{
		philo->info->flag_die++;
		time = time - philo->info->time_start;
		sem_wait(philo->info->print);
		printf("%s%ld ms %d is died%s\n", RED, time, philo->nb, WHITE);
		ft_free(philo->info);
		exit(1);
	}
	return (0);
}

int	ft_forks(t_philo *philo)
{
	sem_wait(philo->info->forks);
	ft_print("%s%ld ms %d has taken a fork%s\n", philo, GREEN);
	if (philo->info->size == 1)
	{
		ft_sleep(philo->info->time_die + 1);
		return (0);
	}
	if (ft_monitor(philo))
		return (0);
	sem_wait(philo->info->forks);
	ft_print("%s%ld ms %d has taken a fork%s\n", philo, GREEN);
	return (1);
}

void	ft_eat(t_philo *philo)
{
	if (ft_forks(philo))
	{
		philo->nb_meal++;
		ft_print("%s%ld ms %d is eating%s\n", philo, YELLOW);
		philo->t_last_meal = ft_time();
		ft_sleep(philo->info->time_eat);
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		if (ft_monitor(philo))
			return ;
		if (philo->nb_meal == philo->info->max_eat)
			exit (2);
	}
	else
	{
		if (ft_monitor(philo))
			return ;
	}
}

void	ft_life(t_philo *philo)
{
	philo->t_last_meal = philo->start_eat;
	if (philo->nb % 2 == 0)
		ft_sleep(philo->info->time_eat);
	while (!philo->info->flag_die && philo->nb_meal < philo->info->max_eat)
	{
		if (philo->nb_meal < philo->info->max_eat && !philo->info->flag_die)
			ft_eat(philo);
		if (philo->nb_meal < philo->info->max_eat && !philo->info->flag_die)
		{
			ft_print("%s%ld ms %d is sleeping%s\n", philo, BLUE);
			ft_sleep(philo->info->time_sleep);
		}
		if (philo->nb_meal < philo->info->max_eat && !philo->info->flag_die)
		{
			ft_print("%s%ld ms %d is thinking%s\n", philo, VIOLET);
			ft_sleep(5);
		}
	}
	ft_free(philo->info);
}

void	ft_start_philo(t_info *info)
{
	int		i;
	t_philo	*philo;
	pid_t	pid;

	i = -1;
	philo = info->philos;
	info->time_start = ft_time();
	philo->start_eat = info->time_start;
	while (++i < info->size)
	{
		philo->nb = i + 1;
		pid = fork();
		if (pid == -1)
		{
			printf("error: fork mistake\n");
			return ;
		}
		if (!pid)
		{
			ft_life(philo);
			break ;
		}
		else
			info->pid[i] = pid;
	}
}
