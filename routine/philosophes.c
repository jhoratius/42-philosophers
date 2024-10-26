/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:13:03 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/20 18:31:10 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	*ft_routine(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->id % 2 == 1)
		usleep(philo->time_to_eat / 2);
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

int	philosopher_is_eating(t_meal_table *table, t_philo *philo)
{
	int		L_fork;
	int		R_fork;

	if (!table || !philo || !philo->id)
		return (1);
	if (table->n_philosophes == 1)
		return (one_philo_routine(table, philo));
	L_fork = philo->id - 1;
	R_fork = (philo->id) % table->n_philosophes;

	if (philo->time_to_eat == 0)
		philo->time_to_eat = get_time();
	if (L_fork < 0 || L_fork >= table->n_philosophes
		|| R_fork < 0 || R_fork >= table->n_philosophes)
			return (lock_and_print(table, philo, "err: Fork out of bounds"), 1);
	if (philo->nb_eat_times != 0
		&& get_time() - philo->time_to_eat > table->die_limit)
	{
		pthread_mutex_lock(&table->someone_died);
		philo->is_dead = true;
		table->emergency_call = true;
		pthread_mutex_unlock(&table->someone_died);
		lock_and_print(table, philo, "died\n");
		return (1);
	}
	if (ft_emergency_call(table) == true)
		return (1);
	if (manage_forks(table, philo, L_fork, R_fork) == 1)
		return (1);
	philo->nb_eat_times += 1;
	return (0);
}

int	philosopher_is_sleeping(t_meal_table *table, t_philo *philo)
{
	if (!table || !philo || !philo->id)
		return (1);
	if (ft_emergency_call(table) == true)
		return (1);
	lock_and_print(table, philo, "is sleeping\n");
	usleep(table->sleep_limit * 1000);
	return (0);
}

int	philosopher_is_thinking(t_meal_table *table, t_philo *philo)
{
	if (!table || !philo || !philo->id)
		return (1);

	if (ft_emergency_call(table) == true)
		return (1);
	lock_and_print(table, philo, "is thinking\n");
	return (0);
}

int	one_philo_routine(t_meal_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	lock_and_print(table, philo, "has taken a fork\n");
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	while(1)
	{
		philo->time_to_eat = get_time();
		if (philo->time_to_eat - table->start_time > table->die_limit)
		{
			pthread_mutex_lock(&table->someone_died);
			philo->is_dead = true;
			pthread_mutex_unlock(&table->someone_died);
			lock_and_print(table, philo, "died\n");
			return (1);
		}
	}
	return (0);
}
