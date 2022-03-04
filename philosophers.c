/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:26:22 by ahhammou          #+#    #+#             */
/*   Updated: 2022/03/03 15:47:35 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define SEC_PER_DAY   86400
#define SEC_PER_HOUR  3600
#define SEC_PER_MIN   60

typedef struct s_data{
	int id;
	int left_fork;
	int fork;
	long long time_ate;
	int right_fork;
	int time_sleep;
	int time_2eat;
	int time_die;
	int dead;
	int all_eat;
	int ate;
	int i;
	int flag;
	int total_philos;
	long long timestart;
	struct s_test *locks;
	pthread_t t1;
	pthread_mutex_t forks[300];
	pthread_mutex_t eat_check;
	pthread_mutex_t phils;
} t_data;

typedef struct s_test{
	pthread_mutex_t forks[300];
	pthread_mutex_t eat_check;
	pthread_mutex_t phils;
	t_data philo[300];
} t_test;

long long	timestamp()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_usleep(long long sleep)
{
	struct timeval	t;
	long long fisttime;
	long long time;

	gettimeofday(&t, NULL);
	fisttime = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&t, NULL);
		time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		if (time - fisttime >= sleep)
		{
			printf("%lld\n", time - fisttime);
			break;
		}
	}
}

void *routine(void *philo)
{
	struct timeval tv;
	t_data *zeft;
	int i;
	long long time;
	long hms;

	i = 0;
	zeft = (t_data *)philo;
	// pthread_mutex_lock(&zeft->forks[zeft->id]);
	zeft->left_fork = zeft->id;
	zeft->right_fork = zeft->id + 1;
	if (zeft->id == zeft->total_philos)
		zeft->right_fork = 1;
	time = timestamp();
	while (1)
	{
		if (zeft->flag == 1)
			return(NULL);
		if ((timestamp() - zeft->time_ate) <= zeft->time_die)
		{
			gettimeofday(&tv, NULL);
			hms = tv.tv_sec % SEC_PER_DAY;
			hms = (hms + SEC_PER_DAY) % SEC_PER_DAY;
			int hour = hms / SEC_PER_HOUR;
			int min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
			int sec = (hms % SEC_PER_HOUR) % SEC_PER_MIN;
			printf("Time between meals: %lld\n", timestamp() - zeft->time_ate);
			if (pthread_mutex_lock(&zeft->forks[zeft->right_fork]) && pthread_mutex_lock(&zeft->forks[zeft->left_fork]))
			{
				printf("Philo[%d] Picked t \n", zeft->id);
				zeft->ate++;
				printf("Philo[%d] is eating \n zeft->ate = %d\n", zeft->id, zeft->ate);
				printf("Current local time: %d:%02d:%02d\n", hour + 4, min, sec);
				zeft->time_ate = timestamp();
				printf("left fork: %d, right fork: %d\n", zeft->left_fork, zeft->right_fork);
				ft_usleep(zeft->time_2eat);
				printf("Philo[%d] is Sleeping \n", zeft->id);
				pthread_mutex_unlock(&zeft->forks[zeft->left_fork]);
				pthread_mutex_unlock(&zeft->forks[zeft->right_fork]);
				ft_usleep(zeft->time_sleep);
			}
		}
		else
			zeft->flag = 1;
	}
	// pthread_mutex_unlock(&zeft->forks[zeft->id]);
	return (0);
}

void eat_sleep_rave_repeat(t_data *zeft, int i)
{
	struct timeval	ts;

	printf("Time between meals: %lld\n", timestamp() - zeft->time_ate);
	printf("Philo[%d] Picked t \n", i);
	if ((timestamp() - zeft->time_ate) <= 10000)
	{
		pthread_mutex_lock(&zeft->forks[zeft->id]);
		zeft->ate++;
		printf("Philo[%d] is eating \n zeft->ate = %d\n", i, zeft->ate);
		zeft->time_ate = timestamp();
		ft_usleep(100);
		printf("left fork: %d, right fork: %d\n", zeft->left_fork, zeft->right_fork);
		pthread_mutex_unlock(&zeft->forks[zeft->id]);
	}
	else
		zeft->flag = 1;
	printf("Philo[%d] is Sleeping \n", i);
	ft_usleep(zeft->time_sleep);
}

int main(int argv, char **argc)
{
	t_data *philo[atoi(argc[1])];
	t_test test;
	int threads[atoi(argc[1])];
	int i;
	struct timeval t;

	i = 1;
	while (i <= atoi(argc[1]))
	{
		philo[i] = malloc(sizeof(t_data) * 1);
		pthread_mutex_init(&philo[i]->phils, NULL);
		philo[i]->total_philos = atoi(argc[1]);
		philo[i]->time_2eat = atoi(argc[3]);
		philo[i]->ate = 0;
		philo[i]->flag = 0;
		philo[i]->time_sleep = atoi(argc[4]);
		philo[i]->time_die = atoi(argc[2]);
		philo[i]->id = i;
		philo[i]->i = 100;
		philo[i]->time_ate = timestamp();
		threads[i-1] = pthread_create(&philo[i]->t1, NULL, &routine, (void *)philo[i]);
		i++;
	}
	i = 1;
	usleep(50);
	i = 1;
	while (i <= atoi(argc[1]))
	{
		if (philo[i]->flag == 1)
			return (0);
		pthread_join(philo[i]->t1, NULL);
		i++;
	}
	i = 1;
	while (i <= atoi(argc[1]))
	{
		if (philo[i]->flag == 1)
			return (0);
		i++;
	}
	i = 1;
	while (i <= atoi(argc[1]))
	{
		pthread_mutex_destroy(&philo[i]->phils);
		i++;
	}
	return (0);
}
