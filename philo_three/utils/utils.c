/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:47:03 by lmallado          #+#    #+#             */
/*   Updated: 2020/12/07 14:47:04 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void		ft_putstr(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i] != '\0')
	{
		c = s[i];
		write(1, &c, 1);
		i++;
	}
}

static int	to_skip_symbols(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' ||
			str[i] == '\f' ||
			str[i] == '\n' ||
			str[i] == '\r' ||
			str[i] == '\v' ||
			str[i] == ' ')
		i++;
	return (i);
}

int			print_error(int id)
{
	ft_putstr(RED);
	ft_putstr("Error\n");
	if (id == 1)
		ft_putstr("Not a valid arguments, sorry :(\n");
	if (id == 2)
		ft_putstr("Something went wrong with mutex init, sorry :(\n");
	if (id == 3)
		ft_putstr("Something went wrong with threads init, sorry :(\n");
	if (id == 4)
		ft_putstr("Wrong number of arguments, sorry :(\n");
	ft_putstr(RESET);
	return (-1);
}

t_philo		*philo_dup(t_philo philo_struct, int id, t_vars *vars)
{
	t_philo	*new;
	char	*id_s;

	id_s = ft_itoa(id);
	if (!(new = malloc(sizeof(t_philo))))
		return (NULL);
	new->id = id;
	new->eat_num = 0;
	new->waiter = vars->waiter;
	new->semaphore = vars->semaphore;
	new->write_lock = vars->write_lock;
	new->time_lock = vars->time_lock;
	new->number_must_eat = philo_struct.number_must_eat;
	new->philosophers_count = philo_struct.philosophers_count;
	new->time_to_die = philo_struct.time_to_die;
	new->time_to_eat = philo_struct.time_to_eat;
	new->time_to_sleep = philo_struct.time_to_sleep;
	gettimeofday(&new->started_at, NULL);
	gettimeofday(&new->last_eat, NULL);
	sem_unlink(id_s);
	new->eat_lock = sem_open(id_s, O_CREAT, 0660, 1);
	free(id_s);
	return (new);
}

int			ft_atoi(const char *str)
{
	int		res;
	int		is_minus;
	int		i;

	i = 0;
	is_minus = 1;
	res = 0;
	i = to_skip_symbols(str);
	if (str[i] == '-')
		is_minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res += str[i] - '0';
		i++;
		if (str[i] >= '0' && str[i] <= '9')
			res *= 10;
	}
	res -= 1;
	res *= is_minus;
	res += is_minus;
	return (res);
}
