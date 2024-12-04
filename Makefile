CC = clang

SRC_DIR = src
OBJ_DIR = obj
BUILD = build
APP = build/app

LINK_FLAGS =\
			-lm\

SOURCES = \
		  $(SRC_DIR)/main.c\
		  $(SRC_DIR)/utils.c\
		  $(SRC_DIR)/player.c\
		  $(SRC_DIR)/area.c\
		  $(SRC_DIR)/terminal.c\
		  $(SRC_DIR)/rendering.c\
		  $(SRC_DIR)/events.c\
		  $(SRC_DIR)/app.c\

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: dirs $(APP)

$(APP): $(OBJECTS)
	$(CC) -o $(APP) $(LINK_FLAGS) $(OBJECTS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $<

dirs:
	@mkdir -p build obj

clean:
	rm -rf build/* obj/*
