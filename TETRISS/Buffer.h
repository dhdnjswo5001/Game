#pragma once
#include<Windows.h>
#define BufferX 100
#define BufferY 100
HANDLE hBuffer[2];  //���� �ڵ�
int nScreenIndex;   //���� ���� ���۰� ���� ����

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
	Sleep(33);  //�ε巯�� �ø����� ���� 0.033���� ������(����� 1�ʿ� 33���� �������� �׸��� �� �� ���� �ε巴�� �ν��ϰ� �մϴ�. �׷��� 0.033��)
	SetConsoleActiveScreenBuffer(hBuffer[nScreenIndex]);    //���۸� Ȱ���� �����ν� ȭ�鿡 ������ ������ �ѹ��� ���
	nScreenIndex = !nScreenIndex;   //���� ���� ����
}
//���۾��� �Լ�
void WriteBuffer(int x, int y, char* str)
{
	DWORD dw;   //��ǥ�� �����ϱ� ���� ����ä�� ����.
	COORD CursorPosition = { x, y };    //��ǥ ����
	SetConsoleCursorPosition(hBuffer[nScreenIndex], CursorPosition);    //��ǥ �̵�
	WriteFile(hBuffer[nScreenIndex], str, strlen(str), &dw, NULL);    //���ۿ� ��
}
//���ۻ���
void CreateBuffer()
{
	COORD size = { BufferX, BufferY }; //������ ũ�� ���� ����ä
	SMALL_RECT rect; //â ũ�� ���� ����ü
	rect.Left = 0;
	rect.Right = BufferX - 1;
	rect.Top = 0;
	rect.Bottom = BufferY - 1;
	//���۸� �����ϱ� ���� ������ ũ��� â�� ũ�⸦ ������ ����ü COORD�� SMALL_RECT�� �������ְ� ���ϴ� ũ�⸦ ���� ���� �����Ͻø� �˴ϴ�.

	//ù��° ���� ����
	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //���� ����
	SetConsoleScreenBufferSize(hBuffer[0], size); //�ܼ� ������ ũ�� ����
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect); //�ܼ� â�� ũ�� ����

//�ι�° ���� ����
	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); //���� ����
	SetConsoleScreenBufferSize(hBuffer[1], size); //�ܼ� ������ ũ�� ����
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect); //�ܼ� â�� ũ�� ����
}
