CFLAGS 		:= -O2 -Wall -Wextra -Wpedantic
CXXFLAGS 	:= $(CFLAGS)
LDFLAGS 	:= -lGL -lglfw -lGLEW
OBJ 		:= main.o shader.o
GLSL_H		:= vert.glsl.h frag.glsl.h
BIN 		:= break_agx


$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $(OBJ) $(LDFLAGS)

main.o: main.cpp $(GLSL_H)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o: %.cpp 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%.glsl.h: %.glsl
	tts $< > $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: $(BIN) clean
