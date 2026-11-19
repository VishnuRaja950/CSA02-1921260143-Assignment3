#include <stdio.h>
#include <stdlib.h>
#define MAX_CANDIDATES 12
#define MAX_VOTES 500000
 
int main(void) {
    int c, v;
    int count[MAX_CANDIDATES + 1] = {0};
    int order[MAX_CANDIDATES];
    int valid = 0, invalid = 0;
    printf("Number of candidates (1-%d): ", MAX_CANDIDATES);
    if (scanf("%d", &c) != 1 || c < 1 || c > MAX_CANDIDATES) {
        fprintf(stderr, "Invalid candidate count.\n");
        return 1;
    }
    printf("Number of votes (0-%d): ", MAX_VOTES);
    if (scanf("%d", &v) != 1 || v < 0 || v > MAX_VOTES) {
        fprintf(stderr, "Invalid vote count.\n");
        return 1;
    }
    for (int i = 0; i < v; ++i) {
        int vote;
        if (scanf("%d", &vote) != 1) {
            fprintf(stderr, "Invalid or missing vote input.\n");
            return 1;
        }
        if (vote >= 1 && vote <= c) {
            ++count[vote];
            ++valid;
        } else {
            ++invalid;
        }
    }
    for (int i = 0; i < c; ++i) order[i] = i + 1;
    /* Stable insertion sort of candidate IDs by vote count descending. */
    for (int i = 1; i < c; ++i) {
        int key = order[i], j = i - 1;
        while (j >= 0 && count[order[j]] < count[key]) {
            order[j + 1] = order[j];
            --j;
        }
        order[j + 1] = key;
    }
    printf("Valid votes: %d\nInvalid votes: %d\n", valid, invalid);
    printf("Candidate totals (descending):\n");
    for (int i = 0; i < c; ++i)
        printf("Candidate %d: %d\n", order[i], count[order[i]]);
    int top = count[order[0]], tied = 0;
    for (int i = 1; i < c; ++i)
        if (count[order[i]] == top) tied = 1;
     if (tied) puts("Result: Tie for winner");
    else printf("Winner: Candidate %d\n", order[0]);
    return 0;
}
Manual test with invalid votes and a tie
Input:
3
8
1 2 3 0 -1 4 1 2
