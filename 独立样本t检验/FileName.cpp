#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 计算均值
double calculate_mean(double data[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// 计算方差
double calculate_variance(double data[], int n, double mean) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (data[i] - mean) * (data[i] - mean);
    }
    return sum / (n - 1);
}

// 计算t统计量（假设方差相等）
double calculate_t_statistic(double mean1, double mean2, double var1, double var2, int n1, int n2) {
    double pooled_variance = ((n1 - 1) * var1 + (n2 - 1) * var2) / (n1 + n2 - 2);
    double t = (mean1 - mean2) / sqrt(pooled_variance * (1.0 / n1 + 1.0 / n2));
    return t;
}

// 获取t分布的临界值（简单实现，实际应用中应使用统计库）
double get_t_critical_value(int df, double alpha) {
    // 示例临界值表（双尾检验，alpha=0.05）
    double t_table[] = {
        12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365, 2.306, 2.262, 2.228
    };
    if (df >= 1 && df <= 10) {
        return t_table[df - 1];
    }
    else {
        return -1; // 超出范围
    }
}
int main() {
    int n1, n2;

    // 获取第一个样本的大小和数据
    printf("第一组数据有几个数?: ");
    scanf("%d", &n1);
    double* sample1 = (double*)malloc(n1 * sizeof(double));
    printf("请输入第一个样本的数据（用空格分隔）: ");
    for (int i = 0; i < n1; i++) {
        scanf("%lf", &sample1[i]);
    }

    // 获取第二个样本的大小和数据
    printf("第二组数据有几个数: ");
    scanf("%d", &n2);
    double* sample2 = (double*)malloc(n2 * sizeof(double));
    printf("请输入第二个样本的数据（用空格分隔）: ");
    for (int i = 0; i < n2; i++) {
        scanf("%lf", &sample2[i]);
    }

    // 计算均值和方差
    double mean1 = calculate_mean(sample1, n1);
    double mean2 = calculate_mean(sample2, n2);
    double var1 = calculate_variance(sample1, n1, mean1);
    double var2 = calculate_variance(sample2, n2, mean2);

    // 计算t统计量
    double t = calculate_t_statistic(mean1, mean2, var1, var2, n1, n2);

    // 获取自由度和显著性水平
    int df = n1 + n2 - 2;
    double alpha;
    printf("请输入显著性水平（例如 0.05）: ");
    scanf("%lf", &alpha);

    // 获取t分布的临界值
    double t_critical = get_t_critical_value(df, alpha);
    if (t_critical == -1) {
        printf("自由度超出范围，无法获取临界值。\n");
        free(sample1);
        free(sample2);
        return 1;
    }

    // 输出结果
    printf("\n样本1均值: %.4f\n", mean1);
    printf("样本2均值: %.4f\n", mean2);
    printf("样本1方差: %.4f\n", var1);
    printf("样本2方差: %.4f\n", var2);
    printf("t统计量: %.4f\n", t);
    printf("自由度: %d\n", df);
    printf("t分布临界值: %.4f\n", t_critical);

    // 判断是否拒绝原假设
    if (fabs(t) > t_critical) {
        printf("拒绝原假设：两个样本的均值有显著差异。\n");
    }
    else {
        printf("无法拒绝原假设：两个样本的均值无显著差异。\n");
    }

    // 释放内存
    free(sample1);
    free(sample2);
    system("pause");
    return 0;
}