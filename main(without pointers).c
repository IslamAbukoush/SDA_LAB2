#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b);
void print_arr(int arr[], int n);
void even_odd_swap(int arr[], int len);
void odd_sort(int arr[], int len, int asc);
void quicksort(int array[], int length, int asc);
void quicksort_recursion(int array[], int low, int high, int asc);
int partition(int array[], int low, int high, int asc);
int shellSort(int arr[], int n, int asc);
void merge(int arr[], int asc, int l, int m, int r);
void merge_sort_recursive(int arr[], int asc, int l, int r);
void merge_sort(int arr[], int n, int asc);
void counting_sort(int arr[], int n, int asc);

int main() {
    int len;
    printf("Enter the length of the array: ");
    scanf("%i", &len);

    int input[len];

    printf("Enter the array element by element: ");
    for (int i = 0; i < len; i++) {
        scanf("%i", &input[i]);
    }

    printf("\nYour array: ");
    print_arr(input, len);

    int swap;
    int alg;
    int asc;
    printf("Apply the swapping algorithm?\n");
    printf("0- No.\n");
    printf("1- Yes.\n");
    scanf("%i", &swap);
    if (swap) even_odd_swap(input, len);

    printf("Choose the sorting algorithm: \n");
    printf("1- Quick Sort.\n");
    printf("2- Shell Sort.\n");
    printf("3- Merge Sort.\n");
    printf("4- Counting Sort.\n");
    printf("5- Odd Sort.\n");
    printf("6- Exit.\n");
    printf("Choice: ");
    scanf("%i", &alg);

    printf("Choose the order: \n");
    printf("0- Descending.\n");
    printf("1- Ascending.\n");
    printf("Choice: ");
    scanf("%i", &asc);

    if (alg == 1) {
        quicksort(input, len, asc);
    } else if (alg == 2) {
        shellSort(input, len, asc);
    } else if (alg == 3) {
        merge_sort(input, len, asc);
    } else if (alg == 4) {
        counting_sort(input, len, asc);
    } else if (alg == 5) {
        odd_sort(input, len, asc);
    } else {
        exit(0);
    }

    printf("Sorted array: ");
    print_arr(input, len);

    return 0;
}

void swap(int* a, int* b) {
    const int t = *a;
    *a = *b;
    *b = t;
}

void print_arr(int arr[], int n) {
    if (n < 1) return;
    printf("{");
    for (int i = 0; i < n - 1; i++) {
        printf("%i, ", arr[i]);
    }
    printf("%i}\n", arr[n - 1]);
}

void even_odd_swap(int arr[], int len) {
    for (int i = 2; i < len; i += 3) {
        swap(&arr[i], &arr[i - 2]);
        if (++i < len) swap(&arr[i], &arr[i - 2]);
    }
}

void odd_sort(int arr[], int len, int asc) {
    for (int i = 1; i < len - 1; i += 2) {
        for (int j = i + 2; j < len; j += 2) {
            if ((asc && arr[i] > arr[j]) || (!asc && arr[i] < arr[j])) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

void quicksort(int array[], int length, int asc) {
    srand(time(NULL));
    quicksort_recursion(array, 0, length - 1, asc);
}

void quicksort_recursion(int array[], int low, int high, int asc) {
    if (low < high) {
        int pivot_index = partition(array, low, high, asc);
        quicksort_recursion(array, low, pivot_index - 1, asc);
        quicksort_recursion(array, pivot_index + 1, high, asc);
    }
}

int partition(int array[], int low, int high, int asc) {
    int pivot_index = low + (rand() % (high - low));
    if (pivot_index != high)
        swap(&array[pivot_index], &array[high]);
    int pivot_value = array[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if ((array[j] <= pivot_value && asc) || (array[j] >= pivot_value && !asc)) {
            swap(&array[i], &array[j]);
            i++;
        }
    }
    swap(&array[i], &array[high]);
    return i;
}

int shellSort(int arr[], int n, int asc) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && ((arr[j - gap] > temp && asc) || (arr[j - gap] < temp && !asc)); j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
    return 0;
}

void merge(int arr[], int asc, int l, int m, int r) {
    int len_l = m - l + 1;
    int len_r = r - m;
    int arr_l[len_l];
    int arr_r[len_r];
    for (int i = 0; i < len_l; i++)
        arr_l[i] = arr[i + l];
    for (int i = 0; i < len_r; i++)
        arr_r[i] = arr[i + m + 1];
    int i, j, k;
    for (i = 0, j = 0, k = l; k <= r; k++) {
        if ((i < len_l) && ((arr_l[i] <= arr_r[j] && asc) || (arr_l[i] >= arr_r[j] && !asc) || j >= len_r)) {
            arr[k] = arr_l[i++];
        } else {
            arr[k] = arr_r[j++];
        }
    }
}

void merge_sort_recursive(int arr[], int asc, int l, int r) {
    if (l >= r)
        return;
    int m = (l + r) / 2;
    merge_sort_recursive(arr, asc, l, m);
    merge_sort_recursive(arr, asc, m + 1, r);
    merge(arr, asc, l, m, r);
}

void merge_sort(int arr[], int

 n, int asc) {
    merge_sort_recursive(arr, asc, 0, n - 1);
}

void counting_sort(int arr[], int n, int asc) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    int index[max + 1];
    int result[n];
    for (int i = 0; i < max + 1; i++)
        index[i] = 0;
    for (int i = 0; i < n; i++)
        index[arr[i]]++;
    if (asc) {
        for (int i = 1; i < max + 1; i++)
            index[i] += index[i - 1];
    } else {
        for (int i = max - 1; i >= 0; i--)
            index[i] += index[i + 1];
    }
    for (int i = 0; i < n; i++)
        result[--index[arr[i]]] = arr[i];
    for (int i = 0; i < n; i++)
        arr[i] = result[i];
}