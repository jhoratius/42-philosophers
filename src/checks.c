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

void	lock_and_print(t_table *table, t_philo *philo, char *str)
{
	unsigned long	time;

	if (ft_emergency_call(table) == true && ft_strcmp(str, "died\n") != 0)
		return ;
	time = get_time() - table->start_time;
	pthread_mutex_lock(&table->print_lock);
	printf("%zu %d %s", time, philo->id, str);
	pthread_mutex_unlock(&table->print_lock);
}

int	check_emergency(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->someone_died);
	if (table->emergency_call == true)
		return (pthread_mutex_unlock(&table->someone_died), 0);
	pthread_mutex_unlock(&table->someone_died);
	while (++i < table->n_philosophes)
	{
		pthread_mutex_lock(&table->last_meal);
		if (get_time() - table->philosophes[i].last_meal > table->die_limit)
		{
			pthread_mutex_unlock(&table->last_meal);
			pthread_mutex_lock(&table->someone_died);
			table->emergency_call = true;
			pthread_mutex_unlock(&table->someone_died);
			lock_and_print(table, &table->philosophes[i], "died\n");
			return (0);
		}
		pthread_mutex_unlock(&table->last_meal);
	}
	return (1);
}

int	check_stomachs_full(t_table *table)
{
	pthread_mutex_lock(&table->someone_died);
	if (table->stomachs_full == true)
	{
		pthread_mutex_unlock(&table->someone_died);
		return (0);
	}
	pthread_mutex_unlock(&table->someone_died);
	return (1);
}

void	found_philo_corpse(t_table *table, int fork_1, int fork_2)
{
	pthread_mutex_lock(&table->someone_died);
	table->emergency_call = true;
	pthread_mutex_unlock(&table->someone_died);
	unlock_forks(table, fork_1, fork_2);
}
