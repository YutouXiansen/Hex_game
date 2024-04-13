#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <MCT.h>
using namespace std;

MCTNode::MCTNode(MCTNode* parent, int parent_board[11][11])
{
	this->parent = parent;
	this->score = 0;
	this->search_time = 0;
	for (int i = 0; i < 11; i++)				//将父节点棋盘赋值给子节点棋盘，根据具体情况添加棋子
	{
		for (int j = 0; j < 11; j++)
		{
			this->Current_board[i][j] = parent_board[i][j];
		}
	}
}

int MCTNode::UCT()
{
	return 1.414 * sqrt(log(this->children_search_time) / this->search_time) + 1.0 * this->win_time / this->search_time;
}

MCTNode* MCTNode::select()
{

}

int MCTNode::is_win()
{
	return 1;
}