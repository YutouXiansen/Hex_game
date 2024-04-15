#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <MCT.h>
using namespace std;

const int SIZE = 15;
int board[SIZE][SIZE] = { 0 };//本方1，对方-1，空白0

int main()
{
	int x, y, n;
	//恢复目前的棋盘信息
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y; if (x != -1) board[x][y] = -1;	//对方
		cin >> x >> y; if (x != -1) board[x][y] = 1;	//我方
	}
	cin >> x >> y;
	if (x != -1) board[x][y] = -1;	//对方

	//此时board[][]里存储的就是当前棋盘的所有棋子信息,x和y存的是对方最近一步下的棋




	else{
		printf("1 2");
		return 0;
	}

	round0=2*n-who_first(board)-1;
	/************************************************************************************/
	/***********在下面填充你的代码，决策结果（本方将落子的位置）存入new_x和new_y中****************/
	//下面仅为随机策略的示例代码，可删除
	int avail_x[SIZE * SIZE], avail_y[SIZE * SIZE]; //合法位置表
	int cnt = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (board[i][j] == 0) {
				avail_x[cnt] = i;
				avail_y[cnt] = j;
				cnt++;
			}
	srand(time(0));
	int rand_pos = rand() % cnt;
	int new_x = avail_x[rand_pos];
	int new_y = avail_y[rand_pos];
	/***********在上方填充你的代码，决策结果（本方将落子的位置）存入new_x和new_y中****************/
	/************************************************************************************/

	// 向平台输出决策结果
	cout << new_x << ' ' << new_y << endl;
	return 0;
}
