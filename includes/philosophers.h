/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:27:59 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/07/15 19:32:01 by jhoratiu         ###   ########.fr       */
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
	float		eating_time;
	float		sleeping_time;
	float		thinking_time;
	bool		is_dead;
}				t_philo;

typedef struct s_meal_table
{
	struct s_philo	*philosophes;
	int				n_philosophes;
	float			eat_limit;
	float			sleep_limit;
	float			think_limit;
	int				n_times_to_eat_each;
}				t_meal_table;

// parsing
bool		parsing(char **av);

// utils
int			ft_atoi(const char *nptr);
bool		ft_atoi2(const char *nptr, int *n);

# endif