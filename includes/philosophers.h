/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouduri <rmouduri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:20:26 by rmouduri          #+#    #+#             */
/*   Updated: 2021/12/06 14:13:46 by rmouduri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define AVAILABLE 0
# define NOT_AVAILABLE 1
# define PROG_NAME	"Philosophers: "

# include <pthread.h>
# include <sys/time.h>

# define FORK " has taken a fork\n"
# define EATING " is eating\n"
# define SLEEPING " is sleeping\n"
# define THINKING " is thinking\n"
# define IS_DEAD " is dead\n"

typedef struct s_info
{
	unsigned int	nb_of_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	has_finished;
	int				must_eat;
	int				alive;
	char			*forks;
	char			*ids;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*ids_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	alive_mutex;
}	t_info;

typedef struct s_philo
{
	struct s_info		*info;
	int					forks;
	int					rfork;
	int					lfork;
	pthread_t			thread;
	unsigned int		id;
	unsigned int		has_eaten;
	unsigned long long	last_meal;
}	t_philo;

int					check_philo_args(int ac, char **av);
int					init_info(int ac, char **av, t_info *philo);
int					init_philos(t_info *info, t_philo **philos);
int					init_threads(t_philo *philos, int nb_of_philo, int i);
int					free_structs(t_info *info, t_philo *philo);
void				*simulation(t_philo *philo);
void				ph_get_forks(t_philo *philo);
void				ph_eat(t_philo *philo);
void				ph_sleep(t_philo *philo);
void				*monitoring(void *arg);
unsigned long long	get_elapsedtime(void);
void				ft_usleep(unsigned long long ms);
void				print_state(char *state, t_philo *philo,
						char is_monitor, char fork);
int					is_alive(t_philo *philo);

int					return_error(char *s1, char *s2, char *s3, int ret);
int					ft_strlen(const char *s);
int					ft_isdigit(int c);
long long int		ft_atoi(const char *str);
char				*ft_strcpy(char *dest, char *src);

#endif
