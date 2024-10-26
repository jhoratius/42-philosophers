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

int	check_philo_died(t_meal_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->someone_died);
	while (i < table->n_philosophes)
	{
		if (table->philosophes[i].is_dead == true)
			return (pthread_mutex_unlock(&table->someone_died), 0);
		i++;
	}
	pthread_mutex_unlock(&table->someone_died);
	return (1);
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