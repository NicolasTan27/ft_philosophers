/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntan <ntan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:36:56 by ntan              #+#    #+#             */
/*   Updated: 2022/05/09 15:30:22 by ntan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_prog {
	pthread_t		*threads;
	int				start;
	int				*philo_tab;
	int				*fork_tab;
	int				n_philo;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_lunch;
	int				last_to_eat;
	int				flag_last_eat;
	struct timeval	time;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	take_fork;
	pthread_mutex_t	start_mutex;
}			t_prog;

typedef struct s_data {
	struct timeval	think;
	struct timeval	meal;
	struct timeval	sleep;
	int				state;
	int				id;
	int				last;
	t_prog			*sprog;
}				t_data;

int			return_free(char *str);
void		*init_prog(int ac, char **av);

int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *str);
int			ft_isdigit(int c);

long int	t(t_data *philo);
long int	t2(struct timeval value);
void		print_eating(t_data *philo, int id);

int			check_meal(t_data *philo);
int			check_end_1(t_data *philo);
int			check_end(t_data *philo);

int			take_fork(t_data *philo);
int			update_state(t_data *philo);
int			print_status(t_data *philo);
void		*alive(void *arg);
t_data		*create_data(int philo_num, t_prog *prog);

int			create_threads(t_prog *prog);
int			philosophers(int ac, char **av);

/** GARBAGE COLLECTOR **/

# define ERROR 0
# define NOERR 1

typedef struct s_memlst		t_memlst;

struct	s_memlst
{
	void		*address;
	t_memlst	*nxt;
};

int			mempush(void *ptr, const size_t byte, const size_t size);
int			memfree(void *ptr);
int			memrelease(void);

#endif