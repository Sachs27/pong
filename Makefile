# TODO:
#   [ ]给所有源文件加上文件注释。
#   [ ]完成开发后 CFLAGS 去掉 -g。
#   [ ]增加电脑 AI。

BIN_DIR	= bin
SRC_DIR	= src
INC_DIR	= include
OBJ_DIR	= obj
EXE		=  

TARGET	= $(BIN_DIR)/pong$(EXE)
SOURCES	= $(wildcard $(SRC_DIR)/*.c)
OBJECTS	= $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPENDS	= deps

CC	= gcc
CFLAGS	= -g
LIBS	= -lm -lSDL -lSDL_image -lSDL_mixer
INCLUDE	= -I$(INC_DIR)

all: $(TARGET)

run: $(TARGET)
	cd $(BIN_DIR) && ./$(TARGET:$(BIN_DIR)/%=%)
clean:
	-rm -f $(DEPENDS)
	-rm -f $(OBJECTS)

cleanall: clean
	-rm -f $(TARGET)

.PHONY: run all clean cleanall obj

$(TARGET): $(OBJECTS) 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

sinclude $(DEPENDS)

$(DEPENDS): $(SOURCES)
	@$(CC) -MM $^ >$@.$$$$; \
	sed 's,\([_a-zA-Z0-9]*\)\.o[ :]*,$(OBJ_DIR)/\1.o : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

obj: $(OBJECTS)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<
