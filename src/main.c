/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:30:02 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/08/02 18:43:15 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char** av)
{
	pthread_t		thread1;
	pthread_t		thread2;
	pthread_t		thread3;
	t_meal_table	table;
	void			*ft_routine(void *add);
	int				*tab;

	int				value1 = 1;
	int				value2 = 2;
	int				value3 = 3;
	// check if there is an exact number of arguments
	// if (ac != 6)
	// 	return (printf("Wrong number of arguments!\nTry again!\n"), 1);
	// check if all the arguments are numbers

	// how am I going to use that tab ?
	tab = parsing(ac, av);
	if (!tab)
		return (1);
	free(tab);
	// add infos in struct table and free if return value is NULL
	if (ft_append_infos_table(&table, av) == false)
		return (1);

	// creates a thread
	pthread_create(&thread1, NULL, ft_routine, (void *) &value1);
	pthread_create(&thread2, NULL, ft_routine, (void *) &value2);
	pthread_create(&thread3, NULL, ft_routine, (void *) &value3);
	
	// 1st arg is the id/ptr
	// 2nd arg is attributes (mostly NULL)
	// 3rd arg is the function the thread starts to execute
	// 4th arg is arguments for the routine, can be a structure for multiples args

	//ft_routine((void *) &value1);
	//ft_routine((void *) &value2);

	// join the thread
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	// quit a thread (must be inside the pthread_create function passed in argument)
	// pthread_exit();
	ft_free_struct(&table);
	return (0);
}

void	*ft_routine(void *add)
{
	int		*add_num = (int *) (add);

	printf("start thread ");
	printf("%d\n", *add_num);
	// pthread_exit(ptr);
	return (NULL);
}

bool	ft_append_infos_table(t_meal_table *table, char **av)
{
	table->n_philosophes = ft_atoi(av[1]);
	printf("table->n_philosophes : %d\n", table->n_philosophes);
	if (table->n_philosophes == 0)
		return (false);
	table->die_limit = ft_atoi(av[2]);
	printf("table->die_limit : %f\n", table->die_limit);
	if (table->die_limit == 0)
		return (false);
	table->eat_limit = ft_atoi(av[3]);
	printf("table->eat_limit : %f\n", table->eat_limit);
	if (table->eat_limit == 0)
		return (false);
	table->sleep_limit = ft_atoi(av[4]);
	printf("table->sleep_limit : %f\n", table->sleep_limit);
	if (table->sleep_limit == 0)
		return (false);
	if (!av[5])
		return (true);
	table->n_times_to_eat_each = ft_atoi(av[5]);
	printf("table->n_times_to_eat_each : %d\n", table->n_times_to_eat_each);
	if (table->n_times_to_eat_each == 0)
		return (false);
	return (true);
}
