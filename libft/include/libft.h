/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:09:18 by stempels          #+#    #+#             */
/*   Updated: 2025/03/20 16:12:10 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*--------------------------LIBRARY-------------------------------------------*/
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
/**/
/*--------------------------MACROS--------------------------------------------*/
# define BA_10 "0123456789"
# define BA_16 "0123456789abcdef"
# define BA_X16 "0123456789ABCDEF"
/**/
# define FORMAT "csdiuxXp%"
/**/
/*--------------------------STRUCTURES----------------------------------------*/
typedef struct s_list
{
	int				content;
	struct s_list	*next;
}	t_list;

typedef struct s_ctrl
{
	int	cost_a;
	int	cost_b;
	int	cost;
	int	lst_min;
	int	lst_max;
}	t_ctrl;
/**/
/*--------------------------LIBC_FUNCTIONS------------------------------------*/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isspace(char c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
/**/
/*--------------------------MALLOC_FUNCTIONS----------------------------------*/
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
/**/
/*Additional functions*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
/**/
/*--------------------------PRINTING_FUNCTIONS--------------------------------*/
size_t	ft_putchar_fd(char c, int fd);
size_t	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_putnbr_bfd(long long nbr, char *base, int fd);
int		ft_putunbr_bfd(unsigned long long nbr, char *base, int fd);
int		ft_printf_fd(int fd, const char *str, ...);
/**/
/*--------------------------UTILS_FONCTIONS-----------------------------------*/
int		get_s(char *arg, int fd);
int		get_p(unsigned long long arg, char *base, int fd);
/**/
/*--------------------------LIST_FUNCTIONS------------------------------------*/
t_list	*ft_lstnew(int content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(int));
void	ft_lstclear(t_list **lst, void (*del)(int));
void	ft_lstiter(t_list *lst, void (*f)(int));
t_list	*ft_lstmap(t_list *lst, void *(*f)(int), void (*del)(int));
/**/
/*--------------------------CALC_FUNCTIONS------------------------------------*/
int		ft_abs(int a);
/**/
#endif
