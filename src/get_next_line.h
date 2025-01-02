/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkerman <rkerman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:39:15 by rkerman           #+#    #+#             */
/*   Updated: 2025/01/02 13:11:21 by rkerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
# 	define BUFFER_SIZE 42
#endif

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

#endif
