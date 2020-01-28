#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>

#define BUFFSIZE 64
#define MAXSIZE 100

static double vector_x[MAXSIZE] = {0};
static double vector_y[MAXSIZE] = {0};
static double vector_predict[MAXSIZE] = {0};

static double max_x;
static double max_y;
static double mean_x;
static double mean_y;
static double teta_0_intercept;
static double teta_1_grad;
static double RMSE;
static double r_square;
static double prediction;

static char intercept[BUFFSIZE];
static char grad[BUFFSIZE];
static char xrange[BUFFSIZE];
static char yrange[BUFFSIZE];
static char lossname_RMSE[BUFFSIZE] = "Simple Linear Regression using RMSE'";

static char cmd_gnu_0[BUFFSIZE] = "set title '";
static char cmd_gnu_1[BUFFSIZE] = "intercept = ";
static char cmd_gnu_2[BUFFSIZE] = "grad = ";
static char cmd_gnu_3[BUFFSIZE] = "set xrange [0:";
static char cmd_gnu_4[BUFFSIZE] = "set yrange [0:";
static char cmd_gnu_5[BUFFSIZE] = "f(x) = (grad * x) + intercept";
static char cmd_gnu_6[BUFFSIZE] = "plot f(x), 'data.temp' with points pointtype 7";

static char const *commands_gnuplot[] = {
    cmd_gnu_0,
    cmd_gnu_1,
    cmd_gnu_2,
    cmd_gnu_3,
    cmd_gnu_4,
    cmd_gnu_5,
    cmd_gnu_6,
};

static size_t size;

static void user_input()
{
    printf("Enter x,y vector size, MAX = 100\n");
    scanf("%lu", &size);
    if (size > MAXSIZE) {
        printf("Wrong input size is too big\n");
        user_input();
    }
    printf("vector's size is %lu\n", size);

    size_t i;
    for (i = 0; i < size; i++) {
        printf("Enter vector_x[%ld] values\n", i);
        scanf("%lf", &vector_x[i]);
    }

    for (i = 0; i < size; i++) {
        printf("Enter vector_y[%ld] values\n", i);
        scanf("%lf", &vector_y[i]);
    }
}

static void display_vector()
{
    size_t i;
    for (i = 0; i < size; i++){
        printf("vector_x[%lu] = %lf\t", i, vector_x[i]);
        printf("vector_y[%lu] = %lf\n", i, vector_y[i]);
    }
}

static void concatenate(char p[], char q[]) {
   int c;
   int d;
   c = 0;

   while (p[c] != '\0') {
      c++;
   }
   d = 0;

   while (q[d] != '\0') {
      p[c] = q[d];
      d++;
      c++;
   }
   p[c] = '\0';
}

static void compute_mean_x_y()
{
    size_t i;
    double tmp_x = 0.0;
    double tmp_y = 0.0;
    for (i = 0; i < size; i++) {
        tmp_x += vector_x[i];
        tmp_y += vector_y[i];
    }

    mean_x = tmp_x / size;
    mean_y = tmp_y / size;

    printf("mean_x = %lf\n", mean_x);
    printf("mean_y = %lf\n", mean_y);
}

static void compute_teta_1_grad()
{
    double numerator = 0.0;
    double denominator = 0.0;
    double tmp1 = 0.0;
    double tmp2 = 0.0;
    size_t i;

    for (i = 0; i < size; i++) {
        numerator += (vector_x[i] - mean_x) * (vector_y[i] - mean_y);
    }

    for (i = 0; i < size; i++) {
        tmp1 = vector_x[i] - mean_x;
        tmp2 = tmp1 * tmp1;
        denominator += tmp2;
    }

    teta_1_grad = numerator / denominator;
    printf("teta_1_grad = %lf\n", teta_1_grad);
}

static void compute_teta_0_intercept()
{
    teta_0_intercept = mean_y - (teta_1_grad * mean_x);
    printf("teta_0_intercept = %lf\n", teta_0_intercept);
}

static void compute_prediction()
{
    size_t i;
    for (i = 0; i < size; i++) {
        vector_predict[i] = teta_0_intercept + (teta_1_grad * vector_x[i]);
        printf("y^[%ld] = %lf\n", i, vector_predict[i]);
    }
    printf("\n");
}

static void compute_RMSE()
{
    compute_prediction();
    double error = 0;
    size_t i;
    for (i = 0; i < size; i++) {
        error = (vector_predict[i] - vector_y[i]) * (vector_predict[i] - vector_y[i]);
        printf("error y^[%ld] =  %lf\n", i, error);
        RMSE += error;
    }
    /* mean */
    RMSE = RMSE / size;
    /* square root mean */
    RMSE = sqrt(RMSE);
    printf("\nRMSE = %lf\n", RMSE);
}

static void compute_loss_function()
{
    int input = 0;
    printf("Which loss function do you want to use?\n");
    printf(" 1 - RMSE\n");
    scanf("%d", &input);
    switch(input) {
        case 1:
            concatenate(cmd_gnu_0, lossname_RMSE);
            compute_RMSE();
            printf("\n");
            break;
        default:
            printf("Wrong input try again\n");
            compute_loss_function(size);
    }
}

static void compute_r_square(size_t size)
{
    double num_err = 0.0;
    double den_err = 0.0;
    size_t i;

    for (i = 0; i < size; i++) {
        num_err += (vector_y[i] - vector_predict[i]) * (vector_y[i] - vector_predict[i]);
        den_err += (vector_y[i] - mean_y) * (vector_y[i] - mean_y);
    }
    r_square = 1 - (num_err/den_err);
    printf("R_square = %lf\n", r_square);
}

static void compute_predict_for_x()
{
    double x = 0.0;
    printf("Please enter x value\n");
    scanf("%lf", &x);
    prediction = teta_0_intercept + (teta_1_grad * x);
    printf("y^ if x = %lf -> %lf\n",x, prediction);
}

static void compute_max_x_y()
{
    size_t i;
    double tmp1= 0.0;
    double tmp2= 0.0;

    for (i = 0; i < size; i++) {
        if (vector_x[i] > tmp1) {
            tmp1 = vector_x[i];
            max_x = vector_x[i];

        }
        if (vector_y[i] > tmp2) {
            tmp2 = vector_y[i];
            max_y = vector_y[i];
        }
    }
    printf("vector_x max value %lf\n", max_x);
    printf("vector_y max value %lf\n", max_y);
}

static void display_model_line()
{
    sprintf(intercept, "%0.7lf", teta_0_intercept);
    sprintf(grad, "%0.7lf", teta_1_grad);
    sprintf(xrange, "%0.7lf", max_x + 1);
    sprintf(yrange, "%0.7lf", max_y + 1);

    concatenate(cmd_gnu_1, intercept);
    concatenate(cmd_gnu_2, grad);
    concatenate(cmd_gnu_3, xrange);
    concatenate(cmd_gnu_3, "]");
    concatenate(cmd_gnu_4, yrange);
    concatenate(cmd_gnu_4, "]");

    printf("grad = %s\n", grad);
    printf("intercept = %s\n", intercept);
    printf("xrange = %s\n", xrange);
    printf("yrange = %s\n", yrange);

    printf("cmd_gnu_0: %s\n", cmd_gnu_0);
    printf("cmd_gnu_1: %s\n", cmd_gnu_1);
    printf("cmd_gnu_2: %s\n", cmd_gnu_2);
    printf("cmd_gnu_3: %s\n", cmd_gnu_3);
    printf("cmd_gnu_4: %s\n", cmd_gnu_4);
    printf("cmd_gnu_5: %s\n", cmd_gnu_5);
    printf("cmd_gnu_6: %s\n", cmd_gnu_6);

    /* print plot */
    FILE *gnuplot_pipe = (FILE*)popen("gnuplot -persistent", "w");
    FILE *temp = (FILE*)fopen("data.temp", "w");

    /* create data.temp */
    size_t i;
    for (i = 0; i < size; i++)
    {
        fprintf(temp, "%f %f \n", vector_x[i], vector_y[i]);
    }

    /* display gnuplot */
    for (i = 0; i < 7; i++)
    {
        fprintf(gnuplot_pipe, "%s \n", commands_gnuplot[i]);
    }
}

int main(void)
{
    printf("===========================================\n");
    printf("INPUT DATA\n");
    printf("===========================================\n");
    user_input();
    display_vector();
    printf("\n");

    printf("===========================================\n");
    printf("COMPUTE MEAN X:Y, TETA_1 TETA_0\n");
    printf("===========================================\n");
    compute_mean_x_y();
    compute_max_x_y();
    compute_teta_1_grad();
    compute_teta_0_intercept();
    printf("\n");

    printf("===========================================\n");
    printf("COMPUTE LOSS FUNCTION\n");
    printf("===========================================\n");
    compute_loss_function();

    printf("===========================================\n");
    printf("COMPUTE R_square\n");
    printf("===========================================\n");
    compute_r_square(size);
    printf("\n");

    printf("===========================================\n");
    printf("COMPUTE y^ according to x\n");
    printf("===========================================\n");
    compute_predict_for_x();
    printf("\n");

    printf("===========================================\n");
    printf("DISPLAY LINEAR REGRESSION\n");
    printf("===========================================\n");
    display_model_line();
    printf("\n");

    return 0;
}
