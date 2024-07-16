/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:22:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/16 15:47:16 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);
static int	ft_eat(t_philo *philo);

t_philo	*routine(void *philosopher)
{
	t_philo		*philo;
	long int	time;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&philo->data->printf_mutex);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	time = get_time(philo);
	// if (philo->data->philos_number % 2 == 1)
	// 	ft_usleep(50, philo);
	philo->last_eat = time;
	while (philo->data->check_dead != true)
	{
		if (ft_think(philo) == EXIT_FAILURE)
			return (NULL);
		if (ft_eat(philo) == EXIT_FAILURE)
			return (NULL);
		if (ft_sleep(philo) == EXIT_FAILURE)
			return (NULL);
	}
	return (NULL);
}

static int	ft_think(t_philo *philo)
{
	long int	time;

	time = get_time(philo);
	if (mutex_printf("is thinking", time, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_sleep(t_philo *philo)
{
	long int	time;

	time = get_time(philo);
	philo->next_sleep = philo->data->time_to_sleep;
	if (mutex_printf("is sleeping", time, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_usleep(philo->data->time_to_sleep, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_eat(t_philo *philo)
{
	long int	time;

	if (take_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	time = get_time(philo);
	philo->next_sleep = philo->data->time_to_sleep;
	philo->last_eat = time;
	if (mutex_printf("is eating", time, philo) == EXIT_FAILURE)
		return (drop_fork(philo), EXIT_FAILURE);
	increase_eat_count(philo);
	if (ft_usleep(philo->data->time_to_eat, philo) == EXIT_FAILURE)
		return (drop_fork(philo), EXIT_FAILURE);
	philo->last_eat += philo->data->time_to_eat;
	drop_fork(philo);
	return (EXIT_SUCCESS);
}

void	*solo_philo(void *data_arg)
{
	t_data	*data;
	t_philo	*philo;
	long	time;
	
	data = (t_data *)data_arg;
	philo = data->philos;
	data->start_time = get_time(philo);
	time = get_time(philo);
	pthread_mutex_lock(&philo->fork);
	mutex_printf("has taken a fork", time, philo);
	while (time < data->time_to_die)
	{
		time = get_time(philo);
		usleep(100);
	}
	mutex_printf("died", time, philo);
	return (NULL);
}
