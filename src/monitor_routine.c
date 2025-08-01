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

static int	dead_philo(t_philo *philo, size_t time_to_die)
{
	int		dead;
	long	elapsed;

	dead = 0;
	pthread_mutex_lock(&philo->meal_lock);
	elapsed = get_curr_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (elapsed > (long)time_to_die)
	{
		dead = 1;
		print_action("died", philo);
		set_status(&philo->data->sim_lock, &philo->data->sim_finished);
	}
	return (dead);
}

static int	check_full_philo(t_data *data)
{	
	if (data->meals_required == -1)
		return (1);
	pthread_mutex_lock(&data->meal_lock);
	if (data->philos_full == (int)data->num_of_philos)
	{
		set_status(&data->sim_lock, &data->sim_finished);
		pthread_mutex_unlock(&data->meal_lock);
		pthread_mutex_lock(&data->print_lock);
		printf("Philos ate enough\n");
		pthread_mutex_lock(&data->print_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (1);
}

static bool	threads_ready(pthread_mutex_t *mutex, long *threads, int philo_num)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(mutex);
	if (*threads == (long)philo_num)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void    *routine_monitor(void *args)
{
	t_data  *data;
	size_t		i;
	
	i = 0;
	data = (t_data *) args;
	while (!threads_ready(&data->sim_lock, &data->threads_running_num, data->num_of_philos))
		usleep(100);
	while (!program_ended(data->philos))
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
