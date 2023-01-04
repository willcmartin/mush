# A C Makefile Template
# Author: Jeremy Barenholtz
# -------------------------
# This is a fully functional but primarily an educational document, with far 
# too many explanatory comments. I hope you consolidate and modify this to 
# suit your particular project's needs.

# The names of the programs you want to compile. The convention is that you 
# have a <program>.c file containing the main() of the program. E.g., if 
# you have a program named myprogram and defined in file myprogram.c, 
# write "PROGS=myprogram"
PROGS=mush
# The names of any extra classes, etc. you want to compile for the programs 
# listed above. It expects that you have a <extra>.c file for each one 
# specified. E.g., if you have a module named mylist defined in a file named 
# "mylist.c", write "EXTRAS = mylist".
EXTRAS=lexer pprint builtin

# In order to make your program run `make <program>` or to make all programs, 
# run `make` or `make all` (the "all" target is set to depend on all programs).

# The following variables define the directory structure of your project. If 
# you wish to not have any of the specified directories, set the relevant 
# variable equal to "." rather than leave empty. So if you want a completely 
# flat structure, set SRC_DIR, BLD_DIR, and RES_DIR to ".", like "SRC_DIR=.".

# Directory for your source files. It will look for .cpp files directly in the 
# source directory
SRC_DIR=src
# Directory for your compiled output
BLD_DIR=build
# Directory for your resources (misc. files)
# RES_DIR=res
# All the directories
DIRS=$(sort $(SRC_DIR) $(BLD_DIR))

# The C compiler. This uses the output of the command `which gcc`, which 
# returns the path of the executable `gcc` in your environment.
CC=gcc

# These are the compiler warning options. I've included a large set of 
# standard warnings that I think are generally good to have on unless you have
# a specific justification for not using them for a given project.
# Not all of these are ideal for all projects, so you certainly should modify 
# them if need be.
#
# I also encourage you to look up the details of any of these warnings!

C_WARNINGS=# clear the warnings
C_WARNINGS+=-Wall -Wextra # enable a set of standard useful warnings
# C_WARNINGS+=-Werror # all warnings are errors
# warn aboutimplicit double promotion (e.g., use of 2.6 instead 2.6f)
# C_WARNINGS+=-Wdouble-promotion
# check security of format strings
# C_WARNINGS+=-Wformat=2 -Wformat-truncation -Wformat-overflow
# produce duplicate symbol warning for tentative definitions
# C_WARNINGS+=-fno-common
# C_WARNINGS+=-Wconversion # warn dangerous implicit conversions
# C_WARNINGS+=-Wfloat-equal # warn floating point equality check
# C_WARNINGS+=-Wundef # warn uninitialized identifier in #if directive
# warn if function declared without argument types
# C_WARNINGS+=-Wstrict-prototypes
# C_WARNINGS+=-Werror-implicit-function-declaration # the name says it all
# warn if global function is defined without prototype
# C_WARNINGS+=-Wmissing-prototypes
# C_WARNINGS+=-pedantic # warn if using forbidden extension for standard

# The -MMD flag tracks dependencies of user header files that are included, 
# and the -MF flag outputs a list of these dependencies in a file specified by
# the argument that follows. That file is given by $(@:.o=.d), which is can 
# be a little intimidating, but breaks down as follows: "@" is the name of the 
# make target, and ".o=.d" says replace ".o" with ".d" in that name, "@". So 
# if the target name is the object file "myprogram.o", then these dependencies 
# will be in the file "myprogram.d".
#
# TLDR; This allows changes to header files to cause the executable to 
# recompiled, even though the header files are not directly involved in the 
# make command.
C_DEPS=-MMD -MF $(@:.o=.d)

# Here you put any macros you want to define, prefixed with "-D", like 
# "-DENABLE_EASTER_EGGS"
# C_DEFINES=

# Here you put any paths to the parent folders of any includes you used, 
# prefixed with "-I", like "-I/path/to/library/include"
C_INCLUDES="-I/include"

# These are the final C compiler flags used. Here you should define your
# standard and optimization or debug options
CFLAGS=$(if $(DEBUG),-Og -g,-O3) # run make DEBUG=1 to use -Og -g flags
# CFLAGS+=-std=c99
# CFLAGS+=$(CXX_WARNINGS)
# CFLAGS+=$(CXX_DEPS)
# CFLAGS+=$(CXX_DEFINES)
# CFLAGS+=$(C_INCLUDES)

# Here you put any paths to libraries you want to link, prefixed with "-L", 
# like "-L/path/to/library/lib". There should be ".a", ".so", ".lib", or 
# ".dylib" files in this directory
# LDFLAGS=

# Here you put any libraries you want to link, prefixed with "-l", like
# "-lboost" or "-larmadillo". From the previous variable's comment, there 
# should be a file with the named "lib<name>.a", ".so", ".lib", or ".dylib"
# (and you would just write "-l<name>").
# LDLIBS=

# All your program source files (<program>.cpp in the source directory)
PROGS_SRC=$(patsubst %,$(SRC_DIR)/%.c,$(PROGS))
# Your program object files (<program>.o files in the build directory)
PROGS_OBJ=$(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(PROGS_SRC))
# Your program dependency files (<program>.d files in the build directory)
PROGS_DEP=$(PROGS_OBJ:.o=.d)

# Same but for your extra files, classes, etc. 
EXTRAS_SRC=$(patsubst %, $(SRC_DIR)/%.c, $(EXTRAS))
EXTRAS_OBJ=$(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o, $(EXTRAS_SRC))
EXTRAS_DEP=$(EXTRAS_OBJ:.o=.d)

# All the resource files, or nothing if no resource directory
# ifneq ($(RES_DIR),.)
# 	RES_FILES:=$(patsubst %,$(RES_DIR)/%,$(shell [ -d $(RES_DIR) ] && ls $(RES_DIR)))
# endif

# All the resource files in the build folder, or nothing if no resource files
# ifneq ($(RES_FILES),)
# 	BLD_RES_FILES:=$(patsubst $(RES_DIR)/%,$(BLD_DIR)/%,$(RES_FILES))
# endif

# By default make all the programs
all: $(PROGS)

# Target for building the programs. Depends on the directories being created, 
# the executables, and the resources being copied
$(PROGS): %: dirs $(BLD_DIR)/% # resources

# Target for building the executables. Depends on the extra object files,
# and the program's object files
$(addprefix $(BLD_DIR)/,$(PROGS)): %: $(EXTRAS_OBJ) %.o
	$(CC) $(EXTRAS_OBJ) $@.o -o $@ $(LDFLAGS)

# Target for compiling object files. Depends on the source cpp files.
$(PROGS_OBJ) $(EXTRAS_OBJ): $(BLD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target for copying all resource files to build directory
# resources: $(BLD_RES_FILES)

# Target for copying individual resources files to build directory.
# Depends on the files in the resource directory
# $(BLD_RES_FILES): $(BLD_DIR)/%: $(RES_DIR)/%
# 	cp -a $^ $@

# Target for creating all required directories
dirs: $(DIRS)

# Target to create each directory. Creates each directory if it doesn't exist
$(DIRS):
	mkdir -p $@

# Delete all files created during build. These are the executables, the object
# files, the dependency files, and the copied resource files.
clean:
	rm -rf $(PROGS) $(PROGS_OBJ) $(PROGS_DEP) $(EXTRAS_OBJ) $(EXTRAS_DEP) $(BLD_RES_FILES)

.PHONY: clean

-include $(PROGS_DEP) $(EXTRAS_DEP)