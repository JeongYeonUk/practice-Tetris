#include "StageManager.h"
#include "Stage.h"

CStageManager* CStageManager::m_pInst = nullptr;

CStageManager::CStageManager() :
	m_pCurStage(nullptr)
{
}


CStageManager::~CStageManager()
{
	
}

bool CStageManager::Init()
{
	m_pCurStage = new CStage;

	if (!m_pCurStage->Init())
		return false;

	return true;
}

void CStageManager::Run()
{
	m_pCurStage->Render();
}
