/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 00:15:38 by mel-oual          #+#    #+#             */
/*   Updated: 2020/02/28 04:33:12 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
void *ft_memset(void *b, int c, size_t len)
{
	unsigned i;

	i = 0;
	while (i < len)
	{
		((unsigned char*)b)[i++] = (unsigned char)c;
	}
	return (b);
}

int ft_strchr(char c, char *str)
{
	int x;
	x = -1;

	while(str[++x])
		if(str[x] == c)
			return(x);
	return(-1);
}

int ft_strlen(const char *str)
{
	int len;
	len = 0;
	if(str == NULL || *str == '\0')
		return(0);
	while(str[len] != 0)
		len++;
	return(len);
}

char *ft_strnew(int len)
{
	char *str_new;
	str_new = NULL;

	if(!(str_new = (char *)malloc(sizeof(char) * len)))
		return(NULL);
	return(str_new);
}

char *ft_strjoin(char *s1, char *s2)
{
	char *tmp;
	int len_s1;
	int len_s2;

	tmp = NULL;
	len_s1 = 0;
	len_s2 = 0;

	if(s1 == NULL || s2 == NULL)
		return(NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if(!(tmp = (char *)malloc(sizeof(char) * len_s1 + len_s2 + 1)))
		return(NULL);
	while(s1 <= s1 + len_s1 && *s1)
	{
		*tmp = *s1;
		tmp++;
		s1++;
	}
	while(s2 <= s2 + len_s2 && *s2)
	{
		*tmp = *s2;
		tmp++;
		s2++;
	}
	*(tmp + 1) = '\0';
	return(tmp - (len_s1 + len_s2));
}
void ft_strdel(char *str)
{
	if(str != NULL)
		free(str);
	str = NULL;
}
char *ft_strndup(char *str, int i)
{
	int x;
	char *tmp;
	x = -1;
	tmp = NULL;
	if(!(tmp = (char *)malloc(sizeof(char) * i + 1)))
		return(0);
	while(++x < i && str[x])
		tmp[x] = str[x];
	tmp[x] = '\0';
	return(tmp);
}
char *ft_strdup(char *str)
{
	char *tmp;
	int x;
	x = -1;
	tmp = NULL;

	tmp = ft_strnew(ft_strlen(str) + 1);
	while(str[++x])
		tmp[x] = str[x];
	tmp[x] = '\0';
	return(tmp);
}
