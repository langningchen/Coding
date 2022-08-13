#include <iostream> 
#include <windows.h>
#include <vector>
#include <mmsystem.h>
#include <cstdio>

#pragma comment(lib, "winmm.lib")
using namespace std;

#define GameW 10
#define GameH 20
const int CtrlLeft = GameW*2+4 + 3 
const int SPEED = 3000;	//游戏刷新速度 

struct Point {
    Point(){}
    Point(int x, int y) {_x = x, _y = y;}
    int _x, _y;
};

HANDLE g_hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE g_hInput  = GetStdHandle(STD_INPUT_HANDLE);

Point g_ptCursor(0,0);
BOOL isChecking = FALSE;
BOOL g_bGameOver = FALSE;
int g_nGameBack[GameH][GameW], Case;
int nowKeyInfo = -1;
int g_nDiff = 5;	//游戏难度 
int g_nLife = 2;	//生命值 
int g_nScore = 0;	//分数初始化 

void SetCursor(COORD cd) {
    SetConsoleCursorPosition(g_hOutput, cd);
}
void SetCursor(int x, int y){
    COORD cd = {x, y};
    SetCursor(cd);
}
void SetBlockCursor(int x, int y){
    COORD cd = {2*x + 2, y + 1};
    SetCursor(cd);
}

void SetBack(int x, int y, BOOL bk) {
    SetBlockCursor(x, y);
    if (bk) 
        printf("%s", "■");
    else
        printf("　");
}

bool Out(int x, int y) {
    return x < 0 || y < 0 || x >= GameW || y >= GameH; 
}

struct xBlock {
public:
    int len;
    int nowRotateID;
    BOOL mask[4][4][4];
    static vector <xBlock> List;

    xBlock() { len = 0; }
    xBlock(int l, char *str) {
        int i, j, k;
        len = l;
        memset(mask, FALSE, sizeof(mask));
        for (i = 0; i < l; i++) {
            for (j = 0; j < l; j++) {
                mask[0][i][j] = str[i*l + j] - '0';
            }
        }
        for (k = 1; k < 4; k++) {
            for (i = 0; i < len; i++) {
                for (j = 0; j < len; j++) {
                    mask[k][i][j] = mask[k-1][j][len-1-i];
                }
            }
        }
        nowRotateID = rand() % 4;
    }

    void rotate() {
        nowRotateID ++;
        if (nowRotateID >= 4)
            nowRotateID = 0;
    }

    BOOL getUnit(int x, int y, int roID) {
        if (roID == -1) {
            roID = nowRotateID;
        }
        return mask[roID][y][x];
    }
};

vector <xBlock> xBlock::List;

class Block {
public:
    int x, y;
    int ID;
    xBlock bk;

    void reset(xBlock *pbk) {
        bk = *pbk;

        x = 4, y = 0;
        ID = ++ Case;

        if (collide(0,0)) {
            lifeDown();
        }
        draw();
        
        *pbk = xBlock::List[rand() % xBlock::List.size()];
    }
    
    void lifeDown() {
        int i, j;
        for (i = 0; i < GameH; i++) {
            for (j = 0; j < GameW; j++) {
                SetBack(j, i, TRUE);
                Sleep(10);
            }
        }
        if (g_nLife) {
            g_nLife --;
            for (i = g_nLife; i < 6; i++) {
                SetCursor(CtrlLeft + i, 15);
                printf("%c", ' ');
            }
            for (i = GameH-1; i >= 0; i--) {
                for (j = GameW-1; j >= 0; j--) {
                    SetBack(j, i, FALSE);
                    Sleep(10);
                    g_nGameBack[i][j] = 0;
                }
            }
        }else {
            g_bGameOver = TRUE;
        }
    }

    void erase() {
        int i, j;
        for (i = 0; i < bk.len; i++) {
            for (j = 0; j < bk.len; j++) {
                if (bk.getUnit(j, i, -1)) {
                    if (! Out(j+x, i+y) && g_nGameBack[i+y][j+x]) {
                        SetBack(j+x, i+y, FALSE);
                        g_nGameBack[i+y][j+x] = 0;
                    }
                }
            }
        }
    }
    void draw() {
        int i, j;
        for (i = 0; i < bk.len; i++) {
            for (j = 0; j < bk.len; j++) {
                if (bk.getUnit(j, i, -1)) {
                    if (! Out(j+x, i+y) && ! g_nGameBack[i+y][j+x]) {
                        SetBack(j+x, i+y, TRUE);
                        g_nGameBack[i+y][j+x]  = ID;
                    }
                }
            }
        }
    }
    void draw(int x, int y) {
        int i, j;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                SetCursor(x + 2*j, y + i);
                if (bk.getUnit(j, i, -1)) {    
                    printf("%s", "■");
                }else 
                    printf("　");
            }
        }
    }
    bool collide(int dx, int dy, int roID = -1) {
        int i, j;
        for (i = 0; i < bk.len; i++) {
            for (j = 0; j < bk.len; j++) {
                if (bk.getUnit(j, i, roID)) {
                    Point ptPos(j + x + dx, i + y + dy);
                    if (Out(ptPos._x, ptPos._y)
                    || g_nGameBack[ptPos._y][ptPos._x] && ID != g_nGameBack[ptPos._y][ptPos._x]) {
                        return TRUE;
                    }
                }
            }
        }
        return FALSE;
    }

    void rotate(int nTimes = 1) {
        int nextro = (bk.nowRotateID + nTimes) % 4;
        if (collide(0, 0, nextro)) {
            return ;
        }
        Beep(12000, 50);
        erase();
        bk.nowRotateID = nextro;
        draw();
    }

    BOOL changepos(int dx, int dy) {
        if (collide(dx, dy)) {
            return FALSE;
        }
        erase();
        x += dx;
        y += dy;
        draw();
        return TRUE;
    }
};

void GameInit() {
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.bVisible = FALSE;
    cursor_info.dwSize   = 100;
    SetConsoleCursorInfo(g_hOutput, &cursor_info);
    xBlock::List.push_back(xBlock(3, "010111000"));
    xBlock::List.push_back(xBlock(3, "110110000"));
    xBlock::List.push_back(xBlock(3, "111001000"));
    xBlock::List.push_back(xBlock(3, "111100000"));
    xBlock::List.push_back(xBlock(3, "110011000"));
    xBlock::List.push_back(xBlock(3, "011110000"));
    xBlock::List.push_back(xBlock(4, "1000100010001000"));
}

void DrawFrame(int x, int y, int nWidth, int nHeight) {
    int i;
    for (i = 0; i < nWidth; i++) {
        SetCursor(x + 2*i + 2, y);
        printf("%s", "一");
        SetCursor(x + 2*i + 2, y + nHeight+1);
        printf("%s", "┄");
    }
    for (i = 0; i < nHeight; i++) {
        SetCursor(x, y + i + 1);
        printf("%s", "┆");
        SetCursor(x + nWidth*2+2, y + i + 1);
        printf("%s", "┆");
    }        
    SetCursor(x, y);
    printf("%s", "┌");    
    SetCursor(x, y + nHeight+1);
    printf("%s", "└");
    SetCursor(x + nWidth*2+2, y);
    printf("%s", "┐");    
    SetCursor(x + nWidth*2+2, y + nHeight+1);
    printf("%s", "┘");
}

void MissionInit() {
    memset(g_nGameBack, FALSE, sizeof(g_nGameBack));
    Case = 1;
    int i;
    DrawFrame(0, 0, GameW, GameH);
    DrawFrame(GameW*2+4, 0, 4, GameH);
    SetCursor(CtrlLeft, 2);
    printf("Next");
    
    SetCursor(CtrlLeft, 8);
    printf("Speed");
    for (i = 0; i < g_nDiff; i++) {
        SetCursor(CtrlLeft + i, 9);
        printf("%c", 1);
    }

    SetCursor(CtrlLeft, 11);
    printf("Score");
    SetCursor(CtrlLeft, 12);
    printf("%d", g_nScore);

    SetCursor(CtrlLeft, 14);
    printf("Life");
    for (i = 0; i < g_nLife; i++) {
        SetCursor(CtrlLeft + i, 15);
        printf("%c", 3);
    }
}

void Check() {
    isChecking = TRUE;
    int i, j, k;
    vector <int> line;
    for (i = 0; i < GameH; i++) {
        for (j = 0; j < GameW; j++) {
            if (! g_nGameBack[i][j])
                break;
        }
        if (j == GameW) {
            line.push_back(i);
        }
    }
    if (line.size()) {
        int nCount = 7;
        while (nCount --) {
            for (i = 0; i < line.size(); i++) {
                for (j = 0; j < GameW; j++) {
                    SetBack(j, line[i], nCount&1);
                }
            }
            Sleep(70);
        }
        for (i = 0; i < line.size(); i++) {
            for (j = 0; j < GameW; j++) {
                g_nGameBack[line[i]][j] = 0;
            }
        }

        for (i = 0; i < GameW; i++) {
            int next = GameH-1;
            for (j = GameH-1; j >= 0; j--) {
                for (k = next; k >= 0; k--) {
                    if (g_nGameBack[k][i]) 
                        break;
                }
                next = k - 1;
                BOOL is = (k >= 0);
                SetBack(i, j, is);
                g_nGameBack[j][i] = is;
            }
        }

        g_nScore += 2*line.size()-1;
        SetCursor(CtrlLeft, 12);
        printf("%d", g_nScore);

        if ( g_nScore >= g_nDiff * g_nDiff * 10) {
            if (g_nDiff <= 6)
                g_nDiff ++;
        }
        if ( g_nScore >= 50 * (g_nLife+1)) {
            if (g_nLife <= 6)
                g_nLife ++;
        }
    }

    isChecking = FALSE;
}
int main() {
    Block* obj = new Block();
    Block* buf = new Block();
    

    BOOL bCreateNew = FALSE;
    int nTimer = GetTickCount();
    int LastKeyDownTime = GetTickCount();


    GameInit();
    MissionInit();
    
    buf -> bk = xBlock::List[rand() % xBlock::List.size()];
    while (1) {
        if (! bCreateNew) {
            bCreateNew = TRUE;
            obj -> reset(&buf -> bk);
            if (g_bGameOver)
                break;
            buf -> draw(CtrlLeft - 1, 4);
        }
        if (GetTickCount() - nTimer >= SPEED / g_nDiff) {
            nTimer = GetTickCount();
            if (! obj -> collide(0, 1))
                obj -> changepos(0, 1);
            else {
                Check();
                bCreateNew = FALSE;
            }
        }
        if (GetTickCount() - LastKeyDownTime >= 100) {
            if (FALSE == isChecking) {
                LastKeyDownTime = GetTickCount();
                if (GetAsyncKeyState(VK_UP)) {
                    obj -> rotate();
                }
                if (GetAsyncKeyState(VK_LEFT)) {
                    obj -> changepos(-1, 0);
                }
                if (GetAsyncKeyState(VK_RIGHT)) {
                    obj -> changepos(1, 0);
                }
                if (GetAsyncKeyState(VK_DOWN)) {
                    if ( FALSE == obj -> changepos(0, 2) )
                        obj -> changepos(0, 1);
                }
            }
        }
    }
    SetCursor(8, 10);
    printf("Game Over!");

    SetCursor(0, GameH + 3);

    while (1) {
        if (GetAsyncKeyState(VK_ESCAPE))
            break;
    }
    return 0;
}
