/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:46:27 by ntan              #+#    #+#             */
/*   Updated: 2022/05/04 17:23:38 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	t(t_data *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec - philo->sprog->time.tv_sec) * 1000
		+ (time.tv_usec / 1000 - philo->sprog->time.tv_usec / 1000));
}

long int	t2(struct timeval value)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec - value.tv_sec) * 1000
		+ (time.tv_usec / 1000 - value.tv_usec / 1000));
}

void	print_eating(t_data *philo, int id)
{
	printf("%ld %d has taken a fork\n", t(philo), id);
	printf("%ld %d has taken a fork\n", t(philo), id);
	printf("%ld %d is eating\n", t(philo), id);
}
