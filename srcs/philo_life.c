/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:53:27 by ntan              #+#    #+#             */
/*   Updated: 2022/05/09 16:18:16 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_data *philo)
{	
	if (philo->sprog->n_philo < 2)
		return (1);
	if (philo->id - 1 % 2 == 0)
	{
		pthread_mutex_lock
		(&philo->sprog->forks[philo->id % philo->sprog->n_philo]);
		pthread_mutex_lock(&philo->sprog->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_lock(&philo->sprog->forks[philo->id - 1]);
		pthread_mutex_lock
		(&philo->sprog->forks[philo->id % philo->sprog->n_philo]);
	}
	pthread_mutex_lock(&philo->sprog->take_fork);
	philo->sprog->philo_tab[philo->id - 1] += 1;
	philo->state = 1;
	gettimeofday(&philo->meal, NULL);
	if (philo->sprog->philo_tab[philo->id - 1] == philo->sprog->max_lunch)
		philo->sprog->last_to_eat = philo->id;
	pthread_mutex_unlock(&philo->sprog->take_fork);
	return (1);
}

int	update_state(t_data *philo)
{
	if (philo->state == 1
		&& t2(philo->meal) >= philo->sprog->eat_time)
	{
		pthread_mutex_unlock(&philo->sprog->forks[philo->id - 1]);
		pthread_mutex_unlock
		(&philo->sprog->forks[philo->id % philo->sprog->n_philo]);
		philo->state = 2;
		pthread_mutex_lock(&philo->sprog->take_fork);
		philo->sprog->fork_tab[philo->id - 1] = 1;
		philo->sprog->fork_tab[philo->id % philo->sprog->n_philo] = 1;
		pthread_mutex_unlock(&philo->sprog->take_fork);
		gettimeofday(&philo->sleep, NULL);
	}
	else if (philo->state == 2
		&& t2(philo->sleep) >= philo->sprog->sleep_time)
	{
		philo->state = 3;
	}
	return (1);
}

int	print_status(t_data *philo)
{
	pthread_mutex_lock(&philo->sprog->mutex);
	if (check_end(philo) == 0)
	{
		if (philo->state == 1)
		{
			pthread_mutex_unlock(&philo->sprog->forks[philo->id - 1]);
			pthread_mutex_unlock
			(&philo->sprog->forks[philo->id % philo->sprog->n_philo]);
		}
		pthread_mutex_unlock(&philo->sprog->mutex);
		return (0);
	}
	if (philo->last != philo->state)
	{	
		if (philo->state == 1)
			print_eating(philo, philo->id);
		if (philo->state == 2)
			printf("%ld %d is sleeping\n", t(philo), philo->id);
		else if (philo->state == 3)
			printf("%ld %d is thinking\n", t(philo), philo->id);
	}
	philo->last = philo->state;
	pthread_mutex_unlock(&philo->sprog->mutex);
	return (1);
}

int	wait_to_start(t_data *philo)
{
	pthread_mutex_lock(&philo->sprog->start_mutex);
	if (philo->sprog->start == 1)
	{
		pthread_mutex_unlock(&philo->sprog->start_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->sprog->start_mutex);
	return (0);
}

void	*alive(void *arg)
{
	t_data	*philo;

	philo = (t_data *)arg;
	while (1)
	{
		if (wait_to_start(philo) == 1)
			break ;
		usleep(100);
	}
	philo->meal = philo->sprog->time;
	while (1)
	{
		if (philo->state == 3 || philo->state == 4)
			take_fork(philo);
		if (philo->state != 0)
			update_state(philo);
		if (print_status(philo) == 0)
			break ;
		usleep(10);
	}
	return ((void *)0);
}
