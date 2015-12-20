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
                     -D_POSIX_C_SOURCE=999999L -D_XOPEN_SOURCE=9999 -D_PLAN9_SOURCE=1 -D__BUILDING_SLIBC=1
# __BUILDING_SLIBC is used to that make all prototypes visible, that are otherwise
# hidden because the library is compiled with a too old revision of C.

# Flag that specifies which C dialect the library is written.
CCFLAGS_CSTD = -std=gnu99

# Flags that specify where the system header files (that would in this case
# be this library's header files) are located.
CCFLAGS_INCLUDES = -Iinclude

# Optimisation flags.
CCFLAGS_OPTIMISE = -Og -g

# Warning flags.
CCFLAGS_WARNINGS = -Wall -Wextra -Wdouble-promotion -Wno-format -Winit-self -Wmissing-include-dirs \
                   -Wtrampolines -Wfloat-equal -Wshadow -Wmissing-prototypes -Wmissing-declarations \
                   -Wredundant-decls -Wnested-externs -Winline -Wno-variadic-macros -Wsign-conversion \
                   -Wswitch-default -Wconversion -Wsync-nand -Wunsafe-loop-optimizations -Wcast-align \
                   -Wstrict-overflow -Wdeclaration-after-statement -Wundef -Wbad-function-cast \
                   -Wcast-qual -Wwrite-strings -Wlogical-op -Waggregate-return -Wstrict-prototypes \
                   -Wold-style-definition -Wpacked -Wvector-operation-performance \
                   -Wunsuffixed-float-constants -Wsuggest-attribute=const -Wsuggest-attribute=noreturn \
                   -Wsuggest-attribute=pure -Wsuggest-attribute=format -Wnormalized=nfkc
# -pedantic is excluded.
# -Wno-format is temporarily substituted for -Wformat=1


# All flags used required when compiling the library.
CCFLAGS_COMMON = $(CCFLAGS_UNHOSTED) $(CCFLAGS_SLIBC_DEFS) $(CCFLAGS_CSTD) $(CCFLAGS_INCLUDES) \
                 $(CCFLAGS_OPTIMISE) $(CCFLAGS_WARNINGS)
CCFLAGS_COMMON += $(CPPFLAGS) $(CFLAGS)
CCFLAGS_STATIC = $(CCFLAGS_COMMON)
CCFLAGS_SHARED = $(CCFLAGS_COMMON) -fPIC -DSHARED

# Flags required when genering header file dependency list.
MMFLAGS = $(CCFLAGS_COMMON) -Igen -MG


# Flags to pass into the texinfo manual compilers, when processing with TeX.
TEXINFO_FLAGS =

# Flags to pass into the texinfo manual compilers, when not processing with TeX.
INFO_FLAGS =

# This shall be set to 'logo' when doc/logo.svg exists, and is the logo of the project.
LOGO =

# The  number of splits of the info manual.
INFOPARTS = 0

# Splits number of the info manual.
INFOPARTS_ = $(shell seq $(INFOPARTS))


SHE = '\#'

# Object files to build.
OBJECTS = $(shell find src | grep '\.c$$' | grep -v $(SHE) | sed -e 's:^src/:obj/:' -e 's:\.c$$:\.o:')

# All header files.
HEADERS = $(shell find . | grep '\.h$$' | grep -v $(SHE) | sed -e 's:^\./::')

# All code files.
SOURCES = $(shell find src | grep '\.c$$' | grep -v $(SHE))

# Generated headers files.
GENERATED = include/bits/intconf.h



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
all: $(OBJECTS) doc


# Build the library.
.PHONY: lib
lib: $(OBJECTS)

# Build object file.
obj/%.o: $(GENERATED)
	@mkdir -p $$(dirname $@)
	$(CC) -c -o $@ src/$*.c $(CCFLAGS_SHARED)

# Preprocess header files.
include/%.h: gen/%.h bin/gen/%
	@mkdir -p $$(dirname $@)
	gpp -s // < $< > $@

bin/gen/%: obj/gen/%.o
	@mkdir -p $$(dirname $@)
	$(CC) $(CCFLAGS_WARNINGS) -std=c99 -o $@ $^

obj/gen/%.o: gen/%.c
	@mkdir -p $$(dirname $@)
	$(CC) -c -o $@ $<

# Build the documentation.
.PHONY: doc
doc: info pdf ps dvi

.PHONY: info pdf ps dvi
info: bin/slibc.info
pdf: bin/slibc.pdf
ps: bin/slibc.ps
dvi: bin/slibc.dvi

# Project logo for the manual.
obj/%.svg: doc/%.svg
	@mkdir -p obj
	cp $< $@

obj/%.pdf: doc/%.svg
	@mkdir -p obj
	rsvg-convert --format=pdf $< > $@

obj/%.eps: obj/%.ps
	ps2eps $<

obj/%.ps: doc/%.svg
	@mkdir -p obj
	rsvg-convert --format=ps $< > $@

# Compile texinfo manual.
bin/%.info $(foreach P,$(INFOPARTS_),bin/%.info-$(P)): doc/info/%.texinfo doc/info/*.texinfo doc/info/*/*.texinfo
	@mkdir -p bin
	$(MAKEINFO) $(INFO_FLAGS) $<
	mv $*.info bin
ifneq ($(INFOPARTS),0)
	mv $*.info-* bin
endif

bin/%.pdf: doc/info/%.texinfo doc/info/*.texinfo doc/info/*/*.texinfo $(foreach F,$(LOGO),obj/$(F).pdf)
	@! test -d obj/pdf || rm -rf obj/pdf
	@mkdir -p obj/pdf bin
	cd obj/pdf && texi2pdf $(TEXINFO_FLAGS) ../../$< < /dev/null
	mv obj/pdf/$*.pdf $@

bin/%.dvi: doc/info/%.texinfo doc/info/*.texinfo doc/info/*/*.texinfo $(foreach F,$(LOGO),obj/$(F).eps)
	@! test -d obj/dvi || rm -rf obj/dvi
	@mkdir -p obj/dvi bin
	cd obj/dvi && $(TEXI2DVI) $(TEXINFO_FLAGS) ../../$< < /dev/null
	mv obj/dvi/$*.dvi $@

bin/%.ps: doc/info/%.texinfo doc/info/*.texinfo doc/info/*/*.texinfo $(foreach F,$(LOGO),obj/$(F).eps)
	@! test -d obj/ps || rm -rf obj/ps
	@mkdir -p obj/ps bin
	cd obj/ps && texi2pdf $(TEXINFO_FLAGS) --ps ../../$< < /dev/null
	mv obj/ps/$*.ps $@


# Generate list of file dependencies for object files.
obj/deps.mk: Makefile $(HEADERS) $(SOURCES) $(GENERATED)
	@mkdir -p obj
	find src | grep '\.c$$' | xargs $(CC) -MM $(MMFLAGS) > $@
	sed -i 's#^[^ :]*\.o: src\([^ ]*\)/[^ /]*\.c#obj\1/&#' $@
	sed -i 's# gen/\([^ ]*\.h\)# \1#g' $@



# Clean generated files.
.PHONY: clean
clean:
	-rm -rf obj bin
	-rm -f include/bits/intconf.h

# Remove all files that are not part of the source.
.PHONY: distclean
distclean: clean
	-rm -f config.mk

