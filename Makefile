# This file is part of Metagine.
# 
# Metagine is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Metagine is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Metagine.  If not, see <http://www.gnu.org/licenses/>.

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

