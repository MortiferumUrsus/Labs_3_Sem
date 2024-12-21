# Укажите компилятор
CXX = g++
CXXFLAGS = -Wall -g -I. -Isorters -Isequence


# Список исходных файлов
SRC = data_generator.cpp sequence.cpp sort_tests.cpp main.cpp ui.cpp comparator.cpp

# Список заголовочных файлов
HDR = array_sequence.h sorters/binary_insertion_sorter.h comparator.h data_generator.h data_structure.h \
      sorters/insertion_sorter.h isorter.h sequence.h sorters/shaker_sorter.h smrt_ptr.h ui.h \
      sorters/batcher_sorter.h sorters/bubble_sorter.h sorters/heap_sorter.h \
      sorters/merge_sorter.h sorters/quadratic_selection_sorter.h sorters/quick_sorter.h \
      sorters/selection_sorter.h sorters/shell_sorter.h sorters/tree_selection_sorter.h \
	  sort_tests.h

# Имя итогового исполняемого файла
TARGET = program

# Папка с текстовыми файлами
DATA_DIR = data_files

# Текстовые файлы
DATA_FILES = $(DATA_DIR)/first_names.txt $(DATA_DIR)/last_names.txt $(DATA_DIR)/middle_names.txt \
             $(DATA_DIR)/address.txt $(DATA_DIR)/occupations.txt

# Рабочие файлы
GENERATED_FILES = generated_data.csv

# Правило по умолчанию
all: $(TARGET)

# Компиляция исполняемого файла
$(TARGET): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Копирование текстовых файлов в выходной каталог
copy_files:
	mkdir -p output
	cp $(DATA_FILES) ./output/

# Очистка скомпилированных файлов и рабочих файлов
clean:
	rm -f $(TARGET)
	rm -f $(GENERATED_FILES)
	rm -rf ./output

# Упрощённое правило для тестирования с копированием данных
test: all copy_files
	./$(TARGET)