/*----------------------------------------
   
	 php开发工具

  ----------------------------------------*/
#include <stdio.h>
#include <windows.h>
#include <time.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("PHP Tools") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;
     
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;
     
     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
     hwnd = CreateWindow (szAppName, TEXT ("PHP Tools"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          1000, 150,
                          NULL, NULL, hInstance, NULL) ;
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HWND  hwndButton[21] ;
     static RECT  rect ;
     static TCHAR szBuffer[255] ;
     static int   cxChar, cyChar ;
	 int i;
     HDC          hdc ;
     PAINTSTRUCT  ps ;
     struct tm info;
	 int ret;

     switch (message)
     {
     case WM_CREATE :
		  GetClientRect(hwnd,&rect);
          cxChar = rect.right/20;
          cyChar = rect.bottom/3;
          for( i = 1 ; i <= 11 ; i = i+2){

			hwndButton[i] = CreateWindow ( TEXT ("edit"), 
                                   NULL,
                                   WS_CHILD | WS_VISIBLE | WS_BORDER  ,
                                   cxChar*(i-1), cyChar,
                                   cxChar, cyChar,
                                   hwnd, (HMENU) i,
                                   ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
		  }
		  
		hwndButton[2] = CreateWindow ( TEXT ("static"), TEXT("y"),WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE , cxChar*1, cyChar,
                               cxChar, cyChar,hwnd, (HMENU) 2, ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
		hwndButton[4] = CreateWindow ( TEXT ("static"), TEXT("mon"),WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE , cxChar*3, cyChar,
                               cxChar, cyChar,hwnd, (HMENU) 4, ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
		hwndButton[6] = CreateWindow ( TEXT ("static"), TEXT("d"),WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE , cxChar*5, cyChar,
                               cxChar, cyChar,hwnd, (HMENU) 6, ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
		hwndButton[8] = CreateWindow ( TEXT ("static"), TEXT("h"),WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE , cxChar*7, cyChar,
                               cxChar, cyChar,hwnd, (HMENU) 8, ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
		hwndButton[10] = CreateWindow ( TEXT ("static"), TEXT("min"),WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE , cxChar*9, cyChar,
                               cxChar, cyChar,hwnd, (HMENU) 10, ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
		hwndButton[12] = CreateWindow ( TEXT ("static"), TEXT("s"),WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE , cxChar*11, cyChar,
                               cxChar, cyChar,hwnd, (HMENU) 12, ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
		  

          hwndButton[13] = CreateWindow ( TEXT("button"), 
                                   TEXT("switch"),
                                   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                   cxChar*12, cyChar,
                                   cxChar*2, cyChar,
                                   hwnd, (HMENU) 13,
                                   ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;

		  hwndButton[15] = CreateWindow ( TEXT ("edit"), 
                                   NULL,
                                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT ,
                                   cxChar*15, cyChar,
                                   cxChar*4, cyChar,
                                   hwnd, (HMENU) 15,
                                   ((LPCREATESTRUCT) lParam)->hInstance, NULL) ;
          return 0 ;

     case WM_SIZE :
          
          return 0 ;
          
     case WM_PAINT :
          InvalidateRect (hwnd, &rect, TRUE) ;
          
          hdc = BeginPaint (hwnd, &ps) ;
          
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DRAWITEM :
     case WM_COMMAND :
		 
		 if(LOWORD (wParam) == 13){
			GetWindowText(hwndButton[1],szBuffer,GetWindowTextLength(hwndButton[1])+1);
			info.tm_year = atoi(szBuffer)-1900;
			GetWindowText(hwndButton[3],szBuffer,GetWindowTextLength(hwndButton[3])+1);
			info.tm_mon = atoi(szBuffer)-1;
			GetWindowText(hwndButton[5],szBuffer,GetWindowTextLength(hwndButton[5])+1);
			info.tm_mday = atoi(szBuffer);
			GetWindowText(hwndButton[7],szBuffer,GetWindowTextLength(hwndButton[7])+1);
			info.tm_hour = atoi(szBuffer);
			GetWindowText(hwndButton[9],szBuffer,GetWindowTextLength(hwndButton[9])+1);
			info.tm_min = atoi(szBuffer);
			GetWindowText(hwndButton[11],szBuffer,GetWindowTextLength(hwndButton[11])+1);
			info.tm_sec = atoi(szBuffer);//MessageBox (NULL, TEXT (szBuffer), TEXT ("HelloMsg"), 0) ;
			info.tm_isdst = -1;
			ret = mktime(&info);
			if(ret == -1){
				sprintf(szBuffer, "%d",ret); 
				MessageBox (NULL, TEXT (szBuffer), TEXT ("HelloMsg"), 0) ;
			}else{
				sprintf(szBuffer, "%d", ret); 
				MessageBox (NULL, TEXT (szBuffer), TEXT ("HelloMsg"), 0) ;
				SetWindowText(hwndButton[15],szBuffer);
			}

		 }
          break ;
          
     case WM_DESTROY :
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
