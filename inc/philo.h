/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:44:45 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/30 21:27:26 by jdorazio         ###   ########.fr       */
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
	size_t	last_meal;
	int		is_eating;
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
	int			stop_sim;
	size_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	simulation_lock;
	t_philo		*philos;
	pthread_t	monitor_thread;
}	t_data;

// ##--- INIT ---##
int	init_data(t_data *data, int ac, char **av);
// ## ---------- ##

// ##--- UTILLSINIT ---##
int		ft_atoi(const char *nptr);
void	error_message(char *error);
size_t	now(void);
// ## ---------- ##

// ##--- UTILLSINIT ---##
void	*routine_monitor(void *args);
// ## ---------- ##

// ##--- UTILLSINIT ---##
void	*routine(void *args);
// ## ---------- ##

void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);


size_t	timestamp(t_philo *philo);
void	print_action(char *s, t_philo *philo);

void	ft_usleep(size_t duration_ms);
int sim_stopped(t_philo *philo);
# endif
