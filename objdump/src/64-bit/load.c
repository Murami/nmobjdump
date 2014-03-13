/*
** load.c for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/src
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:25:37 2014
** Last update Thu Mar 13 18:48:59 2014 
*/

#include "objdump.h"

Elf64_Ehdr*	load_elf_header64(t_filemap* filemap)
{
  return (fmapaccess(filemap, 0, sizeof(Elf64_Ehdr)));
}

Elf64_Phdr*	load_segment_header64(t_filemap* filemap,
				      Elf64_Ehdr* elf,
				      unsigned int nsegment)
{
  return (fmapaccess(filemap,
		     gethost64(elf->e_phoff, elf) +
		     gethost16(elf->e_phentsize, elf) * nsegment,
		     elf->e_phentsize));
}

Elf64_Shdr*	load_section_header64(t_filemap* filemap,
				      Elf64_Ehdr* elf,
				      unsigned int nsection)
{
  return (fmapaccess(filemap,
		     gethost64(elf->e_shoff, elf) +
		     gethost16(elf->e_shentsize, elf) * nsection,
		     elf->e_shentsize));
}

char*		load_section_name64(t_filemap* filemap,
				    Elf64_Ehdr* elf,
				    unsigned int indexstr)
{
  Elf64_Shdr*	names_section;
  char*		stringtable;
  char*		string;

  names_section = load_section_header64(filemap,
					elf,
					gethost16(elf->e_shstrndx, elf));
  if (names_section == NULL)
    return (NULL);
  if (indexstr >= gethost32(names_section->sh_size, elf))
    return (NULL);
  stringtable = fmapaccess(filemap,
			   gethost64(names_section->sh_offset, elf),
			   gethost32(names_section->sh_size, elf));
  if (stringtable == NULL)
    return (NULL);
  string = stringtable + indexstr;
  if (strnlen(string, gethost32(names_section->sh_size, elf) - indexstr) ==
      gethost32(names_section->sh_size, elf) - indexstr)
    return (NULL);
  return (string);
}
