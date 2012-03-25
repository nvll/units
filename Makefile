# Macros
MKDIR = mkdir -p $(dir $@)
GET_PARENT = $(dir $(lastword $(MAKEFILE_LIST)))

# Setup vars for build
CC = gcc 
OUTPUT := runtests
OBJDIR := build
CFLAGS =-std=c99 -O2 -W -Wall -Wno-unused-function -Wno-unused-parameter
DEFINES = 
INCLUDE =-I.
ECHO = @ 
TESTDIR = tests

# Src files to build / link in
SRC := main.c
SRC += $(wildcard $(TESTDIR)/*.c)

OBJS := $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPS := $(OBJS:.o=.d)

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

-include $(DEPS)
