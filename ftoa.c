/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmallist <fmallist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:15:28 by fmallist          #+#    #+#             */
/*   Updated: 2019/11/26 20:58:2 by fmallist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>

unsigned	g_tens[8] = {10, 100, 1000, 10000, 100000,
						1000000, 10000000, 100000000};

int			count_zeros(t_float *n)
{
	unsigned last;
	if (n->fractional.size_num == 0)
		return (0);
	last = ft_numlen_u(n->fractional.arr[n->fractional.size_num - 1]);
	return (52 - n->exp - 9 * (n->fractional.size_num - 1) - last);
}

static void		handle_f_prec(t_float *n, t_printf *data)
{
	unsigned j;

	if (n->fractional.size_num == 0)
		return ;
	if (data->precision == 0)
		data->precision = 6;
	if (data->precision == -1)
	{
		n->fractional.size_num = 0;
		return ;
	}
	data->precision -= count_zeros(n);
	printf("123:%d\n", count_zeros(n));
	data->precision++;
	printf("fractional.size_num:%d\n", n->fractional.size_num);
	j = n->fractional.size_num - 1 - data->precision / 9
	- (data->precision % 9 == 0 ? 1 : 0);
	printf("j:%d\n", data->precision);
	data->precision -= (n->fractional.size_num - 2) * 9 -
	ft_numlen_u(n->fractional.arr[n->fractional.size_num - 1]);
	n->fractional.size_num = j + 1;
	printf("????:%d\n", ft_numlen_u(n->fractional.arr[j]) - data->precision);
	n->fractional.arr[j] = n->fractional.arr[j] / g_tens[ft_numlen_u(n->fractional.arr[j]) - data->precision];
	//if ((n->fractional.arr[j] /= g_tens[ft_numlen_u(n->fractional.arr[j]) - data->precision]) % 10 > 5)
		//add_long_short(&n->fractional, 1);
}

static void		print_float(t_float number, t_printf *data)
{
	unsigned zeros;
	int i, j;
	j = 0;
	i = 0;
	i = number.decimal.size_num - 1;
	while (i >= 0)
	{
		j = 9 - ft_numlen_u(number.decimal.arr[i]);
		if ((unsigned)i == number.decimal.size_num - 1)
			j = 0;
		while (j-- > 0)
			data->buff[data->length++] = '0';
		itoa_base_buff_u(number.decimal.arr[i], data);
		i--;
	}
	data->buff[data->length++] = '.';
	i = number.fractional.size_num - 1;
	zeros = count_zeros(&number);
	while (zeros--)
		data->buff[data->length++] = '0';
	if (i >= 0)
		while (i >= 0)
		{
			j = 9 - ft_numlen_u(number.fractional.arr[i]);
			if ((unsigned)i == number.fractional.size_num - 1)
				j = 0;
			while (j-- > 0)
				data->buff[data->length++] = '0';
			itoa_base_buff_u(number.fractional.arr[i], data);
			i--;
		}
	else
	{
		ft_strcpy(&data->buff[data->length], "000000");
		data->length += 6;
	}
}

void		init_float_bitfields(t_float *number, t_printf *data)
{
	int			i;
	int			j;
	__uint128_t	bits;

	i = 51;
	j = 0;
	number->fractional.arr[0] = 1;
	bits = *(__uint128_t *)(&number->num);
	number->exp = ((bits >> 52) & 0x7FF) - 1023;
	if (number->exp >= 0 && (bits != 0 || !((bits >> 63) & 1)))
		number->decimal.arr[0] = 1;
	number->decimal.size_num = 1;
	if (number->exp > 0)
		while (i > 51 - number->exp)
		{
			multiply_long_short(&number->decimal, 2);
			if (((bits >> (__uint128_t)i) & 1) && i >= 0)
				add_long_short(&number->decimal, 1);
			i--;
		}
	if (number->exp < 0)
	{
		number->num++;
		bits = *(__uint128_t *)(&(number->num));
		number->exp = ((bits >> 52) & 0x7FF) - 1023;
	}
	i = 52 - number->exp;
	while (--i >= 0)
	{
		multiply_long_short(&number->fractional, 10);
		if ((bits >> i) & 1)
			add_long_long(&number->fractional,
			big_power_of_five(52 - number->exp - i));
	}
	handle_f_prec(number, data);
	print_float(*number, data);
}

void		float_to_str(t_float *n, t_printf *data)
{
	data->type = FL;

	init_float_bitfields(n, data);
}

void		handle_floats(t_printf *data)
{
	t_float	fl;
	t_ldbl	ldbl;

	ft_bzero(&fl, sizeof(t_float));
	ft_bzero(&ldbl, sizeof(t_ldbl));


	if (data->size == BIGL)
	{
		ldbl.num = va_arg(data->ap, long double);
		//ldbl_to_str(&ldbl, data);
	}
	else
	{
		fl.num = va_arg(data->ap, double);
		float_to_str(&fl, data);
	}
}
