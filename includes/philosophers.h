/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:27:59 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/20 18:28:20 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct s_meal_table	t_table;

typedef struct s_philo
{
	int						id;
	unsigned long			last_meal;
	int						nb_eat_times;
	pthread_t				thread;
	t_table					*table;
}				t_philo;

typedef struct s_meal_table
{
	t_philo					*philosophes;
	int						n_philosophes;
	unsigned long			eat_limit;
	unsigned long			sleep_limit;
	unsigned long			die_limit;
	int						n_times_to_eat_each;
	unsigned long			start_time;
	bool					stomachs_full;
	bool					emergency_call;
	pthread_mutex_t			start;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_lock;
	pthread_mutex_t			someone_died;
}				t_table;

// routine
// philosophes
void		*ft_routine(t_philo *philo);
int			philosopher_is_eating(t_table *table, t_philo *philo);
int			philosopher_is_sleeping(t_table *table, t_philo *philo);
int			philosopher_is_thinking(t_table *table, t_philo *philo);
int			one_philo_routine(t_table *table, t_philo *philo);

// philo_lunch
int			manage_forks(t_table *table, t_philo *philo,
				int l_fork, int r_fork);
int			eat_locks(t_table *table, t_philo *philo, int fork_1, int fork_2);
void		found_philo_corpse(t_table *table, int fork_1, int fork_2);
int			usleep_alarm(t_table *table, t_philo *philo,
				unsigned long time_to_wait);
void		unlock_forks(t_table *table, int fork_1, int fork_2);

// src
// checks
void		lock_and_print(t_table *table, t_philo *philo, char *str);
bool		ft_emergency_call(t_table *table);
int			check_emergency(t_table *table);
unsigned long	get_time(void);

// free
void		ft_free_struct(t_table *table);

// init
int			ft_initialisation(t_table *table, char **av);
int			init_table(t_table *table, char **av);
int			init_philosophes(t_table *table);
bool		ft_append_infos_table(t_table *table, char **av);

// main
int			end_of_simulation(t_table *table);

// parsing
int			*parsing(int ac, char **av);
int			ft_count_av(char **av);

// utils
int			ft_atoi(const char *nptr);
bool		ft_atoi2(const char *nptr, int *n);
long		ft_check_sign(char c, int *i);
int			ft_strcmp(char *s1, char *s2);

#endif