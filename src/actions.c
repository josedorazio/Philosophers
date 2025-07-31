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
	set_long(&philo->data->meal_lock, &philo->last_meal, now());
	print_action("is eating.", philo);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->meals_required != -1)
	{
		philo->meals_eaten++;
		if (philo->meals_eaten == philo->data->meals_required)
			increase_int(&philo->data->meal_lock, &philo->data->philos_full);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_sleep(t_philo *philo)
{
	print_action("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_action("is thinking", philo);
}

// void	lock_forks(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action("has taken left fork", philo);
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action("has taken right fork", philo);
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action("has taken right fork", philo);
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action("has taken left fork", philo);
// 	}
// }
