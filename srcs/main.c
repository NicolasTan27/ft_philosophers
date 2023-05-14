/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:34:32 by ntan              #+#    #+#             */
/*   Updated: 2022/05/09 16:01:46 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == '\0')
			return (return_free("ERROR : EMPTY ARG\n"));
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (return_free("ERROR : INVALID ARGS\n"));
			else if (ft_strlen(av[i]) >= 10)
				return (return_free("ERROR : WHY SUCH LONG ARGS ?\n"));
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (check_args(ac, av))
			philosophers(ac, av);
	}
	else
		return (return_free("ERROR : MISSING OR TOO MUCH ARGS\n"));
	memrelease();
	return (0);
}
