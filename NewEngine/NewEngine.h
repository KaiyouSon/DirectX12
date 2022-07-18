#pragma once
#include <string>

void NewEngineInit();
void NewEngineUpda();
void NewEnginePreDraw();
void NewEngineSetDraw3D();
void NewEngineSetDraw2D();
void NewEngineSetDrawLine();
void NewEnginePostDraw();
void NewEngineEnd();

// �E�C���h�E�֘A
bool ProcessMessage();
void SetWindowSize(int WIN_WIDTH, int WIN_HEIGHT);
void SetWindowTitle(const std::string TITLE);
void SetBackgroundColor(float Red, float Green, float Blue);
