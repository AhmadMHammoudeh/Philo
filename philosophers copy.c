/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:26:22 by ahhammou          #+#    #+#             */
/*   Updated: 2022/03/11 19:01:24 by ahhammou         ###   ########.fr       */
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
	int p_id;
	long long time_ate;
	int dead;
	int last_action;
	int all_eat;
	int ate;
	int i;
	int right;
	int r_f;
	int l_f;
	long long timestart;
	long long timestamp;
	struct s_test *locks;
	pthread_t t1;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_mutex_t eat_check;
	pthread_mutex_t phils;
} t_data;

typedef struct s_test{
	pthread_mutex_t *forks;
	pthread_mutex_t philos;
	int *fork_state;
	int total_philos;
	int time_sleep;
	int time_2eat;
	int time_die;
	long long time_start;
	int min_eater;
	int flag;
	int total_eat;
	int min_achive;
	t_data *philo;
} t_test;

long long	timestamp()
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

// gettimeofday(&tv, NULL);
// hms = tv.tv_sec % SEC_PER_DAY;
// hms = (hms + SEC_PER_DAY) % SEC_PER_DAY;
// int hour = hms / SEC_PER_HOUR;
// int min = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
// int sec = (hms % SEC_PER_HOUR) % SEC_PER_MIN;


void	ft_usleep(long long sleep)
{
	struct timeval	t;
	struct timeval	t2;
	long long fisttime;
	long long time;

	gettimeofday(&t, NULL);
	fisttime = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&t2, NULL);
		time = (t2.tv_sec * 1000) + (t2.tv_usec / 1000);
		if (time - fisttime >= sleep)
		{
			// printf("We are Usleeping%lld\n", time - fisttime);
			break;
		}
	}
}

int printer(t_data *philo, char *arg)
{
	if (philo->locks->flag == 1)
		return (0);
	printf("%lld", philo->timestamp);
	printf("%s\n", arg);
	return (1);
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

void philo_eat(t_data *philo)
{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(&philo->locks->philos);
		printf("Philo[%d] has both forks \n", philo->p_id);
		philo->locks->total_eat++;
		printf("Philo[%d] is eating zeft->ate = %d\n", philo->id, philo->locks->total_eat);
		philo->ate++;
		printf("Philo[%d] ate [%d] times \n", philo->p_id, philo->ate);
		if (philo->ate == philo->locks->min_eater)
			philo->locks->min_achive++;
		pthread_mutex_unlock(&philo->locks->philos);
		philo->time_ate = timestamp();
		ft_usleep(philo->locks->time_2eat);
		philo->last_action = 0;
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		if (philo->locks->fork_state[philo->id] == 1 && philo->locks->fork_state[philo->right] == 1)
		{
			philo->locks->fork_state[philo->id] = 0;
			philo->locks->fork_state[philo->right] = 0;
			philo->r_f = 0;
			philo->l_f = 0;
			// printer("Philo[%d] has dropped both forks \n", philo->p_id);
			printer(philo,"Philo[%d] has dropped both forks \n");
		}
}

// void fork_pick(t_data *philo)
// {
// 	long long stamp;

// 	stamp = timestamp() - philo->locks->time_start;
// 	philo->last_action = 1;
// 	if (philo->locks->fork_state[philo->id] == 0)
// 	{
// 		philo->locks->fork_state[philo->id] = 1;
// 		philo->l_f = 1;
// 		printf("%lld Philo[%d] Picked left fork \n", stamp, philo->id);
// 	}
// 	if (philo->locks->fork_state[philo->right] == 0)
// 	{
// 		philo->locks->fork_state[philo->right] = 1;
// 		philo->r_f = 1;
// 		printf("%lld Philo[%d] Picked right fork \n", stamp, philo->id);
// 	}
// 	if (philo->r_f == 1 && philo->l_f == 1)
// 	{
// 		philo_eat(philo);
// 	}
// }
void *fork_pick(t_data *philo)
{
	long long stamp;

	philo->timestamp = timestamp() - philo->timestart;
	philo->last_action = 1;
	if (philo->locks->fork_state[philo->id] == 0)
	{
		philo->locks->fork_state[philo->id] = 1;
		philo->l_f = 1;
		printf("%lld Philo[%d] Picked left fork \n", philo->timestamp, philo->p_id);}
	if (philo->locks->fork_state[philo->right] == 0 && philo->r_f == 0)
		{philo->locks->fork_state[philo->right] = 1;
		philo->r_f = 1;
		printf("%lld Philo[%d] Picked right fork \n", philo->timestamp, philo->id);}
	if (philo->r_f == 1 && philo->l_f == 1)
	{
		philo_eat(philo);
	}
	return (NULL);
}



void *routine(t_data *philo)
{
	struct timeval tv;
	int i;
	long long time;
	long hms;
	int id;

	i = 0;
	philo->time_ate = timestamp();
	philo->timestart = timestamp();
	while (1)
	{
		if (philo->locks->flag == 1 || philo->locks->min_achive == philo->locks->total_philos)
			return (NULL);
		if ((timestamp() - philo->time_ate) <= philo->locks->time_die)
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
			if (philo->locks->fork_state[philo->id] == 0 || philo->locks->fork_state[philo->right] == 0)
				fork_pick(philo);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
				philo->locks->flag = 1;
				printf("PHILO [%d] HAS DEID\n", philo->id);
		}
		usleep(10);
		if (philo->last_action == 0)
		{
			printf("Philo[%d] is Sleeping \n", philo->id);
			ft_usleep(philo->locks->time_sleep);
			philo->last_action = 2;
		}		
		// if (philo->last_action == 1)
		// {
		// 	printf("I am thinking Philo[%d]\n", philo->id);
		// 	philo->last_action = 1;
		// }
	}
	// pthread_mutex_unlock(&zeft->forks[zeft->id]);
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

void ft_exit(t_test *test)
{
	int i;
	
	i = 1;
	while (i <= test->total_philos)
	{
		if (test->flag == 1)
			break ;
		i++;
	}
	i = 1;
	while (i <= test->total_philos)
	{
		pthread_mutex_destroy(&test->philo[i].phils);
		i++;
	}
}

int main(int argv, char **argc)
{
	t_test *test;
	int i;
	struct timeval t;

	i = 1;
	test = malloc(sizeof(t_test) * 1);
	test->time_sleep = atoi(argc[4]);
	test->time_die = atoi(argc[2]);
	test->time_start = timestamp();
	printf("%lld time \n", test->time_start);
	test->time_2eat = atoi(argc[3]);
	test->flag = 0;
	test->min_achive = 0;
	test->total_eat = 0;
	if (argc[5])
		test->min_eater = atoi(argc[5]);
	else
		test->min_eater = 2147483647;
	test->total_philos = atoi(argc[1]);
	test->philo = malloc(sizeof(t_data) * test->total_philos);
	test->forks = malloc(sizeof(pthread_mutex_t) * test->total_philos);
	test->fork_state = malloc(sizeof(int) * test->total_philos);
	// test->forks = malloc(sizeof(pthread_mutex_t) * test->total_philos);
	while (i < test->total_philos + 1)
	{
		pthread_mutex_init(&test->philo[i].phils, NULL);
		test->philo[i].ate = 0;
		test->philo[i].timestamp = 0;
		test->philo[i].r_f = 0;
		test->philo[i].l_f = 0;
		test->fork_state[i - 1] = 0;
		test->philo[i].id = i - 1;
		test->philo[i].p_id = i;
		printf("%d\n", test->philo[i].id);
		test->philo[i].last_action = 1;
		test->philo[i].locks = test;
		printf("Time of creation: %lld\n", timestamp());
		test->philo[i].left_fork = &test->forks[i - 1];
		test->philo[i].right_fork = &test->forks[i];
		test->philo[i].right = i;
		if (i == test->total_philos)
		{
			test->philo[i].right = 0;
			test->philo[i].right_fork = &test->forks[0];
		}
		pthread_mutex_init(test->philo[i].left_fork, NULL);
		printf("time->die%d\n", test->time_die);
		pthread_create(&test->philo[i].t1, NULL, &call_function, (void *)&test->philo[i]);
		i++;
	}
	i = 1;
	while (i <= test->total_philos)
	{
		pthread_join(test->philo[i].t1, NULL);
		usleep(5);
		if (test->flag == 1)
			break ;
		i++;
	}
	ft_exit(test);
	return (0);
}
