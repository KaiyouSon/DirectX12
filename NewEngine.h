#pragma once

void NewEngineInit();
void NewEngineEnd();
void ProcessMessage();

// ウインドウ関連
void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);
void SetWindowTitle(const wchar_t* TITLE);
bool CloseWindow();
void SetBackgroundColor(int Red, int Green, int Blue);
void NewEnginePreDraw();
void NewEnginePostDraw();