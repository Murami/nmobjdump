/*
** dump_section.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:23:21 2014
** Last update Wed Mar 12 23:13:06 2014 
*/

#include "objdump.h"

static void		print_raw_bytes32(t_dump_infos* dump_infos)
{
  unsigned int	i;
  int		cpy_ndword;

  cpy_ndword = dump_infos->ndword;
  i = 0;
  printf(" ");
  while (dump_infos->ndword < 4)
    {
      printf("         ");
      dump_infos->ndword++;
    }
  if (dump_infos->granularity != 0)
    cpy_ndword--;
  while (i < (4 * cpy_ndword + dump_infos->granularity))
    {
      if (dump_infos->buffer[i] >= ' ' && dump_infos->buffer[i] <= '~')
	printf("%c", dump_infos->buffer[i]);
      else
	printf(".");
      i++;
    }
}

static void		dump_section_content_byte32(void* offset, unsigned int section_size,
						    t_dump_infos* dump_infos)
{
  unsigned char*	pvalue;
  unsigned char		granularity;

  dump_infos->granularity = 0;
  while (dump_infos->granularity != 4 && dump_infos->offset < section_size)
    {
      pvalue = offset + dump_infos->offset;
      printf("%02x", *pvalue);
      dump_infos->buffer[dump_infos->ndword * 4 + dump_infos->granularity] =
	*pvalue;
      dump_infos->offset++;
      dump_infos->granularity++;
    }
  granularity = dump_infos->granularity;
  while  (granularity != 4)
    {
      printf("  ");
      granularity++;
    }
}

static void		dump_section_content_dword32(t_filemap* filemap, Elf32_Shdr* section,
					     t_dump_infos* dump_infos, Elf32_Ehdr* elf)
{
  printf(" %04x ", gethost32(section->sh_addr, elf) + dump_infos->offset);
  while (dump_infos->ndword < 4 && dump_infos->offset <
	 gethost32(section->sh_size, elf))
    {
      dump_section_content_byte32(filemap->map +
				  gethost32(section->sh_offset, elf),
				  gethost32(section->sh_size, elf), dump_infos);
      printf(" ");
      dump_infos->ndword++;
    }
  print_raw_bytes32(dump_infos);
  memset(dump_infos->buffer, 0, 16);
}

int		dump_section_content32(t_filemap* filemap, Elf32_Shdr* section,
				       char* section_name, Elf32_Ehdr* elf)
{
  t_dump_infos		dump_infos;

  memset(&dump_infos, 0, sizeof(t_dump_infos));
  if (gethost32(section->sh_size, elf) == 0 ||
      gethost32(section->sh_size, elf) == SHT_NOBITS ||
      strcmp(section_name, ".bss") == 0)
    return (0);
  if (!fmapaccess(filemap, gethost32(section->sh_offset, elf),
		  gethost32(section->sh_size, elf)))
    {
      fprintf(stderr,
	      "error: invalid section %s of size %d\n",
	      section_name,
	      gethost32(section->sh_size, elf));
      return (-1);
    }
  while (dump_infos.offset < gethost32(section->sh_size, elf))
    {
      dump_infos.ndword = 0;
      dump_section_content_dword32(filemap, section, &dump_infos, elf);
      printf("\n");
    }
  return (0);
}
