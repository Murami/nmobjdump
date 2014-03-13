##
## Makefile in /home/guerot_a/depots/PSU_2013_myscript
## 
## Made by anthony guerot
## Login   <guerot_a@epitech.net>
## 
## Started on  Sun Mar  2 18:06:05 2014 anthony guerot
## Last update Thu Mar 13 18:52:11 2014 
##

## FILES

NAME		=	my_objdump

SRC		=	main			\
			endian			\
			fmapaccess		\
			map			\
			32-bit/objdump32	\
			32-bit/dump_section	\
			32-bit/load		\
			64-bit/objdump64	\
			64-bit/dump_section	\
			64-bit/load

SRC_EXT		=	.c

## DIRECTORIES

DOBJ		=	obj
DSRC		=	src
DBIN		=	bin

## COMPILATION

DINC		=	include			\
			template

CFLAGS		=	-Wall			\
			-Wextra			\
			`sdl-config --cflags`

## LINKAGE

LIB		=

DLIB		=

LDFLAGS		= `sdl-config --libs`

## RUNS

CC		=	gcc
RM		=	rm -rf
MD		=	mkdir -p

####################
## INTERNAL RULES ##
####################

## CONSTANTS

DBGBOOL		=	yes

DBG		=	-g3		\
			-ggdb

WERROR		=	-Werror

## FILES

OBJ		=	$(addsuffix .o, $(SRC))
_SRC		=	$(addsuffix $(SRC_EXT), $(SRC))

## DIRECTORIES

DINC		:=	$(addsuffix /, $(DINC))
DOBJ		:=	$(addsuffix /, $(DOBJ))
DSRC		:=	$(addsuffix /, $(DSRC))
DBIN		:=	$(addsuffix /, $(DBIN))

## COMPILATION ARGS

CINC		=	$(addprefix -I, $(DINC))

COBJ		=	$(addprefix $(DOBJ), $(OBJ))
CSRC		=	$(addprefix $(DSRC), $(_SRC))
CNAME		=	$(addprefix $(DBIN), $(NAME))

## LINKAGE ARGS

LIB		:=	$(addprefix -l, $(LIB))
DLIB		:=	$(addsuffix /, $(DLIB))
DLIB		:=	$(addprefix -L, $(DLIB))

## FLAGS

ifeq ($(DBGBOOL), yes)
	CFLAGS  += $(DBG)
endif

ifeq ($(DBGBOOL), no)
	CFLAGS	+= $(WERROR)
endif

CFLAGS		+=	$(CINC)
LDFLAGS		+=	$(LIBS)

## MISC RULES

SD_SRC		= $(shell cd $(DSRC) && find . -type d | uniq)
SD_TMP		= $(shell find . -name "*~")
MAKEOBJ		= $(addprefix $(DOBJ), %.o) : $(addprefix $(addprefix $(DSRC), %), $(SRC_EXT))

all:	$(CNAME)

dbg:	$(CNAME)

$(CNAME):	$(COBJ)
		@$(MD) $(DBIN)
		@echo "Linkage : $(CNAME)"
		@$(CC) $(COBJ) -o $(CNAME) $(LDFLAGS)

$(COBJ):	$(MAKEOBJ)
		@$(MD) $(DOBJ)
		@for dir in $(SD_SRC); \
		do \
		if [ ! -d "$(DOBJ)$$dir" ];then \
			$(MD) $(DOBJ)$$dir; \
		fi \
		done
		@echo "Compilation : $<"
		@$(CC) -c $< -o $@ $(CFLAGS)

cleantmp:
		@echo "Deleting tmp files"
		@for file in $(SD_TMP); \
		do \
		$(RM) $$file; \
		done

clean:		cleantmp
		@echo "Deleting obj files"
		@$(RM) $(COBJ)

fclean:		clean
		@echo "Deleting executable"
		@$(RM) $(CNAME)

re:		fclean all
redbg:		fclean dbg

.PHONY:		fclean clean all dbg re
