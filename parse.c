/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esakgul <esakgul@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:13:34 by esakgul           #+#    #+#             */
/*   Updated: 2026/01/09 17:38:56 by esakgul          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_digit(char c)
{
    if(c >= 48 && c <= 57)
        return 1;
    return 0;
}

int parse (int ac, char **av)
{
    int i = 1;
    int j = 0;
    
    if (ac < 5 || ac > 6)
        return 1;
        
    while(i < ac)
    {
        while(av[i][j] != '\0')
        {
            if (!is_digit(av[i][j]))
                return 1;
                j++;
        }
        i++;
    }
    
}