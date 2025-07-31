/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:56:10 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/27 18:56:10 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool get_status(pthread_mutex_t *mutex, bool *status)
{
	bool	rst;

	pthread_mutex_lock(mutex);
	rst = *status;
	pthread_mutex_unlock(mutex);
	return (rst); 
}

bool	sim_stopped(t_philo *philo)
{
	return (get_status(&philo->data->sim_lock, &philo->data->sim_finished));
}



void	wait_threads(t_data *data)
{
	while (!get_status(&data->sim_lock, &data->ready_threads))
		usleep(100);
}

void	set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void	increase_int(pthread_mutex_t *mutex, int *var)
{
	pthread_mutex_lock(mutex);
	(*var)++;
	pthread_mutex_unlock(mutex);
}

void	*philo1(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action("has taken left fork", philo);
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
	print_action("has died. RIP", philo);
	return (NULL);
}


void	*routine_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	wait_threads(philo->data);
	set_long(&philo->data->meal_lock, &philo->last_meal, philo->data->start_time);
	increase_int(&philo->data->sim_lock, &philo->data->philos_ready);
	if (philo->data->num_of_philos == 1)
		return (philo1(philo));
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!sim_stopped(philo))
	{
		if (philo->data->meals_required != -1
			&& philo->meals_eaten >= philo->data->meals_required)
			break ;
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

static void	destroy_all(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->sim_lock);
	free(data->philos);
	free(data->forks);
}

void set_bool(pthread_mutex_t *mutex, bool *status)
{
	pthread_mutex_lock(mutex);
	*status = true;
	pthread_mutex_unlock(mutex);
}

static int	create_thread(t_data *data)
{
	size_t		i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &routine_monitor, data) != 0)
		return (destroy_all(data), 0);
	i = 0;
	data->start_time = now();
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&routine_philo, &data->philos[i]) != 0)
			return (destroy_all(data), 0);
		i++;
	}
	set_bool(&data->sim_lock, &data->ready_threads);
	if (pthread_join(monitor, NULL) != 0)
		return (destroy_all(data), 0);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (destroy_all(data), 0);
		i++;
	}
	return (1);
}

static void	check_av(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		error_message("Number of arguments not 4 or 5.");
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > PHILO_MAX)
		error_message("Num. Philo. must be between 1 - 200");
	if (ft_atoi(av[2]) <= 0)
		error_message("time to die must be bigger than 0");
	if (ft_atoi(av[3]) <= 0)
		error_message("time to eat must be bigger than 0");
	if (ft_atoi(av[4]) <= 0)
		error_message("time to sleep must be bigger than 0");
	if (av[5] && (ft_atoi(av[5]) < 0))
		error_message("invalid number of eating times\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	check_av(ac, av);
	if (!init_data(&data, ac, av))
		return (printf("Initialization error\n"), EXIT_FAILURE);
	if (!create_thread(&data))
		return (printf("Thread craetion error\n"), EXIT_FAILURE);
	destroy_all(&data);
	return (EXIT_SUCCESS);
}
