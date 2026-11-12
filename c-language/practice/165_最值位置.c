/* ============================================================
 * 题号：165
 * 题名：最值位置
 * 考点：数组 · 遍历与下标记录
 * 状态：✅ 本地实测通过（2026-11-12）
 *
 * 实测说明：
 *   - max 初值取 arr[0]，位置用下标；输出 `n max place`。
 *   - 1..8 → 8 8 7。
 *
 * 本地测试用例：
 *   - 8 / 1 2 3 4 5 6 7 8 → 8 8 7
 * ============================================================ */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int arr[90] = { 0 };
	int n = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	int max = arr[0];
	int place = 0;

	for (int i = 0; i < n; i++)
	{
		if (max < arr[i])
		{
			max = arr[i];
			place = i;
		}
	}

	printf("%d %d %d\n", n, max, place);

	return 0;

}
