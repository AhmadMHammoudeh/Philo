/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:19:43 by ahhammou          #+#    #+#             */
/*   Updated: 2022/05/05 12:14:47 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	philo_eat(t_data *philo)
{
	printer(philo, "Philo", "has both forks");
	pthread_mutex_lock(&philo->locks->lock);
	if (philo->ate + 1 == philo->locks->min_eater)
		philo->locks->min_achive++;
	pthread_mutex_unlock(&philo->locks->lock);
	printer(philo, "Philo", "is eating");
	philo->ate++;
	philo->timestamp = timestamp() - philo->timestart;
	philo->time_ate = timestamp();
	ft_usleep(philo->locks->time_2eat, philo);
	philo->last_action = 0;
	printer(philo, "Philo", "has dropped both forks");
	philo->r_f = 0;
	philo->l_f = 0;
	pthread_mutex_lock(philo->right_fork);
	philo->locks->fork_state[philo->right] = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	philo->locks->fork_state[philo->id] = 0;
	pthread_mutex_unlock(philo->left_fork);
}

void	fork_pick(t_data *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo->last_action = 1;
	if (philo->locks->fork_state[philo->id] == 0 && philo->l_f == 0)
	{
		philo->locks->fork_state[philo->id] = 1;
		philo->l_f = 1;
		printer(philo, "Philo", "Picked left fork");
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	if (philo->locks->fork_state[philo->right] == 0 && philo->r_f == 0)
	{
		philo->locks->fork_state[philo->right] = 1;
		philo->r_f = 1;
		printer(philo, "Philo", "Picked right fork");
	}
	pthread_mutex_unlock(philo->right_fork);
	if (philo->r_f == 1 && philo->l_f == 1)
		philo_eat(philo);
}
