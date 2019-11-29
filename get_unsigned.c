/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:14:42 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/12 21:57:34 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_unsigned(t_printf *data, t_ull *n)
{
	*n = va_arg(data->ap, t_ull);
	if (data->size & H)
	*n = (unsigned short)*n;
	else if (data->size & HH)
	*n = (unsigned char)*n;
	else if (!(data->size & L) && !(data->size & LL))
	*n = (unsigned int)*n;
	if (data->flag & PLUS)
		data->flag ^= PLUS;
	else if (data->flag & SPACE)
		data->flag ^= SPACE;
}
