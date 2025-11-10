#include "DxLib.h"
#include <vector>
#include <string>
#include <cmath>

// 2D 射的風ゲーム (DXライブラリ使用)
// - マウス位置に照準を追従
// - 左クリックで建物を撃つ
// - 時間内に全て破壊でクリア

struct Building {
    int x, y, w, h;
    int hp, maxHp;
    bool destroyed;
};

const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int CROSSHAIR_SIZE = 12;
const int DAMAGE = 25;
const int TIME_LIMIT_SEC = 45;

std::vector<Building> CreateBuildings() {
    std::vector<Building> v;
    v.push_back({ 100, 200, 120, 220, 100, 100, false });
    v.push_back({ 260, 180, 100, 240, 120, 120, false });
    v.push_back({ 390, 220, 160, 200, 150, 150, false });
    v.push_back({ 580, 170, 140, 250, 180, 180, false });
    return v;
}

bool PointInRect(int px, int py, const Building& b) {
    return px >= b.x && px <= b.x + b.w && py >= b.y && py <= b.y + b.h;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_W, SCREEN_H, 32);
    SetMainWindowText("DXLibrary 2D 射的風ゲーム");

    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    std::vector<Building> buildings = CreateBuildings();
    int destroyedCount = 0;

    DWORD startTick = GetNowCount();
    DWORD timeLimitMs = TIME_LIMIT_SEC * 1000;

    bool gameClear = false;
    bool gameOver = false;

    bool prevMouseLeft = false;

    while (ProcessMessage() == 0) {
        ClearDrawScreen();

        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        DWORD now = GetNowCount();
        int elapsed = (int)(now - startTick);
        int remainMs = (int)timeLimitMs - elapsed;
        if (remainMs <= 0 && !gameClear) {
            gameOver = true;
        }

        int mx, my;
        GetMousePoint(&mx, &my);

        int mouseInput = GetMouseInput();
        bool mouseLeft = (mouseInput & MOUSE_INPUT_LEFT) != 0;

        // 左クリック時に照準位置の建物を攻撃
        if (mouseLeft && !prevMouseLeft && !gameOver && !gameClear) {
            for (auto& b : buildings) {
                if (!b.destroyed && PointInRect(mx, my, b)) {
                    b.hp -= DAMAGE;
                    if (b.hp <= 0) {
                        b.destroyed = true;
                        destroyedCount++;
                    }
                }
            }
        }
        prevMouseLeft = mouseLeft;

        // 背景
        DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(64, 164, 255), TRUE);
        DrawBox(0, SCREEN_H - 80, SCREEN_W, SCREEN_H, GetColor(40, 120, 40), TRUE);

        // 建物描画
        for (const auto& b : buildings) {
            if (!b.destroyed) {
                DrawBox(b.x, b.y, b.x + b.w, b.y + b.h, GetColor(200, 200, 200), TRUE);
                for (int xx = b.x + 10; xx < b.x + b.w - 10; xx += 30) {
                    for (int yy = b.y + 10; yy < b.y + b.h - 10; yy += 30) {
                        DrawBox(xx, yy, xx + 14, yy + 14, GetColor(255, 255, 200), TRUE);
                    }
                }
                int barW = b.w;
                int filled = (int)((float)b.hp / (float)b.maxHp * barW);
                DrawBox(b.x, b.y - 12, b.x + barW, b.y - 4, GetColor(0, 0, 0), TRUE);
                DrawBox(b.x + 2, b.y - 10, b.x + 2 + filled - 4, b.y - 6, GetColor(220, 50, 50), TRUE);
                DrawFormatString(b.x, b.y - 26, GetColor(255, 255, 255), "HP: %d/%d", b.hp, b.maxHp);
            }
            else {
                DrawBox(b.x, b.y + b.h - 40, b.x + b.w, b.y + b.h, GetColor(120, 80, 60), TRUE);
                DrawString(b.x + 10, b.y + b.h - 36, "Destroyed", GetColor(255, 255, 255));
            }
        }

        // 照準（マウス位置に追従）
        DrawLine(mx - CROSSHAIR_SIZE, my, mx + CROSSHAIR_SIZE, my, GetColor(255, 255, 255));
        DrawLine(mx, my - CROSSHAIR_SIZE, mx, my + CROSSHAIR_SIZE, GetColor(255, 255, 255));

        // HUD
        int remainSec = remainMs > 0 ? (remainMs + 999) / 1000 : 0;
        DrawFormatString(8, 8, GetColor(255, 255, 255), "Time Left: %d s", remainSec);
        int total = (int)buildings.size();
        DrawFormatString(8, 28, GetColor(255, 255, 255), "Destroyed: %d / %d", destroyedCount, total);
        DrawFormatString(8, 48, GetColor(255, 255, 255), "Damage per hit: %d", DAMAGE);
        DrawFormatString(8, 68, GetColor(255, 255, 255), "Click left mouse to shoot");

        // クリア判定
        if (destroyedCount == total && !gameClear) {
            gameClear = true;
        }

        if (gameClear) {
            DrawBox(200, 200, 600, 360, GetColor(0, 0, 0), TRUE);
            DrawFormatString(300, 240, GetColor(255, 255, 255), "GAME CLEAR!");
            DrawFormatString(260, 280, GetColor(255, 255, 255), "Press ESC to exit");
        }
        else if (gameOver) {
            DrawBox(200, 200, 600, 360, GetColor(0, 0, 0), TRUE);
            DrawFormatString(300, 240, GetColor(255, 255, 255), "TIME UP! GAME OVER");
            DrawFormatString(260, 280, GetColor(255, 255, 255), "Press ESC to exit");
        }

        ScreenFlip();
        WaitTimer(16);
    }

    DxLib_End();
    return 0;
}