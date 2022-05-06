/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:19:43 by ahhammou          #+#    #+#             */
/*   Updated: 2022/05/06 05:00:45 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	philo_eat(t_data *philo)
{
	// printer(philo, "Philo", "has both forks");
	printer(philo, "Philo", "is eating");
	pthread_mutex_lock(&philo->locks->lock);
	if (philo->ate + 1 == philo->locks->min_eater)
		philo->locks->min_achive++;
	pthread_mutex_unlock(&philo->locks->lock);
	philo->ate++;
	philo->timestamp = timestamp() - philo->timestart;
	philo->time_ate = timestamp();
	ft_usleep(philo->locks->time_2eat, philo);
	philo->last_action = 0;
	// printer(philo, "Philo", "has dropped both forks");
	philo->l_f = 0;
	philo->r_f = 0;
	pthread_mutex_lock(&philo->locks->forks[philo->right]);
	philo->locks->fork_state[philo->right] = philo->torite;
	pthread_mutex_unlock(&philo->locks->forks[philo->right]);
	pthread_mutex_lock(&philo->locks->forks[philo->id]);
	philo->locks->fork_state[philo->id] = philo->left;
	pthread_mutex_unlock(&philo->locks->forks[philo->id]);
}

void	fork_pick(t_data *philo)
{
	pthread_mutex_lock(&philo->locks->forks[philo->id]);
	philo->last_action = 1;
	if ((philo->locks->fork_state[philo->id] == 0 || philo->locks->fork_state[philo->id] == philo->p_id) && philo->l_f == 0)
	{
		philo->locks->fork_state[philo->id] = philo->p_id;
		philo->l_f = 1;
		printer(philo, "Philo", "Picked left fork");
	}
	pthread_mutex_unlock(&philo->locks->forks[philo->id]);
	pthread_mutex_lock(&philo->locks->forks[philo->right]);
	if ((philo->locks->fork_state[philo->right] == 0 || philo->locks->fork_state[philo->right] == philo->p_id) && philo->r_f == 0)
	{
		philo->locks->fork_state[philo->right] = philo->p_id;
		philo->r_f = 1;
		printer(philo, "Philo", "Picked right fork");
	}
	pthread_mutex_unlock(&philo->locks->forks[philo->right]);
	// if (philo->locks->fork_state[philo->right] == philo->p_id && philo->locks->fork_state[philo->id] == philo->p_id)
	if (philo->r_f == 1 && philo->l_f == 1)
		philo_eat(philo);
}
