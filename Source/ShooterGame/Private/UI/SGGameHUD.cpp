// Study Shooter Game from Udemy. All Rights Reserved.


#include "UI/SGGameHUD.h"
#include "Engine/Canvas.h"

void ASGGameHUD::DrawHUD()
{
    Super::DrawHUD();
    
    DrawCrossHair();
}

void ASGGameHUD::DrawCrossHair()
{
    const FVector2D CenterPoint(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);
    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(CenterPoint.X - HalfLineSize, CenterPoint.Y, CenterPoint.X + HalfLineSize, CenterPoint.Y, LineColor, LineThickness);
    DrawLine(CenterPoint.X, CenterPoint.Y - HalfLineSize, CenterPoint.X, CenterPoint.Y + HalfLineSize, LineColor, LineThickness);
}
