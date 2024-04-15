#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "gittest.h"
using namespace std;







MCTNode::MCTNode(MCTNode* parent,int x,int y)
{
	this->parent = parent;
	this->score = 0;
	this->search_time = 0;
	this->x=x,this->y=y;
}

double MCTNode::UCT()
{
	return 1.414 * sqrt(log(this->children_search_time) / this->search_time+0.0001) + 1.0 * this->win_time / this->search_time+0.01;
}

MCTNode* MCTNode:: expand(MCTNode* node) {
	//双距离选点
	struct xgznode** better_choice;
	MCTNode* new_node;
	for(int k=0;k<6;k++){

	new_node = new MCTNode(node,better_choice[k]->i,better_choice[k]->j);
	node->child.emplace_back(new_node);
	}
	return new_node;
}

MCTNode* MCTNode::select(MCTNode* node)
{
		coulor=1;
		while (!node->isTerminal()) {
			if (node->isAllExpand()) {
				node = node->bestChild(node, true);
			} else {
				node = node->expand(node);
//				return sub_node;
			}
			
			//补充棋盘
			Current_board[node->x][node->y]=1;
			coulor=-coulor;
		}
		
	
		
		
		return node;

}
//达到层数后随机落点
int MCTNode::simulate(){
	int x,y,wins=0;
	//通过第一颗子判断谁先手
	if( Current_board[1][2] == 1){//我方先手
		coulor=1;
	}
	x = rand() % (11) ;
	y = rand() % (11) ;
	for(int i=0;i<=0;i++){           //未添加次数
		
		while(Current_board[x][y]!=0){
			x = rand() % (11) ;
			y = rand() % (11) ;
		}
		Current_board[x][y]=coulor;
		coulor=-coulor;
	}
	//判断输赢？
//	is_win();
	
//	memcpy(Current_board,board,121*sizeof(int));
    return wins;
}

void MCTNode::backup(MCTNode* node, double reward) {
	while (node != nullptr) {
		node->search_time++;
		node->score+=reward;
		node = node->parent;
	}
}
int MCTNode::is_win()
{
	return 1;
}


MCTNode* MCTNode::bestChild(MCTNode* node, bool is_exploration) {
	
	
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


MCTNode* MCTNode:: monteCarloTreeSearch(int x,int y,int board[11][11]) {
	memcpy(Current_board,board,121*sizeof(int));
	MCTNode* root = new MCTNode(nullptr,x,y);
	
	
	MCTNode* expand_node = root->select(root);
	expand_node->win_time+=expand_node->simulate();
	double reward = UCT(expand_node);
	backup(expand_node, reward);
	
	
	Node* best_next_node = bestChild(node, false);
	return best_next_node;
}
