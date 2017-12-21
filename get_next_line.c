/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesanche <lesanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 13:55:51 by lesanche          #+#    #+#             */
/*   Updated: 2017/12/21 16:34:46 by lesanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstadd_end(t_list **begin_list, t_list *n)
{
	t_list *l;

	l = *begin_list;
	if (l == NULL)
	{
		*begin_list = n;
		return ;
	}
	while (l->next)
		l = l->next;
	l->next = n;
}

int		ft_shift_str_until(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != c)
		i++;
	if (i + 1 >= (int)ft_strlen(str))
	{
		str[0] = '\0';
		return (1);
	}
	while (str[i + 1 + j] != '\0')
	{
		str[j] = str[i + 1 + j];
		j++;
	}
	str[j] = '\0';
	return (0);
}

int		get_line_len(t_list *begin_list)
{
	t_list	*elem;
	int		len;
	int		i;
	char	*str;

	len = 0;
	elem = begin_list;
	while (elem)
	{
		str = elem->content;
		i = 0;
		while (str[i] && (str[i] != '\n'))
			i++;
		len += i;
		elem = elem->next;
	}
	return (len);
}

int		c_in_str(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i > 1)
		return (0);
	if (i == 1 && str[0] == c)
		return (1);
	if (i == 0)
		return (1);
	return (0);
}

void	del_content(void *content, size_t n)
{
	n++;
	free(content);
}

int		get_next_line(const int fd, char **line)
{
	static char		buf[BUFF_SIZE + 1];
	int				nb;
	t_list			*b_list;
	t_list			*el;

	b_list = 0;
	nb = 0;
	while (1)
	{
		el = ft_lstnew(buf, BUFF_SIZE + 1);
		ft_lstadd_end(&b_list, el);
		if (ft_strchr(buf, '\n') || (nb = read(fd, buf, BUFF_SIZE)) == 0)
			break ;
		if (nb == -1 || fd < 0)
			return (-1);
		buf[nb] = '\0';
	}
	*line = (char*)malloc((get_line_len(b_list) + 1) * sizeof(char));
	*line[0] = '\0';
	el = b_list;
	while (el)
	{
		ft_strncat(*line, el->content, get_line_len(b_list) - ft_strlen(*line));
		el = el->next;
	}
	ft_lstdel(&b_list, &del_content);
	if ((int)ft_strlen(buf) == 1 && buf[0] == '\n')
		buf[0] = '\0';
	else if ((nb < BUFF_SIZE) && (ft_strlen(*line) == 0) && c_in_str(buf, '\n'))
		return (0);
	ft_shift_str_until(buf, '\n');
	return (1);
}
