# slibc — Yet another C library
# Copyright © 2015  Mattias Andrée (maandree@member.fsf.org)
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.




# Flags required at compilation of a libc, specifying that unhosted C is used.
CCFLAGS_UNHOSTED = -nostdinc -ffreestanding

# Preprocessor flags defined by slibc that are required to build the slibc.
CCFLAGS_SLIBC_DEFS = -D_SLIBC_SOURCE=1 -D_GNU_SOURCE=1 -D_BSD_SOURCE=1 -D_SLIBC_SUPPRESS_WARNINGS=1 \
                     -D_POSIX_C_SOURCE=999999L -D_XOPEN_SOURCE=9999

# Flag that specifies which C dialect the library is written.
CCFLAGS_CSTD = -std=gnu99

# Flags that specify where the system header files (that would in this case
# be this library's header files) are located.
CCFLAGS_INCLUDES = -Iinclude

# Optimisation flags.
CCFLAGS_OPTIIMISE = -Og -g

# Warning flags.
CCFLAGS_WARNINGS = -Wall -Wextra -Wdouble-promotion -Wformat=2 -Winit-self -Wmissing-include-dirs \
                   -Wtrampolines -Wfloat-equal -Wshadow -Wmissing-prototypes -Wmissing-declarations \
                   -Wredundant-decls -Wnested-externs -Winline -Wno-variadic-macros -Wsign-conversion \
                   -Wswitch-default -Wconversion -Wsync-nand -Wunsafe-loop-optimizations -Wcast-align \
                   -Wstrict-overflow -Wdeclaration-after-statement -Wundef -Wbad-function-cast \
                   -Wcast-qual -Wwrite-strings -Wlogical-op -Waggregate-return -Wstrict-prototypes \
                   -Wold-style-definition -Wpacked -Wvector-operation-performance \
                   -Wunsuffixed-float-constants -Wsuggest-attribute=const -Wsuggest-attribute=noreturn \
                   -Wsuggest-attribute=pure -Wsuggest-attribute=format -Wnormalized=nfkc
# -pedantic is excluded.


# All flags used required when compiling the library.
CCFLAGS_COMMON = $(CCFLAGS_UNHOSTED) $(CCFLAGS_SLIBC_DEFS) $(CCFLAGS_CSTD) $(CCFLAGS_INCLUDES) \
                 $(CCFLAGS_OPTIIMISE) $(CCFLAGS_WARNINGS)
CCFLAGS_COMMON += $(CPPFLAGS) $(CFLAGS)
CCFLAGS_STATIC = $(CCFLAGS_COMMON)
CCFLAGS_SHARED = $(CCFLAGS_COMMON) -fPIC -DSHARED

# Flags required when genering header file dependency list.
MMFLAGS = $(CCFLAGS_COMMON) -MG


# Object files to build.
OBJECTS = $(shell find src | grep '\.c$$' | sed -e 's:^src/:obj/:' -e 's:\.c$$:\.o:')

# All header files.
HEADERS = $(shell find . | grep '\.h$$' | sed -e 's:^\./::')

# All code files.
SOURCES = $(shell find src | grep '\.c$$')



# You may add config.mk to the topmost directory
# to change any configurations above.
-include config.mk

# The default rule.
.PHONY: default
default: all

# Include list of file dependencies for object files.
include obj/deps.mk




# Build everything.
.PHONY: all
all: $(OBJECTS)


# Build object file.
obj/%.o:
	@mkdir -p $$(dirname $@)
	$(CC) -c -o $@ src/$*.c $(CCFLAGS_SHARED)





# Generate list of file dependencies for object files.
obj/deps.mk: Makefile $(HEADERS) $(SOURCES)
	@mkdir -p obj
	@find src | grep '\.c$$' | xargs $(CC) -MM $(MMFLAGS) > $@
	@sed -i 's#^[^ :]*\.o: src\([^ ]*\)/[^ /]*\.c#obj\1/&#' $@



# Clean generated files.
.PHONY: clean
clean:
	-rm -rf obj bin

# Remove all files that are not part of the source.
.PHONY: distclean
distclean: clean
	-rm -f config.mk

