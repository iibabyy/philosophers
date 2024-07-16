/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/16 16:04:40 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_check(t_philo *philo)
{
	long int		time_without_eat;
	pthread_mutex_t	*dead_mutex;
	bool			*check_dead;

	check_dead = &philo->dead;
	dead_mutex = &philo->check_dead_mutex;
	time_without_eat = (get_time(philo) - philo->last_eat);
	pthread_mutex_lock(dead_mutex);
	// printf("-----------------------------------------------------\n");
	// printf("philo[%d]: time %li - last eat : %li\n", philo->id + 1,
	// 		time_without_eat + philo->last_eat, philo->last_eat);
	// printf("\t=%li\n", time_without_eat);
	// printf("\t\ttime to die : %li\n", philo->data->time_to_die);
	if (*check_dead == true)
	{
		pthread_mutex_unlock(dead_mutex);
		return (true);
	}
	if (time_without_eat >= philo->data->time_to_die)
	{
		*check_dead = true;
		philo->last_eat = get_time(philo);
		set_dead_philo(philo);
		pthread_mutex_unlock(dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(dead_mutex);
	return (false);
}

int	take_fork(t_philo *philo)
{
	if ((philo->data->philos_number % 2 == 0 && philo->id % 2 == 0)
		|| (philo->data->philos_number % 2 == 1 && philo->id % 3 == 0))
	{
		pthread_mutex_lock(&philo->fork);
		if (mutex_printf("has taken a fork", get_time(philo),
			philo) == EXIT_FAILURE)
			return (pthread_mutex_unlock(&philo->fork), EXIT_FAILURE);
		pthread_mutex_lock(philo->next_fork);
		if (mutex_printf("has taken a fork", get_time(philo),
			philo) == EXIT_FAILURE)
			return (drop_fork(philo), EXIT_FAILURE);
	}
	else
	{
		pthread_mutex_lock(philo->next_fork);
		if (mutex_printf("has taken a fork", get_time(philo),
			philo) == EXIT_FAILURE)
			return (pthread_mutex_unlock(philo->next_fork), EXIT_FAILURE);
		pthread_mutex_lock(&philo->fork);
		if (mutex_printf("has taken a fork", get_time(philo),
			philo) == EXIT_FAILURE)
			return (drop_fork(philo), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	drop_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->next_fork);
		pthread_mutex_unlock(&philo->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->next_fork);
	}
	return (EXIT_SUCCESS);
}

int	mutex_printf(char *str, long int time, t_philo *philo)
{
	pthread_mutex_t	*printf_mutex;

	printf_mutex = &philo->data->printf_mutex;
	/* if (dead_check(philo) == true)
		return (EXIT_FAILURE); */
	pthread_mutex_lock(printf_mutex);
	if (get_dead(philo) == true)
		return (pthread_mutex_unlock(printf_mutex), EXIT_FAILURE);
	printf("%li	%i	%s\n", time / 1000, philo->id + 1, str);
	pthread_mutex_unlock(printf_mutex);
	return (EXIT_SUCCESS);
}
