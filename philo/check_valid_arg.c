/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:34:05 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:25:02 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	check_target_int(char *target)
{
	long long	temp;

	if (!target || !(*target))
		return (0);
	temp = ft_strtol(target);
	if (temp < -2147483648 || temp > 2147483647)
		return (0);
	else
		return (1);
}

int	check_valid_arg(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != 0)
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		if (!check_target_int(argv[i]))
			return (0);
		if (i == 1 && ft_strtol(argv[i]) == 0)
			return (0);
		if (i == 5 && ft_strtol(argv[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
