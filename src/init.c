/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:52:42 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/13 20:41:27 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

static void	init_philos(t_sim *data)
{
	size_t	i;
	size_t	num_philos;

	num_philos = data->num_of_philos; 
	i = 0;
	data->philos = malloc(num_philos * sizeof(t_philo));
	if (!data->philos)
		error_message("failed philos allocation.");
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		// data->philos[i].start_time = get_current_time();
		data->philos[i].last_meal = get_current_time();
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % num_philos];
		pthread_mutex_init(&data->philos[i].meal_lock, NULL);
		i++;
	}
}

static void	init_forks(t_sim *data)
{
	size_t	i;

	data->forks = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		error_message("failed fork allocation");
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			error_message("failed to init fork");
		i++;
	}
}

static void	parse_args(t_sim *data, char **av)
{
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_required = -1;
	if (av[5])
		data->meals_required = ft_atoi(av[5]);
	data->start_time = get_current_time();
	data->simulation_running = 1;
}

void	init_sim(t_sim *data, char **av)
{
	parse_args(data, av);
	if (pthread_mutex_init(&data->simulation_lock, NULL) != 0)
		error_message("failed fork allocation");
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->simulation_lock);
		error_message("failed fork allocation");
	}
	init_forks(data);
	init_philos(data);
}
