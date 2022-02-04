/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:56:25 by llonnrot          #+#    #+#             */
/*   Updated: 2021/11/29 19:33:07 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_calculen(long c)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	if (c < 0)
		c = -c;
	while (c > 0)
	{
		c = c / 10;
		i++;
	}
	return (i);
}

static	char	*ft_calculator(char *s, long n, int base, int ifnegative)
{
	int		i;
	int		rem;

	i = 0;
	if (n < 0)
	{
		n = -n;
		ifnegative = 1;
	}
	while (n != 0)
	{
		rem = n % base;
		if (rem > 9)
			s[i++] = (rem - 10) + 'A';
		else
			s[i++] = rem + '0';
		n = n / base;
	}
	if (ifnegative == 1)
		s[i++] = '-';
	s[i++] = '\0';
	return (s);
}

static	char	*ft_reverse(char *s)
{
	int		i;
	int		len;
	char	*revstr;

	revstr = (char *) malloc (sizeof(char) * ft_strlen(s) + 1);
	if (!revstr)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	len = len - 1;
	while (len >= 0)
	{
		revstr[i] = s[len];
		len--;
		i++;
	}
	revstr[i] = '\0';
	return (revstr);
}

char	*ft_itoa(int n)
{
	int		i;
	int		ifnegative;
	int		base;
	char	*newstr;
	long	num;

	num = n;
	base = 10;
	ifnegative = 0;
	i = ft_calculen(num);
	newstr = (char *)malloc(sizeof(char) * i + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	if (num == 0)
	{
		newstr[i] = '0';
		newstr[i + 1] = '\0';
		return (newstr);
	}
	newstr = ft_calculator(newstr, num, base, ifnegative);
	newstr = ft_reverse(newstr);
	return (newstr);
}
