/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmallado <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 19:34:13 by lmallado          #+#    #+#             */
/*   Updated: 2020/12/04 19:34:16 by lmallado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	thinking_move(t_philo *philo)
{
	if (!philo->vars->death)
		print_log(&philo->mutex[philo->philosophers_count],
		MAG,
		"is thinking", philo);
	return (philo->vars->death);
}

int	fork_move(t_philo *philo, int fork_id)
{
	if (!philo->vars->death)
	{
		pthread_mutex_lock(&philo->mutex[fork_id]);
		print_log(&philo->mutex[philo->philosophers_count], YEL,
		"has taken a fork", philo);
	}
	return (philo->vars->death);
}

int	eating_move(t_philo *philo, t_forks forks)
{
	if (!philo->vars->death)
	{
		pthread_mutex_lock(&philo->vars->get_time_mutex);
		gettimeofday(&philo->last_eat, NULL);
		pthread_mutex_unlock(&philo->vars->get_time_mutex);
		print_log(&philo->mutex[philo->philosophers_count], GRN,
		"is eating", philo);
		philo->eat_num++;
		pthread_mutex_lock(&philo->eat_lock);
		sleep_for(philo->time_to_eat, &philo->vars->get_time_mutex);
		pthread_mutex_unlock(&philo->mutex[forks.first]);
		pthread_mutex_unlock(&philo->mutex[forks.second]);
		pthread_mutex_unlock(&philo->eat_lock);
		if (philo->eat_num == philo->number_must_eat)
			return (1);
	}
	return (philo->vars->death);
}

int	sleeping_move(t_philo *philo)
{
	if (!philo->vars->death && philo->eat_num != philo->number_must_eat)
	{
		print_log(&philo->mutex[philo->philosophers_count],
		BLU, "is sleeping", philo);
		sleep_for(philo->time_to_sleep, &philo->vars->get_time_mutex);
	}
	return (philo->vars->death);
}
