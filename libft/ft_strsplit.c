/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llonnrot <llonnrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:35:08 by llonnrot          #+#    #+#             */
/*   Updated: 2022/02/08 19:01:47 by llonnrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_freetwod(char **twod, size_t ai)
{
	while (ai != 0)
	{
		free(twod[ai]);
		ai--;
	}
}

static	int	ft_rows(char const *s, char c)
{
	int	i;
	int	twod;

	twod = 0;
	i = 0;
	if (s[i] == c)
		twod--;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		if (s[i] == c && s[i + 1] != '\0')
			twod++;
		while (s[i] && s[i] == c)
			i++;
	}
	if (twod >= 1)
		twod++;
	if (s[i - 1] == c && s[i - 2] == c)
		twod--;
	if (twod <= 0)
		return (1);
	return (twod);
}

static	char	**ft_mallocstr(char const *s, char **twod, int c)
{
	int	ai;
	int	si;
	int	cc;

	ai = 0;
	si = 0;
	cc = 0;
	while (s[si])
	{
		while (s[si] && s[si] == c)
			si++;
		if (s[si] == '\0')
			break ;
		while (s[si] && s[si++] != c)
			cc++;
		twod[ai] = (char *)malloc(sizeof(char) * cc + 1);
		cc = 0;
		ai++;
	}
	return (twod);
}

static	char	**ft_assignchar(char const *s, char **twod, int c, int asi)
{
	int	ai;
	int	si;

	ai = 0;
	si = 0;
	while (s[si])
	{
		while (s[si] && s[si] == c)
			si++;
		if (s[si] == '\0')
			break ;
		while (s[si] && s[si] != c)
			twod[ai][asi++] = s[si++];
		if (s[si])
			twod[ai][asi] = '\0';
		ai++;
		asi = 0;
	}
	if (ai == 0)
	{
		twod[0] = NULL;
		ai = 1;
	}
	twod[ai] = 0;
	return (twod);
}

char	**ft_strsplit(char const *s, char c)
{
	size_t		ai;
	size_t		rows;
	int			asi;
	char		**twod;

	if (s == NULL)
		return (NULL);
	ai = 0;
	asi = 0;
	rows = ft_rows(s, c);
	twod = (char **)malloc(sizeof(char *) * rows + 1);
	if (twod == NULL)
		return (NULL);
	twod = ft_mallocstr(s, twod, c);
	if (twod[ai] == NULL)
	{
		ft_freetwod(twod, ai);
		free (twod);
		return (NULL);
	}
	twod = ft_assignchar(s, twod, c, asi);
	return (twod);
}
