/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:17:01 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/14 16:53:24 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static bool	dead_philo(t_philo *philo, t_sim *data)
{
	size_t	inact;

	pthread_mutex_lock(&philo->meal_lock);
	inact = get_current_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (inact >= data->time_to_die)
	{
		pthread_mutex_lock(&data->simulation_lock);
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->simulation_lock);
		print_action(" died. RIP.", philo);
		return (true);
	}
	return (false);
}

static bool	full_philos(t_sim *data)
{	
	size_t	i;

	i = 0;
	if (data->meals_required == -1)
		return (false);
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

static int	philo_state(t_sim *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (dead_philo(&data->philos[i], data))
			return (0);
		i++;
	}
	if (full_philos(data))
	{
		pthread_mutex_lock(&data->simulation_lock);
		data->simulation_running = 0;
		pthread_mutex_unlock(&data->simulation_lock);
		pthread_mutex_lock(&data->print_lock);
		printf("All philosophers ate enough\n");
		pthread_mutex_unlock(&data->print_lock);
		return (0);
	}
	return (1);
}

void	*routine_monitor(void *args)
{
	t_sim	*data;
	
	data = (t_sim *) args;
	while (running_sim(data) == 1)
	{
		if (!philo_state(data))
			break;
		usleep(500);
	}
	return (NULL);
}
