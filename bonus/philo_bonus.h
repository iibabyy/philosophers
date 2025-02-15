/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:54:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/22 07:48:27 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

# define MALLOC_FAILED "syscall: malloc failed"
# define USAGE "verify your arguments"

typedef struct s_philo
{
	long long int	last_eat;
	int				eat_count;
	int				id;
	bool			is_dead;
}					t_philo;

typedef struct s_data
{
	sem_t			*forks;
	sem_t			*taking_forks;
	sem_t			*printf_mutex;
	sem_t			*dead_check;
	sem_t			*eat_check;
	sem_t			*kill_process;
	sem_t			*last_eat_sem;
	pthread_t		*monitor;
	struct s_philo	philo;
	long long		start_time;
	long long		last_eat;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				*pid;
	int				philos_number;
	int				must_eat;
}					t_data;

long int			ft_atol(const char *str);
int					error(char *err, int exit_status);
void				init_data(t_data *data);
int					parse(char **argv, t_data *data);
int					ft_usleep(long int time, t_data *data);
long long int		get_time(t_data *data);
void				routine(t_data *data);
int					drop_fork(t_data *data, int forks);
int					mutex_printf(char *str, long long time, t_data *data);
void				start_solo_philo(t_data *data);
void				solo_philo(t_data *data);
void				check_eat(t_data *data);
void				eat_checker(t_data *data);
void				dead_checker(t_data *data);
void				end_philos(t_data *data, int philo_number);
void				start_checkers(t_data *data);
void				exit_and_kill(char *err_mssg, int status, t_data *data);
int					take_fork(t_data *data);
bool				dead_philo(t_data *data);
void				check_philos(t_data *data);
int					wait_process(t_data *data);
int					start_process(t_data *data);
sem_t				*open_sem(char *sem_name, t_data *data);
sem_t				*create_sem(char *sem_name, t_data *data, int sem_value);
void				free_and_exit(char *error, int status,
						t_data *data, bool errno);
void				kill_sig(t_data *data);
long long			get_last_eat(t_data *data);
void				set_last_eat(long long time, t_data *data);
void				philo_monitoring(void *data_param);
void				start_philo_monitor(t_data *data);

#endif