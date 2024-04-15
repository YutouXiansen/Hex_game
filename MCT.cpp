#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <MCT.h>
using namespace std;
extern int Current_board[11][11];
int visited[11][11] = { 0 };			//用作判断结束时是否已遍历该点的标识







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
int MCTNode::is_win()				//我方赢了返回1
{
	int win_flag = 0;
	//board
	//先判断我方先手后手
	//先判断红方先手，上下贯通
	if(Current_board[1][2] == 1)			//我方先手
	{
		for (int i = 0; i < 11; i++)
		{
			if (Current_board[0][i] == 1)			//进入搜索程序
			{
				if (Current_board[0][i + 1] == 1)
				{
					visited[0][i + 1] = 1;
					if (search_first(0, i + 1, 1))
						return 1;
				}
			}
		}
		for (int i = 0; i < 11; i++)					//这个在退出函数时再运行一次
		{
			for (int j = 0; j < 11; j++)
				visited[i][j] = 0;
		}
	}
	else if (Current_board[1][2] == -1)				//我方后手
	{
		for (int i = 0; i < 11; i++)
		{
			if (Current_board[0][i] == -1)			//进入搜索程序
			{
				if (Current_board[0][i + 1] == -1)
				{
					visited[0][i + 1] = 1;
					if (search_first(0, i + 1, -1))
						return 0;				//我军败了
				}
			}
		}
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
				visited[i][j] = 0;
		}
	}
}

int MCTNode::search_first(int x, int y, int colour)
{
	if (x == 10)
		return 1;
	if (x - 1 >= 0 && y >= 0 && Current_board[x - 1][y] == colour && visited[x - 1][y] == 0)
	{
		visited[x - 1][y] = 1;
		if (search_first(x - 1, y, colour))
			return 1;
	}
	if (x + 1 >= 0 && y >= 0 && Current_board[x + 1][y] == colour && visited[x + 1][y] == 0)
	{
		visited[x + 1][y] = 1;
		if (search_first(x + 1, y, colour))
			return 1;
	}
	if (x - 1 >= 0 && y + 1 >= 0 && Current_board[x - 1][y + 1] == colour && visited[x - 1][y + 1] == 0)
	{
		visited[x - 1][y + 1] = 1;
		if (search_first(x - 1, y + 1, colour))
			return 1;
	}
	if (x >= 0 && y + 1 >= 0 && Current_board[x][y + 1] == colour && visited[x][y + 1] == 0)
	{
		visited[x][y + 1] = 1;
		if (search_first(x, y + 1, colour))
			return 1;
	}
	if (x + 1 >= 0 && y - 1 >= 0 && Current_board[x + 1][y - 1] == colour && visited[x + 1][y - 1] == 0)
	{
		visited[x + 1][y - 1] = 1;
		if (search_first(x + 1, y - 1, colour))
			return 1;
	}
	if (x >= 0 && y - 1 >= 0 && Current_board[x][y - 1] == colour && visited[x][y - 1] == 0)
	{
		visited[x][y - 1] = 1;
		if (search_first(x, y - 1, colour))
			return 1;
	}
	return 0;
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
int who_first(int board[11][11]){
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
