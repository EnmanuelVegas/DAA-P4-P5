	# Universidad de La Laguna
	# Escuela Superior de Ingeniería y Tecnología
	# Grado en Ingeniería Informática
	# Asignatura: Diseño y Análisis de Algoritmos (3º curso)
	# 
	# @file makefile: Fichero de compilación automática para proyectos.
	# @author Enmanuel Vegas (alu0101281698@ull.edu.es)
	# REFERENCIAS : https://www.softwaretestinghelp.com/cpp-makefile-tutorial/
	# https://makefiletutorial.com/
	# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
	# https://www.youtube.com/watch?v=Q9YugCnWWB4 -- Prelaunch task
	# 'make' ALIAS IN ~/.bashrc. make='make -C src/ --no-print-directory'
	# https://stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean		
	# tar -czvf nombre_comprimido.tgz carpeta_a_comprimir

CXX=g++
MAKEFLAGS=--no-print-directory
CXXFLAGS=-std=c++20 -g -O0
# CXXFLAGS = -std=c++20 -g -O0 -fsanitize=address

SRC=src
OBJ=build
SOURCES=$(shell find $(SRC) -name '*.cc')
OBJECTS=$(patsubst $(SRC)/%.cc, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE=vrpt_transport

.PHONY: clean clmake all

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@
# rm -rf *.out *~
#	rm -rf *.out *~ build/*


$(OBJ)/%.o : $(SRC)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/* *.out *~ $(EXECUTABLE)
	# clear
	@echo "directory cleaned up..."

clmake:
	make clean
	make
