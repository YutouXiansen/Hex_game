#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include<algorithm>

using namespace std;

#define inf 500

const int SIZE1 = 15;
const int RealSIZE = 13;
int board1[RealSIZE][RealSIZE] = { 0 };//本方1，对方-1，空白0  // [A][1]

struct xgznode
{
	int i;
	int j;
	int distance;
};

bool  operator > (xgznode a, xgznode b)
{
	if (a.distance > b.distance)
		return true;
	else
		return false;
}

vector <xgznode> redneedsort;
vector <xgznode> buleneedsort;

int** myred_twodis_bule_to_A0(int** board1);    // red = 1    blue = -1
int** myred_twodis_bule_to_A10(int** board1);
int** myred_twodis_red_to_A0(int** board1);
int** myred_twodis_red_to_A10(int** board1);
int** mybule_twodis_bule_to_A0(int** board1);   // red = -1    blue = 1
int** mybule_twodis_bule_to_A10(int** board1);
int** mybule_twodis_red_to_A0(int** board1);
int** mybule_twodis_red_to_A10(int** board1);
int findseconddis(int i, int j,int flag,int** dis);      //flag = 1  ---> count 1
void make_real(int** board);
void redsort(int** dis_red);
void bulesort(int** dis_bule);
int** myred_toget_twodis_red(int** board1);
int** myred_toget_twodis_bule(int** board1);
int** mybule_toget_twodis_bule(int** board1);
int** mybule_toget_twodis_red(int** board1);
int getpot();
