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

int	philosopher_is_eating(t_meal_table *table, t_philo *philo)
{
	int		L_fork;
	int		R_fork;

	if (!table || !philo || !philo->id)
		return (1);
	L_fork = philo->id - 1;
	R_fork = (philo->id) % table->n_philosophes;

	if (L_fork < 0 || L_fork >= table->n_philosophes 
		|| R_fork < 0 || R_fork >= table->n_philosophes) {
		pthread_mutex_lock(&table->print_lock);
		fprintf(stderr, "Error: Fork IDs out of bounds (L_fork: %d, R_fork: %d)\n", L_fork, R_fork);
		pthread_mutex_unlock(&table->print_lock);
		return (1);
	}
	philo->time_to_eat = get_time() - table->start_time;
	if (philo->time_to_eat > table->eat_limit)
	{
		philo->is_dead = true;
		pthread_mutex_lock(&table->print_lock);
		printf("%zu %d has died\n", get_time() - table->start_time, philo->id);
		pthread_mutex_unlock(&table->print_lock);
		return (1);
	}

	pthread_mutex_lock(&table->forks[L_fork]);
	pthread_mutex_lock(&table->print_lock);
	printf("%zu %d has taken a 🍴\n", get_time() - table->start_time, philo->id);
	// printf("Philosopher %d has taken a 🍴\n", philo->id);
	pthread_mutex_unlock(&table->print_lock);

	pthread_mutex_lock(&table->forks[R_fork]);
	pthread_mutex_lock(&table->print_lock);
	printf("%zu %d has taken a 🍴\n", get_time() - table->start_time, philo->id);
	// printf("Philosopher %d has taken a 🍴\n", philo->id);
	pthread_mutex_unlock(&table->print_lock);

	pthread_mutex_lock(&table->print_lock);
	printf("%zu %d is eating 🍝\n", get_time() - table->start_time, philo->id);
	// printf("Philosopher %d is eating 🍝...\n", philo->id);
	pthread_mutex_unlock(&table->print_lock);

	philo->nb_eat_times += 1;
	usleep(table->eat_limit * 1000);

	pthread_mutex_unlock(&table->forks[L_fork]);
	pthread_mutex_unlock(&table->forks[R_fork]);
	pthread_mutex_lock(&table->print_lock);
	printf("%zu %d has eaten %d times\n", get_time() - table->start_time, philo->id, philo->nb_eat_times);
	pthread_mutex_unlock(&table->print_lock);
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

	pthread_mutex_lock(&table->print_lock);
	printf("Philosopher %d is sleeping\n", philo->id);
	pthread_mutex_unlock(&table->print_lock);
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

	pthread_mutex_lock(&table->print_lock);
	printf("Philosopher %d is thinking\n", philo->id);
	pthread_mutex_unlock(&table->print_lock);
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

	// struct timeval	end;
	// long			secds;
	// long			usecds;
	// double			elapsed;
	// int				v_ret;

	// gettimeofday(&start, NULL);
	// usleep(1000000);
	// gettimeofday(&end, NULL);
	// secds = end.tv_sec - start.tv_sec;
	// usecds = end.tv_usec - start.tv_usec;
	// if (usecds < 0)
	// {
	// 	secds -= 1;
	// 	usecds +=1000000;
	// }
	// elapsed = secds * 1000000.0 + usecds;
	// printf("Elapsed : %.0f microseconds\n", elapsed);