#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 函数声明
double get_t_critical_value(int df, double confidence_level);

int main() {
    int df;  // 自由度
    double confidence_level;  // 置信度
    double t_critical_value;  // t分布的临界值

    // 获取用户输入的自由度
    printf("请输入自由度 (df): ");
    scanf("%d", &df);

    // 获取用户输入的置信度
    printf("请选择置信度 (例如 0.90, 0.95, 0.99): ");
    scanf("%lf", &confidence_level);

    // 获取对应的t分布临界值
    t_critical_value = get_t_critical_value(df, confidence_level);

    // 输出结果
    if (t_critical_value != -1) {
        printf("在自由度为 %d 和置信度为 %.2f 的情况下，t分布的临界值是: %.4f\n", df, confidence_level, t_critical_value);
    }
    else {
        printf("无法找到对应的t分布临界值，请检查输入的自由度和置信度。\n");
    }
    system("pause");
    system("pause");
    return 0;
}

// 获取t分布临界值的函数
double get_t_critical_value(int df, double confidence_level) {
    // 这里可以使用查表法或调用统计库来获取临界值
    // 以下是一个简单的示例，假设我们有一些预定义的临界值

    // 示例数据：自由度对应的临界值（假设置信度为0.95）
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

    // 确定置信度对应的列
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
        return -1;  // 无效的置信度
    }

    // 检查自由度是否在范围内
    if (df < 1 || df > 10) {
        return -1;  // 无效的自由度
    }

    // 返回对应的临界值
    return t_table[df - 1][column];
}