#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

std::vector<int> generateRandomNumbers(int size, int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    std::vector<int> numbers;
    numbers.reserve(size);
    for (int i = 0; i < size; ++i) {
        numbers.push_back(dis(gen));
    }
    return numbers;
}

void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int quickPartition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = quickPartition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void mergeArrays(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        mergeArrays(arr, l, m, r);
    }
}

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(arr[minIndex], arr[i]);
    }
}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template<typename F, typename... Args>
double measureTime(F function, std::vector<int>& data, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    function(data, std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    int size;
    std::cout << "Podaj rozmiar tablicy do posortowania: ";
    std::cin >> size;

    const int min = 1;
    const int max = 100;

    std::vector<int> data = generateRandomNumbers(size, min, max);

    std::cout << "Tablica przed sortowaniem: ";
    printArray(data);

    double time;

    std::vector<int> bubbleSorted = data;
    time = measureTime(bubbleSort, bubbleSorted);
    std::cout << "Sortowanie babelkowe: ";
    printArray(bubbleSorted);
    std::cout << std::fixed << std::setprecision(6) << "Czas sortowania: " << time << " sekund (" << time * 1000 << " milisekund)" << std::endl;

    std::vector<int> quickSorted = data;
    time = measureTime(quickSort, quickSorted, 0, quickSorted.size() - 1);
    std::cout << "Sortowanie szybkie: ";
    printArray(quickSorted);
    std::cout << std::fixed << std::setprecision(6) << "Czas sortowania: " << time << " sekund (" << time * 1000 << " milisekund)" << std::endl;

    std::vector<int> mergeSorted = data;
    time = measureTime(mergeSort, mergeSorted, 0, mergeSorted.size() - 1);
    std::cout << "Sortowanie przez scalanie: ";
    printArray(mergeSorted);
    std::cout << std::fixed << std::setprecision(6) << "Czas sortowania: " << time << " sekund (" << time * 1000 << " milisekund)" << std::endl;

    std::vector<int> selectionSorted = data;
    time = measureTime(selectionSort, selectionSorted);
    std::cout << "Sortowanie przez wybieranie: ";
    printArray(selectionSorted);
    std::cout << std::fixed << std::setprecision(6) << "Czas sortowania: " << time << " sekund (" << time * 1000 << " milisekund)" << std::endl;

    std::vector<int> insertionSorted = data;
    time = measureTime(insertionSort, insertionSorted);
    std::cout << "Sortowanie przez wstawianie: ";
    printArray(insertionSorted);
    std::cout << std::fixed << std::setprecision(6) << "Czas sortowania: " << time << " sekund (" << time * 1000 << " milisekund)" << std::endl;

    return 0;
}
