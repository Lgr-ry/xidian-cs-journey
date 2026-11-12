/* ============================================================
 * 题号：193
 * 题名：评分系统
 * 考点：数组 · 排序 + 去极值求平均
 * 状态：✅ 本地实测通过（2026-11-12）
 *
 * 实测说明：
 *   - 冒泡排序：外层 n-1 轮，内层 j < n-1-i，比较 a[j] 与 a[j+1]。
 *   - 排序后累加 arr[1..n-2]，除以 n-2。
 *   - 六个用例全过（有序/乱序/n=3/全相同/n=10/含并列）。
 *
 * 本地测试用例：
 *   - 5 / 90 70 80 75 85 → 80.00
 *   - 3 / 50 100 60 → 60.00
 * ============================================================ */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int n = 0;
	scanf("%d", &n);

	int arr[12] = { 0 };
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
	
	double fenshu = 0.0;
	int sum = 0;

	for (int i = 1; i < n - 1; i++)
	{
		sum = sum + arr[i];
	}

	fenshu = (double)sum / (n-2);

	printf("%.2f\n", fenshu);

	return 0;

}
