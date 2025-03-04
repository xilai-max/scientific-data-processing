#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ��������
double get_t_critical_value(int df, double confidence_level);

int main() {
    int df;  // ���ɶ�
    double confidence_level;  // ���Ŷ�
    double t_critical_value;  // t�ֲ����ٽ�ֵ

    // ��ȡ�û���������ɶ�
    printf("���������ɶ� (df): ");
    scanf("%d", &df);

    // ��ȡ�û���������Ŷ�
    printf("��ѡ�����Ŷ� (���� 0.90, 0.95, 0.99): ");
    scanf("%lf", &confidence_level);

    // ��ȡ��Ӧ��t�ֲ��ٽ�ֵ
    t_critical_value = get_t_critical_value(df, confidence_level);

    // ������
    if (t_critical_value != -1) {
        printf("�����ɶ�Ϊ %d �����Ŷ�Ϊ %.2f ������£�t�ֲ����ٽ�ֵ��: %.4f\n", df, confidence_level, t_critical_value);
    }
    else {
        printf("�޷��ҵ���Ӧ��t�ֲ��ٽ�ֵ��������������ɶȺ����Ŷȡ�\n");
    }
    system("pause");
    system("pause");
    return 0;
}

// ��ȡt�ֲ��ٽ�ֵ�ĺ���
double get_t_critical_value(int df, double confidence_level) {
    // �������ʹ�ò�������ͳ�ƿ�����ȡ�ٽ�ֵ
    // ������һ���򵥵�ʾ��������������һЩԤ������ٽ�ֵ

    // ʾ�����ݣ����ɶȶ�Ӧ���ٽ�ֵ���������Ŷ�Ϊ0.95��
    double t_table[10][3] = {
        {6.314, 12.706, 63.657},  // df=1
        {2.920, 4.303, 9.925},   // df=2
        {2.353, 3.182, 5.841},    // df=3
        {2.132, 2.776, 4.604},   // df=4
        {2.015, 2.571, 4.032},   // df=5
        {1.943, 2.447, 3.707},   // df=6
        {1.895, 2.365, 3.499},   // df=7
        {1.860, 2.306, 3.355},   // df=8
        {1.833, 2.262, 3.250},   // df=9
        {1.812, 2.228, 3.169}    // df=10
    };

    // ȷ�����Ŷȶ�Ӧ����
    int column;
    if (confidence_level == 0.90) {
        column = 0;
    }
    else if (confidence_level == 0.95) {
        column = 1;
    }
    else if (confidence_level == 0.99) {
        column = 2;
    }
    else {
        return -1;  // ��Ч�����Ŷ�
    }

    // ������ɶ��Ƿ��ڷ�Χ��
    if (df < 1 || df > 10) {
        return -1;  // ��Ч�����ɶ�
    }

    // ���ض�Ӧ���ٽ�ֵ
    return t_table[df - 1][column];
}