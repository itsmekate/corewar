/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 17:19:34 by kprasol           #+#    #+#             */
/*   Updated: 2017/11/16 15:57:29 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;
	t_list	*head;
	t_list	*newelem;

	if (lst == NULL || f == NULL)
		return (NULL);
	newlst = (t_list*)malloc(sizeof(t_list));
	if (newlst == NULL)
		return (NULL);
	head = f(lst);
	newelem = head;
	lst = lst->next;
	while (lst)
	{
		newlst = f(lst);
		if (newlst == NULL)
			return (NULL);
		newelem->next = newlst;
		newelem = newlst;
		lst = lst->next;
	}
	newelem->next = NULL;
	return (head);
}
