#include "ShapeManager.h"
#include "Rectangle.h"
#include "ShapeGun.h"
#include "ShapeRGun.h"
#include "ShapeLine.h"
#include "ShapeT.h"
#include "ShapeS.h"
#include "ShapeZ.h"
#include "Shape.h"
#include "StageManager.h"
#include "Stage.h"

CShapeManager* CShapeManager::m_pInst = nullptr;

CShapeManager::CShapeManager() :
	m_pCurShape(nullptr),
	m_pNextShape(nullptr)
{
	m_pCurShape = CreateRandomShape();
	m_pNextShape = CreateRandomShape();
	m_iSpeed = 0;
}


CShapeManager::~CShapeManager()
{
	SAFE_DELETE(m_pCurShape);
	SAFE_DELETE(m_pNextShape);
}

void CShapeManager::Update()
{
	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	++m_iSpeed;

	if (pStage->GetSpeed() == m_iSpeed)
	{
		if (m_pCurShape->MoveDown())
		{
			pStage->AddBlock(m_pCurShape, m_pCurShape->GetPosition());

			SAFE_DELETE(m_pCurShape);

			m_pCurShape = m_pNextShape;
			m_pCurShape->SetPosition(4, 0);

			m_pNextShape = CreateRandomShape();
		}
		m_iSpeed = 0;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_pCurShape->MoveLeft();
	}

	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_pCurShape->MoveRight();
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_pCurShape->Rotation();
	}
}

void CShapeManager::Render()
{
	m_pCurShape->Render();

	m_pNextShape->SetPosition(13, 3);
	m_pNextShape->RenderNext();
}

CShape * CShapeManager::CreateRandomShape()
{
	int iType = rand() % ST_END;

	return CreateShape((SHAPE_TYPE)iType);
}

CShape * CShapeManager::CreateShape(SHAPE_TYPE eType)
{
	CShape* pShape = nullptr;

	switch (eType)
	{
	case ST_RECT:
		pShape = new CRectangle;
		break;
	case ST_GUN:
		pShape = new CShapeGun;
		break;
	case ST_RGUN:
		pShape = new CShapeRGun;
		break;
	case ST_LINE:
		pShape = new CShapeLine;
		break;
	case ST_T:
		pShape = new CShapeT;
		break;
	case ST_S:
		pShape = new CShapeS;
		break;
	case ST_Z:
		pShape = new CShapeZ;
		break;
	}

	if (!pShape->Init())
	{
		SAFE_DELETE(pShape);
		return nullptr;
	}

	return pShape;
}
