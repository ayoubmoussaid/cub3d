/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoussai <amoussai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 08:59:19 by amoussai          #+#    #+#             */
/*   Updated: 2020/01/24 14:32:26 by amoussai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	ft_error(char *str)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	exit(0);
}

void	check_file(char *str)
{
	int fd;

	if ((fd = open(str, O_RDONLY)) == -1)
	{
		perror("Error\ncub3D");
		exit(0);
	}
	close(fd);
}
