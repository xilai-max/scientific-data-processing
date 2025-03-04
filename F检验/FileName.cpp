#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// �����ֵ
double calculate_mean(double data[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += data[i];
    }
    return sum / n;
}

// ����ƽ����
double calculate_sum_of_squares(double data[], int n, double mean) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += (data[i] - mean) * (data[i] - mean);
    }
    return sum;
}

// ������ANOVA����
void one_way_anova(double* groups[], int group_sizes[], int k, double alpha) {
    int total_n = 0;
    for (int i = 0; i < k; i++) {
        total_n += group_sizes[i];
    }

    // �����ܾ�ֵ
    double total_sum = 0.0;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < group_sizes[i]; j++) {
            total_sum += groups[i][j];
        }
    }
    double total_mean = total_sum / total_n;

    // �������ƽ���� (SSB)
    double ssb = 0.0;
    for (int i = 0; i < k; i++) {
        double group_mean = calculate_mean(groups[i], group_sizes[i]);
        ssb += group_sizes[i] * (group_mean - total_mean) * (group_mean - total_mean);
    }

    // ��������ƽ���� (SSW)
    double ssw = 0.0;
    for (int i = 0; i < k; i++) {
        double group_mean = calculate_mean(groups[i], group_sizes[i]);
        ssw += calculate_sum_of_squares(groups[i], group_sizes[i], group_mean);
    }

    // �������ɶ�
    int df_between = k - 1;      // ������ɶ�
    int df_within = total_n - k; // �������ɶ�

    // �������
    double msb = ssb / df_between; // ������
    double msw = ssw / df_within;  // ���ھ���

    // ����Fͳ����
    double f = msb / msw;

    // ������
    printf("\nANOVA ���:\n");
    printf("���ƽ���� (SSB): %.4f\n", ssb);
    printf("����ƽ���� (SSW): %.4f\n", ssw);
    printf("������ɶ� (df_between): %d\n", df_between);
    printf("�������ɶ� (df_within): %d\n", df_within);
    printf("������ (MSB): %.4f\n", msb);
    printf("���ھ��� (MSW): %.4f\n", msw);
    printf("Fͳ����: %.4f\n", f);

    // ��F�ֲ�������������ˮƽΪ0.05��
    double f_critical;
    printf("������F�ֲ����ٽ�ֵ���������ɶȺ�������ˮƽ���: ");
    scanf("%lf", &f_critical);

    // �ж��Ƿ�ܾ�ԭ����
    if (f > f_critical) {
        printf("�ܾ�ԭ���裺����������ľ�ֵ���������졣\n");
    }
    else {
        printf("�޷��ܾ�ԭ���裺�����ֵ���������졣\n");
    }
}

int main() {
    int k; // ����
    printf("����������: ");
    scanf("%d", &k);

    // ��̬�����ڴ�洢ÿ������
    double** groups = (double**)malloc(k * sizeof(double*));
    int* group_sizes = (int*)malloc(k * sizeof(int));

    // ����ÿ������
    for (int i = 0; i < k; i++) {
        printf("������� %d ���������С: ", i + 1);
        scanf("%d", &group_sizes[i]);

        groups[i] = (double*)malloc(group_sizes[i] * sizeof(double));
        printf("������� %d ������ݣ��ÿո�ָ���: ", i + 1);
        for (int j = 0; j < group_sizes[i]; j++) {
            scanf("%lf", &groups[i][j]);
        }
    }

    // ����������ˮƽ
    double alpha;
    printf("������������ˮƽ������ 0.05��: ");
    scanf("%lf", &alpha);

    // ���е�����ANOVA����
    one_way_anova(groups, group_sizes, k, alpha);

    // �ͷ��ڴ�
    for (int i = 0; i < k; i++) {
        free(groups[i]);
    }
    free(groups);
    free(group_sizes);
    system ("pause");
    return 0;
}