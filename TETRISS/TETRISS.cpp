﻿// Tetris.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"

#include <iostream>
#include<time.h>
#include<string>
#include <vector>
#include "Shape.h"
#include<Windows.h>
#include<conio.h>
#include <cstdlib>
#define tileXLen 15
#define tileYLen 25
#define start_endLine 5
#define maxScoreCount 6
using namespace std;
//Tile구조체
//Controlled -> 현재 내가 컨트롤하고 있는 블록과 아닌 블록 나눠줌
typedef struct Tile
{
	bool Controlled = true;
	string tileST = "";
}Tile;


Tile tileArry[tileYLen][tileXLen];
int score;
//Score가 표시되는 줄
int scoreRenderLine = 2;
//Score Render버퍼
char Score[maxScoreCount];
// 내려가는 동안 Sleeptime -> 클수록 느려짐
int DownPauseTime = 50;

//스코어 출력을 위해 int에서 string으로 바꿔줌(재귀함수 이용)
void Int2string(int _score,int k)
{
	if (_score<10)
	{
		return;
	}
	_score /= 10;
	Int2string(_score,++k);
	Score[maxScoreCount-k] =char( _score%10 +48);
	
}

// 내가 조종하는 타일이 움직일때 이전의 타일을 배열에서 지워주는 함수
void tileContentInit()
{
	for (int i = 1; i < tileYLen-1; i++)
	{
		for (int j = 1; j < tileXLen-1; j++)
		{
			if (tileArry[i][j].Controlled==true && tileArry[i][j].tileST == "■" )
			{
				tileArry[i][j].tileST = "  ";

			}
			
		}
		// 배열에 스코어 입력
		if (i == scoreRenderLine)
		{
			int Scoreindex = 0;
			for (int k = 0; k < maxScoreCount; k++)
			{
				if (Scoreindex >= maxScoreCount) { break; }
				for (int p = 0; p < 1; p++)
				{
					tileArry[i][(tileXLen / 2) + k].tileST[p] =Score[Scoreindex];
					Scoreindex++;

				}
			}
		}
	}
}
// 스코어버퍼 처음에 0으로 초기화 해줌
void scoreInit()
{
	score = 0;
	for (int i = 0; i < maxScoreCount; i++)
	{
		Score[i] = '0';
	}
	Score[0] = ' ';
	Score[1] = '0';
}
// 타일배열 초기화
void tileArryInit()
{
	for (int i = 0; i < tileYLen; i++)
	{
		for (int j = 0; j < tileXLen; j++)
		{
			tileArry[i][j].tileST = "  ";
		}
	}
}

// 해당 좌표 타일 설정
void tileSet(int x, int y,bool isControlled)
{
	tileArry[y][x].tileST = "■";
	tileArry[y][x].Controlled = isControlled;

}
// 초기 맵세팅
void maptileArrySetting()
{
	tileArryInit();
	scoreInit();
	for (int i = 0; i < tileYLen; i++)
	{
		for (int j = 0; j < tileXLen; j++)
		{
			if ((i==0 || i== tileYLen-1) || (j==0 || j==tileXLen-1))
			{
				tileSet(j, i,false);
			}	
		}
	}
}
// 타일배열에 있는 문자를 그대로 그려주는 함수
void Rendering()
{
	system("cls");
	for (int i = 0; i < tileYLen; i++)
	{
		for (int j = 0; j < tileXLen; j++)
		{
			cout << tileArry[i][j].tileST;
		}
		cout << endl;
	}
}

// 주변에 Controlled가 false인 타일이 없으면 내가 조종하는 모형을 스핀하게 하는 함수
void Spin(Shape* Shapes)
{

	Shapes->SetSpindirvec(true);
	bool blocked = false;
	for (int i = 0; i < Shapes->vec.size(); i++)
	{
		if (tileArry[Shapes->vec[i].second][Shapes->vec[i].first].Controlled==false)
		{
			blocked = true;
			Shapes->SetSpindirvec(true);
			break;
		}
	}
	if (blocked == false)
	{
		for (int i = 0; i < Shapes->vec.size(); i++)
		{
			tileSet(Shapes->vec[i].first, Shapes->vec[i].second, true);
		}
	}
	

}

// 컨트롤하는 모형이 안착했으면 더이상 컨트롤 못하게 하는 함수
void Controlled_outShape(Shape* Shapes)
{
	for (int i = 0; i < Shapes->vec.size(); i++)
	{
		tileArry[Shapes->vec[i].second][Shapes->vec[i].first].Controlled = false;
		tileArry[Shapes->vec[i].second][Shapes->vec[i].first].tileST = "■";
	}
}

// 컨트롤모형이 안착할때마다 채워진 타일 없는지 체크 후 있으면 스코어 올리고 전체 타일 내려줌
void CheckScoreLine(int topline)
{
	for (int i = tileYLen-2; i >= 1; i--)
	{
		bool ischeck = true;
		for (int j = 1; j < tileXLen - 1; j++)
		{
			if (tileArry[i][j].Controlled == true && tileArry[i][j].tileST == "  ")
			{
				ischeck = false;
				break;
			}
		}
		if (ischeck==true)
		{
			score += 10;
			Int2string(score, 1);
			Score[maxScoreCount - 1] = char(score % 10 + 48);
			for (int k = i; k >=start_endLine; k--)
				{
				for (int m = 1; m < tileXLen-1; m++)
					{
						tileArry[k+1][m] = tileArry[k][m];
					}
				}
			i = tileYLen - 2;
		}
	}
}

// 게임오버
void GameOver()
{
	system("cls");
	cout << "END!" << endl;
	Sleep(100000);
	return;
}

// 해당 좌표에 원하는 모형 만들어줌
Shape* MakeShape(int x, int y, Shapetype type)
{
	Shape* Shapes = new Shape(5, 5,type);

	for (int i = 0; i < Shapes->vec.size(); i++)
	{
		tileSet(Shapes->vec[i].first, Shapes->vec[i].second,true);
	}
	return Shapes;
}

//컨트롤 모형의 움직임 함수
void MoveShape(Shape* Shapes)
{
	int key;
	while (true)
	{
		bool canMove = true;
		Rendering();
		tileContentInit();
		if (_kbhit())
		{
			key = _getch();
			if (key == 224)
			{
				key = _getch();
				// 키가 눌리면
				if (key == 'M'  )
				{
					// 갈수있는지 검사
					for (int i = 0; i < Shapes->vec.size(); i++)
					{
						if (tileArry[Shapes->vec[i].second][Shapes->vec[i].first + 1].Controlled == false)
						{
							canMove = false;
							break;
						}
					}
					//컨트롤 모형 벡터 움직이기
					if (canMove==true)
					{
						for (int i = 0; i < Shapes->vec.size(); i++)
						{
							tileSet(Shapes->vec[i].first++, Shapes->vec[i].second, true);
						}
					}
					
				}
				// 키가 눌리면
				else if (key == 'K')
				{
					// 갈수있는지 검사
					for (int i = 0; i < Shapes->vec.size(); i++)
					{
						if (tileArry[Shapes->vec[i].second][Shapes->vec[i].first - 1].Controlled == false)
						{
							canMove = false;
							break;
						}
					}
					// 모형벡터 움직이기
					if (canMove == true)
					{
						for (int i = 0; i < Shapes->vec.size(); i++)
						{
							tileSet(Shapes->vec[i].first--, Shapes->vec[i].second, true);
						}
					}
					
				}
				// 위쪽 방향키 누르면 스핀
				else if (key=='H')
				{
					Spin(Shapes);
				}
				else if (key = 'P')
				{

				}
			}
		}	
		else
		{
			// 내려가는 속도 조절
			Sleep(DownPauseTime);


			for (int i = 0; i < Shapes->vec.size(); i++)
			{
				// 모형이 안착했을때 
				if (tileArry[Shapes->vec[i].second + 1][Shapes->vec[i].first].Controlled == false)
				{
					//쌓아진 모형의 위라인이 일정이상되면 게임오버
					int topline = Shapes->vec[i].second;
					if (topline<=start_endLine)
					{
						GameOver();
						return;
					}
					// 모형컨트롤 뺏기
					Controlled_outShape(Shapes);
					// 점수터트릴 라인 체크
					CheckScoreLine(topline);
					return;
				}
			}
			// 모형 밑으로 내리기
			for (int i = 0; i < Shapes->vec.size(); i++)
			{
				Shapes->vec[i].second += 1;
				tileSet(Shapes->vec[i].first, Shapes->vec[i].second, true);
			}
		}
	}
}
// 초기화 함수
void Start()
{
	maptileArrySetting();
}
// 계속되는 업데이트수행 함수
void Update()
{
	while (true)
	{
		// 랜덤한 모양의 모형생성
		int rannum = rand() % 4;
		Shape* Shape = MakeShape(start_endLine,0,(Shapetype)rannum );
		MoveShape(Shape);	
	}
}
int main()
{
	Start();
	Update();
}