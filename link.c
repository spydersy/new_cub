/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:31:53 by abelarif          #+#    #+#             */
/*   Updated: 2020/11/15 23:51:19 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "link.h"
#include "cub3d.h"

void		insertion(t_liste *liste, char *nvline)
{
	t_line *nouveau;

	nouveau = malloc(sizeof(nouveau));
	if (liste == NULL || nouveau == NULL)
		ft_error("link\n");
	nouveau->line = nvline;
	nouveau->next = liste->first;
	liste->first = nouveau;
}

t_liste		*initialisation(char *str)
{
	t_liste		*liste;
	t_line		*element;

	liste = malloc(sizeof(t_liste));
	element = malloc(sizeof(t_line));
	if (liste == NULL || element == NULL)
		ft_error("link\n");
	element->line = str;
	element->next = NULL;
	liste->first = element;
	return (liste);
}
