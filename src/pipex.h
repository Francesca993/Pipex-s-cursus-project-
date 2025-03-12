/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmontini <fmontini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:42:10 by fmontini          #+#    #+#             */
/*   Updated: 2025/03/12 15:57:53 by fmontini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>  // per pipe, dup2, execve
#include <sys/wait.h> // per wait, waitpid
#include <stdlib.h>   // per malloc, free
#include <fcntl.h>    // per open, close
#include <stdio.h>    // per perror
# include "../Libft/libft.h" // Include le funzioni della libft
# include "../Printf/ft_printf.h" // Include le funzioni della libft

void    error_exit(const char *msg);
void first_child(char *infile, int **pipe_fd, char *in_cmd, char **envp);
void    second_child(char **out_cmd, int **pipe_fd, char **envp, char *outfile);
void    execute_cmd(char *cmd, char **envp);

#endif