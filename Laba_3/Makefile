# Названия файлов
SRC = main.cpp \
      array_sequence.h \
      idictionary.h \
      permissions_manager.h \
      virtual_file.h \
      virtual_directory.h \
      index_manager.h \
      virtual_files_system.h

# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Исполняемый файл
TARGET = my_project

# Основное правило сборки
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Правило очистки
clean:
	rm -f $(TARGET)

.PHONY: all clean