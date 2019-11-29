#include <stdio.h>
#include "ft_printf.h"
#include <float.h>
#include <math.h>


int main(void)
{
	double number0 = 0.2;

	__uint128_t bits = *(__uint128_t *)(&number0);
	unsigned int exp = ((bits >> 52) & 0x7FF) - 1023;
	ft_printf("%f", 10.5);
	// int i = 64;
	// while (--i >= 0)
	// {
	// 	if ((bits >> i) & 1)
	// 		printf("1");
	// 	else
	// 		printf("0");
	// }
	return (0);
}

