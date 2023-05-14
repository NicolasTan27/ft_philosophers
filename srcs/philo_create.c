/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:55:31 by ntan              #+#    #+#             */
/*   Updated: 2022/05/09 15:31:51 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*create_data(int philo_num, t_prog *prog)
{
	t_data	*info;

	info = NULL;
	if (mempush(&info, sizeof(*info), 1) == 0)
		return (NULL);
	info->state = 4;
	info->id = philo_num;
	info->sprog = prog;
	info->last = 4;
	if (philo_num == prog->n_philo)
	{
		gettimeofday(&prog->time, NULL);
		pthread_mutex_lock(&prog->start_mutex);
		prog->start = 1;
		pthread_mutex_unlock(&prog->start_mutex);
	}
	return (info);
}

int	create_threads(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->n_philo)
	{
		if (pthread_create(&prog->threads[i], NULL,
				&alive, create_data(i + 1, prog)) != 0)
			return (return_free("FAIL TO CREATE A THREAD\n"));
		i++;
	}
	i = 0;
	while (i < prog->n_philo)
	{
		if (pthread_join(prog->threads[i], NULL) != 0)
			return (return_free("FAIL TO JOIN A THREAD\n"));
		i++;
	}
	pthread_mutex_destroy(&prog->mutex);
	pthread_mutex_destroy(&prog->start_mutex);
	pthread_mutex_destroy(&prog->take_fork);
	i = -1;
	while (++i < prog->n_philo)
		pthread_mutex_destroy(&prog->forks[i]);
	return (1);
}

int	philosophers(int ac, char **av)
{
	t_prog	*prog;

	prog = init_prog(ac, av);
	if (prog == NULL)
		return (0);
	if (create_threads(prog) == 0)
		return (0);
	return (1);
}
