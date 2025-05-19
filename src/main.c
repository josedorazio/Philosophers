/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:56:10 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/27 18:56:10 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"


void	*routine(void *arg)
{
	printf("FALTA CREAR FUNCION");
	return (NULL);
}

void	create_thread(t_data *data)
{
	pthread_t	observer;
	size_t	i;

	while (i < data->num_of_philos)
	{
		if (pthread_create(&observer, NULL, routine, &data->philos[i]))
			error_message("failed to createt thread");
		
		
	}

}

void	free_program(t_data *data)
{

	free(data->philos);
	free(data->forks);
}


void	init_program(t_program *program, char **av)
{

	init_data(&program->data, av);
	create_thread(&program->data);



	//ALL FREES
	free_program(&program->data);

}

// ./philo 5 800 200 200 [5]
int	main(int ac, char **av)
{
	t_program	program;

	if (ac != 5 && ac != 6)
		error_message("Number of arguments not 4 or 5.");
	check_av(av);
	init_program(&program, av);
	printf("works");
	return (0);
}
