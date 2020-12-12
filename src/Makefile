SRC_DIRS:=. processor memory ppu
SRC_FILES:=$(foreach file,$(SRC_DIRS),$(wildcard $(file)/*.cpp))
OBJ_FILES:=$(patsubst %.cpp, %.o, $(SRC_FILES))

CPPFLAGS=-ggdb

CC=g++

NAME:=Machine

all: $(OBJ_FILES)
	$(CC) $(CPPFLAGS) -o $(NAME) $(OBJ_FILES)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f -v $(OBJ_FILES)
	@rm -f -v $(NAME)