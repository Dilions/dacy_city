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

	//指定窗口背景色
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//设置光标样式
	wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);
	//设置图标样式
	wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);
	wndcls.hInstance = hInstance;  // 指定窗口实例句柄 ?
	wndcls.lpfnWndProc = WinSunProc; //指定 窗口函数，即窗口主处理函数
	//窗口类名称
	wndcls.lpszClassName = "Visual C++ Game";

	wndcls.lpszMenuName = NULL;  //菜单
	wndcls.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndcls);  //注册窗口类
	HWND hwnd;  //声明窗口句柄

	hwnd = CreateWindow  /*创建窗口，但这里的窗口是不会显示的*/
	(/*已注册窗口类的名称*//*窗口标题*//*窗口风格*/
		"Visual C++ Game", "Visual C++游戏开发", WS_OVERLAPPEDWINDOW,
		/*窗口位置的横坐标*//*窗口位置的纵坐标*//*窗口的宽度*//*窗口的高度*/
		200, 200, 600, 400, NULL, NULL,
		hInstance, NULL);  //实例句柄

		//在这里真正显示窗口

	ShowWindow(hwnd, SW_SHOWNORMAL);
	UpdateWindow(hwnd);  //更新显示
/*初始化工作完成后，WinMain进入所谓的消息循环*/
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);//转换键盘消息//分派消息
	}
	return 0;
}


/*窗口函数。窗口函数通常利用switch/case方式判断消息的种类，

以决定处置方式，由于其是被Windows系统所调用的，所以这是一种call back 函数*/

/****** ******************************** **********************53 */
LRESULT CALLBACK WinSunProc(
	HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)/*窗口句柄*//*消息*//*参数1*//*参数2*/
{
	char szStr[64] = { 0 };
	HDC hdc;  /*定义DC设备*/
	switch (uMsg)/*判断消息类型*/
	{
	case WM_PAINT:  /*更新窗口消息*/

		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps); /*得到设备 hDC*/
		TextOut(hdc, 200, 0, "Visual C++游戏开发", strlen("Visual C++游戏开发"));
		EndPaint(hwnd, &ps); break;

	case WM_LBUTTONDOWN:

		//		CPoint m_mouse;
		//		GetCursorPos(&m_mouse);
		POINT pt; GetCursorPos(&pt); //printf("%ld %ld\n", pt.x, pt.y);
		hdc = GetDC(hwnd);
		sprintf_s(szStr, "%ld %ld鼠标位置\r", pt.x, pt.y);
		TextOut(hdc, 100, 50, szStr, strlen(szStr));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_KEYUP:
		hdc = GetDC(hwnd);
		sprintf_s(szStr, "%d 按键释放\r", wParam);
		TextOut(hdc, 100, 50, szStr, strlen(szStr));
		ReleaseDC(hwnd,hdc);
		break;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		sprintf_s(szStr, "%d 按键按下\r", wParam);
		TextOut(hdc, 100, wParam, szStr, strlen(szStr));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_CLOSE:  /*当单击关闭按钮时，产生关闭消息*/

		if (IDYES == MessageBox(hwnd, "是否真的结束 ? ", "游戏开发", MB_YESNO))
		{
			DestroyWindow(hwnd); /*单击 “确定”按钮，销毁窗口*/
		}
		break;

	case WM_DESTROY:  /*销毁窗口消息*/

		PostQuitMessage(0);  /*退出程序*/break;
	default:
		//在default:处必须调用De fWi ndowProc, 这是Windows内部默认的消息处理函数
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

