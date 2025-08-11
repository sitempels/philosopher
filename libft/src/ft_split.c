/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:53:43 by stempels          #+#    #+#             */
/*   Updated: 2024/12/15 13:39:32 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**word_check(char **res, char const *s, char c);
static void	free_array(char **tab, int j);
static int	word_nbr(char const *s, char c);
static char	*word_cpy(char **res, char const *substr, int size, int j);

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **) ft_calloc(word_nbr(s, c) + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res = word_check(res, s, c);
	return (res);
}

static char	**word_check(char **res, char const *s, char c)
{
	size_t	i;
	int		j;
	int		in_word;

	i = 0;
	j = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
			in_word = i + 1;
		if ((s[i + 1] == c || s[i + 1] == '\0') && in_word)
		{
			res[j] = word_cpy(res, &s[in_word - 1], i - (in_word - 1) + 1, j);
			if (!res[j])
			{
				free_array(res, j);
				return (NULL);
			}
			in_word = 0;
			j++;
		}
		i++;
	}
	return (res);
}

static char	*word_cpy(char **res, char const *substr, int size, int j)
{
	res[j] = (char *) ft_calloc(size + 1, sizeof(char));
	if (!res[j])
		return (NULL);
	ft_memcpy(res[j], substr, size);
	return (res[j]);
}

static void	free_array(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	word_nbr(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		if (s[i] == c && in_word)
			in_word = 0;
		i++;
	}
	return (count);
}
