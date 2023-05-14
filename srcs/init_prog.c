/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:02:33 by ntan              #+#    #+#             */
/*   Updated: 2022/05/09 15:57:35 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	return_free(char *str)
{
	write(2, str, ft_strlen(str));
	memrelease();
	return (0);
}

int	check_values(t_prog *prog, int ac)
{
	if (prog->n_philo <= 0)
		return (return_free("ERROR : INVALID NUMBER OF PHILOSOPHERS\n"));
	if (prog->die_time < 0)
		return (return_free("ERROR : INVALID TIME TO DIE\n"));
	if (prog->eat_time < 0)
		return (return_free("ERROR : INVALID TIME TO EAT\n"));
	if (prog->sleep_time < 0)
		return (return_free("ERROR : INVALID TIME TO SLEEP\n"));
	if (ac == 6 && prog->max_lunch < 0)
		return (return_free("ERROR : INVALID MAX EAT\n"));
	if (ac == 6 && prog->max_lunch == 0)
		return (return_free("WHY DON'T YOU WANT THEM TO EAT ?\n"));
	return (1);
}

int	init_prog_2(t_prog *prog)
{
	int	i;

	pthread_mutex_init(&prog->mutex, NULL);
	pthread_mutex_init(&prog->take_fork, NULL);
	pthread_mutex_init(&prog->start_mutex, NULL);
	if (mempush(&prog->threads, sizeof(pthread_t), prog->n_philo) == 0)
		return (return_free("ERROR : MEMORY ALLOCATION FAILED\n"));
	if (mempush(&prog->forks, sizeof(pthread_mutex_t), prog->n_philo) == 0)
		return (return_free("ERROR : MEMORY ALLOCATION FAILED\n"));
	if (mempush(&prog->philo_tab, sizeof(int), prog->n_philo) == 0)
		return (return_free("ERROR : MEMORY ALLOCATION FAILED\n"));
	if (mempush(&prog->fork_tab, sizeof(int), prog->n_philo) == 0)
		return (return_free("ERROR : MEMORY ALLOCATION FAILED\n"));
	i = 0;
	while (i < prog->n_philo)
	{
		pthread_mutex_init(&prog->forks[i], NULL);
		prog->philo_tab[i] = 0;
		prog->fork_tab[i] = 1;
		i++;
	}
	return (1);
}

void	*init_prog(int ac, char **av)
{
	t_prog	*prog;

	prog = NULL;
	if (mempush(&prog, sizeof(*prog), 1) == 0)
		return (NULL);
	prog->n_philo = ft_atoi(av[1]);
	prog->die_time = ft_atoi(av[2]);
	prog->eat_time = ft_atoi(av[3]);
	prog->sleep_time = ft_atoi(av[4]);
	prog->start = 0;
	prog->flag_last_eat = 0;
	if (ac == 6)
		prog->max_lunch = ft_atoi(av[5]);
	else
		prog->max_lunch = 0;
	if (check_values(prog, ac) == 0)
		return (NULL);
	if (init_prog_2(prog) == 0)
		return (NULL);
	return ((void *)prog);
}
