/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoropet <akoropet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 17:39:28 by akoropet          #+#    #+#             */
/*   Updated: 2019/04/23 16:13:06 by akoropet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define TYPE_NUM 11

# include "../libft/libft.h"
# include <stdarg.h>
# include <locale.h>
# include <wchar.h>

typedef struct				s_type
{
	char	symb;
	int		(*ft)(char *, va_list);
}							t_type;

typedef	struct				s_flags
{
	int		minus;
	int		plus;
	int		zero;
	int		space;
	int		hashtag;
	int		width;
	int		precision;
}							t_flags;

extern t_type				g_type[TYPE_NUM];
extern t_flags				g_flags[5];

int							ft_printf(char *str, ...);
int							check_arg(char **str, int n, va_list ap);

void						ft_flags(char *str, char symb);

int							ft_width(char *str, char symb);
int							ft_precision(char *str, char symb);

int							ft_modifier(char *str, char symb);

int							print_type(char *str, va_list ap);

int							print_s(char *str, va_list ap);
int							create_str_s(char *arg);
void						print_s_with_minus(char *res, char *arg);
void						print_s_without_minus(char *res, char *arg,
	int len);

int							print_p(char *str, va_list ap);
void						write_all(char *num, char *arg, int *count,
	unsigned long long int s);
char						*create_arg(int len);

int							print_o(char *str, va_list ap);
char						*create_str_o(char *num, int len);
int							check_flags_o(char *num, int len);

int							print_c(char *str, va_list ap);
int							print_c_with_minus(char s, int width);
int							print_c_without_minus(char s, int width);

int							print_d(char *str, va_list ap);
char						*create_num(unsigned long long int m);
int							check_flags(unsigned long long int m, int minus);
char						*create_flags(int len, int minus);
int							len_str(int len, int minus);

int							print_i(char *str, va_list ap);

int							print_u(char *str, va_list ap);
int							check_flags_u(char *num, int len);
char						*create_str_u(int len);
void						write_to_res_u(char *res, char *num, int len);

int							print_x(char *str, va_list ap);
int							check_flags_x(char *num, int len);
char						*create_str_x(char *num, int len);
int							print_big_x(char *str, va_list ap);
int							check_flags_big_x(char *num, int len);
void						to_upper_x(char *num, char *str);

int							print_big_c(char *str, va_list ap);
char						*print_unicode(int num);
char						**create_mask(size_t len);
void						write_to_mask(char **mask, char *bin, int len);
int							bin_to_dec(char *bin);

int							print_f(char *str, va_list ap);
int							create_float(long double d, int minus);
char						*write_flags(int full, int drob, int minus);
char						*correct_full(char *full, char *drob);
void						correct_drob(char *drob, char *r, int i, int zero);
char						*create_drob(long double d, int n);
int							in_the_end(int full, int drob, int minus);

int							print_perc(char *str);
int							normal(char *str);
int							write_upper(char *str, int i);
#endif
