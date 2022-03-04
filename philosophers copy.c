/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:26:22 by ahhammou          #+#    #+#             */
/*   Updated: 2022/03/04 12:34:18 by ahhammou         ###   ########.fr       */
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
	long long time_ate;
	int dead;
	int all_eat;
	int ate;
	int i;
	long long timestart;
	struct s_test *locks;
	pthread_t t1;
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	pthread_mutex_t eat_check;
	pthread_mutex_t phils;
} t_data;

typedef struct s_test{
	pthread_mutex_t forks[300];
	pthread_mutex_t eat_check;
	pthread_mutex_t phils;
	int total_philos;
	int time_sleep;
	int time_2eat;
	int time_die;
	int flag;
	t_data *philo;
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

// void *routine(void *philo)
// {
// 	struct timeval tv;
// 	t_test *n_philo;
// 	t_data *p;
// 	int i;
// 	long long time;
// 	long hms;
// 	int id;

// 	i = 0;
// 	n_philo = (t_test *)philo;
// 	// pthread_mutex_lock(&zeft->forks[zeft->id]);
// 	// n_philo->philo->right_fork = n_philo->forks[n_philo->philo->id + 1];
// 	// n_philo->philo->left_fork = n_philo->forks[n_philo->philo->id];
// 	// if (n_philo->philo->id == n_philo->total_philos)
// 	// 	n_philo->philo->right_fork = n_philo->forks[1];
// 	time = timestamp();
// 	gettimeofday(&tv, NULL);
// 	hms = tv.tv_sec % SEC_PER_DAY;
// 	hms = (hms + SEC_PER_DAY) % SEC_PER_DAY;
// 	int hour = hms / SEC_PER_HOUR;
// 	int min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
// 	int sec = (hms % SEC_PER_HOUR) % SEC_PER_MIN;
// 	printf("Current local time: %d:%02d:%02d\n", hour + 4, min, sec);
// 	printf("Time between meals: %lld\n", n_philo->philo->time_ate);
// 	printf("Time to die: %d\n", n_philo->time_die);
// 	id = n_philo->id;
// 	while (1)
// 	{
// 		if (n_philo->flag == 1)
// 			return(NULL);
// 		if ((timestamp() - n_philo->philo[id].time_ate) <= n_philo->time_die)
// 		{
// 			if (pthread_mutex_lock(&n_philo->philo[id].right_fork) && pthread_mutex_lock(&n_philo->philo[id].left_fork))
// 			{
// 				printf("Philo[%d] Picked t \n", n_philo->philo[id].id);
// 				n_philo->philo->ate++;
// 				printf("Philo[%d] is eating \n zeft->ate = %d\n", n_philo->philo[id].id, n_philo->philo->ate);
// 				n_philo->philo[id].time_ate = timestamp();
// 				// printf("left fork: %d, right fork: %d\n", n_philo->philo->left_fork, n_philo->philo->right_fork);
// 				ft_usleep(n_philo[id].time_2eat);
// 				printf("Philo[%d] is Sleeping \n", n_philo->philo[id].id);
// 				pthread_mutex_unlock(&n_philo->philo[id].right_fork);
// 				pthread_mutex_unlock(&n_philo->philo[id].left_fork);
// 				ft_usleep(n_philo->time_sleep);
// 			}
// 		}
// 		else
// 			n_philo->flag = 1;
// 	}
// 	// pthread_mutex_unlock(&zeft->forks[zeft->id]);
// 	return (0);
// }

void *routine(t_data *philo)
{
	struct timeval tv;
	// t_test *n_philo;
	// t_data *p;
	int i;
	long long time;
	long hms;
	int id;

	i = 0;
	// p = malloc(sizeof(t_data) * 1);
	// p = (t_data *)philo;
	// pthread_mutex_lock(&zeft->forks[zeft->id]);
	// n_philo->philo->right_fork = n_philo->forks[n_philo->philo->id + 1];
	// n_philo->philo->left_fork = n_philo->forks[n_philo->philo->id];
	// if (n_philo->philo->id == n_philo->total_philos)
	// 	n_philo->philo->right_fork = n_philo->forks[1];
	time = timestamp();
	gettimeofday(&tv, NULL);
	hms = tv.tv_sec % SEC_PER_DAY;
	hms = (hms + SEC_PER_DAY) % SEC_PER_DAY;
	int hour = hms / SEC_PER_HOUR;
	int min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
	int sec = (hms % SEC_PER_HOUR) % SEC_PER_MIN;
	printf("Current local time: %d:%02d:%02d\n", hour + 4, min, sec);
	printf("Time between meals: %lld\n", philo->time_ate);
	if (philo->locks)
		printf("dsa\n");
	printf("time->die%d\n", philo->locks->time_die);

	// while (1)
	// {
	// 	if (p->locks->flag == 1)
	// 		return(NULL);
	// 	if ((timestamp() - p->time_ate) <= p->locks->time_die)
	// 	{
	// 		if (pthread_mutex_lock(&n_philo->philo[id].right_fork) && pthread_mutex_lock(&n_philo->philo[id].left_fork))
	// 		{
	// 			printf("Philo[%d] Picked t \n", n_philo->philo[id].id);
	// 			n_philo->philo->ate++;
	// 			printf("Philo[%d] is eating \n zeft->ate = %d\n", n_philo->philo[id].id, n_philo->philo->ate);
	// 			n_philo->philo[id].time_ate = timestamp();
	// 			// printf("left fork: %d, right fork: %d\n", n_philo->philo->left_fork, n_philo->philo->right_fork);
	// 			ft_usleep(n_philo[id].time_2eat);
	// 			printf("Philo[%d] is Sleeping \n", n_philo->philo[id].id);
	// 			pthread_mutex_unlock(&n_philo->philo[id].right_fork);
	// 			pthread_mutex_unlock(&n_philo->philo[id].left_fork);
	// 			ft_usleep(n_philo->time_sleep);
	// 		}
	// 	}
	// 	else
	// 		n_philo->flag = 1;
	// }
	// // pthread_mutex_unlock(&zeft->forks[zeft->id]);
	return (0);
}

void	*call_function(void *philo)
{
	routine(philo);
	return (NULL);
}
// void eat_sleep_rave_repeat(t_data *zeft, int i)
// {
// 	struct timeval	ts;

// 	printf("Time between meals: %lld\n", timestamp() - zeft->time_ate);
// 	printf("Philo[%d] Picked t \n", i);
// 	if ((timestamp() - zeft->time_ate) <= 10000)
// 	{
// 		pthread_mutex_lock(&zeft->forks[zeft->id]);
// 		zeft->ate++;
// 		printf("Philo[%d] is eating \n zeft->ate = %d\n", i, zeft->ate);
// 		zeft->time_ate = timestamp();
// 		ft_usleep(100);
// 		printf("left fork: %d, right fork: %d\n", zeft->left_fork, zeft->right_fork);
// 		pthread_mutex_unlock(&zeft->forks[zeft->id]);
// 	}
// 	else
// 		// zeft->flag = 1;
// 	printf("Philo[%d] is Sleeping \n", i);
// 	ft_usleep(zeft->time_sleep);
// }

int main(int argv, char **argc)
{
	t_test *test;
	int i;
	struct timeval t;

	i = 0;
	test = malloc(sizeof(t_test) * 1);
	test->time_sleep = atoi(argc[4]);
	test->time_die = atoi(argc[2]);
	test->time_2eat = atoi(argc[3]);
	test->flag = 0;
	test->total_philos = atoi(argc[1]);
	test->philo = malloc(sizeof(t_data) * test->total_philos);
	// test->forks = malloc(sizeof(pthread_mutex_t) * test->total_philos);
	while (i < test->total_philos)
	{
		printf("%d\n", i);
		pthread_mutex_init(&test->philo[i].phils, NULL);
		test->philo[i].ate = 0;
		test->philo[i].id = i;
		test->philo[i].locks = test;
		test->philo[i].time_ate = timestamp();
		printf("Time of creation: %lld\n", timestamp());
		test->philo[i].left_fork = test->forks[i];
		test->philo[i].right_fork = test->forks[i+1];
		if (i == test->total_philos - 1)
			test->philo[i].right_fork = test->forks[0];
		printf("time->die%d\n", test->time_die);
		pthread_create(&test->philo[i].t1, NULL, &call_function, (void *)&test->philo[i]);
		i++;
	}
	i = 1;
	usleep(50);
	i = 1;
	while (i <= atoi(argc[1]))
	{
		pthread_join(test->philo[i].t1, NULL);
		if (test->flag == 1)
			return (0);
		i++;
	}
	i = 1;
	while (i <= atoi(argc[1]))
	{
		if (test->flag == 1)
			return (0);
		i++;
	}
	i = 1;
	while (i <= atoi(argc[1]))
	{
		pthread_mutex_destroy(&test->philo[i].phils);
		i++;
	}
	return (0);
}
