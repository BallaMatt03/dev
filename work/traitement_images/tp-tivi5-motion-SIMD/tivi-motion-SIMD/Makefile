# ------------------------- #
# -- SigmaDelta Makefile -- #
# ------------------------- #

# Copyright (c) 2000-2013 Lionel Lacassagne


# -- Lile list ----------
FILE = main.c morphoNR.c morphoNR_SSE.c motionNR.c motionNR_SSE.c mutil.c nrutil.c vnrutil.c sequence.c parser.c test_motionNR.c test_motionNR_SSE.c

# -- Paths ----------
SRC_PATH = src
OBJ_PATH = obj
EXE_PATH = exe
INC_PATH = include

#LIB_LIB_PATH = -L../NRC/lib -L../vNRC/lib -L../mySynchro/lib
#LIB_INC_PATH = -I../NRC/include -I../vNRC/include -I../mySynchro/include
# -- OS ----------
OS = LINUX

# -- Config ----------
# if CONFIG = CLI  (Command Line Interface, no Apple Framework)
CONFIG = CLI

# -- Macros ----------
CC = gcc
AR = ar -rc

# -- Flags ----------
C_DEBUG_FLAGS = -O0
C_CC_FLAGS = -std=c99 -DNOALIAS -DALIGNED
C_CC_FLAGS = -std=c99 -DNOALIAS -DALIGNED
C_OPTIMISATION_FLAGS = -O3 -fstrict-aliasing
C_ARCH_FLAGS =  
C_OS_FLAGS = -D$(OS)
C_CONFIG_FLAGS = -openmp -D$(CONFIG) 
C_INC_FLAGS = -I$(INC_PATH)

CFLAGS = $(C_DEBUG_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS)
CFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS)
LDFLAGS = $(C_CC_FLAGS) $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS)$(C_INC_FLAGS) $(LIB_LIB_PATH)

# -- Final product ----------
PRODUCT   = mvt.exe

# -- src and obj List ----------
SRC = $(addprefix ${SRC_PATH}/, $(FILE))
OBJ = $(addprefix ${OBJ_PATH}/, $(addsuffix .o, $(basename $(FILE))))

# -- Base rules ----------
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
   
#-----Main rule ----------
$(EXE_PATH)/$(PRODUCT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(OPTFLAGS) $(CFG)   -lm

# -- Other stuff ----------
depend:
	makedepend $(CFLAGS) -Y $(SRC)

clean:
	rm -f $(OBJ)
	rm -f ${LIB_PATH}/${PRODUCT}

tar:
	tar -cvf sigmadelta_SEE.tar Makefile src include
	gzip -9 sigmadelta_SEE.tar