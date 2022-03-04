/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:41:11 by anifanto          #+#    #+#             */
/*   Updated: 2021/12/16 20:27:50 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define T_SLEEP	100
# define MAX_INT	2147483647
# define RED		"\e[1;31m"
# define YELLOW		"\e[1;33m"
# define GREEN		"\e[1;32m"
# define BLUE		"\e[1;34m"
# define BOLD		"\e[1m"
# define VIOLET		"\e[1;35m"
# define WHITE		"\e[0m"

typedef struct s_philo
{
	int				nb;
	int				nb_meal;
	long			start_eat;
	long			t_last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_info	*info;
}					t_philo;

typedef struct s_info
{
	int				size;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				max_eat;
	int				full_nb;
	int				flag_die;
	long			time_start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}					t_info;

long	ft_atoi(const char *str);
void	ft_free(t_info *info);
void	ft_run_philo(t_info *info);
long	ft_time(void);
void	ft_print(char *str, t_philo *philo, char *color);
void	ft_sleep(int time);
int		ft_die(t_info *info);
void	ft_monitor(t_info *info);
void	ft_print_death(char *str, t_philo *philo, char *color);

#endif
