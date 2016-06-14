#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<conio.h>
#include<limits.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define ID_BEEP 1
#define ID_QUIT 2

char s[100], t[100];							// s -> k               si         t -> l
char c[100];
int k = 0, prima = 0, l = 0;

HWND HwndLabel1, HwndLabel2, HwndLabel3;
HWND but1, but2, but3, but4, but5, but6, but7, but8, but9, first, op, ad, prod,but0;



void adunare(HWND hwnd, char num1[], char num2[])
{
	int a[255], b[255], sum[255];
	int ac = 0, bc = 0, sc = 0;
	int reminder = 0, i;
	char *pa, *pb,*q;


	pa = num1; //pointer to first number
	pb = num2; //pointer to second number

	//storing  first string number in the integer array
	while (*pa) {  //loop while run untill it get null character
		a[ac++] = *pa++ - 48;  //48 is ASCII value of character zero
	}

	//storing  first string number in the integer array
	while (*pb) {
		b[bc++] = *pb++ - 48;
	}

	//additin of two numbers
	if (ac<bc) {
		for (i = ac; i > 0; i--) {
			sum[sc++] = ((a[i - 1] + b[--bc]) + reminder) % 10;
			reminder = ((a[i - 1] + b[bc]) + reminder) / 10;
		}
		while (bc > 0) {
			sum[sc++] = b[--bc] + reminder;
			reminder = 0;
		}
	}
	else {
		for (i = bc; i > 0; i--) {
			sum[sc++] = ((b[i - 1] + a[--ac]) + reminder) % 10;
			reminder = ((b[i - 1] + a[ac]) + reminder) / 10;
		}
		if (ac == 0 && reminder == 1)
			sum[sc++] = reminder;
		while (ac > 0) {
			sum[sc++] = a[--ac] + reminder;
			reminder = 0;
		}
	}



	printf("Adunarea : ");
	for (i = sc-1; i>=0; i--) {
		c[i] = sum[i] + '0';
		
		
	}
	_strrev(c);
	MessageBox(hwnd, c, "Adunarea", MB_OK);

	CreateWindow("STATIC", c,
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		355, 355, 140, 30,
		hwnd, NULL, NULL, NULL);
}



char *multiply(char a[], char b[]) {
	static char mul[1000];
	char c[1000];
	char temp[1000];
	int la, lb;
	int i, j, k = 0, x = 0, y;
	long int r = 0;
	long sum = 0;
	la = strlen(a) - 1;
	lb = strlen(b) - 1;

	for (i = 0; i <= la; i++) {
		a[i] = a[i] - 48;
	}

	for (i = 0; i <= lb; i++) {
		b[i] = b[i] - 48;
	}

	for (i = lb; i >= 0; i--) {
		r = 0;
		for (j = la; j >= 0; j--) {
			temp[k++] = (b[i] * a[j] + r) % 10;
			r = (b[i] * a[j] + r) / 10;
		}
		temp[k++] = r;
		x++;
		for (y = 0; y<x; y++) {
			temp[k++] = 0;
		}
	}

	k = 0;
	r = 0;
	for (i = 0; i<la + lb + 2; i++) {
		sum = 0;
		y = 0;
		for (j = 1; j <= lb + 1; j++) {
			if (i <= la + j) {
				sum = sum + temp[y + i];
			}
			y += j + la + 1;
		}
		c[k++] = (sum + r) % 10;
		r = (sum + r) / 10;
	}
	c[k] = r;
	j = 0;
	for (i = k - 1; i >= 0; i--) {
		mul[j++] = c[i] + 48;
	}
	mul[j] = '\0';
	return mul;
}



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lpCmdLine, int nCmdShow) {

	MSG  msg;
	WNDCLASSW wc = { 0 };
	wc.lpszClassName = L"Buttons";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Buttons",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		150, 150, 600, 400, 0, 0, hInstance, 0);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}





LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {

	case WM_CREATE:
	{
					  CreateWindowW(L"Button", L"Quit",
						  WS_VISIBLE | WS_CHILD,
						  500, 320, 70, 25, hwnd, (HMENU)14, NULL, NULL);

					  HwndLabel1 = CreateWindow("STATIC", "Introdu primul numar:",
						  WS_CHILD | WS_VISIBLE | SS_LEFT,
						  35, 55, 140, 30,
						  hwnd, NULL, NULL, NULL);

					  HwndLabel2 = CreateWindow("STATIC", "Introdu al doilea numar:",
						  WS_CHILD | WS_VISIBLE | SS_LEFT,
						  35, 55, 145, 30,
						  hwnd, NULL, NULL, NULL);

					  HwndLabel3 = CreateWindow("STATIC", "Alege operatia :",
						  WS_CHILD | WS_VISIBLE | SS_LEFT,
						  100, 55, 145, 30,
						  hwnd, NULL, NULL, NULL);

					  first = CreateWindowW(L"Button", L"Introdu al doilea numar",
						  WS_VISIBLE | WS_CHILD,
						  28, 50, 160, 25, hwnd, (HMENU)1, NULL, NULL);

					  op = CreateWindowW(L"Button", L"Alege operatia",
						  WS_VISIBLE | WS_CHILD,
						  28, 50, 160, 25, hwnd, (HMENU)2, NULL, NULL);

					  ad = CreateWindowW(L"Button", L"ADUNARE",
						  WS_VISIBLE | WS_CHILD,
						  20, 100, 130, 25, hwnd, (HMENU)12, NULL, NULL);

					  prod = CreateWindowW(L"Button", L"INMULTIRE",
						  WS_VISIBLE | WS_CHILD,
						  170, 100, 130, 25, hwnd, (HMENU)13, NULL, NULL);

					  but1 = CreateWindowW(L"Button", L"1", WS_VISIBLE | WS_CHILD, 30, 90, 45, 25, hwnd, (HMENU)3, NULL, NULL);
					  but2 = CreateWindowW(L"Button", L"2", WS_VISIBLE | WS_CHILD, 80, 90, 45, 25, hwnd, (HMENU)4, NULL, NULL);
					  but3 = CreateWindowW(L"Button", L"3", WS_VISIBLE | WS_CHILD, 135, 90, 45, 25, hwnd, (HMENU)5, NULL, NULL);
					  but4 = CreateWindowW(L"Button", L"4", WS_VISIBLE | WS_CHILD, 30, 120, 45, 25, hwnd, (HMENU)6, NULL, NULL);
					  but5 = CreateWindowW(L"Button", L"5", WS_VISIBLE | WS_CHILD, 80, 120, 45, 25, hwnd, (HMENU)7, NULL, NULL);
					  but6 = CreateWindowW(L"Button", L"6", WS_VISIBLE | WS_CHILD, 135, 120, 45, 25, hwnd, (HMENU)8, NULL, NULL);
					  but7 = CreateWindowW(L"Button", L"7", WS_VISIBLE | WS_CHILD, 30, 150, 45, 25, hwnd, (HMENU)9, NULL, NULL);
					  but8 = CreateWindowW(L"Button", L"8", WS_VISIBLE | WS_CHILD, 80, 150, 45, 25, hwnd, (HMENU)10, NULL, NULL);
					  but9 = CreateWindowW(L"Button", L"9", WS_VISIBLE | WS_CHILD, 135, 150, 45, 25, hwnd, (HMENU)11, NULL, NULL);
					  but0 = CreateWindowW(L"Button", L"0", WS_VISIBLE | WS_CHILD, 100, 180, 45, 25, hwnd, (HMENU)17, NULL, NULL);

					  ShowWindow(first, SW_HIDE);
					  ShowWindow(op, SW_HIDE);
					  ShowWindow(HwndLabel2, SW_HIDE);
					  ShowWindow(HwndLabel3, SW_HIDE);
					  ShowWindow(ad, SW_HIDE);
					  ShowWindow(prod, SW_HIDE);

	}; break;


	case WM_COMMAND:
	{
					   switch (LOWORD(wParam))
					   {

					   case 1: {

								   char ss[100] = "Ai introdus numarul ";
								   strcat(ss, s);

								   MessageBox(hwnd, ss, "ATENTIE", MB_OK);

								   ShowWindow(first, SW_HIDE);
								   ShowWindow(HwndLabel2, SW_SHOW);

								   prima = 1;

					   }; break;

					   case 2: {

								   char ss[100] = "Ai introdus numarul ";
								   strcat(ss, t);

								   MessageBox(hwnd, ss, "ATENTIE", MB_OK);

								   ShowWindow(HwndLabel3, SW_SHOW);
								   ShowWindow(ad, SW_SHOW);
								   ShowWindow(prod, SW_SHOW);

								   ShowWindow(op, SW_HIDE);
								   ShowWindow(but1, SW_HIDE);
								   ShowWindow(but2, SW_HIDE);
								   ShowWindow(but3, SW_HIDE);
								   ShowWindow(but4, SW_HIDE);
								   ShowWindow(but5, SW_HIDE);
								   ShowWindow(but6, SW_HIDE);
								   ShowWindow(but7, SW_HIDE);
								   ShowWindow(but8, SW_HIDE);
								   ShowWindow(but9, SW_HIDE);
								   ShowWindow(but0, SW_HIDE);


								  
					   }; break;


					   case 3: {

								   if (!prima)
								   {
									   s[k] = '1';
									   k++;

									   ShowWindow(first, SW_SHOW);
									   ShowWindow(HwndLabel1, SW_HIDE);
								   }
								   else
								   {
									   t[l] = '1';
									   l++;

									   ShowWindow(op, SW_SHOW);
									   ShowWindow(HwndLabel2, SW_HIDE);
								   }
					   }; break;

					   case 4: {

								   if (!prima)
								   {
									   s[k] = '2';
									   k++;

									   ShowWindow(first, SW_SHOW);
									   ShowWindow(HwndLabel1, SW_HIDE);
								   }
								   else
								   {
									   t[l] = '2';
									   l++;

									   ShowWindow(op, SW_SHOW);
									   ShowWindow(HwndLabel2, SW_HIDE);
								   }
					   }; break;
					   case 17: {

								   if (!prima)
								   {
									   s[k] = '0';
									   k++;

									   ShowWindow(first, SW_SHOW);
									   ShowWindow(HwndLabel1, SW_HIDE);
								   }
								   else
								   {
									   t[l] = '0';
									   l++;

									   ShowWindow(op, SW_SHOW);
									   ShowWindow(HwndLabel2, SW_HIDE);
								   }
					   }; break;
						   

					   case 5: {

								   if (!prima)
								   {
									   s[k] = '3';
									   k++;

									   ShowWindow(first, SW_SHOW);
									   ShowWindow(HwndLabel1, SW_HIDE);
								   }
								   else
								   {
									   t[l] = '3';
									   l++;

									   ShowWindow(op, SW_SHOW);
									   ShowWindow(HwndLabel2, SW_HIDE);
								   }
					   }; break;

					   case 6: {

								   if (!prima)
								   {
									   s[k] = '4';
									   k++;

									   ShowWindow(first, SW_SHOW);
									   ShowWindow(HwndLabel1, SW_HIDE);
								   }
								   else
								   {
									   t[l] = '4';
									   l++;

									   ShowWindow(op, SW_SHOW);
									   ShowWindow(HwndLabel2, SW_HIDE);
								   }
					   }; break;

					   case 7: {

								   if (!prima)
								   {
									   s[k] = '5';
									   k++;

									   ShowWindow(first, SW_SHOW);
									   ShowWindow(HwndLabel1, SW_HIDE);
								   }
								   else
								   {
									   t[l] = '5';
									   l++;

									   ShowWindow(op, SW_SHOW);
									   ShowWindow(HwndLabel2, SW_HIDE);
								   }
					   }; break;

					   case 8: {

								   if (!prima)
								   {
									   s[k] = '6';
									   k++;

									   ShowWindow(first, SW_SHOW);
									   ShowWindow(HwndLabel1, SW_HIDE);
								   }
								   else
								   {
									   t[l] = '6';
									   l++;

									   ShowWindow(op, SW_SHOW);
									   ShowWindow(HwndLabel2, SW_HIDE);
								   }
					   }; break;

					   case 9: {

								   if (!prima)
								   {
									   s[k] = '7';
									   k++;

									   ShowWindow(first, SW_SHOW);
									   ShowWindow(HwndLabel1, SW_HIDE);
								   }
								   else
								   {
									   t[l] = '7';
									   l++;

									   ShowWindow(op, SW_SHOW);
									   ShowWindow(HwndLabel2, SW_HIDE);
								   }
					   }; break;

					   case 10: {

									if (!prima)
									{
										s[k] = '8';
										k++;

										ShowWindow(first, SW_SHOW);
										ShowWindow(HwndLabel1, SW_HIDE);
									}
									else
									{
										t[l] = '8';
										l++;

										ShowWindow(op, SW_SHOW);
										ShowWindow(HwndLabel2, SW_HIDE);
									}
					   }; break;

					   case 11: {

									if (!prima)
									{
										s[k] = '9';
										k++;

										ShowWindow(first, SW_SHOW);
										ShowWindow(HwndLabel1, SW_HIDE);
									}
									else
									{
										t[l] = '9';
										l++;

										ShowWindow(op, SW_SHOW);
										ShowWindow(HwndLabel2, SW_HIDE);
									}
					   }; break;


					   case 12: {
									adunare(hwnd, s, t);
					   }; break;

					   case 13: {
									char *c = multiply(s, t);
									MessageBox(hwnd, c, "Inmultirea", MB_OK);
					   }; break;

					   case 14: {
									int result = MessageBox(hwnd, "Esti sigur?", "Really?", MB_YESNO);

									if (result == IDYES)
									{
										ExitProcess(0);
									}
									else if (result == IDNO)
									{
										int x = 0;
									}
					   }

					   }
	}; break;



	case WM_CHAR:

		if (wParam == VK_ESCAPE)
			SendMessage(hwnd, WM_CLOSE, 0, 0);
		return 0;
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}