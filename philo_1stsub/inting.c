/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inting.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:23:42 by ahhammou          #+#    #+#             */
/*   Updated: 2022/04/28 14:37:42 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

void	*call_function(void *philo)
{
	routine(philo);
	return (NULL);
}

void	ft_exit(t_test *test)
{
	int	i;

	i = 0;
	while (i < test->total_philos)
	{
		if (!pthread_mutex_lock(&test->forks[i]))
			pthread_mutex_unlock(&test->forks[i]);
		pthread_mutex_destroy(test->philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&test->print);
	pthread_mutex_destroy(&test->philos);
	pthread_mutex_destroy(&test->lock);
	ft_quickexit(test);
}

int	one_lonely_guy(t_test *test)
{
	printf("0 Philo[1]Picked left fork\n");
	ft_usleep(test->time_die);
	printf("%d PHILO [1] HAS DEID\n", test->time_die);
	return (-1);
}

void	initing(t_test *test, int i)
{
	test->philo[i].ate = 0;
	test->philo[i].timestamp = 0;
	test->philo[i].r_f = 0;
	test->philo[i].l_f = 0;
	test->philo[i].id = i;
	test->philo[i].p_id = i + 1;
	test->philo[i].last_action = 1;
	test->philo[i].locks = test;
	test->philo[i].left_fork = &test->forks[i];
	if (i + 1 == test->total_philos)
	{
		test->philo[i].right = 0;
		test->philo[i].right_fork = &test->forks[0];
	}
	else
	{
		test->philo[i].right = i + 1;
		test->philo[i].right_fork = &test->forks[i + 1];
	}
	pthread_create(&test->t1[i], NULL, &call_function, (void *)&test->philo[i]);
}
