#include <stdio.h>
#include <omp.h>
 
#define N 100
 
int main(int argc, char *argv[])
{
    float a[N], b[N], c[N];
    int i;
    omp_set_dynamic(0);      // запретить менять число потоков с помощью переменной окружения
    omp_set_num_threads(10); // установить число потоков в 10

    for (i = 0; i < N; i++)
    {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }

    // вычисляем сумму векторов
    #pragma omp parallel shared(a, b, c) private(i)
    {
    #pragma omp for
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
    }

    printf ("%f\n", c[10]);

    return 0;
}

