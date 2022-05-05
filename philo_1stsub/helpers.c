/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:21:14 by ahhammou          #+#    #+#             */
/*   Updated: 2022/05/05 12:17:10 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philosophers.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long	ft_atoi(char *s, t_test *numb)
{
	int				i;
	unsigned long	num;
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	if (s[0] == '-')
	{
		if (!s[++i])
			exit (write(2, "Error\n", 6));
		sign = -sign;
	}	
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			exit (write(2, "Error\n", 6));
		num = num * 10 + s[i++] - 48;
		if (num > 2147483648 && sign == -1)
			numb->parser = 1;
		if (num > 2147483647 && sign == 1)
			numb->parser = 1;
	}
	return ((int)num * sign);
}

void	ft_usleep(long long sleep, t_data *philo)
{
	struct timeval	t;
	struct timeval	t2;
	long long		fisttime;
	long long		time;

	gettimeofday(&t, NULL);
	fisttime = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	while (1)
	{
		pthread_mutex_lock(&philo->locks->lock);
		if (philo->locks->flag == 1 || \
			philo->locks->min_achive == philo->locks->total_philos)
		{
			pthread_mutex_unlock(&philo->locks->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->locks->lock);
		if (philo->locks->time_die < time - fisttime)
			break ;
		gettimeofday(&t2, NULL);
		time = (t2.tv_sec * 1000) + (t2.tv_usec / 1000);
		if (time - fisttime >= sleep)
			break ;
	}
}

void	ft_usleep_one(long long sleep)
{
	struct timeval	t;
	struct timeval	t2;
	long long		fisttime;
	long long		time;

	gettimeofday(&t, NULL);
	fisttime = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&t2, NULL);
		time = (t2.tv_sec * 1000) + (t2.tv_usec / 1000);
		if (time - fisttime >= sleep)
			break ;
	}
}

int	printer(t_data *philo, char *arg, char *arg2)
{
	pthread_mutex_lock(&philo->locks->print);
	pthread_mutex_lock(&philo->locks->lock);
	if (philo->locks->flag == 1 ||
		philo->locks->min_achive == philo->locks->total_philos)
	{
		pthread_mutex_unlock(&philo->locks->print);
		pthread_mutex_unlock(&philo->locks->lock);
		return (-1);
	}
	philo->timestamp = timestamp() - philo->timestart;
	printf("%lld ", philo->timestamp);
	printf("%s", arg);
	printf("[%d]", philo->p_id);
	printf("%s\n", arg2);
	pthread_mutex_unlock(&philo->locks->print);
	pthread_mutex_unlock(&philo->locks->lock);
	return (1);
}
