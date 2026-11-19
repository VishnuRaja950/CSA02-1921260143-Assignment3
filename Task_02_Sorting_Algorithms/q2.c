#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
    long long comparisons;
    long long moves;
} Stats;
 
void bubble_sort(int a[], int n, Stats *s) {
    s->comparisons = s->moves = 0;
    for (int end = n - 1; end > 0; --end) {
        int swapped = 0;
        for (int j = 0; j < end; ++j) {
            s->comparisons++;
            if (a[j] > a[j + 1]) {
                int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
                s->moves++; swapped = 1;
            }
        }
        if (!swapped) break;
    }
}
 
void selection_sort(int a[], int n, Stats *s) {
    s->comparisons = s->moves = 0;
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            s->comparisons++;
            if (a[j] < a[min]) min = j;
        }
        if (min != i) {
            int t = a[i]; a[i] = a[min]; a[min] = t;
            s->moves++;
        }
    }
}
 
void insertion_sort(int a[], int n, Stats *s) {
    s->comparisons = s->moves = 0;
    for (int i = 1; i < n; ++i) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            s->comparisons++;
            if (a[j] <= key) break;
            a[j + 1] = a[j]; s->moves++; --j;
        }
        a[j + 1] = key;
    }
}
 
int main(void) {
    int original[] = {42, 17, 33, 10, 28, 21};
    int a[6]; Stats s;
    memcpy(a, original, sizeof a);
    bubble_sort(a, 6, &s);
    printf("Bubble: "); for (int i=0;i<6;i++) printf("%d ",a[i]);
    printf("| comparisons=%lld swaps=%lld\n",s.comparisons,s.moves);
 
    memcpy(a, original, sizeof a);
    selection_sort(a, 6, &s);
    printf("Selection: "); for (int i=0;i<6;i++) printf("%d ",a[i]);
    printf("| comparisons=%lld swaps=%lld\n",s.comparisons,s.moves);
 
    memcpy(a, original, sizeof a);
    insertion_sort(a, 6, &s);
    printf("Insertion: "); for (int i=0;i<6;i++) printf("%d ",a[i]);
    printf("| comparisons=%lld shifts=%lld\n",s.comparisons,s.moves);
    return 0;
}
