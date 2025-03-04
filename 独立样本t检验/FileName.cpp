#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// �����ֵ
double calculate_mean(double data[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// ���㷽��
double calculate_variance(double data[], int n, double mean) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (data[i] - mean) * (data[i] - mean);
    }
    return sum / (n - 1);
}

// ����tͳ���������跽����ȣ�
double calculate_t_statistic(double mean1, double mean2, double var1, double var2, int n1, int n2) {
    double pooled_variance = ((n1 - 1) * var1 + (n2 - 1) * var2) / (n1 + n2 - 2);
    double t = (mean1 - mean2) / sqrt(pooled_variance * (1.0 / n1 + 1.0 / n2));
    return t;
}

// ��ȡt�ֲ����ٽ�ֵ����ʵ�֣�ʵ��Ӧ����Ӧʹ��ͳ�ƿ⣩
double get_t_critical_value(int df, double alpha) {
    // ʾ���ٽ�ֵ��˫β���飬alpha=0.05��
    double t_table[] = {
        12.706, 4.303, 3.182, 2.776, 2.571, 2.447, 2.365, 2.306, 2.262, 2.228
    };
    if (df >= 1 && df <= 10) {
        return t_table[df - 1];
    }
    else {
        return -1; // ������Χ
    }
}
int main() {
    int n1, n2;

    // ��ȡ��һ�������Ĵ�С������
    printf("��һ�������м�����?: ");
    scanf("%d", &n1);
    double* sample1 = (double*)malloc(n1 * sizeof(double));
    printf("�������һ�����������ݣ��ÿո�ָ���: ");
    for (int i = 0; i < n1; i++) {
        scanf("%lf", &sample1[i]);
    }

    // ��ȡ�ڶ��������Ĵ�С������
    printf("�ڶ��������м�����: ");
    scanf("%d", &n2);
    double* sample2 = (double*)malloc(n2 * sizeof(double));
    printf("������ڶ������������ݣ��ÿո�ָ���: ");
    for (int i = 0; i < n2; i++) {
        scanf("%lf", &sample2[i]);
    }

    // �����ֵ�ͷ���
    double mean1 = calculate_mean(sample1, n1);
    double mean2 = calculate_mean(sample2, n2);
    double var1 = calculate_variance(sample1, n1, mean1);
    double var2 = calculate_variance(sample2, n2, mean2);

    // ����tͳ����
    double t = calculate_t_statistic(mean1, mean2, var1, var2, n1, n2);

    // ��ȡ���ɶȺ�������ˮƽ
    int df = n1 + n2 - 2;
    double alpha;
    printf("������������ˮƽ������ 0.05��: ");
    scanf("%lf", &alpha);

    // ��ȡt�ֲ����ٽ�ֵ
    double t_critical = get_t_critical_value(df, alpha);
    if (t_critical == -1) {
        printf("���ɶȳ�����Χ���޷���ȡ�ٽ�ֵ��\n");
        free(sample1);
        free(sample2);
        return 1;
    }

    // ������
    printf("\n����1��ֵ: %.4f\n", mean1);
    printf("����2��ֵ: %.4f\n", mean2);
    printf("����1����: %.4f\n", var1);
    printf("����2����: %.4f\n", var2);
    printf("tͳ����: %.4f\n", t);
    printf("���ɶ�: %d\n", df);
    printf("t�ֲ��ٽ�ֵ: %.4f\n", t_critical);

    // �ж��Ƿ�ܾ�ԭ����
    if (fabs(t) > t_critical) {
        printf("�ܾ�ԭ���裺���������ľ�ֵ���������졣\n");
    }
    else {
        printf("�޷��ܾ�ԭ���裺���������ľ�ֵ���������졣\n");
    }

    // �ͷ��ڴ�
    free(sample1);
    free(sample2);
    system("pause");
    return 0;
}