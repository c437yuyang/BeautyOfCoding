#include <iostream>
#include <algorithm>
#include <vector>

#define INF INT_MAX

//S:名字
//C:每种饮料最大数量
//H:满意度
//B:实际购买数量

//动态规划版本，在剩余V容量的情况下，可选从0...T-1种饮料，能够获得的最优解
int Cal(int V, int T)
{
	std::vector<std::vector<int>> opt(V + 1, std::vector<int>(T, 0));
	opt[0][T] = 0;                              // 边界条件，T为所有饮料种类
	for (int i = 1; i <= V; i++)              // 边界条件
	{
		opt[i][T] = -INF;
	}
	for (int j = T - 1; j >= 0; j--)
	{
		for (int i = 0; i <= V; i++)
		{
			opt[i][j] = -INF;
			for (int k = 0; k <= C[j]; k++) // 遍历第j种饮料选取数量k
			{
				if (i < k * V[j])
					break;

				int x = opt[i - k * V[j]][j + 1];
				if (x != -INF)
				{
					x += H[j] * k;
					if (x > opt[i][j])
					{
						opt[i][j] = x;
					}
				}
			}
		}
	}
	return opt[V][0];
}


//带备忘录版本
int[V + 1][T + 1] opt;  	// 子问题的记录项表，假设从i到T种饮料中，
							// 找出容量总和为V'的一个方案，满意度最多能够达到
							// opt（V'，i，T-1），存储于opt[V'][i]，
							// 初始化时opt中存储值为-1，表示该子问题尚未求解。
int Cal(int V, int type)
{
	if (type == T)
	{
		if (V == 0)
			return 0;
		else
			return -INF;
	}
	if (V < 0)
		return -INF;
	else if (V == 0)
		return 0;
	else if (opt[V][type] != -1)
		return opt[V][type]; 	// 该子问题已求解，则直接返回子问题的解；
								// 子问题尚未求解，则求解该子问题
	int ret = -INF;
	for (int i = 0; i <= C[type]; i++)
	{
		int temp = Cal(V – i * C[type], type + 1);
		if (temp != -INF)
		{
			temp += H[type] * i;
			if (temp > ret)
				ret = temp;
		}
	}
	return opt[V][type] = ret;
}

//解法3:贪心策略
//因为每种饮料是2的幂次，先看V%2  如果等于1那必须要买1大小的饮料 ，就找2^0里面饮料H最大的
//然后还需要买V-2^0 这么多饮料，


int main() 
{

}