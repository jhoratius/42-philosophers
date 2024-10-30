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

// philo 1 -> philo->id = 1
// left = 0
// right = 1
int	manage_forks(t_table *table, t_philo *philo, int L_fork, int R_fork)
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

int	eat_locks(t_table *table, t_philo *philo, int fork_1, int fork_2)
{
	if (lock_a_fork(table, philo, fork_1) == 1)
		return (1);
	if (lock_a_fork(table, philo, fork_2) == 1)
		return (pthread_mutex_unlock(&table->forks[fork_1]), 1);
	if (ft_emergency_call(table) == true || check_stomachs_full(table) == 0)
		return (unlock_forks(table, fork_1, fork_2), 1);
	lock_and_print(table, philo, "is eating\n");
	lock_last_meal(table, philo);
	if (usleep_alarm(table, philo, table->eat_limit) == 1)
		return (unlock_forks(table, fork_1, fork_2), 1);
	pthread_mutex_lock(&table->last_meal);
	if (philo->nb_eat_times != 0
		&& get_time() - philo->last_meal > table->die_limit)
	{
		pthread_mutex_unlock(&table->last_meal);
		if (ft_emergency_call(table) == true || check_stomachs_full(table) == 0)
			return (unlock_forks(table, fork_1, fork_2), 1);
		found_philo_corpse(table, fork_1, fork_2);
		return (lock_and_print(table, philo, "died\n"), 1);
	}
	pthread_mutex_unlock(&table->last_meal);
	unlock_forks(table, fork_1, fork_2);
	return (0);
}

int	lock_a_fork(t_table *table, t_philo *philo, int fork)
{
	pthread_mutex_lock(&table->forks[fork]);
	if (ft_emergency_call(table) == true || check_stomachs_full(table) == 0)
		return (pthread_mutex_unlock(&table->forks[fork]), 1);
	lock_and_print(table, philo, "has taken a fork\n");
	return (0);
}

int	usleep_alarm(t_table *table, t_philo *philo, unsigned long time_to_wait)
{
	unsigned long	time_passed;
	unsigned long	time_end;

	time_passed = get_time();
	time_end = get_time() + time_to_wait;
	while (time_passed < time_end)
	{
		usleep(50);
		pthread_mutex_lock(&table->last_meal);
		if (philo->nb_eat_times != 0
			&& get_time() - philo->last_meal > table->die_limit)
		{
			pthread_mutex_unlock(&table->last_meal);
			if (ft_emergency_call(table) == true
				|| check_stomachs_full(table) == 0)
				return (1);
			pthread_mutex_lock(&table->someone_died);
			table->emergency_call = true;
			pthread_mutex_unlock(&table->someone_died);
			return (lock_and_print(table, philo, "died\n"), 1);
		}
		pthread_mutex_unlock(&table->last_meal);
		time_passed = get_time();
	}
	return (0);
}

void	unlock_forks(t_table *table, int fork_1, int fork_2)
{
	pthread_mutex_unlock(&table->forks[fork_1]);
	pthread_mutex_unlock(&table->forks[fork_2]);
}
