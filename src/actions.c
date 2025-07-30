/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:11:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/16 22:22:52 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/philo.h"

int	running_sim(t_sim *data)
{
	int	running;

	pthread_mutex_lock(&data->simulation_lock);
	running = data->simulation_running;
	pthread_mutex_unlock(&data->simulation_lock);
	return (running);
}

void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action("has taken left fork", philo);
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken right fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken right fork", philo);
		pthread_mutex_lock(philo->left_fork);
		print_action("has taken left fork", philo);
	}
}

static void	eat(t_philo *philo)
{
	lock_forks(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	print_action("is eating.", philo);
	pthread_mutex_unlock(&philo->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	ft_sleep(t_philo *philo)
{
	print_action("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_action("is thinking", philo);
}


void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->data->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action("has taken right fork", philo);
		ft_usleep(philo->data->time_to_die);
		print_action("died", philo);
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (running_sim(philo->data) == 1)
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (args);
}
