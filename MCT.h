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
	int Current_board[11][11];			//��ǰ���
	vector<MCTNode*> child;			//�ӽڵ㼯��
	MCTNode* parent;			//���ڵ㣬�Ӽ�����
	int score;				//����
	int search_time;			//��������
	int win_time;			//ʤ������
	int children_search_time;			//�����ӽڵ���������
public:
	MCTNode(MCTNode* parent, int parent_board[11][11]);
	//ѡ���ӽڵ㣬����ֵΪMCTNode*����
	MCTNode* select();
	//��չ�ýڵ㣬����ֵΪ��
	void expend();
	//ģ�⣬����ֵΪint���ͣ��ж���Ӯ
	int simulate();
	//�ж���Ӯ����
	int is_win();
	//���򴫲���ֺ���
	int back();
	//UCT����
	int UCT();
};