/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:41:17 by anifanto          #+#    #+#             */
/*   Updated: 2021/12/22 15:16:13 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	if (res > 2147483647 || sign == -1 || res == 0)
		return (-1);
	return (res * sign);
}

long	ft_time(void)
{
	struct timeval	tp;
	long			rez;

	gettimeofday(&tp, NULL);
	rez = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	return (rez);
}

void	ft_free(t_info *info)
{
	free(info->philos);
	if (info->size != 2)
		free(info->forks);
}

void	ft_print(char *str, t_philo *philo, char *color)
{
	long	time;

	if (!philo->info->flag_die)
	{
		if (pthread_mutex_lock(&philo->info->print))
			return ;
		time = ft_time() - philo->info->time_start;
		if (philo->info->size > philo->info->full_nb)
			printf(str, color, time, philo->nb, WHITE);
		if (pthread_mutex_unlock(&philo->info->print))
			return ;
	}
}

void	ft_sleep(int time)
{
	long	life_time;

	life_time = ft_time();
	while (ft_time() - life_time < time)
		usleep(50);
}
