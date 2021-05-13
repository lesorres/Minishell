/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeeseek <kmeeseek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:49:13 by kmeeseek          #+#    #+#             */
/*   Updated: 2021/04/25 13:37:12 by kmeeseek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	k;

	k = n;
	if (k < 0)
	{
		k = k * (0 - 1);
		ft_putchar_fd('-', fd);
	}
	if (k >= 10)
	{
		ft_putnbr_fd((k / 10), fd);
		ft_putnbr_fd((k % 10), fd);
	}
	else
		ft_putchar_fd((k + 48), fd);
}
