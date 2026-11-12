/* ============================================================
 * 题号：40
 * 题名：等差数列
 * 考点：数组 · 排序后验证与多分支输出
 * 状态：❌ 本地实测未通过（2026-11-12）
 *
 * 实测说明：
 *   - 校验循环写 `i < n`，访问 arr[n] 越界（读到 0），合法数列也被判 no。应 `i < n-1`。
 *   - 判定成功后输出 `yes`，题面要求输出公差绝对值。
 *   - `n <= 2` 分支也输出 yes，同样应输出公差。
 *   - 改前实测：样例1→no（对）、样例2→no（应 2）。
 *
 * 本地测试用例：
 *   - 6 / 23 15 4 18 35 11 → no
 *   - 5 / 2 6 8 4 10 → 2
 * ============================================================ */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	int arr[105] = { 0 };
	int n = 0;

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	if (n <= 2) {
		printf("yes\n");
		return 0;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	int d = arr[1] - arr[0];

	for (int i = 0; i < n; i++)
	{
		if (arr[i + 1] - arr[i] != d)
		{
			printf("no\n");
			return 0;
		}
	}

	printf("yes\n");
	return 0;

}
