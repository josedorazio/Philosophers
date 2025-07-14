/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:44:45 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/14 16:36:15 by jdorazio         ###   ########.fr       */
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

typedef struct s_philo t_philo;
typedef struct s_program t_program;
typedef struct s_sim t_sim;


// each philo will have it's own struct
typedef struct s_philo
{
	// philo id
	pthread_t	thread;
	int			id;
	// state
	bool		eating; // TRUE (eating) | FALSE(not eating)
	bool		is_dead;
	int		meals_eaten;
	size_t		last_meal;
	t_sim		*data;
	// forks
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// Sync
	pthread_mutex_t	meal_lock; // protets last_meal and meals eaten
} t_philo;

typedef struct s_sim
{
	size_t		num_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			meals_required;
	int			simulation_running;
	size_t		start_time;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	simulation_lock;
}	t_sim;

// ##--- INIT ---##
void	init_sim(t_sim *data, char **av);
// ## ---------- ##

// ##--- UTILLSINIT ---##
int		ft_atoi(const char *nptr);
void	error_message(char *error);
void	check_av(int ac, char **av);
size_t	get_current_time(void);
// ## ---------- ##

// ##--- UTILLSINIT ---##
void	*routine_monitor(void *args);
// ## ---------- ##

// ##--- UTILLSINIT ---##
void	*routine(void *args);
// ## ---------- ##
# endif
