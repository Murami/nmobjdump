/*
** map.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:27:44 2014
** Last update Wed Mar 12 23:04:19 2014 
*/

#include "objdump.h"

static size_t		filesize(int fd)
{
  off_t		offset;
  size_t	size;

  offset = lseek(fd, 0, SEEK_CUR);
  if (offset == -1)
    return (-1);
  size = lseek(fd, 0, SEEK_END);
  if (size == (unsigned)-1)
    return (-1);
  if (lseek(fd, offset, SEEK_SET) == -1)
    return (-1);
  return (size);
}

static int		fdmap(int fd, t_filemap* filemap)
{
  filemap->size = filesize(fd);
  filemap->map = mmap(NULL, filemap->size, PROT_READ, MAP_SHARED, fd, 0);
  if (filemap->map == MAP_FAILED)
    return (-1);
  return (0);
}

int		fmap(char* filename, t_filemap* filemap)
{
  int		fd;

  fd = open(filename, O_RDONLY);
  if (fd == -1)
    return (-1);
  if (fdmap(fd, filemap) == -1)
    return (-1);
  if (close(fd) == -1)
    return (-1);
  return (0);
}
