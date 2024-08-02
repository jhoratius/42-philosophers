/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:27:59 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/02 18:19:56 by jhoratiu         ###   ########.fr       */
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

typedef struct s_philo
{
	int			id;
	float		time_to_eat;
	float		time_to_sleep;
	float		time_to_die;
	bool		is_dead;
}				t_philo;

typedef struct s_meal_table
{
	struct s_philo	*philosophes;
	int				n_philosophes;
	float			eat_limit;
	float			sleep_limit;
	float			die_limit;
	int				n_times_to_eat_each;
}				t_meal_table;

// parsing
int			*parsing(int ac, char **av);
int			ft_count_av(char **av);

// main
bool		ft_append_infos_table(t_meal_table *table, char **av);

// free
void		ft_free_struct(t_meal_table *table);

// utils
int			ft_atoi(const char *nptr);
bool		ft_atoi2(const char *nptr, int *n);
long		ft_check_sign(char c, int *i);

# endif