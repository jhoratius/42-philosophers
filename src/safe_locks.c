#include "philosophers.h"

bool	ft_emergency_call(t_table *table)
{
	pthread_mutex_lock(&table->someone_died);
	if (table->emergency_call == true)
		return (pthread_mutex_unlock(&table->someone_died), true);
	pthread_mutex_unlock(&table->someone_died);
	return (false);
}

void	lock_last_meal(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&table->last_meal);
}
