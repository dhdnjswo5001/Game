#pragma once
#include<Windows.h>
#define BufferX 100
#define BufferY 100
HANDLE hBuffer[2];  //버퍼 핸들
int nScreenIndex;   //현재 선택 버퍼가 뭔지 저장

void Release()
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}
void BufferClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[nScreenIndex], ' ', BufferX * BufferY, Coor, &dw);
}
void ClippingBuffer()
{
	Sleep(33);  //부드러운 플리핑을 위한 0.033초의 딜레이(사람은 1초에 33장의 연속적인 그림을 볼 때 가장 부드럽게 인식하고 합니다. 그래서 0.033초)
	SetConsoleActiveScreenBuffer(hBuffer[nScreenIndex]);    //버퍼를 활성하 함으로써 화면에 버퍼의 내용을 한번에 출력
	nScreenIndex = !nScreenIndex;   //다음 버퍼 선택
}
//버퍼쓰기 함수
void WriteBuffer(int x, int y, char* str)
{
	DWORD dw;   //좌표를 저장하기 위한 구조채를 선언.
	COORD CursorPosition = { x, y };    //좌표 설정
	SetConsoleCursorPosition(hBuffer[nScreenIndex], CursorPosition);    //좌표 이동
	WriteFile(hBuffer[nScreenIndex], str, strlen(str), &dw, NULL);    //버퍼에 씀
}
//버퍼생성
void CreateBuffer()
{
	COORD size = { BufferX, BufferY }; //버퍼의 크기 관련 구조채
	SMALL_RECT rect; //창 크기 관련 구조체
	rect.Left = 0;
	rect.Right = BufferX - 1;
	rect.Top = 0;
	rect.Bottom = BufferY - 1;
	//버퍼를 생성하기 전에 버퍼의 크기와 창의 크기를 설정할 구조체 COORD와 SMALL_RECT를 선언해주고 원하는 크기를 위와 같이 선언하시면 됩니다.

	//첫번째 버퍼 생성
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //버퍼 생성
	SetConsoleScreenBufferSize(hBuffer[0], size); //콘솔 버퍼의 크기 설정
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect); //콘솔 창의 크기 설정

//두번째 버퍼 생성
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //버퍼 생성
	SetConsoleScreenBufferSize(hBuffer[1], size); //콘솔 버퍼의 크기 설정
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect); //콘솔 창의 크기 설정
}
