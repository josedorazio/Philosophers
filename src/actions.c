/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:11:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/31 16:54:24 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action("has taken left fork", philo);
	pthread_mutex_lock(philo->right_fork);
	print_action("has taken right fork", philo);
	set_time(&philo->data->meal_lock, &philo->last_meal, get_curr_time());
	philo->meals_eaten++;
	print_action("is eating.", philo);
	ft_usleep(philo->data->time_to_eat, philo);
	if (philo->data->meals_required > 0)
	{
		if (philo->meals_eaten == philo->data->meals_required)
			increase_threads(&philo->data->meal_lock, &philo->data->threads_running_num);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_sleep(t_philo *philo)
{
	print_action("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	print_action("is thinking", philo);
}