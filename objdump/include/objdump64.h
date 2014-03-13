/*
** objdump64.h for  in /home/otoshigami/rendu/PSU_2013_nmobjdump/objdump
**
** Made by
** Login   <otoshigami@epitech.net>
**
** Started on  Thu Mar 13 18:52:41 2014
** Last update Thu Mar 13 18:53:08 2014 
*/

#ifndef OBJDUMP64_H
# define OBJDUMP64_H

# include "filemap.h"

int		dump_section_content64(t_filemap* filemap, Elf64_Shdr* section,
				       char* section_name, Elf64_Ehdr* elf);
Elf64_Ehdr*	load_elf_header64(t_filemap* filemap);
Elf64_Phdr*	load_segment_header64(t_filemap* filemap,
				      Elf64_Ehdr* elf,
				      unsigned int nsegment);
Elf64_Shdr*	load_section_header64(t_filemap* filemap,
				      Elf64_Ehdr* elf,
				      unsigned int nsection);
char*		load_section_name64(t_filemap* filemap,
				    Elf64_Ehdr* elf,
				    unsigned int indexstr);
int		objdump64(t_filemap* filemap, char* filename);

#endif /* OBJDUMP64_H */
