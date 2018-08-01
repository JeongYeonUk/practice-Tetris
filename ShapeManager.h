#pragma once

#include "value.h"

class CShapeManager
{
private:
	CShapeManager();
	~CShapeManager();

private:
	static CShapeManager* m_pInst;

public:
	static CShapeManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CShapeManager;
		return m_pInst;
	}

	static void DestoryInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	class CShape* m_pCurShape;
	class CShape* m_pNextShape;
	int m_iSpeed;

public:
	void Update();
	void Render();
	class CShape* CreateRandomShape();
	class CShape* CreateShape(SHAPE_TYPE eType);
};

