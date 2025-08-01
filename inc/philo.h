/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:44:45 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/31 16:51:01 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <stdbool.h> 

# define PHILO_MAX 200

typedef struct s_data t_data;

// each philo will have it's own struct
typedef struct s_philo
{
	// philo id
	int			id;
	int		meals_eaten;
	long	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_data	*data;
	pthread_t	thread;
} t_philo;

typedef struct s_data
{
	size_t		num_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			meals_required;
	int			philos_full;
	long		start_time;
	long		threads_running_num;
	bool		sim_finished;
	bool		all_threads_ready;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	sim_lock;
	pthread_mutex_t	meal_lock;
	t_philo		*philos;
	pthread_t	monitor_thread;
}	t_data;



// MAIN 
int	main(int ac, char **av);

// ACTIONS 
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);

// ERROR
void	destroy_all(t_data *data);
void	error_message(char *error);

// INIT 
int	init_data(t_data *data, int ac, char **av);

// PHILO ROUTINE (TABLE)
void	*routine_philo(void *args);
void	increase_threads(pthread_mutex_t *mutex, long *var);

// MONITOR ROUTINE 
void    *routine_monitor(void *args);


// STATUS FUNCTIONS
void set_status(pthread_mutex_t *mutex, bool *status);
bool get_status(pthread_mutex_t *mutex, bool *status);
void	set_time(pthread_mutex_t *mutex, long *dest, long value);
long get_time(pthread_mutex_t *mutex, bool *status);
bool	program_ended(t_philo *philo);

// UTILS 
int	ft_atoi(const char *nptr);
long	get_curr_time(void);
void	ft_usleep(size_t mls, t_philo *philo);
void	print_action(char *s, t_philo *philo);


# endif
