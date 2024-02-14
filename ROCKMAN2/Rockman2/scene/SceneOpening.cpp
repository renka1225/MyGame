#include "SceneOpening.h"
#include "Pad.h"
#include "DxLib.h"

SceneOpening::SceneOpening():
	m_isSceneStart(false),
	m_moveFrame(0)
{
	m_opMove = LoadGraph("data/op.ogv");
}

SceneOpening::~SceneOpening()
{
	DeleteGraph(m_opMove);
}

void SceneOpening::Init()
{
	m_isSceneStart = false;
	m_moveFrame = 0;
	SeekMovieToGraph(m_opMove, 0);

	if (GetMovieStateToGraph(m_opMove) == 0)
	{
		PlayMovieToGraph(m_opMove);
	}
	
}

void SceneOpening::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_moveFrame++;
	
	if(m_moveFrame > 1200 || Pad::IsTrigger(pad & PAD_INPUT_A) || Pad::IsTrigger(pad & PAD_INPUT_B) || Pad::IsTrigger(pad & PAD_INPUT_C) || Pad::IsTrigger(pad & PAD_INPUT_X))
	{
		// “®‰æ‚ðˆêŽž’âŽ~
		PauseMovieToGraph(m_opMove);
		StopSoundMem(m_opMove);
		m_isSceneStart = true;

	}
}
