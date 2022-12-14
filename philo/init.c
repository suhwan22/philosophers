/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:29:04 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:07:09 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	init_info(t_info *info, int argc, char **argv)
{
	memset(info, 0, sizeof(t_info));
	info->num_philo = (int)ft_strtol(argv[1]);
	info->time_to_die = (int)ft_strtol(argv[2]);
	info->time_to_eat = (int)ft_strtol(argv[3]);
	info->time_to_sleep = (int)ft_strtol(argv[4]);
	if (argc == 6)
		info->at_least_eat_times = (int)ft_strtol(argv[5]);
	else
		info->at_least_eat_times = -1;
}

int	malloc_philos(t_info *info, t_philo **philos)
{
	*philos = malloc(sizeof(t_philo) * info->num_philo);
	if (*philos == 0)
		return (0);
	return (1);
}

int	init_philos(t_info *info, t_philo *philos, t_end *end)
{
	int	i;

	end->end_state = 0;
	i = 0;
	while (i < info->num_philo)
	{
		philos[i].id = i + 1;
		philos[i].eat_cnt = 0;
		philos[i].info = info;
		philos[i].fork.fork_state = 1;
		philos[i].end = end;
		philos[i].lfork = &philos[i].fork;
		philos[i].rfork = &philos[(i + 1) % info->num_philo].fork;
		i++;
	}
	return (1);
}
