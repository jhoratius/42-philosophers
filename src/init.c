# include "philosophers.h"

int	ft_initialisation(t_meal_table *table, char **av)
{
	if (init_table(table, av) == 1)
		return (1);
	if (init_philosophes(table) == 1)
		return (1);
	return (0);
}

int	init_table(t_meal_table *table, char **av)
{
	*table = (t_meal_table){0} ;
	if (ft_append_infos_table(table, av) == false)
		return (1);
	table->philosophes = malloc(table->n_philosophes * sizeof(t_philo));
	if (!table->philosophes)
		return (1);
	table->forks = malloc(table->n_philosophes * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (free(table->philosophes), 1);
	return (0);
}

int	init_philosophes(t_meal_table *table)
{
	int	i;

	if (!table)
		return (1);
	i = -1;
	while(++i < table->n_philosophes)
	{
		table->philosophes[i].id = i + 1;
		table->philosophes[i].is_dead = false;
		table->philosophes[i].nb_eat_times = 0;
		table->philosophes[i].table = table;
		table->philosophes[i].time_to_eat = 0;
		pthread_mutex_init(&table->forks[i], NULL);
	}
	pthread_mutex_init(&table->print_lock, NULL);
	pthread_mutex_init(&table->someone_died, NULL);
	table->start_time = get_time();
	i = -1;
	while (++i < table->n_philosophes)
	{
		if(pthread_create(&table->philosophes[i].thread, NULL, 
			(void *)ft_routine, &table->philosophes[i]) != 0)
			return (printf("failed to create\n"), 1);
	}
	i = -1;
	while (++i < table->n_philosophes)
		if (pthread_join(table->philosophes[i].thread, NULL) != 0)
			return (printf("failed to join\n"), 1);
	free(table->philosophes);
	free(table->forks);
	return (0);
}

bool	ft_append_infos_table(t_meal_table *table, char **av)
{
	// Number of Philosophers
	table->n_philosophes = ft_atoi(av[1]);
	if (table->n_philosophes == 0)
		return (printf("no philosophers\n"), false);

	// Die limit time in milliseconds
	table->die_limit = ft_atoi(av[2]);
	if (table->die_limit == 0)
		return (printf("no die limit\n"), false);

	// Eat limit time
	table->eat_limit = ft_atoi(av[3]);
	if (table->eat_limit == 0)
		return (printf("no eat limit\n"), false);

	// Sleep limit time
	table->sleep_limit = ft_atoi(av[4]);
	if (table->sleep_limit == 0)
		return (printf("no sleep limit\n"), false);

	// If last parameter, number of times to eat each
	if (!av[5])
	{
		table->n_times_to_eat_each = -1;
		return (true);
	}

	// If last parameter and it's 0, return false
	table->n_times_to_eat_each = ft_atoi(av[5]);
	if (table->n_times_to_eat_each == 0)
		return (printf("no n times to eat each\n"), false);
	return (true);
}