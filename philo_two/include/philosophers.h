/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-omar <mel-omar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 15:22:05 by mel-omar          #+#    #+#             */
/*   Updated: 2021/05/29 21:49:49 by mel-omar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <semaphore.h>
# include <string.h>
# include <sys/time.h>

# define NUMBER_OF_PHILO 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUMBER_MUST_EAT 4
# define FORKS_NAME "sem/forks"
# define OUTPUT_MANAGER_NAME "sem/out_manager"
# define PROTECT_FORKS_NAME "sem/proctect_forks"

typedef enum e_state
{
	THINKING,
	SLEEPING,
	EATING
}			t_state;

struct s_global
{
	long long							arguments[5];
	long long							program_start;
	int									someone_died;
	int									all_eat;
	sem_t								*forks;
	sem_t								*output_manger;
	sem_t								*protect_forks;
};

typedef struct s_philosopher
{
	int							id;
	int							time_eat;
	long long					last_time_eat;
	pthread_t					thread;
	t_state						state;
	sem_t						*is_eating;
	struct s_global				*shared_data;
}								t_philosopher;

int					isdigits(char c);
long long			convert(long long micors);
void				ft_print_error(const char *s);
int					string2number(const char *string);
long long			get_time(void);
void				ft_putc(char c);
void				ft_putnbr(unsigned int number);
void				ft_putstr(const char *str);
void				endl(void);
void				eat_statement(t_philosopher *philo);
void				think_statement(t_philosopher *philo);
void				sleep_statement(t_philosopher *philo);
void				fork_statement(t_philosopher *philo);
int					init_global_var(struct s_global *sd,
						int argc, char *argv[]);
void				death_statement(t_philosopher *philo);
t_philosopher		*init_philosophers(struct s_global *sd);
void				checker_state(t_philosopher *ph);
void				check_time(t_philosopher *ph,
						long long time, long long duration, int type);
void				*philosopher_function(void *philo);
int					check4errors(int argc, char **argv);
#endif