/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:35:54 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:40:37 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	wait_join(pthread_t *monitor, t_philo *philos, int thread_num)
{
	int	i;

	i = 0;
	while (i < thread_num)
		pthread_join(philos[i++].philo_thread, NULL);
	if (monitor)
		pthread_join(*monitor, NULL);
}

void	hold_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork->fork_lock);
	pthread_mutex_lock(&philo->rfork->fork_lock);
	philo->lfork->fork_state = 0;
	philo->lfork->fork_state = 0;
	print_message(philo, "has taken a fork", 0);
	print_message(philo, "has taken a fork", 0);
}

void	release_fork(t_philo *philo)
{
	philo->rfork->fork_state = 1;
	philo->lfork->fork_state = 1;
	pthread_mutex_unlock(&philo->lfork->fork_lock);
	pthread_mutex_unlock(&philo->rfork->fork_lock);
}

int	is_end_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->end->end_lock);
	if (philo->end->end_state)
	{
		pthread_mutex_unlock(&philo->end->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->end->end_lock);
	return (0);
}
