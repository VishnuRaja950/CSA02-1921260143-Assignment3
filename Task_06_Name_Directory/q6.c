#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAMES 500
#define NAME_SIZE 30
 
int compare_names(const char a[], const char b[]) {
    int i = 0;
    while (a[i] && b[i]) {
        int x = tolower((unsigned char)a[i]);
        int y = tolower((unsigned char)b[i]);
        if (x != y) return x - y;
        ++i;
    }
    return (unsigned char)a[i] - (unsigned char)b[i];
}
void remove_newline(char s[]) {
    size_t n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') s[n - 1] = '\0';
}
void sort_names(char names[][NAME_SIZE], int n, long *calls,
                long *copies) {
    for (int i = 1; i < n; ++i) {
        char key[NAME_SIZE];
        strcpy(key, names[i]); *copies += (long)strlen(key) + 1;
        int j = i - 1;
        while (j >= 0) {
            ++(*calls);
            if (compare_names(names[j], key) <= 0) break;
            strcpy(names[j + 1], names[j]);
            *copies += (long)strlen(names[j]) + 1;
            --j;
        }
        strcpy(names[j + 1], key);
        *copies += (long)strlen(key) + 1;
    }
}
int binary_search(char names[][NAME_SIZE], int n, const char key[],
                  long *calls) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        ++(*calls);
        int c = compare_names(names[mid], key);
        if (c == 0) return mid;
        if (c < 0) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int main(void) {
    char names[MAX_NAMES][NAME_SIZE], key[NAME_SIZE];
    int n;
    long comparisons = 0, copies = 0, search_calls = 0;
    printf("Number of names (1-%d): ", MAX_NAMES);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_NAMES) {
        fprintf(stderr, "Invalid number of names.\n");
        return 1;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    for (int i = 0; i < n; ++i) {
        printf("Name %d: ", i + 1);
        if (!fgets(names[i], NAME_SIZE, stdin)) {
            fprintf(stderr, "Input error.\n"); return 1;
        }
        if (!strchr(names[i], '\n') && !feof(stdin)) {
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            fprintf(stderr, "Name too long (maximum 29 characters).\n");
            return 1;
        }
        remove_newline(names[i]);
    }
     sort_names(names, n, &comparisons, &copies);
    printf("\nSorted names:\n");
    for (int i = 0; i < n; ++i) {
        puts(names[i]);
        if (i > 0 && compare_names(names[i - 1], names[i]) == 0)
            printf("Duplicate: %s\n", names[i]);
    }
     printf("Search name: ");
    if (!fgets(key, sizeof key, stdin)) return 1;
    remove_newline(key);
    int pos = binary_search(names, n, key, &search_calls);
    if (pos >= 0) printf("Found at sorted index %d\n", pos);
    else puts("Name not found");
    printf("Sort strcmp-style comparisons: %ld\n", comparisons);
    printf("Characters copied (including terminators): %ld\n", copies);
    printf("Search comparisons: %ld\n", search_calls);
    return 0;
}
