#pragma once

class CTexture;

class CTestSceneMaker
{

public:
	static void EditorScene();

	static void AddPrefab(const wstring& _strName, CTexture* _pTex);

	static void InitSound();

	static void StudyScene();

public:
	CTestSceneMaker();
	~CTestSceneMaker();

public:
	static void init();
};

