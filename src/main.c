/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:30:02 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/07/15 19:50:32 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int ac, char** av, char **env)
{
	int			i;
	pthread_t	thread;
	// void		*ft_routine(void *);

	i = 2;
	// check if there is an exact number of arguments
	if (ac != 6)
		return (1);
	// check if all the arguments are numbers
	if (parsing(av) == false)
		return (1);
	// creates a thread
	pthread_create(&thread, NULL, ft_routine, NULL);
	// 1st arg is the id/ptr
	// 2nd arg is attributes (mostly NULL)
	// 3rd arg is the function the thread starts to execute
	// 4th arg is arguments for the routine, can be a structure for multiples args
	
	// quit a thread (must be inside the pthread_create function passed in argument)
	// pthread_exit();
	return (0);
}

void	*ft_routine(void *ptr)
{
	return (NULL);
}
