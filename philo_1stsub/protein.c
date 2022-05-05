/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protein.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:22:35 by ahhammou          #+#    #+#             */
/*   Updated: 2022/05/05 13:34:51 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	loop_all(t_data *philo)
{
	if ((timestamp() - philo->time_ate) <= philo->locks->time_die)
		fork_pick(philo);
	else
	{
		pthread_mutex_lock(&philo->locks->lock);
		philo->locks->flag = 1;
		pthread_mutex_unlock(&philo->locks->lock);
		pthread_mutex_lock(&philo->locks->print);
		printf("%lld PHILO [%d] HAS DEID\n", \
			timestamp() - philo->timestart, philo->p_id);
		pthread_mutex_unlock(&philo->locks->print);
		philo->last_action = 4;
		return (0);
	}
	return (1);
}

int	big_loop(t_data *philo)
{
	pthread_mutex_lock(&philo->locks->lock);
	if (philo->locks->flag == 1 || \
		philo->locks->min_achive == philo->locks->total_philos)
	{
		pthread_mutex_unlock(&philo->locks->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->locks->lock);
	if (!loop_all(philo))
		return (0);
	usleep(10);
	if (philo->last_action == 0)
	{
		philo->timestamp = timestamp() - philo->timestart;
		printer(philo, "Philo", "is sleeping");
		ft_usleep(philo->locks->time_sleep, philo);
		philo->last_action = 2;
	}		
	if (philo->last_action == 2)
	{
		philo->timestamp = timestamp() - philo->timestart;
		printer(philo, "Philo", "is thinking");
		philo->last_action = 3;
	}
	return (1);
}

void	*routine(t_data *philo)
{
	usleep(10);
	philo->time_ate = timestamp();
	philo->timestart = timestamp();
	if (!((philo->p_id % 2) == 1))
	{
		if (philo->locks->time_2eat > 5)
			ft_usleep(philo->locks->time_2eat, philo);
		else
			ft_usleep(5, philo);
	}
	while (1)
	{
		if (!(big_loop(philo) == 1))
			break ;
	}
	return (NULL);
}
