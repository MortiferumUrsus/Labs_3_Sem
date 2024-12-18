import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Загрузите данные из CSV
file_path = 'load_tests.csv'
if not os.path.isfile(file_path):
    print("The file does not exist.")
else:
    # Загрузка данных из CSV
    data = pd.read_csv(file_path)

# Группировка данных по алгоритму
algorithms = data['Algorithm'].unique()

# Построение графика для каждого алгоритма
for algorithm in algorithms:
    subset = data[data['Algorithm'] == algorithm]
    x = subset['Data Size']
    y = subset['Time (ms)']

    # Полиномиальная аппроксимация
    z = np.polyfit(x, y, 2)  # Степень полинома может быть изменена при необходимости
    p = np.poly1d(z)

    # Построение тренда
    plt.plot(x, p(x), '-', label=f'{algorithm} (trend)')

# Настройки графика
plt.xlabel('Data Size')
plt.ylabel('Time (ms)')
plt.title('Performance of Sorting Algorithms')
plt.legend()
plt.grid(True)
plt.show()