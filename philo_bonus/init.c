/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:54:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/22 01:17:59 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_data(t_data *data)
{
	int	philo_num;

	philo_num = data->philos_number;
	data->pid = malloc(sizeof(int) * (philo_num + 2));
	if (data->pid == NULL)
		exit(error(MALLOC_FAILED, EXIT_FAILURE));
	data->forks = create_sem("forks", data, data->philos_number);
	data->printf_mutex = create_sem("printf_mutex", data, 1);
	data->dead_check = create_sem("dead_check", data, 0);
	data->eat_check = create_sem("eat_check", data, 0);
	data->taking_forks = create_sem("taking_forks", data, 1);
	data->kill_process = create_sem("kill_process", data, 0);
}

void	init_philo(t_data *data)
{
	data->forks = open_sem("forks", data);
	data->printf_mutex = open_sem("printf_mutex", data);
	data->dead_check = open_sem("dead_check", data);
	data->eat_check = open_sem("eat_check", data);
	data->taking_forks = open_sem("taking_forks", data);
	data->kill_process = open_sem("kill_process", data);
	data->pid = NULL;
}

sem_t	*create_sem(char *sem_name, t_data *data, int sem_value)
{
	sem_t	*semaphore;

	sem_unlink(sem_name);
	semaphore = sem_open(sem_name, O_CREAT, 0660, sem_value);
	if (semaphore == SEM_FAILED)
		free_and_exit("sem_open", EXIT_FAILURE, data, true);
	return (semaphore);
}

sem_t	*open_sem(char *sem_name, t_data *data)
{
	sem_t	*sem;

	sem = sem_open(sem_name, 0);
	if (sem == SEM_FAILED)
		free_and_exit("sem_open", EXIT_FAILURE, data, true);
	return (sem);
}
