/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:03 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/07 16:34:41 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	philosopher_is_eating(t_meal_table *table, t_philo *philo)
{
	int		L_fork;
	int		R_fork;

	if (!table || !philo || !philo->id || !(philo->id + 1))
		return ;
	L_fork = philo->id;
	R_fork = (philo->id + 1);
	printf("L_fork : %d\n", L_fork);
	printf("R_fork : %d\n", R_fork);
	pthread_mutex_lock(&table->forks[L_fork]);
	pthread_mutex_lock(&table->forks[R_fork]);

	printf("I'm eatin right now\n");
	usleep(philo->time_to_eat * 1000);

	pthread_mutex_unlock(&table->forks[L_fork]);
	pthread_mutex_unlock(&table->forks[R_fork]);
}
