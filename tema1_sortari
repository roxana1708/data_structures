#include <iostream>
#include <list>
#include <cmath>
#include <chrono>
#include <cstdlib>

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int v[], int dim){

        int i, j;
        for (i = 0; i < dim; i++) {
            for (j = 0; j < dim - i - 1; j++) {
                if (v[j] > v[j + 1]) {
                    swap(&v[j], &v[j + 1]);
                }
            }
        }
}

void countSort(int v[], int dim, int max){

        int m = max;
        int fr[m], i;
        for(i = 0; i < max; i++){
            fr[i] = 0;
        }
        for(i = 0; i < dim; i++){
            fr[v[i]]++;
        }
        int j = 0;
        for(i = 0; i < max; i++){
            if(fr[i] > 0){
                while(fr[i] > 0){
                    v[j] = i;
                    j++;
                    fr[i]--;
                }
            }
        }
}


int nr_cifre(int a){

    int i=0;
    while(a > 0){
        a /= 10;
        i++;
    }
    return i;
}

void radixSort(int *v, int dim, int max){

    int i, j, m, n = 1, index, count = 0, temp;
    std::list<int> bucket[10];

    int steps = nr_cifre(max);
    for(i=0; i<steps; i++) {
        m = pow(10, i + 1);
        n = pow(10, i);
        for (j = 0; j < dim; j++) {
            temp = v[j] % m;
            index = temp/n;
            bucket[index].push_back(v[j]);
        }
        count = 0;
        for (j = 0; j < 10; j++) {
            while (!bucket[j].empty()) {
                v[count] = *(bucket[j].begin());
                bucket[j].erase(bucket[j].begin());
                count++;
            }
        }
    }

}

int* interclasare(int v[], int l, int m, int r){

    int i=0, j=0, h=0;
    int dim1 = m - l +1;
    int dim2 = r - m;

    int vl[dim1], vr[dim2];

    for (i = 0; i < dim1; i++)
        vl[i] = v[l + i];
    for (j = 0; j < dim2; j++)
        vr[j] = v[m + 1+ j];

    i = 0; j = 0; h = l;

    while(i < dim1 && j <dim2){
        if(vl[i] <= vr[j]){
            v[h] = vl[i];
            h++;
            i++;
        }else{
            v[h] = vr[j];
            h++;
            j++;
        }
    }

    if(i < dim1){
        while(i < dim1){
            v[h] = vl[i];
            h++;
            i++;
        }
    }

    if(j < dim2){
        while(j < dim2){
            v[h] = vr[j];
            h++;
            j++;
        }
    }

}

void mergeSort(int v[], int l, int r){

    if(l < r){
        int m = l+(r-l)/2;

        mergeSort(v, l, m);
        mergeSort(v, m+1, r);

        interclasare(v, l, m, r);
    }
}

int partition(int v[], int l, int r){

    int pivot = v[r];
    int i = l-1;

    for (int j = l; j < r; j++){
        if(v[j] <= pivot){
            i++;
            swap(&v[i], &v[j]);
        }
    }

    swap(&v[i+1], &v[r]);
    return i+1;
}

void quickSort(int v[], int st, int dr){

    if(st < dr){
        int ind_pivot = partition(v, st, dr);

        quickSort(v, st, ind_pivot - 1);
        quickSort(v, ind_pivot + 1, dr);
    }
}

int verif(int v[], int dim){

    for(int i = 0; i < dim-1; i++){
        if(v[i] > v[i+1]){
            return 0;
        }
    }
    return 1;
}


int main() {
    int n, max, i;

    std::cout << "n=";
    std::cin >> n;

    int vect[n];

    std::cout << "max=";
    std::cin >> max;

    for(i = 0; i < n; i++) {
        vect[i] = rand()%(max) + 1;
    }

    /*

    ///Bubble Sort
    if(n > 10000){
        std::cout << "Dimensiunea vectorului este prea mare pentru a efectua sortarea cu Bubble Sort";
        std::cout << std::endl;
    }else {
        auto t1 = std::chrono::high_resolution_clock::now();
        bubbleSort(vect, n);
        auto t2 = std::chrono::high_resolution_clock::now();

        auto duration_bubble = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Timp executie bubble sort: " << duration_bubble << " microseconds";
        std::cout << verif(vect, n);
        std::cout << std::endl;

    }


    ///Count Sort
    if(n > 1000000){
        std::cout<< "Dimensiunea vectorului este prea mare pentru a efectua sortarea cu Count Sort";
        std::cout << std::endl;
    }else {
        auto t3 = std::chrono::high_resolution_clock::now();
        countSort(vect, n, max);
        auto t4 = std::chrono::high_resolution_clock::now();

        auto duration_count = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
        std::cout << "Timp executie count sort: " << duration_count << " microseconds";
        std::cout << verif(vect, n);
        std::cout << std::endl;

    }


    ///Quick Sort
    auto t7 = std::chrono::high_resolution_clock::now();
    quickSort(vect, 0, n);
    auto t8 = std::chrono::high_resolution_clock::now();

    auto duration_quick = std::chrono::duration_cast<std::chrono::microseconds>(t8 - t7).count();
    std::cout << "Timp executie quick sort: " << duration_quick << " microseconds";
    std::cout << verif(vect, n);
    std::cout << std::endl;




    ///Merge Sort
    auto t9 = std::chrono::high_resolution_clock::now();
    mergeSort(vect, 0, n);
    auto t10 = std::chrono::high_resolution_clock::now();

    auto duration_merge = std::chrono::duration_cast<std::chrono::microseconds>(t10 - t9).count();
    std::cout << "Timp executie merge sort: " << duration_merge << " microseconds";
    std::cout << verif(vect, n);
    std::cout << std::endl;

    */

    ///Radix Sort
    auto t5 = std::chrono::high_resolution_clock::now();
    radixSort(vect, n, max);
    auto t6 = std::chrono::high_resolution_clock::now();

    auto duration_radix = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t5).count();
    std::cout << "Timp executie radix sort: " << duration_radix << " microseconds";
    std::cout << verif(vect, n);
    std::cout << std::endl;


    return 0;
}
