#include "../inc/philo.h"

void set_status(pthread_mutex_t *mutex, bool *status)
{
	pthread_mutex_lock(mutex);
	*status = true;
	pthread_mutex_unlock(mutex);
}

bool get_status(pthread_mutex_t *mutex, bool *status)
{
	bool	rst;

	pthread_mutex_lock(mutex);
	rst = *status;
	pthread_mutex_unlock(mutex);
	return (rst); 
}

void	set_time(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long get_time(pthread_mutex_t *mutex, bool *status)
{
	bool	rst;

	pthread_mutex_lock(mutex);
	rst = *status;
	pthread_mutex_unlock(mutex);
	return (rst); 
}

bool	program_ended(t_philo *philo)
{
	return (get_status(&philo->data->sim_lock, &philo->data->sim_finished));
}

void	increase_threads(pthread_mutex_t *mutex, long *var)
{
	pthread_mutex_lock(mutex);
	(*var)++;
	pthread_mutex_unlock(mutex);
}