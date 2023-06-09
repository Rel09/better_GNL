/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpotvin <dpotvin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 02:08:14 by dpotvin           #+#    #+#             */
/*   Updated: 2023/03/20 03:21:52 by dpotvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# include <stdlib.h>	// Malloc & Free
# include <unistd.h>	// Read
// Use what's more appropriate for your project
# define BUFFER_SIZE 50 
// why import stdbool when you can do that
typedef enum _bool { FALSE, TRUE } t_bool;
typedef struct _gnl { 
	char *string;
	int strlen;
}	t_gnl;
#endif

