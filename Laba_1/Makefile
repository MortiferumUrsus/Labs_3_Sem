# Определение компилятора и флагов
CXX = g++
CXXFLAGS = -Wall -g

# Цель по умолчанию
all: my_program

# Линковка исполняемого файла
my_program: main.o functional_tests.o load_tests.o stl_tests.o ui.o
	$(CXX) $(CXXFLAGS) -o my_program main.o functional_tests.o load_tests.o stl_tests.o ui.o

# Компиляция объектных файлов
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

functional_tests.o: functional_tests.cpp
	$(CXX) $(CXXFLAGS) -c functional_tests.cpp

load_tests.o: load_tests.cpp
	$(CXX) $(CXXFLAGS) -c load_tests.cpp

stl_tests.o: stl_tests.cpp
	$(CXX) $(CXXFLAGS) -c stl_tests.cpp

ui.o: ui.cpp
	$(CXX) $(CXXFLAGS) -c ui.cpp

# Очистка объектов и исполняемого файла
clean:
	del *.o my_program