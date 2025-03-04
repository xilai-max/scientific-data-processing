#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//输入n+1个数

int main() {
    int n, i;
    float num, sum = 0.0, average;
    printf("第一个数为使用数字个数,然后输入每个数\n ");
    // 输入数字的个数

    scanf("%d", &n);

    // 输入n个数字并计算它们的和
    for (i = 1; i <= n; i++) {

        scanf("%f", &num);
        sum += num;
    }

    // 计算平均数
    average = sum / n;

    // 输出结果
    printf(" %.2f\n", average);
    system("pause");
    return 0;
}