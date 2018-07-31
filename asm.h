/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 15:20:14 by kprasol           #+#    #+#             */
/*   Updated: 2018/07/31 15:20:16 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include <sys/stat.h> 
#include <fcntl.h>

typedef struct 			s_lst
{
	char				*str;
	struct s_lst		*next;
}						t_lst;