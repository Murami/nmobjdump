/*
** fmapaccess.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:32:23 2014
** Last update Sat Mar 15 17:42:26 2014 
*/

#include "objdump.h"

void*		fmapaccess(t_filemap* filemap,
			   unsigned long off,
			   unsigned long size)
{
  if (off + size <= filemap->size && size != 0)
    return (filemap->map + off);
  else
    return (NULL);
}
