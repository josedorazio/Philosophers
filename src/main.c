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

int	simulation_running(t_data *data)
{
	pthread_mutex_lock(data->simulation_lock);
	if (data->simulation_running == 1)
		return (pthread_mutex_unlock(data->simulation_lock), 1);
	pthread_mutex_unlock(data->simulation_lock);
	return(0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (simulation_running(philo->data) == 1)
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (args);
}

void	*monitor_meals(void *args)
{
	t_data	*data;
	size_t	i;
	int		all_done;

	data = (t_data *) args;
	while (1)
	{
		i = 0;
		all_done = 1;
		while (i < data->num_of_philos)
		{
			pthread_mutex_lock(&data->philos[i].meal_lock);
			if (data->philos[i].meals_eaten <= data->meals_required)
				all_done = 0;
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			i++;
		}
		if (all_done)
		{
		pthread_mutex_lock(data->simulation_lock);
		data->simulation_running = 0;
		pthread_mutex_unlock(data->simulation_lock);
		break;
		}
		usleep(1000);
	}
	return (NULL);
}

void	clear_threads(void *args)
{
	t_data	*data;
	size_t	i;

	data = (t_data *) args;
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
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
	pthread_mutex_destroy(data->simulation_lock);
}

void	create_thread(t_data *data)
{
	size_t	i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitor_meals, data))
		error_message("failed to create monitor thread");
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]))
			error_message("failed to create thread.");
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			error_message("failed to join philosopher thread.");
		i++;
	}
	if (pthread_join(monitor, NULL))
		error_message("failed to join monitor thread");
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
