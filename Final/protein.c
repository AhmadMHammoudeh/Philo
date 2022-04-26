/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protein.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:22:35 by ahhammou          #+#    #+#             */
/*   Updated: 2022/04/26 10:53:16 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	loop_all(t_data *philo)
{
	if ((timestamp() - philo->time_ate) <= philo->locks->time_die)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		if (philo->locks->fork_state[philo->id] == 0 || \
			philo->locks->fork_state[philo->right] == 0)
			fork_pick(philo);
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->locks->lock);
		philo->locks->flag = 1;
		pthread_mutex_unlock(&philo->locks->lock);
		printf("%lld PHILO [%d] HAS DEID\n", \
			timestamp() - philo->timestart, philo->p_id);
		return (0);
	}
	return (1);
}

int	loop_last(t_data *philo)
{
	if ((timestamp() - philo->time_ate) <= philo->locks->time_die)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		if (philo->locks->fork_state[philo->id] == 0 || \
			philo->locks->fork_state[philo->right] == 0)
			fork_pick_last(philo);
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
	}
	else
	{
		pthread_mutex_lock(&philo->locks->lock);
		philo->locks->flag = 1;
		pthread_mutex_unlock(&philo->locks->lock);
		printf("%lld PHILO [%d] HAS DEID\n", \
			timestamp() - philo->timestart, philo->p_id);
		return (0);
	}
	return (1);
}

int	big_loop(t_data *philo)
{
	pthread_mutex_lock(&philo->locks->lock);
	if (philo->locks->flag == 1 || \
		philo->locks->min_achive == philo->locks->total_philos)
		return (pthread_mutex_unlock(&philo->locks->lock) - 1);
	pthread_mutex_unlock(&philo->locks->lock);
	loop_all(philo);
	usleep(10);
	if (philo->last_action == 0)
	{
		philo->timestamp = timestamp() - philo->timestart;
		printer(philo, "Philo", "is sleeping");
		ft_usleep(philo->locks->time_sleep);
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

int	big_loop_last(t_data *philo)
{
	pthread_mutex_lock(&philo->locks->lock);
	if (philo->locks->flag == 1 || \
		philo->locks->min_achive == philo->locks->total_philos)
		return (pthread_mutex_unlock(&philo->locks->lock) - 1);
	pthread_mutex_unlock(&philo->locks->lock);
	loop_last(philo);
	usleep(10);
	if (philo->last_action == 0)
	{
		philo->timestamp = timestamp() - philo->timestart;
		printer(philo, "Philo", "is sleeping");
		ft_usleep(philo->locks->time_sleep);
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
	struct timeval	tv;
	int				i;

	i = 0;
	philo->time_ate = timestamp();
	philo->timestart = timestamp();
	if (!(philo->p_id % 2) == 1)
		usleep(25);
	if (philo->p_id != philo->locks->total_philos)
	{
		while (1)
		{
			if (!(big_loop(philo) == 1))
				break ;
		}
	}
	else
	{
		while (1)
		{
			if (!(big_loop_last(philo) == 1))
				break ;
		}
	}
}
