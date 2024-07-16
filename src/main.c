/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:30:02 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/07/16 18:38:51 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char** av, char **env)
{
	pthread_t		thread1;
	pthread_t		thread2;
	t_meal_table	table;
	void			*ft_routine(void *add);

	int				value1 = 1;
	int				value2 = 2;
	// check if there is an exact number of arguments
	//if (ac != 6)
	//	return (1);
	// check if all the arguments are numbers
	//if (!parsing(av))
	//	return (1);
	// add infos in struct table and free if return value is NULL
	if (append_infos_table(&table, av) == NULL)
		return (1);

	// creates a thread
	pthread_create(&thread1, NULL, ft_routine, (void *) &value1);
	pthread_create(&thread2, NULL, ft_routine, (void *) &value2);
	
	// 1st arg is the id/ptr
	// 2nd arg is attributes (mostly NULL)
	// 3rd arg is the function the thread starts to execute
	// 4th arg is arguments for the routine, can be a structure for multiples args

	//ft_routine((void *) &value1);
	//ft_routine((void *) &value2);

	// join the thread
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	// quit a thread (must be inside the pthread_create function passed in argument)
	// pthread_exit();
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
	return (true);
}
