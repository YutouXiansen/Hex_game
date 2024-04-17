#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <MCT.h>
#include <stack>
using namespace std;
extern int Current_board[11][11];
extern int Current_board[11][11];
extern struct Union_node Current_union[11][11];
extern struct Union_node union_board[11][11];
extern stack<int> useless_nodes_x, useless_node_y;
int visited[11][11] = { 0 };			//用作排除搜索结构时自己填的点，加快运行速度







MCTNode::MCTNode(MCTNode* parent, int x, int y)
{
	this->parent = parent;
	this->score = 0;
	this->search_time = 0;
	this->x = x, this->y = y;
}

double MCTNode::UCT()
{
	return 1.414 * sqrt(log(this->parent->children_search_time) / this->search_time + 0.0001) + 1.0 * this->win_time / this->search_time + 0.01;
}

MCTNode* MCTNode::expand(MCTNode* node) {
	//双距离选点
	struct xgznode** better_choice;
	MCTNode* new_node;
	for (int k = 0; k < 6; k++) {

		new_node = new MCTNode(node, better_choice[k]->i, better_choice[k]->j);
		node->child.emplace_back(new_node);
	}
	return new_node;
}

MCTNode* MCTNode::select(MCTNode* node)
{
	color = 1;
	while (!node->isTerminal()) {
		if (node->isAllExpand()) {
			node = node->bestChild(node, true);
		}
		else {
			node = node->expand(node);
			//				return sub_node;
		}

		//补充棋盘
		Current_board[node->x][node->y] = 1;
		color = -color;
	}




	return node;

}
//达到层数后随机落点
int MCTNode::simulate() {
	int x, y, wins = 0;
	//通过第一颗子判断谁先手
	if (Current_board[1][2] == 1) {//我方先手
		color = 1;
	}
	x = rand() % (11);
	y = rand() % (11);
	for (int i = 0; i <= 0; i++) {           //未添加次数

		while (Current_board[x][y] != 0) {
			x = rand() % (11);
			y = rand() % (11);
		}
		Current_board[x][y] = color;
		color = -color;
	}
	//判断输赢？
//	is_win();

//	memcpy(Current_board,board,121*sizeof(int));
	return wins;
}

void MCTNode::backup(MCTNode* node, double reward) {
	while (node != nullptr) {
		node->search_time++;
		node->score += reward;
		node = node->parent;
	}
}
int MCTNode::is_win()				//我方赢了返回1，对方赢了返回-1，未结束返回0
{
	if (Current_board[1][2] == 1)			//我方先手
	{
		for (int j = 0; j < 11; j++)
		{
			if (Current_union[10][j].father_x = 0)
				return 1;
		}
		for (int i = 0; i < 11; i++)
		{
			if (Current_union[i][10].father_y = 0)
				return -1;
		}
		return 0;
	}
	else if (Current_board[1][2] == -1)			//对方先手
	{
		for (int j = 0; j < 11; j++)
		{
			if (Current_union[10][j].father_x = 0)
				return -1;
		}
		for (int i = 0; i < 11; i++)
		{
			if (Current_union[i][10].father_y = 0)
				return 1;
		}
		return 0;
	}
}

void MCTNode::union_find(int color)			//棋盘并查集初始化
{
	if(Current_board[1][2] == 1)			//我方先手，从i/x == 0到 i/x == 10
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (Current_board[i][j] == 1 || Current_board[i][j] == -1)			//对任意一方，父节点均先是自己
				{
					union_board[i][j].father_x = i;
					union_board[i][j].father_y = j;
				}
			}
		}
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (i == 0 && Current_board[i][j] == 1)				//对我方，且第一排元素，父节点就是自己
				{
					;
				}
				else if (Current_board[i][j] == 1)			//对我方，非第一排元素，周围己方落子点都归并一次，归并到j/y值最小的节点
				{
					if (j - 1 >= 0 && Current_board[i][j - 1] == 1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i, j - 1)->father_x)
						{
							union_find_father(i, j - 1)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i, j - 1)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i, j - 1)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i, j - 1)->father_y;
						}
					}
					if (j - 1 >= 0 && i + 1 <= 10 && Current_board[i + 1][j - 1] == 1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i + 1, j - 1)->father_x)
						{
							union_find_father(i + 1, j - 1)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i + 1, j - 1)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i + 1, j - 1)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i + 1, j - 1)->father_y;
						}
					}
					if (i + 1 <= 10 && Current_board[i + 1][j] == 1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i + 1, j)->father_x)
						{
							union_find_father(i + 1, j)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i + 1, j)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i + 1, j)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i + 1, j)->father_y;
						}
					}
					if (j + 1 <= 10 && Current_board[i][j + 1] == 1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i, j + 1)->father_x)
						{
							union_find_father(i, j + 1)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i, j + 1)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i, j + 1)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i, j + 1)->father_y;
						}
					}
					if (i - 1 >= 0 && j + 1 <= 10 && Current_board[i - 1][j + 1] == 1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i - 1, j + 1)->father_x)
						{
							union_find_father(i - 1, j + 1)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i - 1, j + 1)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i - 1, j + 1)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i - 1, j + 1)->father_y;
						}
					}
					if (i - 1 >= 0 && Current_board[i - 1][j] == 1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i - 1, j)->father_x)
						{
							union_find_father(i - 1, j)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i - 1, j)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i - 1, j)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i - 1, j)->father_y;
						}
					}
				}
			}
			for (int j = 0; j < 11; j++)
			{
				for (int i = 0; i < 11; i++)
				{
					if (j == 0 && Current_board[i][j] == -1)				//对对方，且第一排元素，父节点就是自己
					{
						;
					}
					else if (Current_board[i][j] == -1)			//对对方，非第一列元素，周围己方落子点都归并一次，归并到j/y值最小的节点
					{
						if (j - 1 >= 0 && Current_board[i][j - 1] == -1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i, j - 1)->father_y)
							{
								union_find_father(i, j - 1)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i, j - 1)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i, j - 1)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i, j - 1)->father_y;
							}
						}
						if (j - 1 >= 0 && i + 1 <= 10 && Current_board[i + 1][j - 1] == -1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i + 1, j - 1)->father_y)
							{
								union_find_father(i + 1, j - 1)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i + 1, j - 1)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i + 1, j - 1)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i + 1, j - 1)->father_y;
							}
						}
						if (i + 1 <= 10 && Current_board[i + 1][j] == -1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i + 1, j)->father_y)
							{
								union_find_father(i + 1, j)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i + 1, j)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i + 1, j)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i + 1, j)->father_y;
							}
						}
						if (j + 1 <= 10 && Current_board[i][j + 1] == -1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i, j + 1)->father_y)
							{
								union_find_father(i, j + 1)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i, j + 1)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i, j + 1)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i, j + 1)->father_y;
							}
						}
						if (i - 1 >= 0 && j + 1 <= 10 && Current_board[i - 1][j + 1] == -1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i - 1, j + 1)->father_y)
							{
								union_find_father(i - 1, j + 1)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i - 1, j + 1)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i - 1, j + 1)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i - 1, j + 1)->father_y;
							}
						}
						if (i - 1 >= 0 && Current_board[i - 1][j] == -1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i - 1, j)->father_y)
							{
								union_find_father(i - 1, j)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i - 1, j)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i - 1, j)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i - 1, j)->father_y;
							}
						}
					}
				}
			}
		}
	}
	else if (Current_board[1][2] == -1)			//对方先手
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (Current_board[i][j] == 1 || Current_board[i][j] == -1)			//对任意一方，父节点均先是自己
				{
					union_board[i][j].father_x = i;
					union_board[i][j].father_y = j;
				}
			}
		}
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (i == 0 && Current_board[i][j] == -1)				//对对方，且第一排元素，父节点就是自己
				{
					;
				}
				else if (Current_board[i][j] == -1)			//对对方，非第一排元素，周围己方落子点都归并一次，归并到j/y值最小的节点
				{
					if (j - 1 >= 0 && Current_board[i][j - 1] == -1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i, j - 1)->father_x)
						{
							union_find_father(i, j - 1)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i, j - 1)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i, j - 1)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i, j - 1)->father_y;
						}
					}
					if (j - 1 >= 0 && i + 1 <= 10 && Current_board[i + 1][j - 1] == -1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i + 1, j - 1)->father_x)
						{
							union_find_father(i + 1, j - 1)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i + 1, j - 1)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i + 1, j - 1)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i + 1, j - 1)->father_y;
						}
					}
					if (i + 1 <= 10 && Current_board[i + 1][j] == -1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i + 1, j)->father_x)
						{
							union_find_father(i + 1, j)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i + 1, j)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i + 1, j)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i + 1, j)->father_y;
						}
					}
					if (j + 1 <= 10 && Current_board[i][j + 1] == -1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i, j + 1)->father_x)
						{
							union_find_father(i, j + 1)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i, j + 1)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i, j + 1)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i, j + 1)->father_y;
						}
					}
					if (i - 1 >= 0 && j + 1 <= 10 && Current_board[i - 1][j + 1] == -1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i - 1, j + 1)->father_x)
						{
							union_find_father(i - 1, j + 1)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i - 1, j + 1)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i - 1, j + 1)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i - 1, j + 1)->father_y;
						}
					}
					if (i - 1 >= 0 && Current_board[i - 1][j] == -1)
					{
						if (union_find_father(i, j)->father_x <= union_find_father(i - 1, j)->father_x)
						{
							union_find_father(i - 1, j)->father_x = union_find_father(i, j)->father_x;
							union_find_father(i - 1, j)->father_y = union_find_father(i, j)->father_y;
						}
						else
						{
							union_find_father(i, j)->father_x = union_find_father(i - 1, j)->father_x;
							union_find_father(i, j)->father_y = union_find_father(i - 1, j)->father_y;
						}
					}
				}
			}
			for (int j = 0; j < 11; j++)
			{
				for (int i = 0; i < 11; i++)
				{
					if (j == 0 && Current_board[i][j] == 1)				//对我方，且第一排元素，父节点就是自己
					{
						;
					}
					else if (Current_board[i][j] == 1)			//对我方，非第一列元素，周围己方落子点都归并一次，归并到j/y值最小的节点
					{
						if (j - 1 >= 0 && Current_board[i][j - 1] == 1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i, j - 1)->father_y)
							{
								union_find_father(i, j - 1)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i, j - 1)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i, j - 1)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i, j - 1)->father_y;
							}
						}
						if (j - 1 >= 0 && i + 1 <= 10 && Current_board[i + 1][j - 1] == 1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i + 1, j - 1)->father_y)
							{
								union_find_father(i + 1, j - 1)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i + 1, j - 1)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i + 1, j - 1)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i + 1, j - 1)->father_y;
							}
						}
						if (i + 1 <= 10 && Current_board[i + 1][j] == 1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i + 1, j)->father_y)
							{
								union_find_father(i + 1, j)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i + 1, j)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i + 1, j)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i + 1, j)->father_y;
							}
						}
						if (j + 1 <= 10 && Current_board[i][j + 1] == 1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i, j + 1)->father_y)
							{
								union_find_father(i, j + 1)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i, j + 1)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i, j + 1)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i, j + 1)->father_y;
							}
						}
						if (i - 1 >= 0 && j + 1 <= 10 && Current_board[i - 1][j + 1] == 1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i - 1, j + 1)->father_y)
							{
								union_find_father(i - 1, j + 1)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i - 1, j + 1)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i - 1, j + 1)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i - 1, j + 1)->father_y;
							}
						}
						if (i - 1 >= 0 && Current_board[i - 1][j] == 1)
						{
							if (union_find_father(i, j)->father_y <= union_find_father(i - 1, j)->father_y)
							{
								union_find_father(i - 1, j)->father_x = union_find_father(i, j)->father_x;
								union_find_father(i - 1, j)->father_y = union_find_father(i, j)->father_y;
							}
							else
							{
								union_find_father(i, j)->father_x = union_find_father(i - 1, j)->father_x;
								union_find_father(i, j)->father_y = union_find_father(i - 1, j)->father_y;
							}
						}
					}
				}
			}
		}
	}

	//当前并查集的构建

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			Current_union[i][j].father_x = union_board[i][j].father_x;
			Current_union[i][j].father_y = union_board[i][j].father_y;
		}
	}
}

void MCTNode::union_board_reset()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			Current_union[i][j].father_x = union_board[i][j].father_x;
			Current_union[i][j].father_y = union_board[i][j].father_y;
		}
	}
}

void MCTNode::union_find_update(int i, int j, int color)			//落点时并查集更新
{
	if (Current_board[1][2] == 1)			//我方先手
	{
		if(color == 1)			//我方落子
		{
			if (i == 0 && Current_board[i][j] == 1)				//对我方，且第一排元素，父节点就是自己
			{
				;
			}
			else if (Current_board[i][j] == 1)			//对我方，非第一排元素，周围己方落子点都归并一次，归并到j/y值最小的节点
			{
				if (j - 1 >= 0 && Current_board[i][j - 1] == 1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i, j - 1)->father_x)
					{
						union_find_father(i, j - 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i, j - 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i, j - 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i, j - 1)->father_y;
					}
				}
				if (j - 1 >= 0 && i + 1 <= 10 && Current_board[i + 1][j - 1] == 1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i + 1, j - 1)->father_x)
					{
						union_find_father(i + 1, j - 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i + 1, j - 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i + 1, j - 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i + 1, j - 1)->father_y;
					}
				}
				if (i + 1 <= 10 && Current_board[i + 1][j] == 1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i + 1, j)->father_x)
					{
						union_find_father(i + 1, j)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i + 1, j)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i + 1, j)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i + 1, j)->father_y;
					}
				}
				if (j + 1 <= 10 && Current_board[i][j + 1] == 1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i, j + 1)->father_x)
					{
						union_find_father(i, j + 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i, j + 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i, j + 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i, j + 1)->father_y;
					}
				}
				if (i - 1 >= 0 && j + 1 <= 10 && Current_board[i - 1][j + 1] == 1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i - 1, j + 1)->father_x)
					{
						union_find_father(i - 1, j + 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i - 1, j + 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i - 1, j + 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i - 1, j + 1)->father_y;
					}
				}
				if (i - 1 >= 0 && Current_board[i - 1][j] == 1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i - 1, j)->father_x)
					{
						union_find_father(i - 1, j)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i - 1, j)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i - 1, j)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i - 1, j)->father_y;
					}
				}
			}
		}
		if (color == -1)			//对方落子
		{
			if (j == 0 && Current_board[i][j] == -1)				//对对方，且第一排元素，父节点就是自己
			{
				;
			}
			else if (Current_board[i][j] == -1)			//对对方，非第一列元素，周围己方落子点都归并一次，归并到j/y值最小的节点
			{
				if (j - 1 >= 0 && Current_board[i][j - 1] == -1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i, j - 1)->father_y)
					{
						union_find_father(i, j - 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i, j - 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i, j - 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i, j - 1)->father_y;
					}
				}
				if (j - 1 >= 0 && i + 1 <= 10 && Current_board[i + 1][j - 1] == -1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i + 1, j - 1)->father_y)
					{
						union_find_father(i + 1, j - 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i + 1, j - 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i + 1, j - 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i + 1, j - 1)->father_y;
					}
				}
				if (i + 1 <= 10 && Current_board[i + 1][j] == -1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i + 1, j)->father_y)
					{
						union_find_father(i + 1, j)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i + 1, j)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i + 1, j)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i + 1, j)->father_y;
					}
				}
				if (j + 1 <= 10 && Current_board[i][j + 1] == -1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i, j + 1)->father_y)
					{
						union_find_father(i, j + 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i, j + 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i, j + 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i, j + 1)->father_y;
					}
				}
				if (i - 1 >= 0 && j + 1 <= 10 && Current_board[i - 1][j + 1] == -1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i - 1, j + 1)->father_y)
					{
						union_find_father(i - 1, j + 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i - 1, j + 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i - 1, j + 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i - 1, j + 1)->father_y;
					}
				}
				if (i - 1 >= 0 && Current_board[i - 1][j] == -1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i - 1, j)->father_y)
					{
						union_find_father(i - 1, j)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i - 1, j)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i - 1, j)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i - 1, j)->father_y;
					}
				}
			}
		}
	}
	else if (Current_board[1][2] == -1)			//对方先手
	{
		if (color == -1)			//对方落子
		{
			if (i == 0 && Current_board[i][j] == -1)				//对方，且第一排元素，父节点就是自己
			{
				;
			}
			else if (Current_board[i][j] == -1)			//对方，非第一排元素，周围己方落子点都归并一次，归并到j/y值最小的节点
			{
				if (j - 1 >= 0 && Current_board[i][j - 1] == -1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i, j - 1)->father_x)
					{
						union_find_father(i, j - 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i, j - 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i, j - 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i, j - 1)->father_y;
					}
				}
				if (j - 1 >= 0 && i + 1 <= 10 && Current_board[i + 1][j - 1] == -1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i + 1, j - 1)->father_x)
					{
						union_find_father(i + 1, j - 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i + 1, j - 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i + 1, j - 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i + 1, j - 1)->father_y;
					}
				}
				if (i + 1 <= 10 && Current_board[i + 1][j] == -1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i + 1, j)->father_x)
					{
						union_find_father(i + 1, j)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i + 1, j)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i + 1, j)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i + 1, j)->father_y;
					}
				}
				if (j + 1 <= 10 && Current_board[i][j + 1] == -1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i, j + 1)->father_x)
					{
						union_find_father(i, j + 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i, j + 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i, j + 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i, j + 1)->father_y;
					}
				}
				if (i - 1 >= 0 && j + 1 <= 10 && Current_board[i - 1][j + 1] == -1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i - 1, j + 1)->father_x)
					{
						union_find_father(i - 1, j + 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i - 1, j + 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i - 1, j + 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i - 1, j + 1)->father_y;
					}
				}
				if (i - 1 >= 0 && Current_board[i - 1][j] == -1)
				{
					if (union_find_father(i, j)->father_x <= union_find_father(i - 1, j)->father_x)
					{
						union_find_father(i - 1, j)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i - 1, j)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i - 1, j)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i - 1, j)->father_y;
					}
				}
			}
		}
		if (color == 1)			//我方落子
		{
			if (j == 0 && Current_board[i][j] == 1)				//对我方，且第一排元素，父节点就是自己
			{
				;
			}
			else if (Current_board[i][j] == 1)			//对我方，非第一列元素，周围己方落子点都归并一次，归并到j/y值最小的节点
			{
				if (j - 1 >= 0 && Current_board[i][j - 1] == 1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i, j - 1)->father_y)
					{
						union_find_father(i, j - 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i, j - 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i, j - 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i, j - 1)->father_y;
					}
				}
				if (j - 1 >= 0 && i + 1 <= 10 && Current_board[i + 1][j - 1] == 1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i + 1, j - 1)->father_y)
					{
						union_find_father(i + 1, j - 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i + 1, j - 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i + 1, j - 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i + 1, j - 1)->father_y;
					}
				}
				if (i + 1 <= 10 && Current_board[i + 1][j] == 1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i + 1, j)->father_y)
					{
						union_find_father(i + 1, j)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i + 1, j)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i + 1, j)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i + 1, j)->father_y;
					}
				}
				if (j + 1 <= 10 && Current_board[i][j + 1] == 1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i, j + 1)->father_y)
					{
						union_find_father(i, j + 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i, j + 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i, j + 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i, j + 1)->father_y;
					}
				}
				if (i - 1 >= 0 && j + 1 <= 10 && Current_board[i - 1][j + 1] == 1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i - 1, j + 1)->father_y)
					{
						union_find_father(i - 1, j + 1)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i - 1, j + 1)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i - 1, j + 1)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i - 1, j + 1)->father_y;
					}
				}
				if (i - 1 >= 0 && Current_board[i - 1][j] == 1)
				{
					if (union_find_father(i, j)->father_y <= union_find_father(i - 1, j)->father_y)
					{
						union_find_father(i - 1, j)->father_x = union_find_father(i, j)->father_x;
						union_find_father(i - 1, j)->father_y = union_find_father(i, j)->father_y;
					}
					else
					{
						union_find_father(i, j)->father_x = union_find_father(i - 1, j)->father_x;
						union_find_father(i, j)->father_y = union_find_father(i - 1, j)->father_y;
					}
				}
			}
		}
	}
}

Union_node* MCTNode::union_find_father(int x, int y)			//寻找并查集根结点
{
	if (Current_union[x][y].father_x == x && Current_union[x][y].father_y == y)				//根结点是自己，直接返回
		return &Current_union[x][y];
	else				//根结点不是自己，获取后更新
	{
		struct Union_node* final_father;
		final_father = union_find_father(Current_union[x][y].father_x, Current_union[x][y].father_y);
		Current_union[x][y].father_x = final_father->father_x;
		Current_union[x][y].father_y = final_father->father_y;
		return final_father;
	}
}

Union_node* MCTNode::union_find_father_first(int x, int y)			//寻找并查集根结点
{
	if (union_board[x][y].father_x == x && union_board[x][y].father_y == y)				//根结点是自己，直接返回
		return &union_board[x][y];
	else				//根结点不是自己，获取后更新
	{
		struct Union_node* final_father;
		final_father = union_find_father_first(union_board[x][y].father_x, union_board[x][y].father_y);
		union_board[x][y].father_x = final_father->father_x;
		union_board[x][y].father_y = final_father->father_y;
		return final_father;
	}
}

MCTNode* MCTNode::bestChild(MCTNode* node, bool is_exploration) 
{
	int UCT_number = 0;
	MCTNode* best = NULL;
	vector<MCTNode*>::iterator p = node->child.begin();
	for (p; p != node->child.end(); p++)
	{
		if ((*p)->search_time == 0)
			return (*p);
		else if (UCT_number < (*p)->UCT())
			best = (*p);
	}
	return best;
}
//MCTNode* MCTNode::bestChild(MCTNode* node, bool is_exploration) {
//	double best_score = -std::numeric_limits<double>::max();
//	Node* best_sub_node = nullptr;
//	
//	for (Node* sub_node : node->getChildren()) {
//		double C;
//		if (is_exploration) {
//			C = 1 / std::sqrt(2.0);
//		} else {
//			C = 0.0;
//		}
//		
//		double left = sub_node->getQualityValue() / sub_node->getVisitTimes();
//		double right = 2.0 * std::log(node->getVisitTimes()) / sub_node->getVisitTimes();
//		double score = left + C * std::sqrt(right);
//		
//		if (score > best_score) {
//			best_sub_node = sub_node;
//			best_score = score;
//		}
//	}
//	
//	return best_sub_node;
//}
//谁先下
int who_first(int board[15][15]){
	if(board[1][2]==-1){
		return 0;//对面先下
	}
	else{
		return 1;//我们先下
	}
}

MCTNode* MCTNode::monteCarloTreeSearch(int x, int y, int board[11][11]) {
	memcpy(Current_board, board, 121 * sizeof(int));
	MCTNode* root = new MCTNode(nullptr, x, y);


	MCTNode* expand_node = root->select(root);
	expand_node->win_time += expand_node->simulate();
	double reward = UCT();
	backup(expand_node, reward);


	Node* best_next_node = bestChild(node, false);
	return best_next_node;
}

void MCTNode::fill_board()				//只填充桥，无用位置和被捕获位置，|||||同时获取脆弱的桥的信息，以攻击或防守，||||||同时获取被侵入的边界的信息，以防守
{
	for(int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if(visited[i][j] == 0)			//该点不是自己填的
			{
				//我方六个桥||||||else里是脆弱的桥


				if (i - 1 >= 0 && j - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i - 1][j - 1] == 1 && Current_board[i - 1][j] == 0 && Current_board[i][j - 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i - 1][j] == 1;
						union_find_update(i - 1, j, 1);
						visited[i - 1][j] = 1;
						Current_board[i][j - 1] == -1;
						union_find_update(i, j - 1, -1);
						visited[i][j - 1] = 1;
					}
					else
					{
						Current_board[i - 1][j] == -1;
						union_find_update(i - 1, j, -1);
						visited[i - 1][j] = 1;
						Current_board[i][j - 1] == 1;
						union_find_update(i, j - 1, 1);
						visited[i][j - 1] = 1;
					}
				}
				if (i - 1 >= 0 && j + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i + 1][j - 2] == 1 && Current_board[i][j - 1] == 0 && Current_board[i + 1][j - 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i][j - 1] == 1;
						union_find_update(i, j - 1, 1);
						visited[i][j - 1] = 1;
						Current_board[i + 1][j - 1] == -1;
						union_find_update(i + 1, j - 1, -1);
						visited[i + 1][j - 1] = 1;
					}
					else
					{
						Current_board[i][j - 1] == -1;
						union_find_update(i, j - 1, -1);
						visited[i][j - 1] = 1;
						Current_board[i + 1][j - 1] == 1;
						union_find_update(i + 1, j - 1, 1);
						visited[i + 1][j - 1] = 1;
					}
				}
				if (i - 1 >= 0 && j + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i + 2][j - 1] == 1 && Current_board[i + 1][j] == 0 && Current_board[i + 1][j - 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i + 1][j] == 1;
						union_find_update(i + 1, j, 1);
						visited[i + 1][j] = 1;
						Current_board[i + 1][j - 1] == -1;
						union_find_update(i + 1, j - 1, -1);
						visited[i + 1][j - 1] = 1;
					}
					else
					{
						Current_board[i + 1][j] == -1;
						union_find_update(i + 1, j, -1);
						visited[i + 1][j] = 1;
						Current_board[i + 1][j - 1] == 1;
						union_find_update(i + 1, j - 1, 1);
						visited[i + 1][j - 1] = 1;
					}
				}
				if (i - 1 >= 0 && j + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i - 1][j + 2] == 1 && Current_board[i][j + 1] == 0 && Current_board[i - 1][j + 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i][j + 1] == 1;
						union_find_update(i, j + 1, 1);
						visited[i][j + 1] = 1;
						Current_board[i - 1][j + 1] == -1;
						union_find_update(i - 1, j + 1, -1);
						visited[i - 1][j + 1] = 1;
					}
					else
					{
						Current_board[i][j + 1] == -1;
						union_find_update(i, j + 1, -1);
						visited[i + 1][j - 1] = 1;
						Current_board[i - 1][j + 1] == 1;
						union_find_update(i - 1, j + 1, 1);
						visited[i - 1][j + 1] = 1;
					}
				}
				if (i + 1 <= 10 && j + 1 <= 10 && Current_board[i][j] == 1 && Current_board[i + 1][j + 1] == 1 && Current_board[i][j + 1] == 0 && Current_board[i + 1][j] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i][j + 1] == 1;
						union_find_update(i, j + 1, 1);
						visited[i][j + 1] = 1;
						Current_board[i + 1][j] == -1;
						union_find_update(i + 1, j, -1);
						visited[i + 1][j] = 1;
					}
					else
					{
						Current_board[i][j + 1] == -1;
						union_find_update(i, j + 1, -1);
						visited[i][j + 1] = 1;
						Current_board[i + 1][j] == 1;
						union_find_update(i + 1, j, 1);
						visited[i + 1][j] = 1;
					}
				}
				if (i - 2 >= 0 && j + 1 <= 10 && j - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i - 2][j + 1] == 1 && Current_board[i - 1][j + 1] == 0 && Current_board[i][j - 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i - 1][j + 1] == 1;
						union_find_update(i - 1, j + 1, 1);
						visited[i - 1][j + 1] = 1;
						Current_board[i][j - 1] == -1;
						union_find_update(i, j - 1, -1);
						visited[i][j - 1] = 1;
					}
					else
					{
						Current_board[i - 1][j + 1] == -1;
						union_find_update(i - 1, j + 1, -1);
						visited[i - 1][j + 1] = 1;
						Current_board[i][j - 1] == 1;
						union_find_update(i, j - 1, 1);
						visited[i][j - 1] = 1;
					}
				}


				//对方六个桥


				if (i - 1 >= 0 && j - 1 >= 0 && Current_board[i][j] == -1 && Current_board[i - 1][j - 1] == -1 && Current_board[i - 1][j] == 0 && Current_board[i][j - 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i - 1][j] == 1;
						union_find_update(i - 1, j, 1);
						visited[i - 1][j] = 1;
						Current_board[i][j - 1] == -1;
						union_find_update(i, j - 1, -1);
						visited[i][j - 1] = 1;
					}
					else
					{
						Current_board[i - 1][j] == -1;
						union_find_update(i - 1, j, -1);
						visited[i - 1][j] = 1;
						Current_board[i][j - 1] == 1;
						union_find_update(i, j - 1, 1);
						visited[i][j - 1] = 1;
					}
				}
				if (i - 1 >= 0 && j + 2 <= 10 && Current_board[i][j] == -1 && Current_board[i + 1][j - 2] == -1 && Current_board[i][j - 1] == 0 && Current_board[i + 1][j - 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i][j - 1] == 1;
						union_find_update(i, j - 1, 1);
						visited[i][j - 1] = 1;
						Current_board[i + 1][j - 1] == -1;
						union_find_update(i + 1, j - 1, -1);
						visited[i + 1][j - 1] = 1;
					}
					else
					{
						Current_board[i][j - 1] == -1;
						union_find_update(i, j - 1, -1);
						visited[i][j - 1] = 1;
						Current_board[i + 1][j - 1] == 1;
						union_find_update(i + 1, j - 1, 1);
						visited[i + 1][j - 1] = 1;
					}
				}
				if (i - 1 >= 0 && j + 2 <= 10 && Current_board[i][j] == -1 && Current_board[i + 2][j - 1] == -1 && Current_board[i + 1][j] == 0 && Current_board[i + 1][j - 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i + 1][j] == 1;
						union_find_update(i + 1, j, 1);
						visited[i + 1][j] = 1;
						Current_board[i + 1][j - 1] == -1;
						union_find_update(i + 1, j - 1, -1);
						visited[i + 1][j - 1] = 1;
					}
					else
					{
						Current_board[i + 1][j] == -1;
						union_find_update(i + 1, j, -1);
						visited[i + 1][j] = 1;
						Current_board[i + 1][j - 1] == 1;
						union_find_update(i + 1, j - 1, 1);
						visited[i + 1][j - 1] = 1;
					}
				}
				if (i - 1 >= 0 && j + 2 <= 10 && Current_board[i][j] == -1 && Current_board[i - 1][j + 2] == -1 && Current_board[i][j + 1] == 0 && Current_board[i - 1][j + 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i][j + 1] == 1;
						union_find_update(i, j + 1, 1);
						visited[i][j + 1] = 1;
						Current_board[i - 1][j + 1] == -1;
						union_find_update(i - 1, j + 1, -1);
						visited[i - 1][j + 1] = 1;
					}
					else
					{
						Current_board[i][j + 1] == -1;
						union_find_update(i, j + 1, -1);
						visited[i + 1][j - 1] = 1;
						Current_board[i - 1][j + 1] == 1;
						union_find_update(i - 1, j + 1, 1);
						visited[i - 1][j + 1] = 1;
					}
				}
				if (i + 1 <= 10 && j + 1 <= 10 && Current_board[i][j] == -1 && Current_board[i + 1][j + 1] == -1 && Current_board[i][j + 1] == 0 && Current_board[i + 1][j] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i][j + 1] == 1;
						union_find_update(i, j + 1, 1);
						visited[i][j + 1] = 1;
						Current_board[i + 1][j] == -1;
						union_find_update(i + 1, j, -1);
						visited[i + 1][j] = 1;
					}
					else
					{
						Current_board[i][j + 1] == -1;
						union_find_update(i, j + 1, -1);
						visited[i][j + 1] = 1;
						Current_board[i + 1][j] == 1;
						union_find_update(i + 1, j, 1);
						visited[i + 1][j] = 1;
					}
				}
				if (i - 2 >= 0 && j + 1 <= 10 && j - 1 >= 0 && Current_board[i][j] == -1 && Current_board[i - 2][j + 1] == -1 && Current_board[i - 1][j + 1] == 0 && Current_board[i][j - 1] == 0)
				{
					int random_number = (rand() % 2) + 0;
					if (random_number == 0)
					{
						Current_board[i - 1][j + 1] == 1;
						union_find_update(i - 1, j + 1, 1);
						visited[i - 1][j + 1] = 1;
						Current_board[i][j - 1] == -1;
						union_find_update(i, j - 1, -1);
						visited[i][j - 1] = 1;
					}
					else
					{
						Current_board[i - 1][j + 1] == -1;
						union_find_update(i - 1, j + 1, -1);
						visited[i - 1][j + 1] = 1;
						Current_board[i][j - 1] == 1;
						union_find_update(i, j - 1, 1);
						visited[i][j - 1] = 1;
					}
				}


				//我方无用位置1


				if (i - 2 >= 0 && j + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i][j + 1] == 1 && Current_board[i - 1][j + 2] == 1 && Current_board[i - 2][j + 2] == 1 && Current_board[i - 1][j + 1] == 0)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j + 1);
				}
				if (i - 2 >= 0 && j + 1 <= 10 && Current_board[i][j] == 1 && Current_board[i - 1][j + 1] == 1 && Current_board[i - 2][j + 1] == 1 && Current_board[i - 2][j] == 1 && Current_board[i - 1][j] == 0)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j);
				}
				if (i - 1 >= 0 && j - 2 >= 0 && Current_board[i][j] == 1 && Current_board[i - 1][j] == 1 && Current_board[i - 1][j - 1] == 1 && Current_board[i][j - 2] == 1 && Current_board[i][j - 1] == 0)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j - 1);
				}
				if (i + 2 <= 10 && j - 2 >= 0 && Current_board[i][j] == 1 && Current_board[i][j - 1] == 1 && Current_board[i + 1][j - 2] == 1 && Current_board[i + 2][j - 2] == 1 && Current_board[i + 1][j - 1] == 0)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j - 1);
				}
				if (i + 2 <= 10 && j - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i + 1][j - 1] == 1 && Current_board[i + 2][j - 1] == 1 && Current_board[i + 2][j] == 1 && Current_board[i + 1][j] == 0)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j);
				}
				if (i + 1 <= 10 && j + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i + 1][j] == 1 && Current_board[i + 1][j + 1] == 1 && Current_board[i][j + 2] == 1 && Current_board[i][j + 1] == 0)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j + 1);
				}


				//我方无用位置2
				if (i - 2 >= 0 && j + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i - 1][j + 1] == 0 && Current_board[i - 2][j + 1] == -1 && Current_board[i - 2][j + 2] == -1 && Current_board[i - 1][j + 2] == -1)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j + 1);
				}
				if (i - 2 >= 0 && j + 1 <= 10 && j - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i - 1][j] == 0 && Current_board[i - 1][j - 1] == -1 && Current_board[i - 2][j] == -1 && Current_board[i - 2][j + 1] == -1)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j);
				}
				if (i - 1 >= 0 && j - 2 >= 0 && i + 1 <= 10 && Current_board[i][j] == 1 && Current_board[i][j - 1] == 0 && Current_board[i + 1][j - 2] == -1 && Current_board[i][j - 2] == -1 && Current_board[i - 1][j - 1] == -1)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j - 1);
				}
				if (j - 2 >= 0 && i + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i + 1][j - 1] == 0 && Current_board[i + 2][j - 1] == -1 && Current_board[i + 2][j - 2] == -1 && Current_board[i + 1][j - 2] == -1)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j - 1);
				}
				if (i + 2 <= 10 && j + 1 <= 10 && j - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i + 1][j] == 0 && Current_board[i + 1][j + 1] == -1 && Current_board[i + 2][j] == -1 && Current_board[i + 2][j - 1] == -1)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j);
				}
				if (i - 1 >= 0 && j + 2 <= 10 && i + 1 <= 10 && Current_board[i][j] == 1 && Current_board[i][j + 1] == 0 && Current_board[i - 1][j + 2] == -1 && Current_board[i][j + 2] == -1 && Current_board[i + 1][j + 1] == -1)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j + 1);
				}


				//公共无用位置
				if (i - 2 >= 0 && j + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i][j + 1] == 1 && Current_board[i - 1][j + 1] == 0 && Current_board[i - 2][j + 1] == -1 && Current_board[i - 2][j + 2] == -1)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j + 1);
				}
				if (i - 2 >= 0 && j + 1 <= 10 && j - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i - 1][j + 1] == 1 && Current_board[i - 1][j] == 0 && Current_board[i - 1][j - 1] == -1 && Current_board[i - 2][j] == -1)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j);
				}
				if (j - 2 >= 0 && i + 1 <= 10 && i - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i - 1][j] == 1 && Current_board[i][j - 1] == 0 && Current_board[i + 1][j - 2] == -1 && Current_board[i][j - 2] == -1)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j - 1);
				}
				if (j - 2 >= 0 && i + 2 <= 10 && Current_board[i][j] == 1 && Current_board[i][j - 1] == 1 && Current_board[i + 1][j - 1] == 0 && Current_board[i + 2][j - 1] == -1 && Current_board[i + 2][j - 2] == -1)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j - 1);
				}
				if (i + 2 <= 10 && j + 1 <= 10 && j - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i + 1][j - 1] == 1 && Current_board[i + 1][j] == 0 && Current_board[i + 1][j + 1] == -1 && Current_board[i + 2][j] == -1)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j);
				}
				if (j + 2 <= 10 && i + 1 <= 10 && i - 1 >= 0 && Current_board[i][j] == 1 && Current_board[i + 1][j] == 1 && Current_board[i][j + 1] == 0 && Current_board[i - 1][j + 2] == -1 && Current_board[i][j + 2] == -1)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j + 1);
				}


				//对方无用位置1
				if (i - 2 >= 0 && j + 2 <= 10 && Current_board[i][j] == -1 && Current_board[i][j + 1] == -1 && Current_board[i - 1][j + 2] == -1 && Current_board[i - 2][j + 2] == -1 && Current_board[i - 1][j + 1] == 0)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j + 1);
				}
				if (i - 2 >= 0 && j + 1 <= 10 && Current_board[i][j] == -1 && Current_board[i - 1][j + 1] == -1 && Current_board[i - 2][j + 1] == -1 && Current_board[i - 2][j] == -1 && Current_board[i - 1][j] == 0)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j);
				}
				if (i - 1 >= 0 && j - 2 >= 0 && Current_board[i][j] == -1 && Current_board[i - 1][j] == -1 && Current_board[i - 1][j - 1] == -1 && Current_board[i][j - 2] == -1 && Current_board[i][j - 1] == 0)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j - 1);
				}
				if (i + 2 <= 10 && j - 2 >= 0 && Current_board[i][j] == -1 && Current_board[i][j - 1] == -1 && Current_board[i + 1][j - 2] == -1 && Current_board[i + 2][j - 2] == -1 && Current_board[i + 1][j - 1] == 0)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j - 1);
				}
				if (i + 2 <= 10 && j - 1 >= 0 && Current_board[i][j] == -1 && Current_board[i + 1][j - 1] == -1 && Current_board[i + 2][j - 1] == -1 && Current_board[i + 2][j] == -1 && Current_board[i + 1][j] == 0)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j);
				}
				if (i + 1 <= 10 && j + 2 <= 10 && Current_board[i][j] == -1 && Current_board[i + 1][j] == -1 && Current_board[i + 1][j + 1] == -1 && Current_board[i][j + 2] == -1 && Current_board[i][j + 1] == 0)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j + 1);
				}


				//对方无用位置2
				if (i - 2 >= 0 && j + 2 <= 10 && Current_board[i][j] == -1 && Current_board[i - 1][j + 1] == 0 && Current_board[i - 2][j + 1] == 1 && Current_board[i - 2][j + 2] == 1 && Current_board[i - 1][j + 2] == 1)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j + 1);
				}
				if (i - 2 >= 0 && j + 1 <= 10 && j - 1 >= 0 && Current_board[i][j] == -1 && Current_board[i - 1][j] == 0 && Current_board[i - 1][j - 1] == 1 && Current_board[i - 2][j] == 1 && Current_board[i - 2][j + 1] == 1)
				{
					useless_nodes_x.push(i - 1);
					useless_node_y.push(j);
				}
				if (i - 1 >= 0 && j - 2 >= 0 && i + 1 <= 10 && Current_board[i][j] == -1 && Current_board[i][j - 1] == 0 && Current_board[i + 1][j - 2] == 1 && Current_board[i][j - 2] == 1 && Current_board[i - 1][j - 1] == 1)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j - 1);
				}
				if (j - 2 >= 0 && i + 2 <= 10 && Current_board[i][j] == -1 && Current_board[i + 1][j - 1] == 0 && Current_board[i + 2][j - 1] == 1 && Current_board[i + 2][j - 2] == 1 && Current_board[i + 1][j - 2] == 1)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j - 1);
				}
				if (i + 2 <= 10 && j + 1 <= 10 && j - 1 >= 0 && Current_board[i][j] == -1 && Current_board[i + 1][j] == 0 && Current_board[i + 1][j + 1] == 1 && Current_board[i + 2][j] == 1 && Current_board[i + 2][j - 1] == 1)
				{
					useless_nodes_x.push(i + 1);
					useless_node_y.push(j);
				}
				if (i - 1 >= 0 && j + 2 <= 10 && i + 1 <= 10 && Current_board[i][j] == -1 && Current_board[i][j + 1] == 0 && Current_board[i - 1][j + 2] == 1 && Current_board[i][j + 2] == 1 && Current_board[i + 1][j + 1] == 1)
				{
					useless_nodes_x.push(i);
					useless_node_y.push(j + 1);
				}

				while (!useless_nodes_x.size())				//随机落子
				{
					int x = useless_nodes_x.top();
					int y = useless_node_y.top();
					Current_board[x][y] = color;
					visited[x][y] = 1;
					union_find_update(x, y, color);
					useless_nodes_x.pop();
					useless_node_y.pop();
					color = -color;
				}

				visited[i][j] = 1;
			}
		}
	}
}

void MCTNode::visited_reset()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			visited[i][j] = 0;
		}
	}
}
