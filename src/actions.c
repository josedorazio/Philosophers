/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:11:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/05/25 17:24:25 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

void	eat(t_philo *philo)
{

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	printf("Philo %d is eating \n ", philo->id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 0;
	philo->meals_eaten++;
	printf("Meals Eaten %ld\n", philo->meals_eaten);
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	ft_sleep(t_philo *philo)
{
	// 	Log sleeping
	printf("Philo %d is sleeping.\n", philo->id);
	// Sleep for time_to_sleep ms
	usleep((philo->data->time_to_sleep) * 1000);
}

void	think(t_philo *philo)
{
// Log thinking
	printf("Philo %d is thinking.\n", philo->id);
// Small pause or no pause (optional)
}
