#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"
CCore* CCore::m_pInst = nullptr;

CCore::CCore() :
	m_bLoop(true)
{
	srand((unsigned int)time(0));
}


CCore::~CCore()
{
	CShapeManager::DestoryInst();
	CStageManager::DestoryInst();
}

bool CCore::Init()
{
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	if (!CStageManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	while (m_bLoop)
	{
		system("cls");
		CShapeManager::GetInst()->Update();

		CStageManager::GetInst()->Run();
		CShapeManager::GetInst()->Render();

		Sleep(100);
	}
}

void CCore::SetConsolePos(int x, int y)
{
	COORD pos = { (x+1) * 2, y };
	SetConsoleCursorPosition(m_hConsole, pos);
}
