# Nome do Executável
PROJ_NAME=ted

# Compilador
CC=gcc

# Flags de Compilação (conforme PDF)
CFLAGS=-g -std=c99 -fstack-protector-all -Wall

# Flags de Linkagem
LDFLAGS=
LIBS=-lm

# ---- Arquivos Fonte ----
SRCS := $(wildcard *.c)

# Cria lista de arquivos .o
OBJS := $(SRCS:.c=.o)

# ---- Regras de Build ----

all: $(PROJ_NAME)

ted: $(PROJ_NAME)

# Linka todos os .o
$(PROJ_NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROJ_NAME) $(OBJS) $(LIBS)
	@echo "Executável '$(PROJ_NAME)' criado com sucesso em src/"

# Regra genérica para compilar .c para .o
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Regra de Limpeza
clean:
	rm -f $(PROJ_NAME) *.o
	@echo "Limpeza concluída."

.PHONY: all ted clean