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

#include "../inc/philo.h"

// SIMULATION_LOCK
// PRINT LOCK
// FORK
// MEAL LOCK
void	clear_threads(t_sim *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->simulation_lock);
}

void	free_program(t_sim *data)
{
	free(data->philos);
	free(data->forks);
}

void	create_thread(t_sim *data)
{
	size_t	i;
	size_t	num_philos;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &routine_monitor, data) != 0)
		clear_threads(data);
	i = 0;
	num_philos = data->num_of_philos;
	while (i < num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
			&routine, &data->philos[i]) != 0)
			clear_threads(data);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		clear_threads(data);
	i = 0;
	while (i < num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			clear_threads(data);
		i++;
	}
}

// ./philo 5 800 200 200 [5]
int	main(int ac, char **av)
{
	t_sim	data;

	check_av(ac, av);
	init_sim(&data, av);
	create_thread(&data);
	clear_threads(&data);
	free_program(&data);
	return (0);
}
