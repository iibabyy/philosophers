/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/12 02:08:34 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_check(t_philo *philo)
{
	long int	time_without_eat;
	
	if (get_dead(philo) == true)
		return (true);
	time_without_eat = get_time(philo) - philo->last_eat;
	if (time_without_eat >= philo->data->time_to_die)
	{
		set_dead(philo);
		return (true);
	}
	return (false);
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		if (dead_check(philo) == true)
			return (pthread_mutex_unlock(&philo->fork), EXIT_FAILURE);
		mutex_printf("has taken a fork", get_time(philo), philo);
		pthread_mutex_lock(philo->next_fork);
		if (dead_check(philo) == true)
			return (drop_fork(philo), EXIT_FAILURE);
		mutex_printf("has taken a fork", get_time(philo), philo);
	}
	else
	{
		pthread_mutex_lock(philo->next_fork);
		if (dead_check(philo) == true)
			return (pthread_mutex_unlock(philo->next_fork), EXIT_FAILURE);
		mutex_printf("has taken a fork", get_time(philo), philo);
		if (dead_check(philo) == true)
			return (drop_fork(philo), EXIT_FAILURE);
		pthread_mutex_lock(&philo->fork);
		mutex_printf("has taken a fork", get_time(philo), philo);
	}
	return (EXIT_SUCCESS);
}

int	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->next_fork);
	return (EXIT_SUCCESS);
}

void	mutex_printf(char *str, long int time, t_philo *philo)
{
	pthread_mutex_t	*printf_mutex;

	printf_mutex = &philo->data->printf_mutex;
	pthread_mutex_lock(printf_mutex);
	printf("%li	%i	%s\n", time, philo->id + 1, str);
	pthread_mutex_unlock(printf_mutex);
}
