PROGS=mush
EXTRAS=lexer pprint builtin exec

SRC_DIR=src
BLD_DIR=build
DIRS=$(sort $(SRC_DIR) $(BLD_DIR))

CC=gcc

C_WARNINGS=# clear the warnings
C_WARNINGS+=-Wall -Wextra # enable a set of standard useful warnings

C_DEPS=-MMD -MF $(@:.o=.d)

C_INCLUDES="-I/include"

CFLAGS=$(if $(DEBUG),-Og -g,-O3) # run make DEBUG=1 to use -Og -g flags



PROGS_SRC=$(patsubst %,$(SRC_DIR)/%.c,$(PROGS))
PROGS_OBJ=$(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(PROGS_SRC))
PROGS_DEP=$(PROGS_OBJ:.o=.d)

# Same but for your extra files, classes, etc. 
EXTRAS_SRC=$(patsubst %, $(SRC_DIR)/%.c, $(EXTRAS))
EXTRAS_OBJ=$(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o, $(EXTRAS_SRC))
EXTRAS_DEP=$(EXTRAS_OBJ:.o=.d)

all: $(PROGS)

$(PROGS): %: dirs $(BLD_DIR)/% # resources
$(addprefix $(BLD_DIR)/,$(PROGS)): %: $(EXTRAS_OBJ) %.o
	$(CC) $(EXTRAS_OBJ) $@.o -o $@ $(LDFLAGS)
$(PROGS_OBJ) $(EXTRAS_OBJ): $(BLD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

dirs: $(DIRS)

$(DIRS):
	mkdir -p $@

clean:
	rm -rf $(PROGS) $(PROGS_OBJ) $(PROGS_DEP) $(EXTRAS_OBJ) $(EXTRAS_DEP) $(BLD_RES_FILES)

.PHONY: clean

-include $(PROGS_DEP) $(EXTRAS_DEP)