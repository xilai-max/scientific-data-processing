#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//����n+1����

int main() {
    int n, i;
    float num, sum = 0.0, average;
    printf("��һ����Ϊʹ�����ָ���,Ȼ������ÿ����\n ");
    // �������ֵĸ���

    scanf("%d", &n);

    // ����n�����ֲ��������ǵĺ�
    for (i = 1; i <= n; i++) {

        scanf("%f", &num);
        sum += num;
    }

    // ����ƽ����
    average = sum / n;

    // ������
    printf(" %.2f\n", average);
    system("pause");
    return 0;
}