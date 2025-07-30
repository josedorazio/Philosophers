/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:17:01 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/30 21:47:10 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	dead_philo(t_philo *philo, t_sim *data)
{
	size_t	now;
	size_t	diff;

	now = get_current_time();
	pthread_mutex_lock(&philo->meal_lock);
	if (now >= philo->last_meal)
		diff = now - philo->last_meal;
	else
		diff = 0;
	if (diff >= data->time_to_die)
	{
		pthread_mutex_lock(&data->simulation_lock);
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->simulation_lock);
		pthread_mutex_lock(&data->print_lock);
		printf("[%zu] -> Philo[%d] died. RIP.\n", now - data->start_time,
			philo->id);
		pthread_mutex_unlock(&data->print_lock);
		pthread_mutex_unlock(&philo->meal_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (false);
}

static bool	full_philos(t_sim *data)
{
	size_t	i;

	if (data->meals_required == -1)
		return (false);
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten < data->meals_required)
		{
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			return (false);
		}
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	return (true);
}

static bool	check_dead_philo(t_sim *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (dead_philo(&data->philos[i], data))
			return (true);
		i++;
	}
	return (false);
}

static bool	check_full_philo(t_sim *data)
{
	if (full_philos(data))
	{
		pthread_mutex_lock(&data->simulation_lock);
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->simulation_lock);
		pthread_mutex_lock(&data->print_lock);
		printf("All philosophers ate enough\n");
		pthread_mutex_unlock(&data->print_lock);
		return (true);
	}
	return (false);
}

void	*routine_monitor(void *args)
{
	t_sim	*data;

	data = (t_sim *) args;
	while (running_sim(data) == 1)
	{
		if (check_dead_philo(data) || check_full_philo(data))
			break ;
		usleep(1000);
	}
	return (args);
}
