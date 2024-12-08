# Укажите компилятор
CXX = g++
CXXFLAGS = -Wall -g

# Список исходных файлов
SRC = data_generator.cpp sequence.cpp tests.cpp main.cpp ui.cpp

# Список заголовочных файлов
HDR = array_sequence.h binary_insertion_sorter.h comparator.h data_generator.h data_structure.h insertion_sorter.h isorter.h sequence.h shaker_sorter.h smrt_ptr.h ui.h

# Имя итогового исполняемого файла
TARGET = program

# Правило по умолчанию
all: $(TARGET)

# Компиляция исполняемого файла
$(TARGET): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Очистка скомпилированных файлов
clean:
	del $(TARGET).exe