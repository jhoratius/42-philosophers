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

int	eat_locks(t_meal_table *table, t_philo *philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&table->forks[fork_1]);
	if (ft_emergency_call(table) == true)
		return (pthread_mutex_unlock(&table->forks[fork_1]), 1);
	lock_and_print(table, philo, "has taken a fork\n");

	pthread_mutex_lock(&table->forks[fork_2]);
	if (ft_emergency_call(table) == true)
		return (unlock_forks(table, fork_1, fork_2), 1);
	lock_and_print(table, philo, "has taken a fork\n");

	// pthread_mutex_lock(&table->print_lock);
	// printf("%zu %d time to eat :%lu\n", get_time() - table->start_time, philo->id, get_time() - philo->last_meal);
	// pthread_mutex_unlock(&table->print_lock);
	if (ft_emergency_call(table) == true)
		return (unlock_forks(table, fork_1, fork_2), 1);
	lock_and_print(table, philo, "is eating\n");
	pthread_mutex_lock(&table->someone_died);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&table->someone_died);
	usleep(table->eat_limit * 1000);
	unlock_forks(table, fork_1, fork_2);
	return (0);
}

void	unlock_forks(t_meal_table *table, int fork_1, int fork_2)
{
	pthread_mutex_unlock(&table->forks[fork_1]);
	pthread_mutex_unlock(&table->forks[fork_2]);
}