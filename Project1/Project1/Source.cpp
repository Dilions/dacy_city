// more.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "atltypes.h"

LRESULT CALLBACK WinSunProc
(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

int WINAPI WinMain
(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	WNDCLASS wndcls;

	wndcls.cbClsExtra = 0; 
	wndcls.cbWndExtra = 0;

	//ָ�����ڱ���ɫ
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//���ù����ʽ
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);
	//����ͼ����ʽ
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);
	wndcls.hInstance = hInstance;  // ָ������ʵ����� ?
	wndcls.lpfnWndProc = WinSunProc; //ָ�� ���ں�������������������
	//����������
	wndcls.lpszClassName = "Visual C++ Game";

	wndcls.lpszMenuName = NULL;  //�˵�
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndcls);  //ע�ᴰ����
	HWND hwnd;  //�������ھ��

	hwnd = CreateWindow  /*�������ڣ�������Ĵ����ǲ�����ʾ��*/
	(/*��ע�ᴰ���������*//*���ڱ���*//*���ڷ��*/
		"Visual C++ Game", "Visual C++��Ϸ����", WS_OVERLAPPEDWINDOW,
		/*����λ�õĺ�����*//*����λ�õ�������*//*���ڵĿ��*//*���ڵĸ߶�*/
		200, 200, 600, 400, NULL, NULL,
		hInstance, NULL);  //ʵ�����

		//������������ʾ����

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);  //������ʾ
/*��ʼ��������ɺ�WinMain������ν����Ϣѭ��*/
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);//ת��������Ϣ//������Ϣ
	}
	return 0;
}


/*���ں��������ں���ͨ������switch/case��ʽ�ж���Ϣ�����࣬

�Ծ������÷�ʽ���������Ǳ�Windowsϵͳ�����õģ���������һ��call back ����*/

/****** ******************************** **********************53 */
LRESULT CALLBACK WinSunProc(
	HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)/*���ھ��*//*��Ϣ*//*����1*//*����2*/
{
	char szStr[64] = { 0 };
	HDC hdc;  /*����DC�豸*/
	switch (uMsg)/*�ж���Ϣ����*/
	{
	case WM_PAINT:  /*���´�����Ϣ*/

		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps); /*�õ��豸 hDC*/
		TextOut(hdc, 200, 0, "Visual C++��Ϸ����", strlen("Visual C++��Ϸ����"));
		EndPaint(hwnd, &ps); break;

	case WM_LBUTTONDOWN:

		//		CPoint m_mouse;
		//		GetCursorPos(&m_mouse);
		POINT pt; GetCursorPos(&pt); //printf("%ld %ld\n", pt.x, pt.y);
		hdc = GetDC(hwnd);
		sprintf_s(szStr, "%ld %ld���λ��\r", pt.x, pt.y);
		TextOut(hdc, 100, 50, szStr, strlen(szStr));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_KEYUP:
		hdc = GetDC(hwnd);
		sprintf_s(szStr, "%d �����ͷ�\r", wParam);
		TextOut(hdc, 100, 50, szStr, strlen(szStr));
		ReleaseDC(hwnd,hdc);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		sprintf_s(szStr, "%d ��������\r", wParam);
		TextOut(hdc, 100, wParam, szStr, strlen(szStr));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_CLOSE:  /*�������رհ�ťʱ�������ر���Ϣ*/

		if (IDYES == MessageBox(hwnd, "�Ƿ���Ľ��� ? ", "��Ϸ����", MB_YESNO))
		{
			DestroyWindow(hwnd); /*���� ��ȷ������ť�����ٴ���*/
		}
		break;

	case WM_DESTROY:  /*���ٴ�����Ϣ*/

		PostQuitMessage(0);  /*�˳�����*/break;
	default:
		//��default:���������De fWi ndowProc, ����Windows�ڲ�Ĭ�ϵ���Ϣ������
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

