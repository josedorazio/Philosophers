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

void	print_action(char *s, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->print_lock);
	time = now() - philo->data->start_time ;
	if (sim_stopped(philo) == 0)
		printf("[%zu] -> Philo[%d] %s \n", time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print_lock);
}

int	dead_philo(t_philo *philo, size_t time_to_die)
{
	int	dead;
	size_t	time_now;
	ssize_t diff;

	dead = 0;
	time_now = now();
	pthread_mutex_lock(&philo->meal_lock);
	diff = (ssize_t)time_now - (ssize_t)philo->last_meal;
  if (philo->is_eating == 0 && (diff >= (ssize_t)time_to_die))
	{
		dead = 1;
		print_action("died", philo);
 printf("[DEBUG] Philo[%d] died: last_meal=%zu, now=%zu, diff=%zu, time_to_die=%zu, is_eating=%d\n",
               philo->id, philo->last_meal, time_now, diff, time_to_die, philo->is_eating);
	}
  pthread_mutex_unlock(&philo->meal_lock);
	return (dead);
}

static int	check_dead_philo(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (dead_philo(&data->philos[i], data->time_to_die) == 1)
		{
			pthread_mutex_lock(&data->simulation_lock);
			data->stop_sim = 1;
			pthread_mutex_unlock(&data->simulation_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static bool	check_full_philo(t_data *data)
{
	size_t	i;
	size_t	full_count;
	
	if (data->meals_required == -1)
		return (false);
	i = 0;
	full_count = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten >= data->meals_required)
			full_count++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	if (full_count == data->num_of_philos)
	{
		pthread_mutex_lock(&data->simulation_lock);
		data->stop_sim = 1;
		pthread_mutex_unlock(&data->simulation_lock);
		pthread_mutex_lock(&data->print_lock);
		printf("All philosophers ate enough\n");
		pthread_mutex_unlock(&data->print_lock);
		return (true);
	}
	return (false);
}
void    *routine_monitor(void *args)
{
    t_data  *data;
	
    data = (t_data *) args;
		while (now() < data->start_time + 1)
			usleep(100);
    while (1)
    {
        if (check_dead_philo(data) == 1)
            return (NULL);
        if (check_full_philo(data))
            return (NULL); 
        usleep(500);
    }
    return (NULL);
}