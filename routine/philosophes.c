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

void	lock_and_print(t_meal_table *table, t_philo *philo, char *str)
{
	//if (check_philo_died(table) == 0 && ft_strcmp(str, "died\n"))
	//	return ;
	pthread_mutex_lock(&table->print_lock);
	printf("%zu %d %s", get_time() - table->start_time, philo->id, str);
	pthread_mutex_unlock(&table->print_lock);
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
	// pthread_mutex_lock(&table->print_lock);
	// printf("%zu %d time to eat: %lu\n", get_time() - table->start_time, philo->id, get_time() - philo->time_to_eat);
	// pthread_mutex_unlock(&table->print_lock);

	if (philo->nb_eat_times != 0
		&& get_time() - philo->time_to_eat > table->die_limit)
	{
		pthread_mutex_lock(&table->emergency_call);
		philo->is_dead = true;
		pthread_mutex_unlock(&table->emergency_call);
		lock_and_print(table, philo, "died\n");
		return (1);
	}
	// if (check_philo_died(table) == 0)
	// 	return (1);
	if (manage_forks(table, philo, L_fork, R_fork) == 1)
		return (1);
	
	philo->nb_eat_times += 1;
	// pthread_mutex_lock(&table->print_lock);
	// printf("%zu %d time to eat: %lu\n", get_time() - table->start_time, philo->id, get_time() - philo->time_to_eat);
	// pthread_mutex_unlock(&table->print_lock);
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

int	eat_locks(t_meal_table *table,t_philo *philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&table->forks[fork_1]);
	//if (check_philo_died(table) == 0)
	//	return (pthread_mutex_unlock(&table->forks[fork_1]), 1);
	lock_and_print(table, philo, "has taken a fork\n");
	pthread_mutex_lock(&table->forks[fork_2]);

	//if (check_philo_died(table) == 0)
	//	return (pthread_mutex_unlock(&table->forks[fork_1]),
	//		pthread_mutex_unlock(&table->forks[fork_2]), 1);
	lock_and_print(table, philo, "has taken a fork\n");
	lock_and_print(table, philo, "is eating\n");
	usleep(table->eat_limit * 1000);
	if (philo->nb_eat_times != 0 && get_time() - philo->time_to_eat > table->die_limit)
	{
		pthread_mutex_lock(&table->emergency_call);
		philo->is_dead = true;
		pthread_mutex_unlock(&table->emergency_call);
		pthread_mutex_unlock(&table->forks[fork_1]);
		pthread_mutex_unlock(&table->forks[fork_2]);
		return (lock_and_print(table, philo, "died\n"), 1);
	}
	//lock_and_print(table, philo, "has eaten\n");
	philo->time_to_eat = get_time();
	pthread_mutex_unlock(&table->forks[fork_1]);
	pthread_mutex_unlock(&table->forks[fork_2]);
	return (0);
}

int	philosopher_is_sleeping(t_meal_table *table, t_philo *philo)
{
	if (!table || !philo || !philo->id)
		return (1);

	// philo->time_to_eat = get_time() - philo->time_to_eat;
	// if (philo->time_to_eat > table->eat_limit)
	// {
	// 	philo->is_dead = true;
	// 	pthread_mutex_lock(&table->print_lock);
	// 	printf("Philosopher %d has died\n", philo->id);
	// 	pthread_mutex_unlock(&table->print_lock);
	// 	return (1);
	// }
	// if (check_philo_died(table) == 0)
	// 	return (1);
	lock_and_print(table, philo, "is sleeping\n");
	usleep(table->sleep_limit * 1000);
	//lock_and_print(table, philo, "is awake\n");
	return (0);
}

int	philosopher_is_thinking(t_meal_table *table, t_philo *philo)
{
	if (!table || !philo || !philo->id)
		return (1);

	// philo->time_to_eat = get_time() - philo->time_to_eat;
	// if (philo->time_to_eat > table->eat_limit)
	// {
	// 	philo->is_dead = true;
	// 	pthread_mutex_lock(&table->print_lock);
	// 	printf("Philosopher %d has died\n", philo->id);
	// 	pthread_mutex_unlock(&table->print_lock);
	// 	return (1);
	// }

	// if (check_philo_died(table) == 0)
	// 	return (1);
	lock_and_print(table, philo, "is thinking\n");
	// pthread_mutex_lock(&table->print_lock);
	// printf("Philosopher %d is thinking\n", philo->id);
	// pthread_mutex_unlock(&table->print_lock);
	return (0);
}

unsigned long	get_time()
{
	struct timeval	curr_time;
	unsigned long	time;

	time = 0;
	gettimeofday(&curr_time, NULL);
	time = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	return (time);
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
			pthread_mutex_lock(&table->emergency_call);
			philo->is_dead = true;
			pthread_mutex_unlock(&table->emergency_call);
			lock_and_print(table, philo, "died\n");
			return (1);
		}
	}
	return (0);
}
