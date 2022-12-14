/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 08:44:37 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:44:47 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_die(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->num_philo)
	{
		pthread_mutex_lock(&philos[i].access);
		if (get_current_time_ms() - philos[i].time_last_eat >= \
				philos[i].info->time_to_die)
		{
			print_message(philos, "die", 1);
			pthread_mutex_unlock(&philos[i].access);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].access);
		i++;
	}
	return (0);
}

int	check_full_eat(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->info->at_least_eat_times < 0)
		return (0);
	while (i < philos->info->num_philo)
	{
		pthread_mutex_lock(&philos[i].access);
		if (philos[i].eat_cnt < philos->info->at_least_eat_times)
		{
			pthread_mutex_unlock(&philos[i].access);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].access);
		i++;
	}
	return (1);
}

int	check_end_state(t_philo *philos)
{
	if (check_die(philos))
		return (1);
	if (check_full_eat(philos))
		return (2);
	return (0);
}

void	*do_monitor(void *input_philos)
{
	t_philo	*philos;
	int		flag;

	philos = (t_philo *)input_philos;
	while (1)
	{
		flag = check_end_state(philos);
		if (flag == 1)
		{
			pthread_mutex_lock(&philos->end->end_lock);
			philos->end->end_state = 1;
			pthread_mutex_unlock(&philos->end->end_lock);
			pthread_mutex_unlock(&philos->info->print_lock);
			return (0);
		}
		else if (flag == 2)
		{
			pthread_mutex_lock(&philos->end->end_lock);
			philos->end->end_state = 1;
			pthread_mutex_unlock(&philos->end->end_lock);
			return (0);
		}
		usleep(200);
	}
}
