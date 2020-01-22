#pragma once
#include<vector>
using namespace std;
// 모형 타입정의
enum Shapetype {Box, One, L, J};
// 모형클래스
 class Shape
{
public:
	// 각 스핀 방향에따른 벡터 설정
	vector<pair<int, int>>vec;
	vector<pair<int, int>>Upvec;
	vector<pair<int, int>>Leftvec;
	vector<pair<int, int>>Downvec;
	vector<pair<int, int>>Rightvec;
	vector<vector<pair<int, int>>> dirvec = {Upvec,Leftvec,Downvec,Rightvec};
	Shapetype _type;

	// 모형 기준좌표
	int POSX;
	int POSY;
	int currDir;
	
	void SetSpindirvec(bool left)
	{
		//0번째 벡터가 기준점
		POSX = vec[0].first;
		POSY = vec[0].second;

		if (left)
		{
			// 정방향 인덱스 증가
			(++currDir) %= 4;
		}
		else
		{
			// 반대방향 인덱스 증가
			if (currDir - 1 < 0) currDir = 3;
			currDir--;
		}
		// 타입에 따른 방향 벡터 설정
		switch (_type)
		{
		case Box:
			Upvec = { make_pair(POSX,POSY),make_pair(POSX + 1,POSY),make_pair(POSX,POSY + 1),make_pair(POSX + 1,POSY + 1) };
			Downvec = { make_pair(POSX,POSY),make_pair(POSX + 1,POSY),make_pair(POSX,POSY + 1),make_pair(POSX + 1,POSY + 1) };
			Leftvec = { make_pair(POSX,POSY),make_pair(POSX + 1,POSY),make_pair(POSX,POSY + 1),make_pair(POSX + 1,POSY + 1) };
			Rightvec = { make_pair(POSX,POSY),make_pair(POSX + 1,POSY),make_pair(POSX,POSY + 1),make_pair(POSX + 1,POSY + 1) };
			break;
		case One:
			Upvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY - 2),make_pair(POSX,POSY - 1),make_pair(POSX,POSY + 1) };
			Leftvec = { make_pair(POSX,POSY),make_pair(POSX - 2 ,POSY),make_pair(POSX - 1,POSY),make_pair(POSX + 1,POSY) };
			Downvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY - 2),make_pair(POSX,POSY - 1),make_pair(POSX,POSY + 1) };
			Rightvec = { make_pair(POSX,POSY),make_pair(POSX - 2 ,POSY),make_pair(POSX - 1,POSY),make_pair(POSX + 1,POSY) };
			break;
		case L:
			Upvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY - 1),make_pair(POSX + 1,POSY),make_pair(POSX + 2,POSY) };
			Leftvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY - 2),make_pair(POSX,POSY - 1),make_pair(POSX - 1,POSY) };
			Downvec = { make_pair(POSX,POSY),make_pair(POSX - 2 ,POSY),make_pair(POSX - 1,POSY),make_pair(POSX,POSY + 1) };
			Rightvec = { make_pair(POSX,POSY),make_pair(POSX + 1 ,POSY),make_pair(POSX,POSY + 1),make_pair(POSX,POSY + 2) };
			break;
		case J:
			Upvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY - 1),make_pair(POSX - 1 ,POSY),make_pair(POSX - 2,POSY) };
			Leftvec = { make_pair(POSX,POSY),make_pair(POSX - 1 ,POSY),make_pair(POSX,POSY + 1),make_pair(POSX,POSY + 2) };
			Downvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY + 1),make_pair(POSX + 1,POSY),make_pair(POSX + 2,POSY) };
			Rightvec = { make_pair(POSX,POSY),make_pair(POSX + 1 ,POSY),make_pair(POSX,POSY + 1),make_pair(POSX,POSY + 2) };
			break;
		default:
			break;
		}
		dirvec = { Upvec,Leftvec,Downvec,Rightvec };
		vec = dirvec[currDir];
	}
	Shape(int x, int y,Shapetype type)
	{
		// 생성자로써 초기 벡터 설정
		_type = type;
		POSX = x;
		POSY = y;
		currDir = 0;
		switch (type)
		{
		case Box:
			Upvec = { make_pair(POSX,POSY),make_pair(POSX + 1,POSY),make_pair(POSX,POSY + 1),make_pair(POSX + 1,POSY + 1) };
			Downvec = { make_pair(POSX,POSY),make_pair(POSX + 1,POSY),make_pair(POSX,POSY + 1),make_pair(POSX + 1,POSY + 1) };
			Leftvec = { make_pair(POSX,POSY),make_pair(POSX + 1,POSY),make_pair(POSX,POSY + 1),make_pair(POSX + 1,POSY + 1) };
			Rightvec = { make_pair(POSX,POSY),make_pair(POSX + 1,POSY),make_pair(POSX,POSY + 1),make_pair(POSX + 1,POSY + 1) };
			break;
		case One:
			Upvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY - 2),make_pair(POSX,POSY - 1),make_pair(POSX,POSY + 1) };
			Leftvec = { make_pair(POSX,POSY),make_pair(POSX-2 ,POSY),make_pair(POSX-1,POSY),make_pair(POSX+1,POSY) };
			Downvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY - 2),make_pair(POSX,POSY - 1),make_pair(POSX,POSY + 1) };
			Rightvec = { make_pair(POSX,POSY),make_pair(POSX - 2 ,POSY),make_pair(POSX - 1,POSY),make_pair(POSX + 1,POSY) };
			break;
		case L:
			Upvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY - 1),make_pair(POSX + 1,POSY),make_pair(POSX + 2,POSY) };
			Leftvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY-2),make_pair(POSX,POSY-1),make_pair(POSX - 1,POSY) };
			Downvec = { make_pair(POSX,POSY),make_pair(POSX-2 ,POSY),make_pair(POSX-1,POSY),make_pair(POSX,POSY + 1) };
			Rightvec = { make_pair(POSX,POSY),make_pair(POSX+1 ,POSY),make_pair(POSX,POSY+1),make_pair(POSX,POSY+2) };
			break;
		case J:
			Upvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY-1),make_pair(POSX-1 ,POSY),make_pair(POSX-2,POSY) };
			Leftvec = { make_pair(POSX,POSY),make_pair(POSX-1 ,POSY),make_pair(POSX,POSY+1),make_pair(POSX,POSY+2) };
			Downvec = { make_pair(POSX,POSY),make_pair(POSX ,POSY+1),make_pair(POSX+1,POSY),make_pair(POSX+2,POSY) };
			Rightvec = { make_pair(POSX,POSY),make_pair(POSX + 1 ,POSY),make_pair(POSX,POSY + 1),make_pair(POSX,POSY + 2) };
			break;
		default:
			break;
		}
		dirvec = { Upvec,Leftvec,Downvec,Rightvec };
		vec = dirvec[currDir];
	}
	
};
