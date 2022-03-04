/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meal_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anifanto <stasy247@mail.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:38:52 by anifanto          #+#    #+#             */
/*   Updated: 2021/12/17 10:38:55 by anifanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	ft_check_meal(t_info *info)
{
	int	i;
	int	status;

	while (info->full_nb < info->size)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			info->flag_die++;
			break ;
		}
		else if (WIFEXITED(status) && WEXITSTATUS(status) == 2)
			info->full_nb++;
	}
	if (info->flag_die)
	{
		i = -1;
		while (++i < info->size)
			kill(info->pid[i], SIGKILL);
	}
	if (info->full_nb == info->size && !info->flag_die)
	{
		sem_close(info->print);
		printf("%sAll philosophers have ate %d meals\n", BOLD, info->max_eat);
	}
}
