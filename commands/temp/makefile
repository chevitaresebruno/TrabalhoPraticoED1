# Variáveis de sistema operacional
ifeq ($(OS),Windows_NT)
    RM = del /Q
    MKDIRTEMP = if not exist temp mkdir temp
	MKDIRBIN = if not exist lib/bin mkdir lib/bin
    CC = cl
    CFLAGS = /c /W4 /Iinclude
    LDFLAGS = 
    EXE = programa.exe
    TEMP_DIR = temp
else
    RM = rm -f
    MKDIRTEMP = mkdir -p temp
	MKDIRBIN = mkdir -p lib/bin
    CC = gcc
    CFLAGS = -Wall -Iinclude
    LDFLAGS = 
    EXE = programa
    TEMP_DIR = temp
endif

# Diretórios
SRC_DIR = lib/scr
OBJ_DIR = lib/bin	
TEMP_DIR = temp

# Arquivos fonte e objeto
SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
MAIN_OBJ = $(OBJ_DIR)/main.o

# Regras
.PHONY: all lib truly_all clean temp_clean clean_exe

all: $(EXE)

$(EXE): $(MAIN_OBJ) $(OBJS)
	$(CC) $(LDFLAGS) -o $(EXE) $(MAIN_OBJ) $(OBJS)

lib: $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

truly_all: $(EXE)

clean:
	$(RM) $(OBJ_DIR)/*.o

temp_clean:
	$(RM) $(TEMP_DIR)/*

clean_exe:
	$(RM) $(EXE)

clean_temp_exe: clean_exe
	$(RM) $(TEMP_DIR)/*

# Regras específicas para Linux e Windows
ifeq ($(OS),Windows_NT)
    all: $(EXE)
    lib: $(OBJS)
    truly_all: $(EXE)
    clean: $(RM) $(OBJ_DIR)\*.o
    temp_clean: $(RM) $(TEMP_DIR)\*
    clean_exe: $(RM) $(EXE)
    clean_temp_exe: clean_exe temp_clean
else
    all: $(EXE)
    lib: $(OBJS)
    truly_all: $(EXE)
    clean: $(RM) $(OBJ_DIR)/*.o
    temp_clean: $(RM) $(TEMP_DIR)/*
    clean_exe: $(RM) $(EXE)
    clean_temp_exe: clean_exe temp_clean
endif
