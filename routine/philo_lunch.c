/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lunch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:16:50 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/10/26 16:16:52 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat_locks(t_meal_table *table, t_philo *philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&table->forks[fork_1]);
	if (ft_emergency_call(table) == true)
		return (pthread_mutex_unlock(&table->forks[fork_1]), 1);
	lock_and_print(table, philo, "has taken a fork\n");
	pthread_mutex_lock(&table->forks[fork_2]);
	if (ft_emergency_call(table) == true)
		return (pthread_mutex_unlock(&table->forks[fork_1]),
			pthread_mutex_unlock(&table->forks[fork_2]), 1);
	lock_and_print(table, philo, "has taken a fork\n");
	lock_and_print(table, philo, "is eating\n");
	usleep(table->eat_limit * 1000);
	if (philo->nb_eat_times != 0
		&& get_time() - philo->time_to_eat > table->die_limit)
	{
		pthread_mutex_lock(&table->someone_died);
		philo->is_dead = true;
		pthread_mutex_unlock(&table->someone_died);
		pthread_mutex_unlock(&table->forks[fork_1]);
		pthread_mutex_unlock(&table->forks[fork_2]);
		return (lock_and_print(table, philo, "died\n"), 1);
	}
	philo->time_to_eat = get_time();
	pthread_mutex_unlock(&table->forks[fork_1]);
	pthread_mutex_unlock(&table->forks[fork_2]);
	return (0);
}

int	manage_forks(t_meal_table *table, t_philo *philo, int L_fork, int R_fork)
{
	if (L_fork < R_fork)
	{
		if (eat_locks(table, philo, L_fork, R_fork))
			return (1);
	}
	else
	{
		if (eat_locks(table, philo, R_fork, L_fork))
			return (1);
	}
	return (0);
}
