##
## Makefile for  in /home/otoshigami/rendu/PSU_2013_nmobjdump
## 
## Made by 
## Login   <otoshigami@epitech.net>
## 
## Started on  Sun Mar 16 16:46:01 2014 
## Last update Sun Mar 16 16:48:10 2014 
##

all: my_nm my_objdump

my_nm:
	make -C nm

my_objdump:
	make -C objdump

clean:
	make clean -C objdump
	make clean -C nm

fclean:
	make fclean -C objdump
	make fclean -C nm

re:	fclean all

.PHONY:all my_nm my_objdump clean fclean re
