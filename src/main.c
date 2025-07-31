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

int sim_stopped(t_philo *philo)
{
	int stop;

	pthread_mutex_lock(&philo->data->simulation_lock);
	stop = philo->data->stop_sim;
	pthread_mutex_unlock(&philo->data->simulation_lock);
	return (stop);
}

void	*routine_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (now() < philo->data->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(1000);
    while (!sim_stopped(philo))
    {
			if (philo->data->meals_required != -1 &&
				philo->meals_eaten >= philo->data->meals_required)
				break;
      eat(philo);
			if (sim_stopped(philo))
				break;
      ft_sleep(philo);
			if (sim_stopped(philo))
				break;
      think(philo);
    }
    return (NULL);
}

static void	destroy_all(t_data *data)
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
	free(data->philos);
	free(data->forks);
}

static int	create_thread(t_data *data)
{
	size_t		i;
	size_t		num_philos;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &routine_monitor, data) != 0)
		return (destroy_all(data), 0);
	i = 0;
	num_philos = data->num_of_philos;
	while (i < num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine_philo, &data->philos[i]) != 0)
			return (destroy_all(data), 0);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return (destroy_all(data), 0);
	i = 0;
	while (i < num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (destroy_all(data), 0);
		i++;
	}
	return (1);
}
static void	check_av(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		error_message("Number of arguments not 4 or 5.");
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > PHILO_MAX)
		error_message("Num. Philo. must be between 1 - 200");
	if (ft_atoi(av[2]) <= 0)
		error_message("time to die must be bigger than 0");
	if (ft_atoi(av[3]) <= 0)
		error_message("time to eat must be bigger than 0");
	if (ft_atoi(av[4]) <= 0)
		error_message("time to sleep must be bigger than 0");
	if (av[5] && (ft_atoi(av[5]) < 0))
		error_message("invalid number of eating times\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	check_av(ac, av);
	if (!init_data(&data,ac, av))
		return (printf("Initialization error\n"), EXIT_FAILURE);
	if (!create_thread(&data))
			return (printf("Thread craetion error\n"), EXIT_FAILURE);
	destroy_all(&data);
	return (EXIT_SUCCESS);
}
