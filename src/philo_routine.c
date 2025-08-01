#include "../inc/philo.h"

static void	*philo1(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action("has taken left fork", philo);
	ft_usleep(philo->data->time_to_die, philo);
	pthread_mutex_unlock(philo->left_fork);
	print_action("has died. RIP", philo);
	return (NULL);
}


static void	wait_creation(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (!get_status(&data->sim_lock, &data->all_threads_ready))
		usleep(100);
	set_time(&philo->data->meal_lock, &philo->last_meal, philo->data->start_time);
	increase_threads(&philo->data->sim_lock, &philo->data->threads_running_num);
}

void	*routine_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	wait_creation(philo);
	if (philo->data->num_of_philos == 1)
		return (philo1(philo));
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo);
	while (!program_ended(philo))
	{
		if (philo->meals_eaten >= philo->data->meals_required)
			break ;
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}