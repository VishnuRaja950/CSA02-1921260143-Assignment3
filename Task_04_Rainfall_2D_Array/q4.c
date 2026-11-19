#include <stdio.h>
#include <stdlib.h>

#define DISTRICTS 38
#define MONTHS 12

void read_rain(double rain[DISTRICTS][MONTHS])
{
    double monthly[MONTHS];
    int i, j;
    printf("Enter rainfall for 12 months:\n");
    for (j = 0; j < MONTHS; j++) {
        printf("Month %d: ", j + 1);
        if (scanf("%lf", &monthly[j]) != 1 || monthly[j] < 0) {
            printf("Invalid rainfall value!\n");
            exit(1);
        }
    }

    for (i = 0; i < DISTRICTS; i++) {
        for (j = 0; j < MONTHS; j++) {
            rain[i][j] = monthly[j];
        }
    }
}

void annual_totals(const double rain[DISTRICTS][MONTHS],
                   double totals[DISTRICTS])
{
    int i, j;
    for (i = 0; i < DISTRICTS; i++) {
        totals[i] = 0;
        for (j = 0; j < MONTHS; j++)
            totals[i] += rain[i][j];
    }
}
void monthly_averages(const double rain[DISTRICTS][MONTHS],
                      double averages[MONTHS])
{
    int i, j;
    for (j = 0; j < MONTHS; j++) {
        double sum = 0;
        for (i = 0; i < DISTRICTS; i++)
            sum += rain[i][j];
        averages[j] = sum / DISTRICTS;
    }
}

void wettest(const double rain[DISTRICTS][MONTHS],
             int *district, int *month, double *maximum)
{
    int i, j;
    *district = 0;
    *month = 0;
    *maximum = rain[0][0];
    for (i = 0; i < DISTRICTS; i++) {
        for (j = 0; j < MONTHS; j++) {
            if (rain[i][j] > *maximum) {
                *maximum = rain[i][j];
                *district = i;
                *month = j;
            }
        }
    }
}
void deficient(const double totals[DISTRICTS],
               double state_average)
{
    int i;
    for (i = 0; i < DISTRICTS; i++) {
        if (totals[i] < 0.60 * state_average)
            printf("District %d is below 60%% of state average\n",
                   i + 1);
    }
}
int main(void)
{
    double rain[DISTRICTS][MONTHS];
    double totals[DISTRICTS];
    double averages[MONTHS];
    double grand = 0, maximum;
    int wd, wm, i, j;
    read_rain(rain);
    annual_totals(rain, totals);
    monthly_averages(rain, averages);
    for (i = 0; i < DISTRICTS; i++)
        grand += totals[i];
    wettest(rain, &wd, &wm, &maximum);
    printf("\nState annual average per district: %.2f\n",
           grand / DISTRICTS);
    for (j = 0; j < MONTHS; j++)
        printf("Month %d average: %.2f\n",
               j + 1, averages[j]);
    printf("Wettest: district %d, month %d, %.2f mm\n",
           wd + 1, wm + 1, maximum);
    deficient(totals, grand / DISTRICTS);
    return 0;
}
