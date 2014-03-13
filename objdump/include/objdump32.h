/*
** objdump32.h for  in /home/otoshigami/rendu/PSU_2013_nmobjdump
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Wed Mar 12 22:35:59 2014
** Last update Thu Mar 13 18:52:56 2014 
*/

#ifndef OBJDUMP32_H
# define OBJDUMP32_H

# include "filemap.h"

int		dump_section_content32(t_filemap* filemap, Elf32_Shdr* section,
				       char* section_name, Elf32_Ehdr* elf);
Elf32_Ehdr*	load_elf_header32(t_filemap* filemap);
Elf32_Phdr*	load_segment_header32(t_filemap* filemap,
				      Elf32_Ehdr* elf,
				      unsigned int nsegment);
Elf32_Shdr*	load_section_header32(t_filemap* filemap,
				      Elf32_Ehdr* elf,
				      unsigned int nsection);
char*		load_section_name32(t_filemap* filemap,
				    Elf32_Ehdr* elf,
				    unsigned int indexstr);
int		objdump32(t_filemap* filemap, char* filename);

#endif /* OBJDUMP32_H */
