/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** lemin
*/

#include "printf.h"

static const t_fmt jmp[] =
{
		{'s', print_string},
		{'d', print_digit},
		{'c', print_char},
		{'p', print_ptr},
		{'x', print_hex},
		{'o', print_octal}
};

static const size_t nfmt = sizeof(jmp) / sizeof(t_fmt);

inline void __attribute__((always_inline))
print_digit(void *p)
{
		int n = (*(int*)p);

		if (n < 0)
				write(1, "-", 1);
		n = n < 0 ? -n : n;
		my_itoa(n, 10);
}

inline void __attribute__((always_inline))
print_string(void *p)
{
		char *s = *((char**)p);

		if (!s)
		{
				write(1, "(null)", 6);
				return ;
		}
		while (*s)
				write(1, s++, 1);
}

static p_fmt search_fmt(char fmt)
{
		for (size_t i = 0; i < nfmt; i++)
		{
				if (jmp[i].fmt == fmt)
						return (jmp[i].f);
		}
		return (NULL);
}

int my_printf(const char *fmt, ...)
{
		int total = 0;
		p_fmt p = NULL;
		va_list va;
		void* param = NULL;

		va_start(va, fmt);
		for (size_t i = 0; fmt[i]; i++) {
				if ((fmt[i] == '%' && fmt[i + 1] == '%') ||
					(fmt[i] == '\\' && fmt[i + 1] == '%')) {
						write(1, "%", 1);
						++i;
				}
				else if (fmt[i] == '%' && fmt[i + 1] != 0) {
						if ((p = search_fmt(fmt[i + 1]))){
								param = va_arg(va, void*);
								p(&param);
								++i;
						}
				}
				else
						(void)write(1, &fmt[i], 1);
		}
		va_end(va);		
		return (total);
}
