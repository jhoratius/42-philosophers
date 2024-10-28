/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:03 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/10/26 16:16:23 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_routine(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->table->start);
	pthread_mutex_unlock(&philo->table->start);
	if (philo->id % 2 == 0)
		usleep(philo->table->eat_limit / 2);
	while (1)
	{
		if (philo->table->n_times_to_eat_each != -1
			&& i > (philo->table->n_times_to_eat_each - 1))
		{
			pthread_mutex_lock(&philo->table->someone_died);
			philo->table->stomachs_full = true;
			pthread_mutex_unlock(&philo->table->someone_died);
			break ;
		}
		if (philosopher_is_eating(philo->table, philo) == 1)
			break ;
		if (philosopher_is_sleeping(philo->table, philo) == 1)
			break ;
		if (philosopher_is_thinking(philo->table, philo) == 1)
			break ;
		i++;
	}
	return (NULL);
}

int	philosopher_is_eating(t_table *table, t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	if (!table || !philo || !philo->id)
		return (1);
	if (table->n_philosophes == 1)
		return (one_philo_routine(table, philo));
	left_fork = philo->id - 1;
	right_fork = (philo->id) % table->n_philosophes;
	pthread_mutex_lock(&table->last_meal);
	if (philo->last_meal == 0)
		philo->last_meal = get_time();
	pthread_mutex_unlock(&table->last_meal);
	if (left_fork < 0 || left_fork >= table->n_philosophes
		|| right_fork < 0 || right_fork >= table->n_philosophes)
		return (lock_and_print(table, philo, "err: Fork out of bounds"), 1);
	if (ft_emergency_call(table) == true)
		return (1);
	if (manage_forks(table, philo, left_fork, right_fork) == 1)
		return (1);
	philo->nb_eat_times += 1;
	return (0);
}

int	philosopher_is_sleeping(t_table *table, t_philo *philo)
{
	if (!table || !philo || !philo->id)
		return (1);
	if (ft_emergency_call(table) == true)
		return (1);
	lock_and_print(table, philo, "is sleeping\n");
	usleep(table->sleep_limit * 1000);
	return (0);
}

int	philosopher_is_thinking(t_table *table, t_philo *philo)
{
	if (!table || !philo || !philo->id)
		return (1);
	if (ft_emergency_call(table) == true)
		return (1);
	lock_and_print(table, philo, "is thinking\n");
	// if (table->n_philosophes % 2 == 1)
	if (table->sleep_limit < table->eat_limit
		&& table->sleep_limit + table->eat_limit > table->die_limit)
		usleep((table->eat_limit - table->sleep_limit));
	return (0);
}

int	one_philo_routine(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	lock_and_print(table, philo, "has taken a fork\n");
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	pthread_mutex_lock(&table->last_meal);
	while (1)
	{
		philo->last_meal = get_time();
		if (philo->last_meal - table->start_time > table->die_limit)
		{
			pthread_mutex_lock(&table->someone_died);
			table->emergency_call = true;
			pthread_mutex_unlock(&table->someone_died);
			lock_and_print(table, philo, "died\n");
			return (pthread_mutex_unlock(&table->last_meal), 1);
		}
	}
	pthread_mutex_unlock(&table->last_meal);
	return (0);
}
