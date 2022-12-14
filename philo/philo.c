/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:36:08 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:21:16 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	terminate_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->end->end_lock);
	philo->end->end_state = 1;
	pthread_mutex_unlock(&philo->end->end_lock);
}

static int	end_set(t_philo *philos, pthread_t *is_monitor, int i)
{
	terminate_philo(&philos[i]);
	wait_join(is_monitor, philos, i);
	return (0);
}

int	do_philo(t_info *info, t_philo *philos)
{
	int			i;
	time_t		current;
	pthread_t	monitor;

	i = 0;
	current = get_current_time_ms();
	while (i < info->num_philo)
	{
		philos[i].start_time = current;
		philos[i].time_last_eat = philos[i].start_time;
		if (pthread_create(&philos[i].philo_thread, 0, do_thread, &philos[i]))
			return (end_set(philos, 0, i));
		i++;
	}
	if (pthread_create(&monitor, 0, do_monitor, philos))
		return (end_set(philos, &monitor, philos->info->num_philo));
	wait_join(&monitor, philos, info->num_philo);
	return (1);
}
