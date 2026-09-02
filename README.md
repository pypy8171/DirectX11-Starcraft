# YongEngine — DirectX 11 기반 2D/3D 게임 엔진 & 스타크래프트 모작

DirectX 11(Direct3D 11)로 직접 구현한 컴포넌트 기반 게임 엔진과, 그 위에서 동작하는
스타크래프트(프로토스) 모작 게임, 그리고 씬 편집을 위한 **MFC 툴**로 구성된 프로젝트입니다.

엔진 · 게임 로직 · 에디터를 각각 별도 프로젝트로 분리하고, 엔진은 정적 라이브러리로,
게임 로직(Scripts)은 별도 정적 라이브러리로 빌드해 **툴과 게임이 같은 엔진/스크립트 바이너리를 공유**하도록 구성했습니다.

---

## 개발 환경

| 항목 | 내용 |
|---|---|
| 언어 | C++ (Unicode, C++14 이상) |
| 그래픽 API | Direct3D 11 (`d3d11.lib`, `d3dcompiler.lib`) |
| 수학 라이브러리 | DirectXMath / `SimpleMath` (DirectXTK) |
| 사운드 | FMOD |
| 텍스처 로딩 | DirectXTex |
| 에디터 UI | MFC (Dynamic MFC, `CFormView` + `CSplitterWnd`) |
| 툴셋 | Visual Studio (PlatformToolset v143), Windows SDK 10.0 |
| 플랫폼 | Win32(x86) / x64 |

---

## 솔루션 구성

`Client.sln` 하나에 5개의 프로젝트가 들어 있습니다.

| # | 프로젝트 | 종류 | 산출물 | 역할 |
|---|---|---|---|---|
| 00 | **CodeGen** | Console App | `CodeGen.exe` | `04. Scripts`의 헤더를 스캔해 `ScriptMgr.h/.cpp`를 자동 생성 |
| 01 | **Client** | Win32 App | `Game.exe` / `Game64.exe` | 게임 실행 진입점 (윈도우 생성 + 메인 루프) |
| 02 | **Engine** | Static Library | `YongEngine.lib` / `YongEngine64.lib` | 렌더링·리소스·씬·충돌 등 엔진 코어 |
| 03 | **Tool** | MFC App | `03. Tool.exe` | 씬 에디터 (아래 [MFC 툴](#mfc-툴-씬-에디터) 참고) |
| 04 | **Scripts** | Static Library | `Scripts.lib` / `Scripts64.lib` | 스타크래프트 게임 로직 (유닛·건물·UI·스킬 등) |

**의존 관계**

```
        02. Engine (YongEngine.lib)
              ▲            ▲
              │            │
     04. Scripts (Scripts.lib)
              ▲            ▲
              │            │
        01. Client     03. Tool
        (Game.exe)   (03. Tool.exe)

        00. CodeGen ──▶ 04. Scripts/ScriptMgr.h, ScriptMgr.cpp 생성
```

프로젝트 간 헤더 공유는 직접 참조가 아니라 **`Project/Include/` 로 헤더를 복사**하는 방식입니다.
(`EngineCopy.bat`, `ScriptCopy.bat` — 아래 [빌드 방법](#빌드-방법) 참고)

---

## 디렉터리 구조

```
YongEngine/
├─ Client.sln
├─ EngineCopy.bat            # Engine 헤더(.h/.inl) → Include/YongEngine, 셰이더(.fx) → content/Shader 복사
├─ ScriptCopy.bat            # Scripts 헤더(.h) → Include/Scripts 복사 (exclude.txt 제외 목록 사용)
├─ exclude.txt               # 복사 제외 헤더 (stdafx.h, targetver.h)
│
├─ Project/
│  ├─ 00. CodeGen/           # 스크립트 등록 코드 자동 생성기
│  ├─ 01. Client/            # WinMain, 윈도우 생성, 메시지 루프
│  ├─ 02. Engine/            # 엔진 코어 (+ .fx 셰이더 원본)
│  ├─ 03. Tool/              # MFC 씬 에디터
│  ├─ 04. Scripts/           # 게임 로직 스크립트
│  ├─ Include/               # 빌드 시 참조하는 헤더 모음 (배치로 채워짐 / 외부 라이브러리 헤더)
│  └─ Library/               # 정적 라이브러리 출력 (빌드 산출물, 저장소 미포함)
│
└─ Game_Release/
   ├─ bin/                   # 실행 파일 (빌드 산출물, 저장소 미포함)
   └─ content/
      ├─ Scene/              # 툴로 저장한 씬 데이터 (.scene)
      ├─ Prefab/             # 프리팹 데이터
      ├─ Shader/             # 컴파일 대상 .fx 셰이더
      ├─ Texture/  Sound/  Resource/   # 게임 리소스 (저장소 미포함)
      └─ Mesh/
```

> 저장소에는 **소스 코드 + 프로젝트 설정 + 툴로 만든 씬/셰이더 데이터**만 포함되어 있습니다.
> 빌드 산출물(`.vs/`, `Debug/`, `Release/`, `x64/`, `.lib`, `.exe`, `.pdb` 등)과
> 원본 게임에서 추출한 텍스처·사운드 리소스는 `.gitignore`로 제외했습니다.

---

## 엔진 아키텍처

### 1. 실행 흐름

```
WinMain (01. Client)
   └─ CCore::init(hWnd, 1280x720)
        ├─ CDevice      : D3D11 Device / SwapChain / RenderTarget / DepthStencil 생성
        ├─ CKeyMgr      : 키 상태 테이블 초기화
        ├─ CTimeMgr     : QPC 기반 DeltaTime
        ├─ CRenderMgr   : BlendState / DepthStencilState 생성
        ├─ CShaderMgr   : .fx 컴파일 및 셰이더 등록
        ├─ CResMgr      : 기본 Mesh / Material 생성, 사운드 초기화
        ├─ CSceneMgr    : 시작 씬 구성
        └─ 상수 버퍼 생성 (아래 표)
   └─ while(메시지 루프) → CCore::progress()
```

`CCore::progress()` 한 프레임은 다음 순서로 진행됩니다.

| 단계 | 내용 |
|---|---|
| `update` | `CKeyMgr` → `CTimeMgr` → `CSceneMgr`(awake/start/update/lateupdate/finalupdate) → `CEventMgr` |
| `render` | `CDevice::ClearTarget` → `CRenderMgr::render` → `CDevice::Present` |

`CEventMgr`는 오브젝트 생성/삭제, 씬 전환처럼 **순회 중에 바로 처리하면 위험한 작업**을
이벤트로 큐잉했다가 프레임 끝에서 일괄 처리합니다.

### 2. 씬 구조 (Scene → Layer → GameObject → Component)

```
CScene
 └─ CLayer  [최대 32개, MAX_LAYER]
     └─ CGameObject   (부모/자식 계층 구조 지원)
         ├─ CTransform      (필수)
         ├─ CMeshRender     (Mesh + Material)
         ├─ CCollider
         ├─ CCamera
         ├─ CAnimator2D     (CAnimation2D 프레임 정보)
         ├─ CGrid
         └─ vector<CScript> (게임 로직, 04. Scripts)
```

- `CGameObject`는 컴포넌트를 타입별 슬롯으로 보유하고, 스크립트만 `vector`로 다중 부착합니다.
- 업데이트는 `update → lateupdate → finalupdate` 3단계로 나뉘며,
  월드 행렬 갱신·충돌체 등록 등 "모든 로직이 끝난 뒤에 해야 하는 일"은 `finalupdate`에서 처리합니다.
- 모든 엔진 객체는 `CEntity`를 상속해 고유 ID와 이름을 가지며,
  `CLONE(type)` 매크로로 복제(프리팹 인스턴싱)를 지원합니다.

### 3. 리소스 관리 — 참조 카운팅 스마트 포인터

```cpp
Ptr<CTexture> pTex = CResMgr::GetInst()->Load<CTexture>(L"Terran", L"Texture/terran.png");
```

- `CRes`(Mesh / Texture / Material / Sound / Prefab의 부모)가 참조 카운트를 들고 있고,
  `Ptr<T>`가 대입·복사·소멸 시점에 `AddRef` / `SubRef`를 자동 호출합니다.
- `CResMgr`는 `map<wstring, CRes*>`를 리소스 타입별 배열로 관리하고,
  `typeid` 비교로 템플릿 인자 `T`에 맞는 타입 슬롯을 결정합니다.
- 리소스는 **키 + 상대 경로**로 관리되어 씬 파일에 경로만 직렬화됩니다.

### 4. 렌더링

- **`CDevice`** — Device / DeviceContext / SwapChain / RTV / DSV / Viewport, `CConstBuffer` 관리
- **`CRenderMgr`** — 블렌드 상태(`BLEND_TYPE`) · 뎁스 스텐실 상태(`DEPTH_STENCIL_TYPE`) 보관, 라이트 목록 수집 후 렌더 수행
- **`CShaderMgr`** — `.fx` 셰이더 컴파일 및 관리 (`std.fx`, `skybox.fx`, `value.fx`, `test.fx`)
- **`CMaterial`** — 셰이더 + 텍스처 + 파라미터 묶음
- 정점 포맷 `VTX` : Position / Color / UV / Tangent / Binormal / Normal (노멀 매핑 대응)

**상수 버퍼 슬롯**

| 슬롯 | 이름 | 내용 |
|---|---|---|
| b0 | `Transform` | World / View / Proj / WV / WVP / InvWorld |
| b1 | `ShaderParam` | 머티리얼 파라미터 |
| b2 | `Anim2DInfo` | 2D 애니메이션 프레임 UV 정보 |
| b3 | `LightInfo` | 라이트 정보 ×10 |
| b4 | `Global` | 전역 값 |

### 5. 충돌 처리

- `CCollisionMgr`가 **레이어 단위 충돌 행렬**을 관리 (`m_iColliderCheck[MAX_LAYER]` 비트마스크).
- 충돌 쌍은 두 콜라이더의 ID를 `union CID`로 `ULONGLONG` 한 개로 합쳐 `map`에 저장하고,
  이전 프레임 상태와 비교해 `OnCollisionEnter / Stay / Exit`를 구분해 호출합니다.

### 6. 기타

- **사운드** — FMOD 래핑 (`CSound`), `CResMgr::SoundInit()`에서 시스템 초기화
- **멀티스레드** — `CThread` / `CThreadMgr` / `CLoadingThread`로 리소스 비동기 로딩
- **난수** — `well512.h` (WELL512 알고리즘)
- **경로** — `CPathMgr`가 실행 파일 기준 `content/` 상대 경로를 해석

---

## 스크립트 시스템 & 코드 자동 생성

게임 로직은 엔진과 분리해 `04. Scripts` 프로젝트에 `CScript` 파생 클래스로 작성합니다.
(유닛 51종 이상: `ZealotScript`, `DragoonScript`, `CarrierScript`, `ArbiterScript` …
매니저: `UnitMgr`, `BuildingMgr`, `SkillMgr`, `UpgradeMgr`, `TileMgr`, `UIMgr`, `NumberMgr` …)

문제는 **툴에서 "스크립트 이름"을 보고 실제 객체를 생성해야 한다**는 점입니다.
스크립트를 추가할 때마다 문자열 ↔ 클래스 매핑 코드를 손으로 고치는 대신,
`00. CodeGen`이 이 코드를 자동 생성합니다.

```
00. CodeGen 실행
  ├─ Project/04. Scripts/*.h 스캔 (stdafx.h, targetver.h, ScriptMgr.h, SingleTonScript.h 제외)
  └─ 생성물
      ├─ ScriptMgr.h   : enum class SCRIPT_TYPE { ARBITERSCRIPT, ARCHONSCRIPT, ... , END }
      └─ ScriptMgr.cpp : GetScriptInfo() / GetScript(이름→객체) / GetScriptName(객체→이름)
```

덕분에 스크립트 파일 하나만 추가하면 **툴의 스크립트 목록·씬 저장/로드가 자동으로 대응**됩니다.

---

## MFC 툴 (씬 에디터)

`03. Tool`은 엔진을 그대로 링크한 **MFC 기반 씬 에디터**입니다.
게임과 동일한 엔진 코드로 렌더링하기 때문에, 툴에서 보이는 화면이 곧 게임 화면입니다.

### 엔진 루프와 MFC 메시지 루프의 결합

MFC는 자체 메시지 루프를 돌기 때문에 게임 루프를 넣을 자리가 없습니다.
`CToolApp::OnIdle()`을 오버라이드해 **유휴 시간마다 엔진 한 프레임 + 툴 UI 갱신**을 돌립니다.

```cpp
BOOL CToolApp::OnIdle(LONG lCount)
{
    CCore::GetInst()->progress();              // 엔진 1프레임 (update + render)
    ((CMainFrame*)m_pMainWnd)->update();       // 뷰/다이얼로그 값 갱신
    return CWinApp::OnIdle(0);
}
```

렌더링 대상 윈도우는 `CMainFrame::GetGameViewHwnd()`가 돌려주는 **GameView의 HWND**로,
`CDevice` 초기화 시 이 핸들을 넘겨 툴 내부 뷰에 곧바로 그리도록 했습니다.

### 창 레이아웃 (이중 `CSplitterWnd`)

`CMySplitterWnd`(스플리터 바 고정용 파생 클래스) 2개를 중첩해 화면을 나눕니다.

```
CMainFrame
└─ m_MainSplitter (1행 × 3열)
   ├─ (0,0) m_SubSplitter (3행 × 1열)
   │        ├─ (0,0) CBtnView        상단 툴바 — 오브젝트 생성/저장/로드 등 기능 버튼
   │        ├─ (1,0) CGameView       엔진 렌더링 화면 + 마우스 피킹/드래그
   │        └─ (2,0) CDbgView        디버그 출력
   ├─ (0,1) CHierachyView            씬 계층 + 리소스 목록
   └─ (0,2) CComponentView           선택 오브젝트의 컴포넌트 인스펙터
```

| 뷰 | 클래스 | 담당 |
|---|---|---|
| 게임 뷰 | `CGameView` | 엔진 출력 화면. `OnLButtonDown/Up`, `OnRButtonDown`, `OnMouseMove`로 오브젝트 선택·이동 처리 |
| 버튼 뷰 | `CBtnView` | 오브젝트 생성, 씬 저장/불러오기 등 커맨드 |
| 디버그 뷰 | `CDbgView` | 로그·상태 표시 |
| 하이라키 뷰 | `CHierachyView` | `CHierachyDlg`(오브젝트 트리) + `CResDlg`(리소스 트리) 보유 |
| 컴포넌트 뷰 | `CComponentView` | 컴포넌트별 다이얼로그를 배열로 보유, 선택 오브젝트에 있는 컴포넌트의 다이얼로그만 표시 |

### 인스펙터 — 컴포넌트 다이얼로그

모든 인스펙터 패널은 `CComponentDlg`(`CDialogEx` 파생) 를 상속한 **자식 다이얼로그**이며,
`CComponentView`가 `COMPONENT_DLG` 열거값을 인덱스로 하는 배열에 담아 관리합니다.

```cpp
class CComponentDlg : public CDialogEx
{
    virtual void init() {}
    virtual void update(CGameObject* _pTargetObj) = 0;   // 매 프레임 대상 오브젝트 값 반영
    ...
};
```

| 다이얼로그 | 편집 대상 |
|---|---|
| `CTransformDlg` | 위치 / 회전 / 크기 |
| `CMeshRenderDlg` | Mesh · Material · Texture 지정 |
| `CColliderDlg` | 충돌체 오프셋 / 크기 |
| `CCameraDlg` | 투영 방식, 시야각, 렌더 레이어 |
| `CAnimator2DDlg` | 2D 애니메이션 프레임 편집 |
| `CGridDlg` | 그리드(타일) 설정 |
| `CScriptDlg` | 스크립트 부착/제거 (`ScriptMgr`의 자동 생성 목록 사용) |
| `CLayerDlg` | 레이어 이름 및 충돌 레이어 설정 |
| `CListDlg` | 리소스·스크립트 선택용 공용 리스트 팝업 |
| `CTreeDlg` | 트리 컨트롤 공용 베이스 (`CHierachyDlg`, `CResDlg`의 부모) |

`update()`가 순수 가상 함수이므로 **컴포넌트를 새로 만들면 다이얼로그만 추가**하면 되고,
편집 도중 에디트 컨트롤 포커스 여부(`m_bEditFocus`)를 추적해
**입력 중에는 게임 뷰의 키 입력이 먹지 않도록** 처리했습니다.

### 하이라키 / 리소스 트리

- `CHierachyDlg` — 씬의 오브젝트를 트리로 표시. **드래그 앤 드롭으로 부모-자식 관계 변경**
  (`MoveItem`, `GetChildItem`으로 하위 아이템까지 함께 이동), 아이템 삭제 지원
- `CResDlg` — `content/` 폴더를 확장자별로 스캔해(`DataLoad`) Texture / Prefab / Sound 등을
  리소스 타입별 트리로 표시하고, 선택 시 인스펙터에 연결

### 씬 저장 / 불러오기

`CSaveLoadMgr`가 씬 전체를 바이너리로 직렬화합니다.

```
SaveScene(경로)
 ├─ SaveResource : 씬에서 사용하는 리소스 키·경로 기록
 ├─ SavePrefab   : 프리팹 목록 별도 파일로 저장
 └─ SaveLayer → SaveGameObject (재귀: 자식 오브젝트 포함)
        └─ 각 CComponent::Save(FILE*) 가상 함수로 컴포넌트별 데이터 기록

LoadScene(경로)  — 위 순서를 그대로 역으로 복원 (CComponent::Load)
```

저장 포맷을 컴포넌트가 스스로 정의(`virtual void Save/Load(FILE*)`)하므로,
컴포넌트를 추가해도 저장 코드를 한 곳에서 고칠 필요가 없습니다.
결과물은 `Game_Release/content/Scene/*.scene`으로 저장되며, 게임은 이 파일을 그대로 로드합니다.
(저장소에 포함된 `map-1 ~ map-5`, `UI`, `UnitStructure` 등이 실제 툴 산출물입니다.)

---

## 빌드 방법

1. **Visual Studio**(v143 툴셋, Windows SDK 10.0)로 `Client.sln`을 엽니다.
2. FMOD / DirectXTex / FBX SDK 헤더·라이브러리를 `Project/Include/`, `Project/Library/` 아래에 배치합니다.
3. **헤더 복사 배치를 먼저 실행합니다.** (`Project/Include/`는 저장소에 포함되지 않고 이 배치로 채워집니다)
   ```bat
   EngineCopy.bat     :: Engine 헤더 → Include/YongEngine, .fx → content/Shader
   ScriptCopy.bat     :: Scripts 헤더 → Include/Scripts
   ```
4. 다음 순서로 빌드합니다.
   ```
   02. Engine  →  00. CodeGen 실행(ScriptMgr 생성)  →  04. Scripts  →  01. Client / 03. Tool
   ```
5. 실행 파일은 구성에 따라 `Game_Debug/bin/` 또는 `Game_Release/bin/`에 생성되며,
   `content/` 폴더를 기준으로 리소스를 로드합니다.

> **리소스 안내** — 텍스처·사운드는 원본 게임에서 추출한 자산이라 저장소에 포함하지 않았습니다.
> 실행하려면 `Game_Release/content/Texture`, `Sound`, `Resource` 폴더를 별도로 준비해야 합니다.

---

## 이 프로젝트에서 다룬 것

- Direct3D 11 파이프라인 직접 구성 (Device / SwapChain / 상수 버퍼 / 블렌드·뎁스 상태 / 셰이더 관리)
- Unity 스타일의 **GameObject–Component 구조**와 3단계 업데이트 파이프라인
- **참조 카운팅 기반 리소스 관리** (`CRes` + `Ptr<T>` + `CResMgr`)
- 레이어 충돌 행렬과 충돌 쌍 ID 해싱을 이용한 **충돌 상태 추적**
- 지연 이벤트 처리(`CEventMgr`)로 순회 중 객체 생성/삭제 안전성 확보
- **MFC 에디터와 게임 엔진 루프의 결합**, 뷰/다이얼로그 기반 인스펙터 UI
- 컴포넌트가 직렬화를 책임지는 **확장 가능한 씬 저장 포맷**
- 스크립트 등록 코드 **자동 생성기(CodeGen)** 로 반복 작업 제거
