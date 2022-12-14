/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:42:51 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:37:27 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long long	ft_strtol(char *str)
{
	long long	ans;
	int			sign;
	int			count;

	count = 0;
	ans = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\r'
		|| *str == '\n' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (++count && *str && *str >= '0' && *str <= '9')
	{
		ans = 10 * ans + (*str++ - '0');
		if ((count > 19 && sign == -1) || (ans < 0 && sign == -1))
			return ((-9223372036854775807 - 1));
		else if ((count > 19 && sign == 1) || (ans < 0 && sign == 1))
			return (9223372036854775807);
	}
	return (sign * ans);
}

time_t	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(time_t start, int time)
{
	usleep(time * 800);
	while (get_current_time_ms() - start < time)
		usleep(300);
}

time_t	print_message(t_philo *philo, char *str, int die)
{
	time_t	current;

	pthread_mutex_lock(&philo->info->print_lock);
	current = get_current_time_ms();
	if (!is_end_state(philo))
		printf("%ld %d %s\n", current - philo->start_time, philo->id, str);
	if (!die)
		pthread_mutex_unlock(&philo->info->print_lock);
	return (current);
}

time_t	print_message_eating(t_philo *philo)
{
	time_t	current;

	pthread_mutex_lock(&philo->info->print_lock);
	current = get_current_time_ms();
	if (!is_end_state(philo))
		printf("%ld %d is eating\n", current - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_lock);
	return (current);
}
