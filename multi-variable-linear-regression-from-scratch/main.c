#include <stdio.h>
#define MAX_DATASETS 100
#define MAX_VARIABLES 100

double input[MAX_DATASETS][MAX_VARIABLES] = { { 0, }, };
double output[MAX_DATASETS] = { 0, };
int datasetCount = 0;
int variableCount = 0;

int getInput();
int getDataset();
int learningProcess(int learnCount, double learningRate);
double predict(double* testCase);

/* result = ax + by + cz + ... + so on... */
double currentMultipliers[MAX_VARIABLES+1] = {0,};

int main() {
    double learningRate = .001f;
    int learnCount = 1/learningRate;
    int i;
    double testCase[MAX_VARIABLES] = { 0, };

    printf("Multi-Variable Linear Regression Implementation on C\n");
    printf("by Alex4386\n");
    
    printf("how many datasets: ");
    scanf("%d", &datasetCount);

    if (datasetCount > MAX_DATASETS) {
        printf("too many datasets, please change the value in source");
        return 1;
    } else if (datasetCount < 0) {
        printf("invalid dataset amount");
        return 1;
    }

    printf("how many variables: ");
    scanf("%d", &variableCount);

    if (variableCount > MAX_VARIABLES) {
        printf("too many variables, please change the value in source");
        return 1;
    } else if (variableCount < 0) {
        printf("invalid variable amount");
        return 1;
    }

    getInput();

    printf("\n");
    printf("Learning Rate (ex.%3lf): ",learningRate);
    scanf("%lf", &learningRate);
    printf("Learn Iterations (ex.%d): ",(int)(1/learningRate)*10);
    scanf("%d", &learnCount);

    printf("\n");
    printf("Training Datasets:\n");
    getDataset();

    printf("\n");
    printf("Start Learning:\n");
    learningProcess(learnCount, learningRate);

    printf("\n");
    printf("Prediction:\n");
    for (i = 0; i < variableCount; i++) {
        printf("x_%d: ", i);
        scanf("%lf", &testCase[i]);
    }

    printf("Predicted Result: %lf\n", predict(testCase));
}

int getInput() {
    int i, j;

    printf("\n");
    printf("inputs: \n");
    for (i = 0; i < datasetCount; i++) {
        printf("index %d:\n", i);
        for (j = 0; j < variableCount; j++) {
            printf("variable #%d: ", j);
            scanf("%lf", &input[i][j]);
        }
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
    int i,j;
    for (i = 0; i < datasetCount; i++) {
        if (i != 0) printf(", ");
        printf("( ");
        printf("( ");
        for (j = 0; j < variableCount; j++) {
            if (j != 0) printf(", ");
            printf("%lf", input[i][j]);
        }
        printf(" )");
        printf(", %lf )", output[i]);
    }

    return 0;
}

double getLinearCalculation(double *variables, double *multipliers) {
    int i;
    double total = 0;
    /* calculate: ax+b */
    for (i = 0; i < variableCount; i++) {
        total += (variables[i] * multipliers[i]);
    }
    total += multipliers[variableCount];

    return total;
}

double getCurrentSquare(double *multipliers, int index) {
    double c = (output[index] - getLinearCalculation(input[index], multipliers));
    return c*c;
}

double getTotalSM(double *multipliers) {
    double total = 0;
    int i;
    for (i = 0; i < datasetCount; i++) {
        total += getCurrentSquare(multipliers, i);
    }

    return total / (double)datasetCount;
}

int learn(double learningRate) {
    double multiplier[MAX_VARIABLES+1] = {0,};
    int i,j;

    for (i = 0; i < datasetCount; i++) {
        /* derivative of a in (y - (a * input[i] + b))^2 / n */
        for (j = 0; j < variableCount; j++) {
            multiplier[j] += 1/(double)datasetCount * 2 * (output[i] - getLinearCalculation(input[i], currentMultipliers)) * -input[i][j];
        }
        multiplier[variableCount] += 1/(double)datasetCount * 2 * (output[i] - getLinearCalculation(input[i], currentMultipliers)) * -1;
    }

    // printf("Learn Result: %lf, %lf || %lf, %lf\n", a, b, (a * learningRate), (b * learningRate));
    for (i = 0; i <= variableCount; i++) {
        currentMultipliers[i] -= (multiplier[i] * learningRate);
    }

    return 0;
}

int logging(int currentTrial, int learnCount) {
    printf("Learning: %d/%d: ", currentTrial, learnCount);
    for (int i = 0; i < variableCount; i++)
    {
        printf("%lf * x_%d", currentMultipliers[i],i);
        printf("+");
    }
    printf("%lf, Error: %lf\n", currentMultipliers[variableCount], getTotalSM(currentMultipliers));

    return 0;
}

int learningProcess(int learnCount, double learningRate) {
    int i;
    double error = 1e+30;

    for (i = 0; i < learnCount; i++) {
        learn(learningRate);
        logging(i+1, learnCount);
        if (getTotalSM(currentMultipliers) > error) {
            printf("Configuration Error detected!!");
            return 1;
        }
        error = getTotalSM(currentMultipliers);
    }

    return 0;
}

double predict(double* testCase) {
    return getLinearCalculation(testCase, currentMultipliers);
}
