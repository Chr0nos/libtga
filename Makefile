# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/08/17 10:20:32 by snicolet          #+#    #+#              #
#*   Updated: 2018/05/04 18:51:59 by snicolet         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

EXTRA_FLAGS=-pipe -Ofast -g3
FLAGS=-Wall -Werror -Wextra -Wno-unused-result -Wno-reserved-id-macro
#CC=clang
ifeq ($(CC),clang)
	EXTRA_FLAGS+=-Weverything
else
	FLAGS += -Wno-strict-aliasing
endif
COMPILE=$(CC) $(FLAGS) -I. $(EXTRA_FLAGS)
RANLIB=ranlib
AR=ar
LIBSO=libtga.so
NAME=libtga.a
INC=-Iincludes -I../libft/include -I /usr/local/include/ -I$(HOME)/.brew/include

OBJ=tga.o tga_display.o tga_save.o tga_load_ogl.o
################################################################################
##                                                                            ##
##                   COMPILATION RULES : DONT TOUCH: IT'S MAGIC               ##
##                                                                            ##
################################################################################
OBJBUILDDIR=./build
ALLDIR=$(OBJBUILDDIR)/srcs

# all .obj listed with directories
ALLOBJ=$(OBJ:%.o=$(OBJBUILDDIR)/srcs/%.o)

# all .c files listes with directories
ALLSRC=$(OBJ:%.o=srcs/%.c)

all: $(NAME)

alldir: $(ALLDIR)

$(ALLDIR):
	mkdir -p $@

test:
	@echo $(ALLSRC)
	@echo $(ALLOBJ)

%.c:

$(NAME): $(ALLDIR) $(ALLOBJ)
	#@$(MAKE) $(ALLOBJ) | grep "$(COMPILE)"
	$(AR) rc $(NAME) $(ALLOBJ)
	$(RANLIB) $(NAME)

$(OBJBUILDDIR)/%.o: %.c
	$(COMPILE) -c $< -o $@ $(INC)

#windows dll cross compill rule
dll:
	make COMPILER="mingw32-gcc" AR="mingw32-ar" RANLIB="mingw32-ranlib" \
		NAME="libtga.dll"

#linker for libft.so
$(LIBSO): $(ALLDIR) $(ALLOBJ)
	$(COMPILE) -shared $(ALLOBJ) -o $(LIBSO)
so:
	make FLAGS="-fPIC $(FLAGS)" $(LIBSO)

#cleaners
mrproper: fclean
	find . -name ".*.swp" -print -delete
	find . -name "\#*\#" -print -delete

clean:
	rm -rf $(OBJBUILDDIR)

fclean: clean
	$(RM) $(NAME) $(LIBSO)

re: fclean
	$(MAKE)

# normal rule
#.PHONY: norminette so dll re all clean install

# 42file f***ing checker rule

.PHONY: re all clean fclean
