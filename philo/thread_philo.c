/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:09:16 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:40:21 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static	void	*solo_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork->fork_lock);
	philo->lfork->fork_state = 0;
	print_message(philo, "has taken a fork", 0);
	ft_usleep(philo->time_last_eat, philo->info->time_to_die);
	philo->lfork->fork_state = 1;
	pthread_mutex_unlock(&philo->lfork->fork_lock);
	print_message(philo, "die", 1);
	return (NULL);
}

static void	eating(t_philo *philo)
{
	time_t	current;

	hold_fork(philo);
	current = print_message_eating(philo);
	pthread_mutex_lock(&philo->access);
	philo->time_last_eat = current;
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->access);
	ft_usleep(current, philo->info->time_to_eat);
	release_fork(philo);
}

static void	sleeping(t_philo *philo)
{
	time_t	current;

	current = print_message(philo, "is sleeping", 0);
	ft_usleep(current, philo->info->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking", 0);
}

void	*do_thread(void *input_philo)
{
	t_philo	*philo;

	philo = (t_philo *)input_philo;
	if (philo->info->num_philo == 1)
		return (solo_philo(philo));
	if (philo->id % 2 == 0)
		usleep(800);
	while (1)
	{
		if (is_end_state(philo))
			return (0);
		eating(philo);
		if (is_end_state(philo))
			return (0);
		sleeping(philo);
		if (is_end_state(philo))
			return (0);
		thinking(philo);
	}
	return (0);
}
