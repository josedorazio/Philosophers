/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 22:44:45 by jdorazio          #+#    #+#             */
/*   Updated: 2025/04/09 22:44:45 by jdorazio         ###   ########.fr       */
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
typedef struct s_data t_data;


// each philo will have it's own struct
typedef struct s_philo
{
	// philo id
	pthread_t	thread;
	int			id;
	// state
	int			eating; // = 1 (eating) | = 0 (not eating)
	size_t			meals_eaten; 
	size_t		last_meal;
	t_data		*data;
	// forks
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	// Sync
	pthread_mutex_t	meal_lock; // protets last_meal and meals eaten
} t_philo;

typedef struct s_data
{
	size_t		num_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		meals_required;
	int			simulation_running;
	size_t		start_time;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*simulation_lock;
}t_data;

typedef struct s_program
{
	t_data	data;
	pthread_mutex_t	*forks;

}t_program;



// ##--- INIT ---##
void	init_philos(t_data *data);
void	init_forks(t_data *data);
void	assign_forks(t_data *data);
void	init_data(t_data *data, char **av);
void	init_program(t_program *program, char **av);
// ## ---------- ##

// ##--- UTILLSINIT ---##
int		ft_atoi(const char *nptr);
void	error_message(char *error);
void	check_av(char **av);
size_t	get_current_time(void);
// ## ---------- ##


// ##--- UTILLSINIT ---##
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	think(t_philo *philo);
// ## ---------- ##
# endif
