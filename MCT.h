#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

class MCTNode
{
private:
	int Current_board[11][11];			//当前棋局
	vector<MCTNode*> child;			//子节点集合
	MCTNode* parent;			//父节点，加减分用
	int score;				//分数
	int search_time;			//搜索次数
	int win_time;			//胜利次数
	int children_search_time;			//所有子节点搜索次数
public:
	MCTNode(MCTNode* parent, int parent_board[11][11]);
	//选择子节点，返回值为MCTNode*类型
	MCTNode* select();
	//拓展该节点，返回值为空
	void expend();
	//模拟，返回值为int类型，判断输赢
	int simulate();
	//判断输赢函数
	int is_win();
	//反向传播算分函数
	int back();
	//UCT函数
	int UCT();
};