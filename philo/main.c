/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:37:23 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:01:38 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;
	t_end	end;

	if (!check_valid_arg(argc, argv))
		return (0);
	init_info(&info, argc, argv);
	if (!malloc_philos(&info, &philos))
		return (0);
	init_philos(&info, philos, &end);
	if (!init_mutex(&info, philos))
	{
		free(philos);
		return (0);
	}
	if (!do_philo(&info, philos))
	{
		destroy_philo_mutex(philos);
		free(philos);
		return (0);
	}
}
