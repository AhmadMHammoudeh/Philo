/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammou <ahhammou@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:07:08 by ahhammou          #+#    #+#             */
/*   Updated: 2022/04/26 20:59:20 by ahhammou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define SEC_PER_DAY   86400
# define SEC_PER_HOUR  3600
# define SEC_PER_MIN   60

typedef struct s_data{
	int				id;
	int				p_id;
	long long		time_ate;
	int				dead;
	int				last_action;
	int				all_eat;
	int				ate;
	int				i;
	int				right;
	int				r_f;
	int				l_f;
	long long		timestart;
	long long		timestamp;
	struct s_test	*locks;
	pthread_t		t1;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_check;
	pthread_mutex_t	phils;
}					t_data;

typedef struct s_test{
	pthread_mutex_t	*forks;
	pthread_mutex_t	philos;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	pthread_t		*t1;
	int				*fork_state;
	int				parser;
	int				total_philos;
	int				time_sleep;
	int				time_2eat;
	int				time_die;
	long long		time_start;
	int				min_eater;
	int				flag;
	int				total_eat;
	int				min_achive;
	t_data			*philo;
}					t_test;

long		ft_atoi(char *s, t_test *numb);
long long	timestamp(void);
void		ft_usleep(long long sleep);
int			printer(t_data *philo, char *arg, char *arg2);
void		philo_eat(t_data *philo);
void		philo_eat_last(t_data *philo);
void		*fork_pick(t_data *philo);
void		*fork_pick_last(t_data *philo);
void		*routine(t_data *philo);
void		*call_function(void *philo);
void		ft_exit(t_test *test);
int			one_lonely_guy(t_test *test);
void		initing(t_test *test, int i);
int			main(int argv, char **argc);
int			ft_quickexit(t_test *test);

#endif