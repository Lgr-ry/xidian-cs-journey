/* ============================================================
 * 题号：196
 * 题名：输出金字塔
 * 考点：二重循环 · 图形与空格规律
 * 状态：✅ 本地实测通过（2026-11-12）
 *
 * 实测说明：
 *   - 空格数 = rows-1-i；先递增 A..A+i，再递减 A+i-1..A。
 *   - 行末无多余空格，最后一行开头无空格。
 *
 * 本地测试用例：
 *   - C → 3 行：  A / ABA / ABCBA
 * ============================================================ */
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main()
{
	char max_char;
	scanf("%c", &max_char);

	int rows = max_char - 'A' + 1;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < rows - 1 - i; j++)
		{
			printf(" ");
		}

		for (char ch = 'A'; ch <= 'A' + i; ch++)
		{
			printf("%c", ch);
		}

		for (char ch = 'A' + i - 1; ch >= 'A'; ch--)
		{
			printf("%c", ch);
		}

		printf("\n");
	}

	return 0;

}
