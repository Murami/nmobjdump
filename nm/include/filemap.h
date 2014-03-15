/*
** filemap.h for  in /home/otoshigami/rendu/PSU_2013_nmobjdump
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:42:28 2014
** Last update Wed Mar 12 22:53:52 2014 
*/

#ifndef FILEMAP_H
# define FILEMAP_H

typedef struct	s_filemap
{
  unsigned int		size;
  void*			map;
}		t_filemap;

typedef struct	s_dump_infos
{
  unsigned char		buffer[16];
  unsigned int		offset;
  unsigned int		ndword;
  unsigned int		granularity;
}		t_dump_infos;

#endif /* FILEMAP_H */
