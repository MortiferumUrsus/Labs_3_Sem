CXX = g++
CXXFLAGS = -std=c++17 -Wall -mconsole

# Список объектных файлов
OBJECTS = main.o ui.o graph.o algorithms.o tests.o

# Правила для сборки всех целей
all: main

# Правила для сборки исполняемого файла main
main: main.o ui.o graph.o algorithms.o
	$(CXX) $(CXXFLAGS) -o main main.o ui.o graph.o algorithms.o

# Правила для компиляции объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Правила для очистки созданных файлов
clean:
	rm -f $(OBJECTS) main 