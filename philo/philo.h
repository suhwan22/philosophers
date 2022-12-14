/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suhkim <suhkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:32:54 by suhkim            #+#    #+#             */
/*   Updated: 2022/12/14 13:44:47 by suhkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				at_least_eat_times;
	pthread_mutex_t	print_lock;
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t	fork_lock;
	int				fork_state;
}	t_fork;

typedef struct s_end
{
	pthread_mutex_t	end_lock;
	int				end_state;
}	t_end;

typedef struct s_philo
{
	int				id;
	int				eat_cnt;
	pthread_t		philo_thread;
	pthread_mutex_t	access;
	t_fork			fork;
	t_fork			*lfork;
	t_fork			*rfork;
	t_info			*info;
	time_t			start_time;
	time_t			time_last_eat;
	t_end			*end;
}	t_philo;

//utils.c
long long	ft_strtol(char *str);
time_t		get_current_time_ms(void);
void		ft_usleep(long start, int time);
time_t		print_message(t_philo *philo, char *str, int die);
time_t		print_message_eating(t_philo *philo);

//philo_utils.c
void		wait_join(pthread_t *monitor, t_philo *philos, int thread_num);
void		hold_fork(t_philo *philo);
void		release_fork(t_philo *philo);
int			is_end_state(t_philo *philo);

//init.c
void		init_info(t_info *info, int argc, char **argv);
int			init_philos(t_info *info, t_philo *philos, t_end *end);
int			malloc_philos(t_info *info, t_philo **philos);

//check_valid_arg.c
int			check_valid_arg(int argc, char **argv);

//mutex.c
int			init_mutex(t_info *info, t_philo *philos);
void		destroy_philo_mutex(t_philo *philos);

//thread_philo.c
void		*do_thread(void *input_philo);

//philo.c
int			do_philo(t_info *info, t_philo *philos);

//thread_monitor.c
void		*do_monitor(void *input_philos);

#endif
