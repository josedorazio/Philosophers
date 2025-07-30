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

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (get_current_time() < philo->data->start_time)
		usleep(50);
	if (philo->data->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken right fork", philo);
		ft_usleep(philo->data->time_to_die);
		print_action("died", philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->data->simulation_lock);
		philo->data->simulation_running = 0;
		return (pthread_mutex_unlock(&philo->data->simulation_lock), NULL);
	}
	if (philo->id % 2 == 0)
		usleep(3000);
	while (running_sim(philo->data) == 1)
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (args);
}

static void	clear_threads(t_sim *data)
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

static void	create_thread(t_sim *data)
{
	size_t		i;
	size_t		num_philos;
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

int	main(int ac, char **av)
{
	t_sim	data;

	check_av(ac, av);
	init_sim(&data, av);
	create_thread(&data);
	clear_threads(&data);
	return (0);
}
