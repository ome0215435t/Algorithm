#define _CRT_SECURE_NO_WARNINGS 
#include <windows.h>//winapi를 통해 gui 표현하기 위해
#include <tchar.h> //_T를 사용하기위해, TCHAR데이터 타입 사용을 위해
#include "Sorting_Algoritm.h"
#include "BFS_DFS.h"
#include "Graph.h"
#include "A_star.h"
HWND sort_hEdit,avl_hEdit_1, avl_hEdit_2, avl_hEdit_3, avl_hEdit_4, avl_hEdit_5;    //Handle to a Window의 약자
HWND sort, start, quest,mst,topological,dijkstra,a_star,avl,qor;

LRESULT CALLBACK Main(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        CreateWindow(_T("STATIC"), _T("\n\t\t           알고리즘 구현"), WS_CHILD | WS_VISIBLE, 20, 20, 440, 60, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("기본, 특수 정렬"), WS_CHILD | WS_VISIBLE, 10, 110, 150, 40, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("BFS,DFS"), WS_CHILD | WS_VISIBLE, 165, 110, 150, 40, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("프림,크루스칼"), WS_CHILD | WS_VISIBLE, 320, 110, 150, 40, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("위상정렬"), WS_CHILD | WS_VISIBLE, 10, 160, 150, 40, hwnd, (HMENU)4, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("다익스트라,플로이드"), WS_CHILD | WS_VISIBLE, 165, 160, 150, 40, hwnd, (HMENU)5, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("A*알고리즘"), WS_CHILD | WS_VISIBLE, 320, 160, 150, 40, hwnd, (HMENU)6, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("?"), WS_CHILD | WS_VISIBLE,450, 10, 25, 25, hwnd, (HMENU)7, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            ShowWindow(start, SW_HIDE);
            ShowWindow(sort, SW_SHOWNORMAL);
            
        }
        else if (LOWORD(wParam) == 2) {
            ShowWindow(start, SW_HIDE);
            ShowWindow(quest, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 3) {
            ShowWindow(start, SW_HIDE);
            ShowWindow(mst, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 4) {
            ShowWindow(start, SW_HIDE);
            ShowWindow(topological, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 5) {
            ShowWindow(start, SW_HIDE);
            ShowWindow(dijkstra, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 6) {
            ShowWindow(start, SW_HIDE);
            ShowWindow(a_star, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 7) {
            TCHAR outputBuffer[256];
            _stprintf(outputBuffer, _T("제작자 : 2001580 박동엽\n\n참고자료 : C언어로 쉽게 풀어쓴 자료구조 개정3판(생능출판)"));
            MessageBox(hwnd, outputBuffer, _T("-"), MB_OK);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK Sorting(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {//윈도우 메시지를 처리하고 응용 프로그램이 윈도우 이벤트에 대응해주는 함수
    switch (msg) {
    case WM_CREATE: { //윈도우가 생성될 때
        sort_hEdit=CreateWindow(_T("EDIT"), _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 20, 460, 20, hwnd, NULL, NULL, NULL);
        //자식 윈도우로 보이게 테두리로된 10,20위치에 460,30의 크기로 EDIT생성
        CreateWindow(_T("STATIC"), _T("정렬할 배열을 입력(문자= 0, 최대값=2147483647)"), WS_CHILD | WS_VISIBLE, 20, 60, 440, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("띄어쓰기를 통해 원소 구분"), WS_CHILD | WS_VISIBLE, 20, 80, 440, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("원소의 갯수는 EDIT에 적을 수 있는 갯수 만큼 가능"), WS_CHILD | WS_VISIBLE, 20, 100, 440, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("선택정렬"), WS_CHILD | WS_VISIBLE, 340, 140, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        //자식 윈도우로 보이게 특정 위치에 특정 크기로 BUTTON생성, 메뉴핸들 식별변수 HMENU에 1로 저장
        CreateWindow(_T("BUTTON"), _T("삽입정렬"), WS_CHILD | WS_VISIBLE, 40, 140, 100, 30, hwnd, (HMENU)2, NULL, NULL);
        //자식 윈도우로 보이게 특정 위치에 특정 크기로 BUTTON생성, 메뉴핸들 식별변수 HMENU에 2로 저장
        CreateWindow(_T("BUTTON"), _T("버블정렬"), WS_CHILD | WS_VISIBLE, 190, 140, 100, 30, hwnd, (HMENU)3, NULL, NULL);
        //자식 윈도우로 보이게 특정 위치에 특정 크기로 BUTTON생성, 메뉴핸들 식별변수 HMENU에 3로 저장
        CreateWindow(_T("BUTTON"), _T("합병정렬"), WS_CHILD | WS_VISIBLE, 190, 180, 100, 30, hwnd, (HMENU)4, NULL, NULL);
        //자식 윈도우로 보이게 특정 위치에 특정 크기로 BUTTON생성, 메뉴핸들 식별변수 HMENU에 4로 저장
        CreateWindow(_T("BUTTON"), _T("퀵정렬"), WS_CHILD | WS_VISIBLE, 40, 180, 100, 30, hwnd, (HMENU)5, NULL, NULL);
        //자식 윈도우로 보이게 특정 위치에 특정 크기로 BUTTON생성, 메뉴핸들 식별변수 HMENU에 5로 저장
        CreateWindow(_T("BUTTON"), _T("기수정렬"), WS_CHILD | WS_VISIBLE, 340,180, 100, 30, hwnd, (HMENU)6, NULL, NULL);
        //자식 윈도우로 보이게 특정 위치에 특정 크기로 BUTTON생성, 메뉴핸들 식별변수 HMENU에 6로 저장
        CreateWindow(_T("BUTTON"), _T("계수정렬"), WS_CHILD | WS_VISIBLE, 340, 220, 100, 30, hwnd, (HMENU)7, NULL, NULL);
        //자식 윈도우로 보이게 특정 위치에 특정 크기로 BUTTON생성, 메뉴핸들 식별변수 HMENU에 7로 저장
        CreateWindow(_T("BUTTON"), _T("힙정렬"), WS_CHILD | WS_VISIBLE, 190, 220, 100, 30, hwnd, (HMENU)8, NULL, NULL);
        //자식 윈도우로 보이게 특정 위치에 특정 크기로 BUTTON생성, 메뉴핸들 식별변수 HMENU에 8로 저장
        CreateWindow(_T("BUTTON"), _T("뒤로가기"), WS_CHILD | WS_VISIBLE, 40, 220, 100, 30, hwnd, (HMENU)9, NULL, NULL);
        break;
    }
    case WM_COMMAND: { //특정 이벤트가 발생할때
        if (LOWORD(wParam) == 1) { //이벤트 발생시 식별 변수 값이 1인 경우
            TCHAR buffer[256];
            GetWindowText(sort_hEdit, buffer, 256);//hEdit에 적은 텍스트를 buffer로 전부 복사
            int numbers[256];
            int count = 0;
            TCHAR* token = _tcstok(buffer, _T(" "));//buffer에 저장된 텍스트를 " "를 통해 추출하여 token에 저장
            while (token != NULL && count < 256) {
                numbers[count++] = _ttoi(token);//토큰에 있는 문자열을 number 정수 배열로 저장
                token = _tcstok(NULL, _T(" "));//NULL이 매개변수로 오면 다음 토큰을 찾아 반환
            }

            // 입력된 배열을 정렬
            Selection_Sort(numbers, count);

            // 정렬된 배열을 문자열로 변환
            TCHAR outputBuffer[512];
            _stprintf(outputBuffer, _T("코드\nvoid Selection_Sort(int arr[], int n) {\n\tint min,tmp;\n\t\tfor (int i = 0; i < n - 1; i++) {\n\t\tmin = i;\n\t\tfor (int j =i+1; j <n; j++) {\n\t\t\tif (arr[j] < arr[min]) {\n\t\t\t\tmin=j;\n\t\t\t}\n\t\t}\n\t\ttmp = arr[i];\n\t\tarr[i] = arr[min];\n\t\tarr[min] = tmp;\n\t}\n}\n\n정렬된 배열 : "));//첫번째 매개변수는 출력할 문자열 버퍼
            //뒤쪽 매개변수의 값을 앞쪽 매개변수에 저장
            for (int i = 0; i < count; ++i) {
                _stprintf(outputBuffer + _tcslen(outputBuffer), _T("%d "), numbers[i]);
                //문자열 시작위치에 저장된 문자열 길이를 더하여 끝위치에 numbers[i] 값을 추가
            }

            MessageBox(hwnd, outputBuffer, _T("선택정렬"), MB_OK);//확인 버튼이 있는 메시지박스 출력
        }
        else if (LOWORD(wParam) == 2) {
            TCHAR buffer[256];
            GetWindowText(sort_hEdit, buffer, 256);
            int numbers[256];
            int count = 0;
            TCHAR* token = _tcstok(buffer, _T(" "));
            while (token != NULL && count < 256) {
                numbers[count++] = _ttoi(token);
                token = _tcstok(NULL, _T(" "));
            }

            // 입력된 배열을 정렬
            Insertion_Sort(numbers, count);

            // 정렬된 배열을 문자열로 변환
            TCHAR outputBuffer[256];
            _stprintf(outputBuffer, _T("void Insertion_Sort(int arr[], int n) {\n\tint key, j;\n\tfor (int i = 1; i < n; i++) {\n\t\tkey = arr[i];\n\t\tfor (j = i - 1; j >= 0 && arr[j] > key; j--) {\n\t\t\tarr[j + 1] = arr[j];\n\t\t}\n\t\tarr[j + 1] = key;\n\t}\n}\n\n정렬된 배열: "));
            for (int i = 0; i < count; ++i) {
                _stprintf(outputBuffer + _tcslen(outputBuffer), _T("%d "), numbers[i]);
            }

            MessageBox(hwnd, outputBuffer, _T("삽입정렬"), MB_OK);
        }
        else if (LOWORD(wParam) == 3) {
            TCHAR buffer[256];
            GetWindowText(sort_hEdit, buffer, 256);
            int numbers[256];
            int count = 0;
            TCHAR* token = _tcstok(buffer, _T(" "));
            while (token != NULL && count < 256) {
                numbers[count++] = _ttoi(token);
                token = _tcstok(NULL, _T(" "));
            }

            // 입력된 배열을 정렬
            Bubble_Sort(numbers, count);

            // 정렬된 배열을 문자열로 변환
            TCHAR outputBuffer[512];
            _stprintf(outputBuffer, _T("void Bubble_Sort(int arr[], int n) {\n\tint tmp;\n\tfor (int i = n - 1; i > 0; i--) {\n\t\tfor (int j = 0; j < i; j++) {\n\t\t\tif (arr[j] > arr[j + 1]) {\n\t\t\t\ttmp = arr[j];\n\t\t\t\tarr[j] = arr[j + 1];\n\t\t\t\tarr[j + 1] = tmp;\n\t\t\t\}\n\t\t}\n\t}\n}\n\n정렬된 배열: "));
            for (int i = 0; i < count; ++i) {
                _stprintf(outputBuffer + _tcslen(outputBuffer), _T("%d "), numbers[i]);
            }

            MessageBox(hwnd, outputBuffer, _T("버블정렬"), MB_OK);
        }
        else if (LOWORD(wParam) == 4) {
            TCHAR buffer[256];
            GetWindowText(sort_hEdit, buffer, 256);
            int numbers[256];
            int count = 0;
            TCHAR* token = _tcstok(buffer, _T(" "));
            while (token != NULL && count < 256) {
                numbers[count++] = _ttoi(token);
                token = _tcstok(NULL, _T(" "));
            }

            // 입력된 배열을 정렬
            Merge_Sort(numbers, 0,count-1);

            // 정렬된 배열을 문자열로 변환
            TCHAR outputBuffer[1024];
            _stprintf(outputBuffer, _T("void merge(int arr[], int left, int mid, int right) {\n\tint i, j, k;\n\tint n1 = mid - left + 1;\n\tint n2 = right - mid;\n\tint* L = (int*)malloc(n1 * sizeof(int));\n\tint* R = (int*)malloc(n2 * sizeof(int));\n\tfor (i = 0; i < n1; i++)\n\t\tL[i] = arr[left + i];\n\tfor (j = 0; j < n2; j++)\n\t\tR[j] = arr[mid + 1 + j];\n\ti = 0;n\tj = 0;\n\tk = left;\n\twhile (i < n1 && j < n2) {\n\t\tif (L[i] <= R[j]) {\n\t\t\tarr[k] = L[i];\n\t\t\ti++;\n\t\t}\n\t\telse {\n\t\t\tarr[k] = R[j];\n\t\t\tj++;\n\t\t}\n\t\tk++;\n\t}\n\twhile (i < n1) {\n\t\tarr[k] = L[i];\n\t\ti++;\n\t\tk++;\n\t}\n\twhile (j < n2) {\n\t\tarr[k] = R[j];\n\t\tj++;\n\t\tk++;\n\t}\n\tfree(L);\n\tfree(R);\n}\n\nvoid Merge_Sort(int arr[], int left, int right) {\n\tif (left < right) {\n\t\tint mid = left + (right - left) / 2;\n\t\tMerge_Sort(arr, left, mid);\n\t\tMerge_Sort(arr, mid + 1, right);\n\t\tmerge(arr, left, mid, right);\n\t}\n}\n\n정렬된 배열: "));
            for (int i = 0; i < count; ++i) {
                _stprintf(outputBuffer + _tcslen(outputBuffer), _T("%d "), numbers[i]);
            }

            MessageBox(hwnd, outputBuffer, _T("합병정렬"), MB_OK);
        }
        else if (LOWORD(wParam) == 5) {
            TCHAR buffer[256];
            GetWindowText(sort_hEdit, buffer, 256);
            int numbers[256];
            int count = 0;
            TCHAR* token = _tcstok(buffer, _T(" "));
            while (token != NULL && count < 256) {
                numbers[count++] = _ttoi(token);
                token = _tcstok(NULL, _T(" "));
            }

            // 입력된 배열을 정렬
            Quick_Sort(numbers, 0,count-1);

            // 정렬된 배열을 문자열로 변환
            TCHAR outputBuffer[512];
            _stprintf(outputBuffer, _T("void Quick_Sort(int arr[], int L, int R) {\n\tint left = L, right = R;\n\tint pivot = arr[(L + R) / 2];\n\tint temp;\n\twhile (left <= right) {\n\t\twhile (arr[left] < pivot)\n\t\t\tleft++;\n\t\twhile (arr[right] > pivot)\n\t\t\tright--;\n\t\tif (left <= right){\n\t\t\ttemp = arr[left];\n\t\t\tarr[left] = arr[right];\n\t\t\tarr[right] = temp;\n\t\t\tleft++;\n\t\t\tright--;\n\t\t}\n\t}\n\tif (L < right)\n\t\t\tQuick_Sort(arr, L, right);\n\tif (left < R)\n\t\tQuick_Sort(arr, left, R);\n}\n\n정렬된 배열: "));
            for (int i = 0; i < count; ++i) {
                _stprintf(outputBuffer + _tcslen(outputBuffer), _T("%d "), numbers[i]);
            }

            MessageBox(hwnd, outputBuffer, _T("퀵정렬"), MB_OK);
        }
        else if (LOWORD(wParam) == 6) {
        TCHAR buffer[256];
        GetWindowText(sort_hEdit, buffer, 256);
        int numbers[256];
        int count = 0;
        TCHAR* token = _tcstok(buffer, _T(" "));
        while (token != NULL && count < 256) {
            numbers[count++] = _ttoi(token);
            token = _tcstok(NULL, _T(" "));
        }

        // 입력된 배열을 정렬
        Radix_Sort(numbers, count);

        // 정렬된 배열을 문자열로 변환
        TCHAR outputBuffer[1024];
        _stprintf(outputBuffer, _T("void Radix_Sort(int arr[], int n) {\n\tint max = arr[0];\n\tfor (int i = 1; i < n; i++) {\n\t\tif (arr[i] > max) {\n\t\t\tmax = arr[i];\n\t\t}\n\t}\n\tfor (int exp = 1; max / exp > 0; exp *= 10) {\n\t\tint* output = (int*)malloc(n * sizeof(int));\n\t\tint count[10] = { 0 };\n\t\tfor (int i = 0; i < n; i++) {\n\t\t\tcount[(arr[i] / exp) % 10]++;\n\t\t}\n\t\tfor (int i = 1; i < 10; i++) {\n\t\t\tcount[i] += count[i - 1];\n\t\t}\n\t\tfor (int i = n - 1; i >= 0; i--) {\n\t\t\toutput[count[(arr[i] / exp) % 10] - 1] = arr[i];\n\t\t\tcount[(arr[i] / exp) % 10]--;\n\t\t}\n\t\tfor (int i = 0; i < n; i++) {\n\t\t\tarr[i] = output[i];\n\t\t}\n\t\tfree(output);\n\t}\n}\n\n정렬된 배열: "));
        for (int i = 0; i < count; ++i) {
            _stprintf(outputBuffer + _tcslen(outputBuffer), _T("%d "), numbers[i]);
        }

        MessageBox(hwnd, outputBuffer, _T("기수정렬"), MB_OK);
        }
        else if (LOWORD(wParam) == 7) {
        TCHAR buffer[256];
        GetWindowText(sort_hEdit, buffer, 256);
        int numbers[256];
        int count = 0;
        TCHAR* token = _tcstok(buffer, _T(" "));
        while (token != NULL && count < 256) {
            numbers[count++] = _ttoi(token);
            token = _tcstok(NULL, _T(" "));
        }

        // 입력된 배열을 정렬
        Counting_Sort(numbers, count);

        // 정렬된 배열을 문자열로 변환
        TCHAR outputBuffer[1024];
        _stprintf(outputBuffer, _T("void Counting_Sort(int arr[], int n) {\n\tint max = arr[0];\n\tfor (int i = 1; i < n; i++) {\n\t\tif (arr[i] > max) {\n\t\t\tmax = arr[i];\n\t\t}\n\t}\n\tint* countingArray = (int*)malloc((max + 1) * sizeof(int));\n\tfor (int i = 0; i <= max; i++) {\n\t\tcountingArray[i] = 0;\n\t}\n\tfor (int i = 0; i < n; i++) {\n\t\tcountingArray[arr[i]]++;\n\t}\n\tint index = 0;\n\tfor (int i = 0; i <= max; i++) {\n\t\twhile (countingArray[i] > 0) {\n\t\t\tarr[index] = i;\n\t\t\tindex++;\n\t\t\tcountingArray[i]--;\n\t\t}\n\t}\n\tfree(countingArray);\n}\n\n정렬된 배열: "));
        for (int i = 0; i < count; ++i) {
            _stprintf(outputBuffer + _tcslen(outputBuffer), _T("%d "), numbers[i]);
        }

        MessageBox(hwnd, outputBuffer, _T("계수정렬"), MB_OK);
        }
        else if (LOWORD(wParam) == 8) {
            TCHAR buffer[256];
            GetWindowText(sort_hEdit, buffer, 256);
            int numbers[256];
            int count = 0;
            TCHAR* token = _tcstok(buffer, _T(" "));
            while (token != NULL && count < 256) {
                numbers[count++] = _ttoi(token);
                token = _tcstok(NULL, _T(" "));
            }

            // 입력된 배열을 정렬
            Heap_Sort(numbers, count);

            // 정렬된 배열을 문자열로 변환
            TCHAR outputBuffer[1024];
            _stprintf(outputBuffer, _T("void heapify(int arr[], int n, int i) {\n\tint largest = i;\n\tint left = 2 * i + 1;\n\tint right = 2 * i + 2;\n\tif (left < n && arr[left] > arr[largest])\n\t\tlargest = left;\n\tif (right < n && arr[right] > arr[largest])\n\t\tlargest = right;\n\tif (largest != i) {\n\t\tint temp = arr[i];\n\t\tarr[i] = arr[largest];\n\t\tarr[largest] = temp;\n\t\theapify(arr, n, largest);\n\t}\n}\n\nvoid Heap_Sort(int arr[], int n) {\n\tfor (int i = n / 2 - 1; i >= 0; i--)\n\t\theapify(arr, n, i);\n\tfor (int i = n - 1; i > 0; i--) {\n\t\tint temp = arr[0];\n\t\tarr[0] = arr[i];\n\t\tarr[i] = temp;\n\t\theapify(arr, i, 0);\n\t}\n}\n\n정렬된 배열: "));
            for (int i = 0; i < count; ++i) {
                _stprintf(outputBuffer + _tcslen(outputBuffer), _T("%d "), numbers[i]);
            }

            MessageBox(hwnd, outputBuffer, _T("힙정렬"), MB_OK);
            }
            if (LOWORD(wParam) == 9) {
                ShowWindow(start, SW_SHOWNORMAL);
                ShowWindow(sort, SW_HIDE);

            }
        break;
    }
    case WM_DESTROY: {//윈도우가 파괴될때
        PostQuitMessage(0);//현재 실행중인 메시지 루프 종료및 애플리케이션 종료
        break;
    }
    default://아무것도 하지않은상태
        return DefWindowProc(hwnd, msg, wParam, lParam);//기본 동작 유지
    }
    return 0;
}


LRESULT CALLBACK Quest(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    int graph[MAX_SIZE][MAX_SIZE] = {
       {0, 1, 1, 0, 0, 0},
       {1, 0, 0, 1, 0, 0},
       {1, 0, 0, 1, 1, 0},
       {0, 1, 1, 0, 1, 1},
       {0, 0, 1, 1, 0, 1},
       {0, 0, 0, 1, 1, 0}
    };
    bool visited[MAX_SIZE] = { false };
    int startVertex = 0;

    // BFS 호출

    switch (msg) {
    case WM_CREATE:
        CreateWindow(_T("STATIC"), _T("\t\t     인접행렬이 다음과 같음"), WS_CHILD | WS_VISIBLE, 10, 20, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0 ,1, 1, 0, 0, 0"), WS_CHILD | WS_VISIBLE, 10, 70, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t1, 0, 0, 1, 0, 0"), WS_CHILD | WS_VISIBLE, 10, 90, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t1, 0, 0, 1, 1, 0"), WS_CHILD | WS_VISIBLE, 10, 110, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 1, 1, 0, 1, 1"), WS_CHILD | WS_VISIBLE, 10, 130, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 0, 1, 1, 0, 1"), WS_CHILD | WS_VISIBLE, 10, 150, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 0, 0, 1, 1, 0"), WS_CHILD | WS_VISIBLE, 10, 170, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("너비우선탐색"), WS_CHILD | WS_VISIBLE, 340, 220, 100, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("뒤로가기"), WS_CHILD | WS_VISIBLE, 40, 220, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("깊이우선탐색"), WS_CHILD | WS_VISIBLE, 190, 220, 100, 30, hwnd, (HMENU)3, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            ShowWindow(quest, SW_HIDE);
            ShowWindow(start, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 2) {
            TCHAR outputBuffer[1024];
            bfs(graph, MAX_SIZE, startVertex, outputBuffer);
            MessageBox(hwnd, outputBuffer, _T("BFS"), MB_OK);
        }
        else if (LOWORD(wParam) == 3) {
            TCHAR outputBuffer[1024];
            _stprintf(outputBuffer, _T("설명 : 그래프나 트리에서 한 경로를 끝까지 탐색한 후 다음 경로로 넘어가는 방식으로, 스택이나 재귀를 이용하여 구현\n\nDFS 시작점 0 : "));
            dfs(graph, MAX_SIZE, startVertex, visited, outputBuffer);
            MessageBox(hwnd, outputBuffer, _T("DFS"), MB_OK);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK Mst(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    switch (msg) {
    case WM_CREATE:
        CreateWindow(_T("STATIC"), _T("\t\t     인접행렬이 다음과 같음"), WS_CHILD | WS_VISIBLE, 10, 20, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 2, 0, 6, 0"), WS_CHILD | WS_VISIBLE, 10, 50, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t2, 0, 3, 8, 5"), WS_CHILD | WS_VISIBLE, 10, 70, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 3, 0, 0, 7"), WS_CHILD | WS_VISIBLE, 10, 90, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t6, 8, 0, 0, 9"), WS_CHILD | WS_VISIBLE, 10, 110, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 5, 7, 9, 0"), WS_CHILD | WS_VISIBLE, 10, 130, 460, 20, hwnd, NULL, NULL, NULL);

        CreateWindow(_T("BUTTON"), _T("프림"), WS_CHILD | WS_VISIBLE, 340, 220, 100, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("뒤로가기"), WS_CHILD | WS_VISIBLE, 40, 220, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("크루스칼"), WS_CHILD | WS_VISIBLE, 190, 220, 100, 30, hwnd, (HMENU)3, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            ShowWindow(mst, SW_HIDE);
            ShowWindow(start, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 2) {
            TCHAR outputBuffer[1024];
            prim(graph, outputBuffer);
            MessageBox(hwnd, outputBuffer, _T("프림 알고리즘"), MB_OK);
        }
        else if (LOWORD(wParam) == 3) {
            TCHAR outputBuffer[1024];
            kruskal(graph, outputBuffer);
            MessageBox(hwnd, outputBuffer, _T("크루스칼 알고리즘"), MB_OK);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK Topological(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    switch (msg) {
    case WM_CREATE:
        CreateWindow(_T("STATIC"), _T("\t\t     인접행렬이 다음과 같음"), WS_CHILD | WS_VISIBLE, 10, 20, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 2, 0, 6, 0"), WS_CHILD | WS_VISIBLE, 10, 50, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t2, 0, 3, 8, 5"), WS_CHILD | WS_VISIBLE, 10, 70, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 3, 0, 0, 7"), WS_CHILD | WS_VISIBLE, 10, 90, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t6, 8, 0, 0, 9"), WS_CHILD | WS_VISIBLE, 10, 110, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 5, 7, 9, 0"), WS_CHILD | WS_VISIBLE, 10, 130, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("위상정렬"), WS_CHILD | WS_VISIBLE, 340, 220, 100, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("뒤로가기"), WS_CHILD | WS_VISIBLE, 40, 220, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            ShowWindow(topological, SW_HIDE);
            ShowWindow(start, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 2) {
            TCHAR outputBuffer[2048];
            topologicalSort(graph,outputBuffer);
            MessageBox(hwnd, outputBuffer, _T("위상 정렬"), MB_OK);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK Dijkstra(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };
    switch (msg) {
    case WM_CREATE:
        CreateWindow(_T("STATIC"), _T("\t\t     인접행렬이 다음과 같음"), WS_CHILD | WS_VISIBLE, 10, 20, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 2, 0, 6, 0"), WS_CHILD | WS_VISIBLE, 10, 50, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t2, 0, 3, 8, 5"), WS_CHILD | WS_VISIBLE, 10, 70, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 3, 0, 0, 7"), WS_CHILD | WS_VISIBLE, 10, 90, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t6, 8, 0, 0, 9"), WS_CHILD | WS_VISIBLE, 10, 110, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 5, 7, 9, 0"), WS_CHILD | WS_VISIBLE, 10, 130, 460, 20, hwnd, NULL, NULL, NULL);

        CreateWindow(_T("BUTTON"), _T("다익스트라"), WS_CHILD | WS_VISIBLE, 340, 220, 100, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("뒤로가기"), WS_CHILD | WS_VISIBLE, 40, 220, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("플로이드"), WS_CHILD | WS_VISIBLE, 190, 220, 100, 30, hwnd, (HMENU)3, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            ShowWindow(dijkstra, SW_HIDE);
            ShowWindow(start, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 2) {
            TCHAR outputBuffer[1024];
            dijkstra1(graph, 0, outputBuffer);
            MessageBox(hwnd, outputBuffer, _T("다익스트라"), MB_OK);
        }
        else if (LOWORD(wParam) == 3) {
            TCHAR outputBuffer[1024];
            floydWarshall(graph, outputBuffer);
            MessageBox(hwnd, outputBuffer, _T("플로이드"), MB_OK);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK A_star(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    
    switch (msg) {
    case WM_CREATE:
        CreateWindow(_T("STATIC"), _T("\t\t     인접행렬이 다음과 같음"), WS_CHILD | WS_VISIBLE, 10, 20, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 5, 0, 0, 0"), WS_CHILD | WS_VISIBLE, 10, 50, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 8, 0, 2, 0"), WS_CHILD | WS_VISIBLE, 10, 70, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 0, 0, 7, 0"), WS_CHILD | WS_VISIBLE, 10, 90, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 9, 3, 7, 0"), WS_CHILD | WS_VISIBLE, 10, 110, 460, 20, hwnd, NULL, NULL, NULL);
        CreateWindow(_T("STATIC"), _T("\t\t\t0, 0, 0, 0, 0"), WS_CHILD | WS_VISIBLE, 10, 130, 460, 20, hwnd, NULL, NULL, NULL);

        CreateWindow(_T("BUTTON"), _T("A_star"), WS_CHILD | WS_VISIBLE, 340, 220, 100, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow(_T("BUTTON"), _T("뒤로가기"), WS_CHILD | WS_VISIBLE, 40, 220, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            ShowWindow(a_star, SW_HIDE);
            ShowWindow(start, SW_SHOWNORMAL);

        }
        else if (LOWORD(wParam) == 2) {
            TCHAR outputBuffer[1024];
            Astar(outputBuffer);
            MessageBox(hwnd, outputBuffer, _T("A_star"), MB_OK);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowWidth = 500;
    int windowHeight = 300;
    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, Sorting, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("sort"), NULL };
    //구조체 정의 순서별로 구조체의 크기, 스타일,메모리 크기,인스턴스 핸들,아이콘 핸들,커서핸들,배경브러시핸들,메뉴이름,클래스이름,작은 아이콘 핸들
    RegisterClassEx(&wc);//등록
    sort = CreateWindow(wc.lpszClassName, _T("정렬 알고리즘"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y, 500, 300, NULL, NULL, wc.hInstance, NULL);//메인창 생성
    ShowWindow(sort, SW_HIDE);//윈도우에 화면을 표시
    UpdateWindow(sort);//변경시 자동으로 다시 화면을 표시

    WNDCLASSEX main = { sizeof(WNDCLASSEX), CS_CLASSDC, Main, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("main"), NULL };
    RegisterClassEx(&main);
    start = CreateWindow(main.lpszClassName, _T("메인 화면"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y, 500, 300, NULL, NULL, main.hInstance, NULL);
    ShowWindow(start, SW_SHOWNORMAL);
    UpdateWindow(start);

    WNDCLASSEX q = { sizeof(WNDCLASSEX), CS_CLASSDC, Quest, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("quest"), NULL };
    RegisterClassEx(&q);
    quest = CreateWindow(q.lpszClassName, _T("탐색"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y, 500, 300, NULL, NULL, q.hInstance, NULL);
    ShowWindow(quest, SW_HIDE);
    UpdateWindow(quest);

    WNDCLASSEX m = { sizeof(WNDCLASSEX), CS_CLASSDC, Mst, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("mst"), NULL };
    RegisterClassEx(&m);
    mst = CreateWindow(m.lpszClassName, _T("최소 신장 트리"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y, 500, 300, NULL, NULL, m.hInstance, NULL);
    ShowWindow(mst, SW_HIDE);
    UpdateWindow(mst);

    WNDCLASSEX t = { sizeof(WNDCLASSEX), CS_CLASSDC, Topological, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("topological"), NULL };
    RegisterClassEx(&t);
    topological = CreateWindow(t.lpszClassName, _T("위상 정렬"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y, 500, 300, NULL, NULL, t.hInstance, NULL);
    ShowWindow(topological, SW_HIDE);
    UpdateWindow(topological);

    WNDCLASSEX d = { sizeof(WNDCLASSEX), CS_CLASSDC, Dijkstra, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("dijkstra"), NULL };
    RegisterClassEx(&d);
    dijkstra = CreateWindow(d.lpszClassName, _T("최단경로 알고리즘"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y, 500, 300, NULL, NULL, d.hInstance, NULL);
    ShowWindow(dijkstra, SW_HIDE);
    UpdateWindow(dijkstra);

    WNDCLASSEX a = { sizeof(WNDCLASSEX), CS_CLASSDC, A_star, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("a_star"), NULL };
    RegisterClassEx(&a);
    a_star = CreateWindow(a.lpszClassName, _T("A* 알고리즘"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y, 500, 300, NULL, NULL, a.hInstance, NULL);
    ShowWindow(a_star, SW_HIDE);
    UpdateWindow(a_star);



    MSG msg;//MSG는 윈도우 메시지를 저장하는 구조체
    ZeroMemory(&msg, sizeof(msg));//초기화
    while (GetMessage(&msg, NULL, 0, 0)) {//루프
        TranslateMessage(&msg);// 특정 키 메시지를 문자 메시지로 변환하는 역할
        DispatchMessage(&msg);//이벤트를 처리 키보드 입력이나 마우스 클릭
    }

    return msg.wParam;// Windows 응용 프로그램이 종료될 때 프로그램의 종료 코드를 반환하는 부분
}

