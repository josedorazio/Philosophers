
#include "../inc/philo.h"

void	destroy_all(t_data *data)
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
  pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->sim_lock);

	free(data->philos);
	free(data->forks);
}

void	error_message(char *error)
{
	printf("ERROR: %s\n", error);
	exit(EXIT_FAILURE);
}