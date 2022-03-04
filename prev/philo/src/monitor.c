/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:01:26 by anifanto          #+#    #+#             */
/*   Updated: 2021/12/16 20:35:30 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_monitor_die(t_info *info, int j)
{
	info->flag_die++;
	usleep(100);
	ft_print_death("%s%ld ms %d is died%s\n", &info->philos[j], RED);
	ft_die(&(*info));
}

void	ft_monitor(t_info *info)
{
	int	j;

	while (1)
	{
		j = -1;
		while (++j < info->size)
		{
			if (info->philos[j].nb_meal == info->max_eat)
				info->full_nb++;
			if (ft_time() - info->philos[j].t_last_meal >= info->time_die \
			&& (info->philos[j].nb_meal < info->max_eat))
			{
				ft_monitor_die(info, j);
				return ;
			}
			if (info->full_nb == info->size)
			{
				usleep(1000000);
				ft_die(&(*info));
				printf("%sAll philosophers have ate %d meals%s\n", \
				BOLD, info->max_eat, WHITE);
				return ;
			}
		}
	}
}
