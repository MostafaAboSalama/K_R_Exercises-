#include <stdio.h>
#include <time.h>

#define SIZE    100000
#define REPEAT  10000000

/*
 * EX 3-1 (K&R - Binary Search Optimization Study)
 *
 * This program compares two implementations of binary search:
 *
 *   1) Original version (binsearchV1)
 *      - Uses two comparisons per loop iteration:
 *            x < v[mid]
 *            x > v[mid]
 *      - Returns immediately when the element is found.
 *
 *   2) Modified version (binsearchV2 - Exercise 3-1)
 *      - Uses only one comparison per loop iteration.
 *      - Does not return immediately when the element is found.
 *      - Instead, it finds the position where the element
 *        should be, then checks after the loop.
 *
 * Benchmark setup:
 *   - Array size: 100,000 sorted integers
 *   - Repetitions: 10,000,000 searches
 *   - Test value: fixed (present or absent depending on run)
 *   - Compiler: GCC (tested with -O0, -O2, -O3)
 *   - CPU: AMD Ryzen 7 5700G (Linux Mint)
 *
 * Observed results:
 *
 *   -O0:
 *       Original: slightly faster
 *       EX 3-1:   slightly slower
 *
 *   -O2:
 *       Original: slightly faster
 *       EX 3-1:   slightly slower
 *
 *   -O3 / -march=native:
 *       Both versions are nearly identical in performance
 *       (difference within measurement noise).
 *
 * Final conclusion:
 *
 * Although the modified version reduces the number of
 * comparisons inside the loop, this does not produce a
 * consistent performance improvement on modern systems.
 *
 * The reason is that modern compilers heavily optimize both
 * versions, and CPU branch prediction + memory behavior
 * dominate execution time more than comparison count.
 *
 * Therefore, theoretical operation counts alone are not
 * sufficient to predict real-world performance.
 */

int binsearchV1(int x, int v[], int n);
int binsearchV2(int x, int v[], int n);

int main(void)
{
    int v[SIZE];
    int i;
    volatile int result;
    clock_t start, end;

    /* Initialize sorted array */
    for (i = 0; i < SIZE; i++)
        v[i] = i;

    /* =========================
     * Benchmark Original Version
     * ========================= */
    start = clock();

    for (i = 0; i < REPEAT; i++)
        result = binsearchV1(54321, v, SIZE);

    end = clock();

    printf("Original: %.3f sec\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    /* =========================
     * Benchmark EX 3-1 Version
     * ========================= */
    start = clock();

    for (i = 0; i < REPEAT; i++)
        result = binsearchV2(54321, v, SIZE);

    end = clock();

    printf("EX 3-1: %.3f sec\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}

/*
 * Original K&R binary search.
 *
 * Uses up to two comparisons per loop iteration:
 *     x < v[mid]
 *     x > v[mid]
 *
 * Returns index of x if found, otherwise -1.
 */
int binsearchV1(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high) 
    {
        mid = (low + high) / 2;

        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

/*
 * Modified binary search (Exercise 3-1).
 *
 * Performs only one comparison inside the loop.
 * The loop finds the position where x should be located.
 * A final check determines whether x exists.
 */
int binsearchV2(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (x <= v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    /* Verify if x exists at the computed position */
    if (low < n && v[low] == x)
        return low;

    return -1;
}
