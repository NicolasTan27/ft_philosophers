/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:48:27 by ntan              #+#    #+#             */
/*   Updated: 2022/05/09 16:18:34 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meal(t_data *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->sprog->take_fork);
	while (i < philo->sprog->n_philo)
	{
		if (philo->sprog->philo_tab[i] < philo->sprog->max_lunch)
		{
			pthread_mutex_unlock(&philo->sprog->take_fork);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->sprog->take_fork);
	return (1);
}

int	check_end_1(t_data *philo)
{
	int	i;

	i = 0;
	if (check_meal(philo))
	{
		if (philo->sprog->flag_last_eat == 0)
		{
			print_eating(philo, philo->sprog->last_to_eat);
			philo->sprog->flag_last_eat = 1;
		}
		return (0);
	}
	pthread_mutex_lock(&philo->sprog->take_fork);
	while (i < philo->sprog->n_philo)
	{
		if (philo->sprog->philo_tab[i] == -1)
		{
			pthread_mutex_unlock(&philo->sprog->take_fork);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->sprog->take_fork);
	return (1);
}

int	print_died(t_data *philo)
{
	printf("%ld %d died\n", t(philo), philo->id);
	pthread_mutex_lock(&philo->sprog->take_fork);
	philo->sprog->philo_tab[philo->id - 1] = -1;
	pthread_mutex_unlock(&philo->sprog->take_fork);
	return (0);
}

int	check_end(t_data *philo)
{
	int	i;

	if (philo->sprog->max_lunch > 0)
	{
		if (check_end_1(philo) == 0)
			return (0);
	}
	else
	{
		i = 0;
		pthread_mutex_lock(&philo->sprog->take_fork);
		while (i < philo->sprog->n_philo)
		{	
			if (philo->sprog->philo_tab[i] == -1)
			{
				pthread_mutex_unlock(&philo->sprog->take_fork);
				return (0);
			}
			i++;
		}
		pthread_mutex_unlock(&philo->sprog->take_fork);
	}
	if (t2(philo->meal) >= philo->sprog->die_time)
		return (print_died(philo));
	return (1);
}
