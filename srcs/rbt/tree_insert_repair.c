/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_insert_repair.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:34:10 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:34:11 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void		tree_insert_repair(t_rbt *n)
{
	if (tree_parent(n) == NULL)
	{
		tree_insert_case_1(n);
	}
	else if (tree_parent(n)->color == BLACK)
	{
		tree_insert_case_2(n);
	}
	else if (tree_uncle(n) != NULL && tree_uncle(n)->color == RED)
	{
		tree_insert_case_3(n);
	}
	else
	{
		tree_insert_case_4(n);
	}
}
