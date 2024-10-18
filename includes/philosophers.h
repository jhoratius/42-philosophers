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

# ifndef PHILOSOPHERS_H
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

typedef struct s_meal_table t_meal_table;

typedef struct s_philo
{
	int						id;
	int						time_to_eat;
	bool					is_dead;
	int						nb_eat_times;
	pthread_t				thread;
	t_meal_table			*table;
}				t_philo;

typedef struct s_meal_table
{
	t_philo					*philosophes;
	int						n_philosophes;
	int						eat_limit;
	int						sleep_limit;
	int						die_limit;
	int						n_times_to_eat_each;
	unsigned long			start_time;
	pthread_mutex_t			*forks;
	pthread_mutex_t			print_lock;

}				t_meal_table;

// routine
	// philosophes
	int		philosopher_is_eating(t_meal_table *table, t_philo *philo);
	int		philosopher_is_sleeping(t_meal_table *table, t_philo *philo);
	int		philosopher_is_thinking(t_meal_table *table, t_philo *philo);
	bool	philosopher_is_dead(t_meal_table *table, t_philo *philo);
	unsigned long	get_time();

// src
	// parsing
	int			*parsing(int ac, char **av);
	int			ft_count_av(char **av);

	// main
	void		*ft_routine(void *arg);
	bool		ft_append_infos_table(t_meal_table *table, char **av);
	int			init_philosophes(t_meal_table *table);

	// free
	void		ft_free_struct(t_meal_table *table);

	// utils
	int			ft_atoi(const char *nptr);
	bool		ft_atoi2(const char *nptr, int *n);
	long		ft_check_sign(char c, int *i);

# endif