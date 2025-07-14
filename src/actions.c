/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:11:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/14 16:59:22 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

static void	eat(t_philo *philo)
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
	pthread_mutex_lock(&philo->data->print_lock);
	printf("Philo %d is eating \n ", philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->meal_lock);
	philo->eating = 0;
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("Philo %d finished eating. Meals eated %d\n",
		philo->id, philo->meals_eaten);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("Philo %d is sleeping.\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep((philo->data->time_to_sleep) * 1000);
}

static void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("Philo %d is thinking.\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static int	simulation_running(t_sim *data)
{
	int	running;

	pthread_mutex_lock(&data->simulation_lock);
	running = data->simulation_running;
	pthread_mutex_unlock(&data->simulation_lock);
	return (running); // esto retorna 1 ó 0 
}


void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (simulation_running(philo->data) == 1)
	{
		
		eat(philo);
		ft_sleep(philo);
		think(philo);
		usleep(1000);
	}
	return (NULL);
}