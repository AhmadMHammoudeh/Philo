/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:26:22 by ahhammou          #+#    #+#             */
/*   Updated: 2022/05/05 12:06:02 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

int	ft_quickexit(t_test *test)
{
	free(test->philo);
	free(test->t1);
	free(test->fork_state);
	free(test->forks);
	free(test);
	return (-1);
}

int	ft_check_input(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '-')
		return (1);
	while (arg[i] != '\0' && ((arg[i] >= 48 && arg[i] <= 57) \
	|| arg[i] == ' ' || arg[i] == '-'))
		i++;
	if (arg[i] != '\0')
		return (1);
	return (0);
}

int	ft_errors(char **argc)
{
	int	i;

	i = 1;
	while (argc[i])
	{
		if (ft_check_input(argc[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

static int	intering(t_test *test, char **argc, int i)
{
	if (argc[5])
		test->min_eater = ft_atoi(argc[5], test);
	else
		test->min_eater = 2147483647;
	test->time_die = ft_atoi(argc[2], test);
	test->fork_state = malloc(sizeof(int) * test->total_philos);
	test->time_2eat = ft_atoi(argc[3], test);
	test->philo = malloc(sizeof(t_data) * test->total_philos);
	test->t1 = malloc(sizeof(pthread_t) * test->total_philos);
	test->forks = malloc(sizeof(pthread_mutex_t) * test->total_philos);
	test->flag = 0;
	test->min_achive = 0;
	while (++i < test->total_philos)
		pthread_mutex_init(&test->forks[i], NULL);
	pthread_mutex_init(&test->print, NULL);
	pthread_mutex_init(&test->philos, NULL);
	pthread_mutex_init(&test->lock, NULL);
	if (test->total_philos == 1)
		return (one_lonely_guy(test));
	i = -1;
	while (++i < test->total_philos)
		initing(test, i);
	return (0);
}

int	main(int argv, char **argc)
{
	t_test			*test;
	int				i;

	if (argv < 5 || argv > 6)
		return (0);
	if (ft_errors(argc) == 1)
		return (0);
	test = malloc(sizeof(t_test) * 1);
	test->total_philos = ft_atoi(argc[1], test);
	test->time_sleep = ft_atoi(argc[4], test);
	i = -1;
	if (intering(test, argc, i) == -1)
		return (0);
	i = -1;
	while (++i < test->total_philos)
	{
		pthread_mutex_lock(&test->forks[i]);
		test->fork_state[i] = 0;
		pthread_mutex_unlock(&test->forks[i]);
	}
	i = -1;
	while (++i < test->total_philos)
		pthread_join(test->t1[i], NULL);
	ft_exit(test);
	return (0);
}
