#include <stdio.h>
#define datasets 100

double input[datasets] = { 0, };
double output[datasets] = { 0, };
int datasetCount = 0;

int getInput();
int getDataset();
int learningProcess(int learnCount, double learningRate);

/* y = ax + b */
double currentA = 0;
double currentB = 0;

int main() {
    double learningRate = .1f;
    int learnCount = 0;

    printf("Linear Regression Implementation on C\n");
    printf("by Alex4386\n");
    
    while (datasetCount == 0) {
        printf("how many datasets: ");
        scanf("%d", &datasetCount);

        if (datasetCount > datasets) {
            printf("too many datasets, please change the value in source");
            return 0;
        }
    }

    getInput();

    printf("\n");
    printf("Learning Rate: ");
    scanf("%lf", &learningRate);
    printf("Learn Iterations: ");
    scanf("%d", &learnCount);

    printf("\n");
    printf("Training Datasets:\n");
    getDataset();

    printf("\n");
    printf("Start Learning:\n");
    learningProcess(learnCount, learningRate);

}

int getInput() {
    int i;

    printf("\n");
    printf("inputs: \n");
    for (i = 0; i < datasetCount; i++) {
        printf("index %d: ", i);
        scanf("%lf", &input[i]);
    }

    printf("\n");
    printf("outputs:\n");
    for (i = 0; i < datasetCount; i++) {
        printf("index %d: ", i);
        scanf("%lf", &output[i]);
    }
    printf("\n");

    return 0;
}

int getDataset() {
    int i;
    for (i = 0; i < datasetCount; i++) {
        if (i != 0) printf(", ");
        printf("( %lf, %lf )", input[i], output[i]);
    }

    return 0;
}

double getLinearCalculation(double x, double a, double b) {
    /* calculate: ax+b */
    return a*x + b;
}

double getCurrentSquare(double a, double b, int index) {
    double c = (output[index] - getLinearCalculation(input[index], a, b));
    return c*c;
}

double getTotalSM(double a, double b) {
    double total = 0;
    int i;
    for (i = 0; i < datasetCount; i++) {
        total += getCurrentSquare(a, b, i);
    }

    return total / (double)datasetCount;
}

int learn(double learningRate) {
    double a = 0;
    double b = 0;

    int i;

    for (i = 0; i < datasetCount; i++) {
        /* derivative of a in (y - (a * input[i] + b))^2 / n */
        a += 1/(double)datasetCount * 2 * (output[i] - (currentA * input[i] + currentB)) * -input[i];
        b += 1/(double)datasetCount * 2 * (output[i] - (currentA * input[i] + currentB)) * -1;
    }

    // printf("Learn Result: %lf, %lf || %lf, %lf\n", a, b, (a * learningRate), (b * learningRate));
    currentA -= (a * learningRate);
    currentB -= (b * learningRate);    

    return 0;
}

int learningProcess(int learnCount, double learningRate) {
    int i;

    for (i = 0; i < learnCount; i++) {
        learn(learningRate);
        printf("Learning: %d/%d: y = %lf x + %lf, Mean-Square Error: %lf\n", i+1, learnCount, currentA, currentB, getTotalSM(currentA, currentB));
    }

    return 0;
}
