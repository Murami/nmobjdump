/*
** objdump.h for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/include
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:35:42 2014
** Last update Wed Mar 12 23:06:36 2014 
*/

#ifndef OBJDUMP_H
# define OBJDUMP_H

# include <endian.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <elf.h>
# include <fcntl.h>
# include <sys/mman.h>
# include "filemap.h"
# include "objdump32.h"

uint16_t	gethost16(uint16_t value, void* elf);
uint32_t	gethost32(uint32_t value, void* elf);
uint64_t	gethost64(uint64_t value, void* elf);
void*		fmapaccess(t_filemap* filemap, unsigned long off, unsigned long size);
int		fmap(char* filename, t_filemap* filemap);

#endif /* OBJDUMP_H */
