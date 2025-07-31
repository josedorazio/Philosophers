/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:17:01 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/31 16:51:21 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_action(char *s, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = now() - philo->data->start_time ;
	if (sim_stopped(philo) == 0)
		printf("[%zu] -> Philo[%d] %s \n", time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static int	dead_philo(t_philo *philo, size_t time_to_die)
{
	int		dead;
	long	time_now;

	dead = 0;
	pthread_mutex_lock(&philo->meal_lock);
	time_now = now() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_now >= (long)time_to_die)
	{
		dead = 1;
		set_bool(&philo->data->sim_lock, &philo->data->sim_finished);
		print_action("died", philo);
	}
	return (dead);
}

static int	check_full_philo(t_data *data)
{
	int		status;
	
	status = 0;
	if (data->meals_required == -1)
		return (status);
	
	if (data->philos_full == (int)data->num_of_philos)
	{
		set_bool(&data->sim_lock, &data->sim_finished);
		pthread_mutex_lock(&data->print_lock);
		printf("All philosophers ate enough\n");
		pthread_mutex_unlock(&data->print_lock);
	}
	return (status);
}

void    *routine_monitor(void *args)
{
	t_data  *data;
	size_t		i;
	
	i = 0;
	data = (t_data *) args;
	while (data->philos_ready < (int) data->num_of_philos)
		usleep(100);
	while (!sim_stopped(data->philos))
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (dead_philo(&data->philos[i], data->time_to_die)
				|| check_full_philo(data))
				return (NULL);
			i++;
		}
		usleep (100);
	}
	return (NULL);

}
