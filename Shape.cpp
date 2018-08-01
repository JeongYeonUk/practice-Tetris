#include "Shape.h"
#include "Core.h"
#include "Stage.h"
#include "StageManager.h"

CShape::CShape()
{
	m_iDir = RD_UP;
	m_iWidthCount = 0;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_cShape[i][j] = '1';
		}
	}
}


CShape::~CShape()
{
}

bool CShape::Init()
{
	m_tPivot.x = 0;
	m_tPivot.y = 3;

	return true;
}

void CShape::Rotation()
{
}

void CShape::Render()
{
	for (int i = 0; i < 4; ++i)
	{
		int iYindex = m_tPos.y - (3 - i);
		if (iYindex < 0)
			continue;
		for (int j = 0; j < 4; ++j)
		{
			if (m_tPos.x + j >= STAGE_WIDTH)
				continue;			

			if (m_cShape[i][j] == '0')
			{
				CCore::GetInst()->SetConsolePos(m_tPos.x + j, iYindex);
				cout << "бс";
			}
		}
		cout << endl;
	}
}

void CShape::RenderNext()
{
	for (int i = 0; i < 4; ++i)
	{
		int iYindex = m_tPos.y - (3 - i);
		if (iYindex < 0)
			continue;

		
		for (int j = 0; j < 4; ++j)
		{
			if (m_cShape[i][j] == '0')
			{
				CCore::GetInst()->SetConsolePos(m_tPos.x+j, iYindex);
				cout << "бс";
			}
		}
	}
}

bool CShape::MoveDown()
{
	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_cShape[i][j] == '0')
			{
				if (pStage->CheckBlock(m_tPos.x + j, m_tPos.y - (2 - i)))
				{
					return true;
				}
			}
		}
	}

	++m_tPos.y;

	return false;
}

void CShape::MoveLeft()
{
	
	if (m_tPos.x == 0 )
		return;

	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_cShape[i][j] == '0')
			{
				if (pStage->CheckBlock(m_tPos.x + j - 1, m_tPos.y - (3 - i)))
				{
					return;
				}
			}
		}
	}

	--m_tPos.x;
}

void CShape::MoveRight()
{
	if (m_tPos.x + m_iWidthCount == STAGE_WIDTH)
		return;

	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_cShape[i][j] == '0')
			{
				if (pStage->CheckBlock(m_tPos.x + j + 1, m_tPos.y - (3 - i)))
				{
					for (int k = 0; k < 4; ++k)
					{
						for (int l = 0; l < 4; ++l)
						{
							if (m_cShape[k][l] == '0')
							{
								if (m_tPos.y - (3 - k) < 0)
								{
									CCore::GetInst()->End();
									break;
								}
							}
						}
					}

					return;
				}
			}
		}
	}

	++m_tPos.x;
}
