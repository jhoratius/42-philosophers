/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:16:30 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/10/26 16:16:31 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_and_print(t_meal_table *table, t_philo *philo, char *str)
{
	if (ft_emergency_call(table) == false && ft_strcmp(str, "died\n") == 1)
		return ;
	pthread_mutex_lock(&table->print_lock);
	printf("%zu %d %s", get_time() - table->start_time, philo->id, str);
	pthread_mutex_unlock(&table->print_lock);
}

bool	ft_emergency_call(t_meal_table *table)
{
	pthread_mutex_lock(&table->someone_died);
	if (table->emergency_call == true)
		return (pthread_mutex_unlock(&table->someone_died), true);
	pthread_mutex_unlock(&table->someone_died);
	return (false);
}

int	check_emergency(t_meal_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->someone_died);
	if (table->emergency_call == true)
		return (pthread_mutex_unlock(&table->someone_died), 0);
	while (++i < table->n_philosophes)
	{
		//printf("last meal : %zu\n", get_time() - table->philosophes[i].last_meal);
		if (get_time() - table->philosophes[i].last_meal > table->die_limit)
		{
			table->emergency_call = true;
			pthread_mutex_lock(&table->print_lock);
			printf("%zu %d %s", get_time() - table->start_time,
				table->philosophes[i].id, "died\n");
			pthread_mutex_unlock(&table->print_lock);
			//lock_and_print(table, &table->philosophes[i], "died\n");
			return (pthread_mutex_unlock(&table->someone_died), 0);
		}
	}
	pthread_mutex_unlock(&table->someone_died);
	return (1);
}

unsigned long	get_time(void)
{
	struct timeval	curr_time;
	unsigned long	time;

	time = 0;
	gettimeofday(&curr_time, NULL);
	time = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	return (time);
}
