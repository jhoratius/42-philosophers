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

	// fprintf(stderr, "L_fork:%d\n", L_fork);
	// fprintf(stderr, "R_fork:%d\n", R_fork);

	if (philo->time_to_eat == 0)
		philo->time_to_eat = get_time();
	if (L_fork < 0 || L_fork >= table->n_philosophes
		|| R_fork < 0 || R_fork >= table->n_philosophes)
			return (lock_and_print(table, philo, "err: Fork ID out of bounds"), 1);

	if (philo->nb_eat_times != 0
		&& get_time() - philo->time_to_eat > table->eat_limit)
		return (philo->is_dead = true,
			lock_and_print(table, philo, "died\n"), 1);

	pthread_mutex_lock(&table->forks[L_fork]);
	lock_and_print(table, philo, "has taken a fork\n");

	pthread_mutex_lock(&table->forks[R_fork]);
	lock_and_print(table, philo, "has taken a fork\n");

	lock_and_print(table, philo, "is eating\n");
	usleep(table->eat_limit * 1000);
	philo->time_to_eat = get_time();
	
	pthread_mutex_unlock(&table->forks[L_fork]);
	pthread_mutex_unlock(&table->forks[R_fork]);

	philo->nb_eat_times += 1;
	// lock_and_print(table, philo, "has eaten\n");
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

	// pthread_mutex_lock(&table->print_lock);
	// printf("Philosopher %d is sleeping\n", philo->id);
	// pthread_mutex_unlock(&table->print_lock);
	lock_and_print(table, philo, "is sleeping\n");
	usleep(table->sleep_limit * 1000);
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
	fprintf(stderr, "aaaa\n");
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	lock_and_print(table, philo, "has taken a fork\n");
	while(1)
	{
		if (get_time() - philo->time_to_eat > table->eat_limit)
		{
			philo->is_dead = true;
			lock_and_print(table, philo, "died\n");
			return (1);
		}
		// philo->time_to_eat = get_time();
	}
}
