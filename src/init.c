/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:52:42 by jdorazio          #+#    #+#             */
/*   Updated: 2025/05/19 15:42:12 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	init_philos(t_data *data)
{
	size_t	i;

	i = 0;
	data->philos = malloc(data->num_of_philos * sizeof(t_philo));
	if (!data->philos)
		error_message("failed philos allocation.");
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eating = 0;
		data->philos[i].meales_eaten = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].meal_lock, NULL);
		i++;
	}
}

void	assign_forks(t_data *data)
{
	size_t	i;
	size_t	philos;

	i = 0;
	philos = data->num_of_philos;
	while (i < philos)
	{
		// assign left fork to philo
		data->philos[i].left_fork = &data->forks[i];
		// assign right fork to philo. Think about it like a circular list
		data->philos[i].right_fork = &data->forks[(i + 1) % philos];
		i++;
	}
}


void init_forks(t_data *data)
{
	size_t	i;

	data->forks = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		error_message("failed fork allocation");
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	assign_forks(data);
}


void	init_data(t_data *data, char **av)
{
	data->num_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start_time = get_current_time();
	printf("time = %ld\n", data->start_time);
	if (av[5])
		data->meals_required = ft_atoi(av[5]);
	init_philos(data);
	init_forks(data);
}
