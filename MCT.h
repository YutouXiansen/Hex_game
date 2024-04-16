#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;
int Current_board[11][11]={0};			//当前棋局
int coulor,round0;                             
int who_first(int board[15][15]);			//谁先手,先下返回1,后下返回0


struct Union_node
{
	int father_x;
	int father_y;
};
struct Union_node Current_union[11][11];			//并查集




struct xgznode
{
	int i;
	int j;
	int distance;
};








class MCTNode
{
private:
	int x,y;
	vector<MCTNode*> child;			//子节点集合
	MCTNode* parent;			//父节点，加减分用
	int score;				//分数
	int search_time;			//搜索次数
	int win_time;			//胜利次数
	int children_search_time;			//所有子节点搜索次数
public:
	MCTNode(MCTNode* parent,int x,int y);
	//选择子节点，返回值为MCTNode*类型
	MCTNode* select(MCTNode* node);
	//拓展该节点，返回值为空
	MCTNode* expand(MCTNode* node);
	//模拟，返回值为int类型，判断输赢
	int simulate();
	//判断输赢函数
	int is_win();
	//并查集初始化
	void union_find(int color);
	//落点时并查集的更新
	void union_find_update(int x, int y, int color);
	//找父节点函数
	Union_node* union_find_father(int x, int y);
	//反向传播算分函数
	void backup(MCTNode* node, double reward);
	//UCT函数
	double UCT();
	//判断结束
	int isTerminal();
	//判断探索完成
	int isAllExpand();
	//选择最好子节点
	MCTNode* bestChild(MCTNode* node, bool is_exploration);
	//全过程
	MCTNode* monteCarloTreeSearch(int x,int y,int board[11][11]); 
	//填充特殊结构的函数
	void fill_board();
};
