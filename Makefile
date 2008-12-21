PREFIX = /usr/local
CXX? = g++
OBJ = Engine/Main.o Engine/CEngine.o Engine/CVar.o Engine/CVarManager.o
OUT = metagine
CXXFLAGS += `pkg-config --cflags sdl`
LIBS = `pkg-config --libs sdl` -lpthread

all: $(OUT)

.cpp.o:
	@echo [CXX] $<
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	@echo [LD] $@
	@$(CXX) $(LDFLAGS) $(OBJ) $(LIBS) -o $(OUT)

clean:
	-rm -rf $(OBJ) $(OUT) *~

