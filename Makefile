TARGET = bin/random-project
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC)) 

run: clean default
	./$(TARGET) -f ./mydatabase.db -n
	
default: $(TARGET)

clean: 
	rm -f obj/*.o
	rm -f bin/* 
# rm -f *.db

$(TARGET): $(OBJ)
	gcc -o $@ $?

obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinclude