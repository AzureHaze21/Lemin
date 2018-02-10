/*
** EPITECH PROJECT, 2017
** itoa
** File description:
** itoa
*/

#include "printf.h"

static char digits[] = "0123456789abcdef";

void my_itoa(int n, int base)
{
		if (!(n / base))
		{
				write(1, &digits[n], 1);
				return ;
		}
		my_itoa(n / base, base);
		write(1, &digits[n % base], 1);
}

void my_ulltoa(unsigned long long n, int base)
{
		if (!(n / base))
		{
				write(1, &digits[n], 1);
				return ;
		}
		my_ulltoa(n / base, base);
		write(1, &digits[n % base], 1);
}

int my_atoi(char *s)
{
		int ret = 0;
		int sign = 1;

		while (s && (*s) == ' ')
				s++;
		while (*s && *s != ' ' && *s != '\t')
		{
				if (*s == '-')
				{
						sign = -1;
						s++;
				}
				else if (!IS_NUM(*s))
						return (ret * sign);
				ret = (ret * 10) + ((*s) - '0');
				s++;
		}
		return (ret * sign);
}
