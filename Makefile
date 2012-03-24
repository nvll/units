# Macros
MKDIR = mkdir -p $(dir $@)
GET_PARENT = $(dir $(lastword $(MAKEFILE_LIST)))

# Setup vars for build
CC = gcc 
OUTPUT := runtests
OBJDIR := build
CFLAGS =-O2 -W -Wall -Wno-unused-parameter
DEFINES = 
INCLUDE =-I.
ECHO = @ 

# Src files to build / link in
SRC := main.c
SRC += $(wildcard tests/*.c)

OBJS := $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

.PHONY: all

all: $(OUTPUT) 

$(OUTPUT): $(OBJS)
	@echo "linking $(OUTPUT)"
	$(ECHO) $(CC) $^ -o $(OUTPUT)

$(OBJDIR)/%.o: %.c
	@$(MKDIR)
	@echo "compiling $<"
	$(ECHO) $(CC) $(DEFINES) $(CFLAGS) $(INCLUDE) -c $< -MD -MP -MT $@ -MF $(@:%o=%d) -o $@

clean:
	rm -rf $(OBJDIR) $(OUTPUT)
