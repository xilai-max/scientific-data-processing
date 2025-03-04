#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 计算均值
double calculate_mean(double data[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// 计算平方和
double calculate_sum_of_squares(double data[], int n, double mean) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (data[i] - mean) * (data[i] - mean);
    }
    return sum;
}

// 单因素ANOVA检验
void one_way_anova(double* groups[], int group_sizes[], int k, double alpha) {
    int total_n = 0;
    for (int i = 0; i < k; i++) {
        total_n += group_sizes[i];
    }

    // 计算总均值
    double total_sum = 0.0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < group_sizes[i]; j++) {
            total_sum += groups[i][j];
        }
    }
    double total_mean = total_sum / total_n;

    // 计算组间平方和 (SSB)
    double ssb = 0.0;
    for (int i = 0; i < k; i++) {
        double group_mean = calculate_mean(groups[i], group_sizes[i]);
        ssb += group_sizes[i] * (group_mean - total_mean) * (group_mean - total_mean);
    }

    // 计算组内平方和 (SSW)
    double ssw = 0.0;
    for (int i = 0; i < k; i++) {
        double group_mean = calculate_mean(groups[i], group_sizes[i]);
        ssw += calculate_sum_of_squares(groups[i], group_sizes[i], group_mean);
    }

    // 计算自由度
    int df_between = k - 1;      // 组间自由度
    int df_within = total_n - k; // 组内自由度

    // 计算均方
    double msb = ssb / df_between; // 组间均方
    double msw = ssw / df_within;  // 组内均方

    // 计算F统计量
    double f = msb / msw;

    // 输出结果
    printf("\nANOVA 结果:\n");
    printf("组间平方和 (SSB): %.4f\n", ssb);
    printf("组内平方和 (SSW): %.4f\n", ssw);
    printf("组间自由度 (df_between): %d\n", df_between);
    printf("组内自由度 (df_within): %d\n", df_within);
    printf("组间均方 (MSB): %.4f\n", msb);
    printf("组内均方 (MSW): %.4f\n", msw);
    printf("F统计量: %.4f\n", f);

    // 查F分布表（假设显著性水平为0.05）
    double f_critical;
    printf("请输入F分布的临界值（根据自由度和显著性水平查表）: ");
    scanf("%lf", &f_critical);

    // 判断是否拒绝原假设
    if (f > f_critical) {
        printf("拒绝原假设：至少有两组的均值有显著差异。\n");
    }
    else {
        printf("无法拒绝原假设：各组均值无显著差异。\n");
    }
}

int main() {
    int k; // 组数
    printf("请输入组数: ");
    scanf("%d", &k);

    // 动态分配内存存储每组数据
    double** groups = (double**)malloc(k * sizeof(double*));
    int* group_sizes = (int*)malloc(k * sizeof(int));

    // 输入每组数据
    for (int i = 0; i < k; i++) {
        printf("请输入第 %d 组的样本大小: ", i + 1);
        scanf("%d", &group_sizes[i]);

        groups[i] = (double*)malloc(group_sizes[i] * sizeof(double));
        printf("请输入第 %d 组的数据（用空格分隔）: ", i + 1);
        for (int j = 0; j < group_sizes[i]; j++) {
            scanf("%lf", &groups[i][j]);
        }
    }

    // 输入显著性水平
    double alpha;
    printf("请输入显著性水平（例如 0.05）: ");
    scanf("%lf", &alpha);

    // 进行单因素ANOVA检验
    one_way_anova(groups, group_sizes, k, alpha);

    // 释放内存
    for (int i = 0; i < k; i++) {
        free(groups[i]);
    }
    free(groups);
    free(group_sizes);
    system ("pause");
    return 0;
}