#pragma once




extern float angleGraphics[14];
extern float angleHaptics[14];
void OpenHi5Glove();
void CloseHi5Glove();
void GetHi5GloveData();
void CalHandOrient(float *angle);
int CollisionDetection();
void GraphicsRendering(int result_CD);
float *ForceRendering();
