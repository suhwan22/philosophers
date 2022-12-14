/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:42:30 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:15:07 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	init_mutex_fork_access(t_philo *philo)
{
	if (pthread_mutex_init(&(philo->fork.fork_lock), NULL))
		return (0);
	if (pthread_mutex_init(&(philo->access), NULL))
	{
		pthread_mutex_destroy(&(philo->fork.fork_lock));
		return (0);
	}
	return (1);
}

int	init_mutex(t_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_init(&info->print_lock, NULL);
	pthread_mutex_init(&philos->end->end_lock, NULL);
	while (i < info->num_philo)
	{
		if (!init_mutex_fork_access(&(philos[i])))
		{
			while (i--)
			{
				pthread_mutex_destroy(&(philos[i].fork.fork_lock));
				pthread_mutex_destroy(&(philos[i].access));
			}
			return (0);
		}
		i++;
	}
	return (1);
}

void	destroy_philo_mutex(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philos->info->print_lock);
	pthread_mutex_destroy(&philos->end->end_lock);
	while (i < philos->info->num_philo)
	{
		pthread_mutex_destroy(&(philos[i].fork.fork_lock));
		pthread_mutex_destroy(&(philos[i].access));
		i++;
	}
}
