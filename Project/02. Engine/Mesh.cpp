#include "Mesh.h"

#include "Device.h"

#include "Shader.h"


CMesh::CMesh()
	: m_pIB(NULL)
	, m_pLayout(NULL)
	, m_pInstanceBuff(NULL)
	, m_iVtxSize(0)
	, m_iVtxCount(0)
	, m_iIdxSize(0)
	, m_iIdxCount(0)
	, m_pVtxMem(nullptr)
	, m_pIdxMem(nullptr)
	, m_eTopology(D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	for (int i = 0; i < RENDERTARGET_NUM; ++i)
	{
		m_pVB[i] = NULL;
	}
}


CMesh::~CMesh()
{
	for (int i = 0; i < RENDERTARGET_NUM; ++i)
	{
		SAFE_RELEASE(m_pVB[i]);
	}
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_pLayout);
	SAFE_RELEASE(m_pInstanceBuff);
}


CMesh * CMesh::Create(void * _pVtx, UINT _iVtxSize, UINT _iVtxCount, D3D11_USAGE _eVtxUsage, void * _pIdx, UINT _iIdxSize, UINT _iIdxCount, D3D11_USAGE _eIdxUsage, D3D_PRIMITIVE_TOPOLOGY _eTopology)
{
	// Vtx Buffer 생성
	D3D11_BUFFER_DESC tVtxBufferDesc = {};
	tVtxBufferDesc.ByteWidth = _iVtxSize * _iVtxCount;
	tVtxBufferDesc.Usage = _eVtxUsage; // 두개 같이 usage spuaccessflags 바꿀 수 있게 하는 파라미터
	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == tVtxBufferDesc.Usage)
	{
		tVtxBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	tVtxBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA tVtxSubData = {};
	tVtxSubData.pSysMem = _pVtx; // arrVTX //&mInstancedData

	ID3D11Buffer* pVtxBuff = NULL;
	if (FAILED(DEVICE->CreateBuffer(&tVtxBufferDesc, &tVtxSubData, &pVtxBuff)))
	{
		return NULL;
	}


	// Idx Buffer 생성
	D3D11_BUFFER_DESC tIdxBufferDesc = {};
	tIdxBufferDesc.ByteWidth = _iIdxSize * _iIdxCount; // 삼각형 갯수
	tIdxBufferDesc.Usage = _eIdxUsage;
	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == tIdxBufferDesc.Usage)
	{
		tIdxBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	tIdxBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA tIdxSubData = {};
	tIdxSubData.pSysMem = _pIdx;

	ID3D11Buffer* pIdxBuff = NULL;
	if (FAILED(DEVICE->CreateBuffer(&tIdxBufferDesc, &tIdxSubData, &pIdxBuff)))
	{
		return NULL;
	}

	//vector<InstancedData> m_vInstancedData;
	//const int n = 1;
	//m_vInstancedData.resize(n*n*n);

	//m_vInstancedData[0].World = XMFLOAT4X4(
	//	0.5f, 0.f, 0.f, 0.f,
	//	0.f, 0.5f, 0.f, 0.f, //*cos(90*3.14/180)
	//	0.f, 0.f, 0.5f, 0.f, //*sin(270*3.14/180)
	//	100.f, 100.f, 100.f, 1.f);

	//D3D11_BUFFER_DESC tInstBufferDesc;
	//tInstBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//tInstBufferDesc.ByteWidth = sizeof(InstancedData)*m_vInstancedData.size();
	//tInstBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//tInstBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//tInstBufferDesc.MiscFlags = 0;
	//tInstBufferDesc.StructureByteStride = 0;

	//D3D11_SUBRESOURCE_DATA tSubData = {};
	//tSubData.pSysMem = &m_vInstancedData; // arrVTX //&mInstancedData

	//ID3D11Buffer* pInstanceBuffer = NULL;
	//if (FAILED(DEVICE->CreateBuffer(&tInstBufferDesc, &tSubData, &pInstanceBuffer)))
	//{
	//	return NULL;
	//}

	CMesh* pMesh = new CMesh;

	pMesh->m_pVB[0] = pVtxBuff;
	pMesh->m_iVtxSize = _iVtxSize;
	pMesh->m_iVtxCount = _iVtxCount;
	pMesh->m_tVtxDesc = tVtxBufferDesc;

	pMesh->m_pIB = pIdxBuff;
	pMesh->m_iIdxSize = _iIdxSize;
	pMesh->m_iIdxCount = _iIdxCount;
	pMesh->m_tIdxDesc = tIdxBufferDesc;

	//pMesh->m_pInstanceBuff = pInstanceBuffer;
	//pMesh->m_tInstDesc = tInstBufferDesc;
	pMesh->m_eTopology = _eTopology;

	// Layout 만들기
	// 하나의 정점 구성이 어떻게 되어있는지를 알려서
	// vertex 쉐이더에서 원하는 정보만 추출해서 가져갈 수 있도록 알림
	int iOffset = 0;

	// sementicname, sementicindex, format, inputslot, offset, inputslotclass, instancedatasteprate
	D3D11_INPUT_ELEMENT_DESC tLayoutDesc[6] = {
		//{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, 0, D3D11_INPUT_PER_VERTEX_DATA ,0 },
		//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT , 0, GetSizeofFormat(DXGI_FORMAT_R32G32B32_FLOAT), D3D11_INPUT_PER_VERTEX_DATA ,0 },
		//{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT , 0, GetSizeofFormat(DXGI_FORMAT_R32G32B32_FLOAT) + GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT), D3D11_INPUT_PER_VERTEX_DATA ,0 },

		//{ "WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT , 1, GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT) * 0, D3D11_INPUT_PER_INSTANCE_DATA ,1 },
		//{ "WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT , 1, GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT) * 1, D3D11_INPUT_PER_INSTANCE_DATA ,1 },
		//{ "WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT , 1, GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT) * 2, D3D11_INPUT_PER_INSTANCE_DATA ,1 },
		//{ "WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT , 1, GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT) * 3, D3D11_INPUT_PER_INSTANCE_DATA ,1 }
	};

	tLayoutDesc[0].SemanticName = "POSITION"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
	tLayoutDesc[0].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
	tLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tLayoutDesc[0].InputSlot = 0;
	tLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc[0].InstanceDataStepRate = 0; // 인스턴싱 할때 
	tLayoutDesc[0].AlignedByteOffset = iOffset;

	iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32_FLOAT);

	tLayoutDesc[1].SemanticName = "COLOR"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
	tLayoutDesc[1].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
	tLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	tLayoutDesc[1].InputSlot = 0;
	tLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc[1].InstanceDataStepRate = 0; // 인스턴싱 할때 
	tLayoutDesc[1].AlignedByteOffset = iOffset;

	iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32A32_FLOAT);

	tLayoutDesc[2].SemanticName = "TEXCOORD"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
	tLayoutDesc[2].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
	tLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	tLayoutDesc[2].InputSlot = 0;
	tLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc[2].InstanceDataStepRate = 0; // 인스턴싱 할때 
	tLayoutDesc[2].AlignedByteOffset = iOffset;

	iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32_FLOAT);

	tLayoutDesc[3].SemanticName = "TANGENT"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
	tLayoutDesc[3].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
	tLayoutDesc[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tLayoutDesc[3].InputSlot = 0;
	tLayoutDesc[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc[3].InstanceDataStepRate = 0; // 인스턴싱 할때 
	tLayoutDesc[3].AlignedByteOffset = iOffset;

	iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32_FLOAT);

	tLayoutDesc[4].SemanticName = "BINORMAL"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
	tLayoutDesc[4].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
	tLayoutDesc[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tLayoutDesc[4].InputSlot = 0;
	tLayoutDesc[4].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc[4].InstanceDataStepRate = 0; // 인스턴싱 할때 
	tLayoutDesc[4].AlignedByteOffset = iOffset;

	iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32_FLOAT);

	tLayoutDesc[5].SemanticName = "NORMAL"; // 버텍스 쉐이더랑 일치하는 시멘틱 이름
	tLayoutDesc[5].SemanticIndex = 0;			// 같은 시멘틱에 대한 offset 인덱스
	tLayoutDesc[5].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	tLayoutDesc[5].InputSlot = 0;
	tLayoutDesc[5].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tLayoutDesc[5].InstanceDataStepRate = 0; // 인스턴싱 할때 
	tLayoutDesc[5].AlignedByteOffset = iOffset;

	iOffset += GetSizeofFormat(DXGI_FORMAT_R32G32B32_FLOAT);

	for (UINT i = 0; i < 6; ++i)
	{
		pMesh->m_vecLayout.push_back(tLayoutDesc[i]);
	}

	return pMesh;
}

void CMesh::UpdateData()
{
}

void CMesh::SetShader(CShader * _pShader)
{
	if (m_pVtxBlob == _pShader->GetVSBlob())
		return;

	m_pVtxBlob = _pShader->GetVSBlob();

	SAFE_RELEASE(m_pLayout);
	DEVICE->CreateInputLayout(&m_vecLayout[0], m_vecLayout.size(), m_pVtxBlob->GetBufferPointer(), m_pVtxBlob->GetBufferSize(), &m_pLayout);
}

void CMesh::render()
{
	CONTEXT->IASetInputLayout(m_pLayout); // 정점 구조 알리기

	//UINT iStride[2] = { m_iVtxSize, sizeof(InstancedData) };	// 정점 한개의 간격(버퍼내에서 다음 정점으로 이동하기 위한 정보)
	//UINT iOffset[2] = { 0,0 };			// 버퍼내에서 몇번째 정점부터 렌더링 할지 결정
	//ID3D11Buffer* pBuffer[2] = {};
	//pBuffer[0] = m_pVB[0];
	//pBuffer[1] = m_pInstanceBuff;

	//CONTEXT->IASetVertexBuffers(0, 2, pBuffer, iStride, iOffset);
	//CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 3D 모델의 기본 구성요소 도형형태 지정
	//CONTEXT->IASetIndexBuffer(m_pIB, DXGI_FORMAT_R32_UINT, 0); // 하나에 4바이트

	//CONTEXT->DrawIndexedInstanced(36, 2, 0, 0, 0);  // m_iIdxCount

	UINT iStride = m_iVtxSize;	// 정점 한개의 간격(버퍼내에서 다음 정점으로 이동하기 위한 정보)
	UINT iOffset = 0;		// 버퍼내에서 몇번째 정점부터 렌더링 할지 결정

	CONTEXT->IASetVertexBuffers(0, 1, &m_pVB[0], &iStride, &iOffset);
	CONTEXT->IASetPrimitiveTopology(m_eTopology); // 3D 모델의 기본 구성요소 도형형태 지정, D3D11_PRIMITIVE_TOPOLOGY_LINELIST
	CONTEXT->IASetIndexBuffer(m_pIB, DXGI_FORMAT_R32_UINT, 0); // 하나에 4바이트
	CONTEXT->DrawIndexed(m_iIdxCount,0,0);  // m_iIdxCount
}

void CMesh::FileSave(FILE * _pFile)
{
}

void CMesh::FileLoad(FILE * _pFile)
{
}