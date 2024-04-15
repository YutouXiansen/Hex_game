#include "Hexxgz.h"

void make_real(int** board)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			board1[i + 1][j + 1] = board[i][j];
		}
	}
	return;
}

int** myred_twodis_bule_to_A0(int** board1) // red = 1    blue = -1
{
	for (int i = 0; i < 13; i++)
	{
		board1[0][i] = 1;
		board1[12][i] = 1;
		board1[i][0] = -1;
		board1[i][12] = -1;
	}
	int** dis = new int* [RealSIZE];
	for (int i = 0; i < RealSIZE; i++)
	{
		dis[i] = new int[RealSIZE];
	}
	fill(dis, dis + RealSIZE * RealSIZE, 128);
	for (int i = 1; i <= 11; i++)
	{
		if (board1[i][1] == -1)
		{
			dis[i][1] = 0;
		}
		else if (board1[i][1] == 0)
		{
			dis[i][1] = 1;
		}
		else
		{
			dis[i][1] = inf;
		}
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			if (board1[i][j] == -1)
			{
				dis[i][j] = 0;
			}
			if (board1[i][j] == 1)
			{
				dis[i][j] = inf;
			}
		}
	}
	int flag = 0;
	while (1)
	{
		for (int i = 1; i <= 11; i++)
		{
			for (int j = 1; j <= 11; j++)
			{
				int distemp = findseconddis(i, j, -1, dis);
				if (distemp != dis[i][j])
				{
					flag = 1;
					dis[i][j] = distemp;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return dis;
}

int** myred_twodis_bule_to_A10(int** board1)  // red = 1    blue = -1
{
	for (int i = 0; i < 13; i++)
	{
		board1[0][i] = 1;
		board1[12][i] = 1;
		board1[i][0] = -1;
		board1[i][12] = -1;
	}
	int** dis = new int* [RealSIZE];
	for (int i = 0; i < RealSIZE; i++)
	{
		dis[i] = new int[RealSIZE];
	}
	fill(dis, dis + RealSIZE * RealSIZE, 128);
	for (int i = 1; i <= 11; i++)
	{
		if (board1[i][11] == -1)
		{
			dis[i][11] = 0;
		}
		else if (board1[i][11] == 0)
		{
			dis[i][11] = 1;
		}
		else
		{
			dis[i][11] = inf;
		}
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			if (board1[i][j] == -1)
			{
				dis[i][j] = 0;
			}
			if (board1[i][j] == 1)
			{
				dis[i][j] = inf;
			}
		}
	}
	int flag = 0;
	while (1)
	{
		for (int i = 11; i > 0; i--)
		{
			for (int j = 11; j > 0; j--)
			{
				int distemp = findseconddis(i, j, -1, dis);
				if (distemp != dis[i][j])
				{
					flag = 1;
					dis[i][j] = distemp;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return dis;
}

int** myred_twodis_red_to_A0(int** board1) // red = 1    blue = -1
{
	for (int i = 0; i < 13; i++)
	{
		board1[0][i] = 1;
		board1[12][i] = 1;
		board1[i][0] = -1;
		board1[i][12] = -1;
	}
	int** dis = new int* [RealSIZE];
	for (int i = 0; i < RealSIZE; i++)
	{
		dis[i] = new int[RealSIZE];
	}
	fill(dis, dis + RealSIZE * RealSIZE, 128);
	for (int i = 1; i <= 11; i++)
	{
		if (board1[i][1] == -1)
		{
			dis[i][1] = 0;
		}
		else if (board1[i][1] == 0)
		{
			dis[i][1] = 1;
		}
		else
		{
			dis[i][1] = inf;
		}
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			if (board1[i][j] == -1)
			{
				dis[i][j] = 0;
			}
			if (board1[i][j] == 1)
			{
				dis[i][j] = inf;
			}
		}
	}
	int flag = 0;
	while (1)
	{
		for (int i = 1; i <= 11; i++)
		{
			for (int j = 1; j <= 11; j++)
			{
				int distemp = findseconddis(i, j, 1, dis);
				if (distemp != dis[i][j])
				{
					flag = 1;
					dis[i][j] = distemp;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return dis;
}

int** myred_twodis_red_to_A10(int** board1)  // red = 1    blue = -1
{
	for (int i = 0; i < 13; i++)
	{
		board1[0][i] = 1;
		board1[12][i] = 1;
		board1[i][0] = -1;
		board1[i][12] = -1;
	}
	int** dis = new int* [RealSIZE];
	for (int i = 0; i < RealSIZE; i++)
	{
		dis[i] = new int[RealSIZE];
	}
	fill(dis, dis + RealSIZE * RealSIZE, 128);
	for (int i = 1; i <= 11; i++)
	{
		if (board1[i][11] == -1)
		{
			dis[i][11] = 0;
		}
		else if (board1[i][11] == 0)
		{
			dis[i][11] = 1;
		}
		else
		{
			dis[i][11] = inf;
		}
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			if (board1[i][j] == -1)
			{
				dis[i][j] = 0;
			}
			if (board1[i][j] == 1)
			{
				dis[i][j] = inf;
			}
		}
	}
	int flag = 0;
	while (1)
	{
		for (int i = 11; i > 0; i--)
		{
			for (int j = 11; j > 0; j--)
			{
				int distemp = findseconddis(i, j, 1, dis);
				if (distemp != dis[i][j])
				{
					flag = 1;
					dis[i][j] = distemp;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return dis;
}

int** mybule_twodis_bule_to_A0(int** board1) // red = -1    blue = 1
{
	for (int i = 0; i < 13; i++)
	{
		board1[0][i] = -1;
		board1[12][i] = -1;
		board1[i][0] = 1;
		board1[i][12] = 1;
	}
	int** dis = new int* [RealSIZE];
	for (int i = 0; i < RealSIZE; i++)
	{
		dis[i] = new int[RealSIZE];
	}
	fill(dis, dis + RealSIZE * RealSIZE, 128);
	for (int i = 1; i <= 11; i++)
	{
		if (board1[i][1] == -1)
		{
			dis[i][1] = 0;
		}
		else if (board1[i][1] == 0)
		{
			dis[i][1] = 1;
		}
		else
		{
			dis[i][1] = inf;
		}
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			if (board1[i][j] == -1)
			{
				dis[i][j] = 0;
			}
			if (board1[i][j] == 1)
			{
				dis[i][j] = inf;
			}
		}
	}
	int flag = 0;
	while (1)
	{
		for (int i = 1; i <= 11; i++)
		{
			for (int j = 1; j <= 11; j++)
			{
				int distemp = findseconddis(i, j, 1, dis);
				if (distemp != dis[i][j])
				{
					flag = 1;
					dis[i][j] = distemp;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return dis;
}

int** mybule_twodis_bule_to_A10(int** board1)  // red = -1    blue = 1
{
	for (int i = 0; i < 13; i++)
	{
		board1[0][i] = -1;
		board1[12][i] = -1;
		board1[i][0] = 1;
		board1[i][12] = 1;
	}
	int** dis = new int* [RealSIZE];
	for (int i = 0; i < RealSIZE; i++)
	{
		dis[i] = new int[RealSIZE];
	}
	fill(dis, dis + RealSIZE * RealSIZE, 128);
	for (int i = 1; i <= 11; i++)
	{
		if (board1[i][11] == -1)
		{
			dis[i][11] = 0;
		}
		else if (board1[i][11] == 0)
		{
			dis[i][11] = 1;
		}
		else
		{
			dis[i][11] = inf;
		}
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			if (board1[i][j] == -1)
			{
				dis[i][j] = 0;
			}
			if (board1[i][j] == 1)
			{
				dis[i][j] = inf;
			}
		}
	}
	int flag = 0;
	while (1)
	{
		for (int i = 11; i > 0; i--)
		{
			for (int j = 11; j > 0; j--)
			{
				int distemp = findseconddis(i, j, 1, dis);
				if (distemp != dis[i][j])
				{
					flag = 1;
					dis[i][j] = distemp;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return dis;
}

int** mybule_twodis_red_to_A0(int** board1) // red = -1    blue = 1
{
	for (int i = 0; i < 13; i++)
	{
		board1[0][i] = -1;
		board1[12][i] = -1;
		board1[i][0] = 1;
		board1[i][12] = 1;
	}
	int** dis = new int* [RealSIZE];
	for (int i = 1; i <= 11; i++)
	{
		dis[i] = new int[RealSIZE];
	}
	fill(dis, dis + RealSIZE * RealSIZE, 128);
	for (int i = 1; i <= 11; i++)
	{
		if (board1[i][1] == -1)
		{
			dis[i][1] = 0;
		}
		else if (board1[i][1] == 0)
		{
			dis[i][1] = 1;
		}
		else
		{
			dis[i][1] = inf;
		}
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			if (board1[i][j] == -1)
			{
				dis[i][j] = 0;
			}
			if (board1[i][j] == 1)
			{
				dis[i][j] = inf;
			}
		}
	}
	int flag = 0;
	while (1)
	{
		for (int i = 1; i <= 11; i++)
		{
			for (int j = 1; j <= 11; j++)
			{
				int distemp = findseconddis(i, j, -1, dis);
				if (distemp != dis[i][j])
				{
					flag = 1;
					dis[i][j] = distemp;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return dis;
}

int** mybule_twodis_red_to_A10(int** board1)  // red = -1    blue = 1
{
	for (int i = 0; i < 13; i++)
	{
		board1[0][i] = -1;
		board1[12][i] = -1;
		board1[i][0] = 1;
		board1[i][12] = 1;
	}
	int** dis = new int* [RealSIZE];
	for (int i = 0; i < RealSIZE; i++)
	{
		dis[i] = new int[RealSIZE];
	}
	fill(dis, dis + RealSIZE * RealSIZE, 128);
	for (int i = 1; i <= 11; i++)
	{
		if (board1[i][11] == -1)
		{
			dis[i][11] = 0;
		}
		else if (board1[i][11] == 0)
		{
			dis[i][11] = 1;
		}
		else
		{
			dis[i][11] = inf;
		}
	}
	for (int i = 1; i <= 11; i++)
	{
		for (int j = 1; j <= 11; j++)
		{
			if (board1[i][j] == -1)
			{
				dis[i][j] = 0;
			}
			if (board1[i][j] == 1)
			{
				dis[i][j] = inf;
			}
		}
	}
	int flag = 0;
	while (1)
	{
		for (int i = 11; i > 0; i--)
		{
			for (int j = 11; j > 0; j--)
			{
				int distemp = findseconddis(i, j, -1, dis);
				if (distemp != dis[i][j])
				{
					flag = 1;
					dis[i][j] = distemp;
				}
			}
		}
		if (flag == 0)
			break;
	}
	return dis;
}

int findseconddis(int i, int j, int flag, int** dis)
{
	vector <xgznode*> aim;
	vector <xgznode*> temp;
	xgznode* t1 = new xgznode;
	t1->i = i;
	t1->j = j;
	temp.push_back(t1);
	int newflag = 0;
	while (newflag == 1)
	{
		newflag == 0;
		xgznode* a = temp.back();
		if (a->j - 1 >= 0 && board1[a->i][a->j - 1] == 0)
		{
			int s1flag = 0;
			for (int i = 0; i < aim.size(); i++)
			{
				if (aim[i]->i == a->i && aim[i]->j == a->j - 1)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i;
				t11->j = a->j - 1;
				aim.push_back(t11);
			}
		}
		else if (a->j - 1 >= 0 && board1[a->i][a->j - 1] == flag)
		{
			int s1flag = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i]->i == a->i && temp[i]->j == a->j - 1)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i;
				t11->j = a->j - 1;
				temp.push_back(t11);
				newflag = 1;
			}
		}

		if (a->j + 1 < 13 && board1[a->i][a->j + 1] == 0)
		{
			int s1flag = 0;
			for (int i = 0; i < aim.size(); i++)
			{
				if (aim[i]->i == a->i && aim[i]->j == a->j + 1)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i;
				t11->j = a->j + 1;
				aim.push_back(t11);
			}
		}
		else if (a->j + 1 < 13 && board1[a->i][a->j + 1] == flag)
		{
			int s1flag = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i]->i == a->i && temp[i]->j == a->j + 1)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i;
				t11->j = a->j + 1;
				temp.push_back(t11);
				newflag = 1;
			}
		}

		if (a->i - 1 >= 0 && board1[a->i - 1][a->j] == 0)
		{
			int s1flag = 0;
			for (int i = 0; i < aim.size(); i++)
			{
				if (aim[i]->i == a->i - 1 && aim[i]->j == a->j)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i - 1;
				t11->j = a->j;
				aim.push_back(t11);
			}
		}
		else if (a->i - 1 >= 0 && board1[a->i - 1][a->j] == flag)
		{
			int s1flag = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i]->i == a->i - 1 && temp[i]->j == a->j)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i - 1;
				t11->j = a->j;
				temp.push_back(t11);
				newflag = 1;
			}
		}

		if (a->i + 1 < 13 && board1[a->i + 1][a->j] == 0)
		{
			int s1flag = 0;
			for (int i = 0; i < aim.size(); i++)
			{
				if (aim[i]->i == a->i + 1 && aim[i]->j == a->j)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i + 1;
				t11->j = a->j;
				aim.push_back(t11);
			}
		}
		else if (a->i + 1 < 13 && board1[a->i + 1][a->j] == flag)
		{
			int s1flag = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i]->i == a->i + 1 && temp[i]->j == a->j)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i + 1;
				t11->j = a->j;
				temp.push_back(t11);
				newflag = 1;
			}
		}

		if (a->i + 1 < 13 && a->j - 1 >= 0 && board1[a->i + 1][a->j - 1] == 0)
		{
			int s1flag = 0;
			for (int i = 0; i < aim.size(); i++)
			{
				if (aim[i]->i == a->i + 1 && aim[i]->j == a->j - 1)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i + 1;
				t11->j = a->j - 1;
				aim.push_back(t11);
			}
		}
		else if (a->i + 1 < 13 && a->j - 1 >= 0 && board1[a->i + 1][a->j - 1] == flag)
		{
			int s1flag = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i]->i == a->i + 1 && temp[i]->j == a->j - 1)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i + 1;
				t11->j = a->j - 1;
				temp.push_back(t11);
				newflag = 1;
			}
		}

		if (a->i - 1 >= 0 && a->j + 1 < 13 && board1[a->i - 1][a->j + 1] == 0)
		{
			int s1flag = 0;
			for (int i = 0; i < aim.size(); i++)
			{
				if (aim[i]->i == a->i - 1 && aim[i]->j == a->j + 1)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i - 1;
				t11->j = a->j + 1;
				aim.push_back(t11);
			}
		}
		else if (a->i - 1 >= 0 && a->j + 1 < 13 && board1[a->i - 1][a->j + 1] == flag)
		{
			int s1flag = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i]->i == a->i - 1 && temp[i]->j == a->j + 1)
				{
					s1flag = 1;
				}
			}
			if (s1flag == 0)
			{
				xgznode* t11 = new xgznode;
				t11->i = a->i - 1;
				t11->j = a->j + 1;
				temp.push_back(t11);
				newflag = 1;
			}
		}
	}
	for (int k = 0; k < aim.size(); k++)
	{
		aim[k]->distance = dis[aim[k]->i][aim[k]->j];
	}

	xgznode* min1 = aim[0];
	xgznode* min2 = aim[1];
	if (*min1 > *min2)
	{
		min1 = aim[1];
		min2 = aim[0];
	}
	for (int k = 2; k < aim.size(); k++)
	{
		if (*min1 > *aim[k])
		{
			min2 = min1;
			min1 = aim[k];
		}
		if (*aim[k] > *min1 && *min2 > *aim[k])
		{
			min2 = aim[k];
		}
	}
	return min2->distance + 1;
}

int** myred_toget_twodis_red(int** board1)
{
	int** twodis_red = new int* [11];
	for (int i = 0; i < 11; i++)
	{
		twodis_red[i] = new int[11];
	}
	int** dis1 = myred_twodis_red_to_A0(board1);
	int** dis2 = myred_twodis_red_to_A10(board1);
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			twodis_red[i][j] = dis1[i + 1][j + 1] + dis2[i + 1][j + 1];
		}
	}
	return twodis_red;
}

int** myred_toget_twodis_bule(int** board1)
{
	int** twodis_bule = new int* [11];
	for (int i = 0; i < 11; i++)
	{
		twodis_bule[i] = new int[11];
	}
	int** dis1 = myred_twodis_bule_to_A0(board1);
	int** dis2 = myred_twodis_bule_to_A10(board1);
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			twodis_bule[i][j] = dis1[i + 1][j + 1] + dis2[i + 1][j + 1];
		}
	}
	return twodis_bule;
}

int** mybule_toget_twodis_bule(int** board1)
{
	int** twodis_bule = new int* [11];
	for (int i = 0; i < 11; i++)
	{
		twodis_bule[i] = new int[11];
	}
	int** dis1 = mybule_twodis_bule_to_A0(board1);
	int** dis2 = mybule_twodis_bule_to_A10(board1);
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			twodis_bule[i][j] = dis1[i + 1][j + 1] + dis2[i + 1][j + 1];
		}
	}
	return twodis_bule;
}

int** mybule_toget_twodis_red(int** board1)
{
	int** twodis_red = new int* [11];
	for (int i = 0; i < 11; i++)
	{
		twodis_red[i] = new int[11];
	}
	int** dis1 = mybule_twodis_red_to_A0(board1);
	int** dis2 = mybule_twodis_red_to_A10(board1);
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			twodis_red[i][j] = dis1[i + 1][j + 1] + dis2[i + 1][j + 1];
		}
	}
	return twodis_red;
}

void redsort(int** twodis_red)
{
	for (int i = 1; i < 13; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			xgznode temp;
			temp.i = i;
			temp.j = j;
			temp.distance = twodis_red[i][j];
			redneedsort.push_back(temp);
		}
	}
	sort(redneedsort.begin(), redneedsort.end(), greater<xgznode>());
}

void bulesort(int** twodis_bule)
{
	for (int i = 1; i < 13; i++)
	{
		for (int j = 1; j < 13; j++)
		{
			xgznode temp;
			temp.i = i;
			temp.j = j;
			temp.distance = twodis_bule[i][j];
			buleneedsort.push_back(temp);
		}
	}
	sort(buleneedsort.begin(), buleneedsort.end(), greater<xgznode>());
}

int getpot()
{
	int redmin = redneedsort.back().distance;
	int bulemin = buleneedsort.back().distance;
	int 
}