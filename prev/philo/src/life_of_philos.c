/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:51:43 by anifanto          #+#    #+#             */
/*   Updated: 2021/12/16 20:34:11 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_die(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->size)
	{
		pthread_detach(info->philos[i].thread);
		pthread_mutex_destroy(&info->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->print);
	return (0);
}

void	ft_eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork))
		return ;
	ft_print("%s%ld ms %d has taken a fork%s\n", philo, GREEN);
	if (pthread_mutex_lock(philo->right_fork))
		return ;
	ft_print("%s%ld ms %d has taken a fork%s\n", philo, GREEN);
	philo->t_last_meal = ft_time();
	philo->nb_meal++;
	ft_print("%s%ld ms %d is eating%s\n", philo, YELLOW);
	ft_sleep(philo->info->time_eat);
	if (pthread_mutex_unlock(philo->left_fork))
		return ;
	if (pthread_mutex_unlock(philo->right_fork))
		return ;
}

void	*ft_life(void *tmp)
{
	t_philo	*philo;

	philo = tmp;
	if (philo->nb % 2 == 0)
		ft_sleep(philo->info->time_eat);
	while (1)
	{
		if (philo->nb_meal < philo->info->max_eat && !philo->info->flag_die)
			ft_eat(philo);
		if (philo->nb_meal < philo->info->max_eat && !philo->info->flag_die)
		{
			ft_print("%s%ld ms %d is sleeping%s\n", philo, BLUE);
			ft_sleep(philo->info->time_sleep);
		}
		if (philo->nb_meal < philo->info->max_eat && !philo->info->flag_die)
			ft_print("%s%ld ms %d is thinking%s\n", philo, VIOLET);
	}
}

void	ft_print_death(char *str, t_philo *philo, char *color)
{
	long	time;

	if (pthread_mutex_lock(&philo->info->print))
		return ;
	time = ft_time() - philo->info->time_start;
	if (philo->info->size > philo->info->full_nb)
		printf(str, color, time, philo->nb, WHITE);
	if (pthread_mutex_unlock(&philo->info->print))
		return ;
}

void	ft_run_philo(t_info *info)
{
	int		i;

	i = 0;
	while (i < info->size)
	{
		if (pthread_create(&info->philos[i].thread, NULL, \
		ft_life, &info->philos[i]) != 0)
		{
			usleep(T_SLEEP);
			ft_free(info);
			return ;
		}
		i++;
	}
}
