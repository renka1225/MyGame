#include "Fireworks.h"
#include "DxLib.h"

Fireworks::Fireworks(int startX) :
	m_pos(startX + GetRand(80) - 40, 500.0f),
	m_frame(0),
	m_height(0)
{
	m_fireParts.resize(16);
	//updateFunc_ = &Fireworks::WaitUpdate;
	//drawFunc_ = &Fireworks::WaitDraw;
}

void Fireworks::Update()
{
	//(this->*updateFunc_)();
	RiseUpdate();
	ExplodeUpdate();
	WaitUpdate();
}

void Fireworks::Draw()
{
	//(this->*drawFunc_)();
	RiseDraw();
	ExplodeDraw();
	WaitDraw();
}

void Fireworks::Fire()
{
	//updateFunc_ = &Fireworks::RiseUpdate;
	//drawFunc_ = &Fireworks::RiseDraw;
	RiseUpdate();
	RiseDraw();
	m_height = 250+ GetRand(250);	// ‚‚³
}

void Fireworks::RiseUpdate()
{
	m_historyPos.push_front(m_pos);
	if (m_historyPos.size() > 20)
	{
		m_historyPos.pop_back();
	}
	m_pos.x += (GetRand(8) - 4);
	m_pos.y -= 4.0f;
	if (m_pos.y <= 500- m_height)
	{
		//updateFunc_ = &Fireworks::ExplodeUpdate;
		//drawFunc_ = &Fireworks::ExplodeDraw;
		ExplodeUpdate();
		ExplodeDraw();
		const float dangle = 2.0 * DX_PI_F / m_fireParts.size();
		float angle = 0;
		for (auto& p : m_fireParts)
		{
			p.m_pos = m_pos;
			p.m_vec = { cosf(angle), sinf(angle) };
			p.m_vec *= 5.0f;
			angle += dangle;
			m_frame = 120;
		}
	}
	else
	{

	}
}

void Fireworks::RiseDraw()
{
	Vec2 lastPos = m_pos;
	int thickness = 20;
	for (const auto& p : m_historyPos)
	{
		DrawCircleAA(p.x, p.y, (float)thickness * 0.5f, 16, 0xfffff00);
		lastPos = p;
		thickness--;
	}
	DrawCircleAA(m_pos.x, m_pos.y, 10, 16, 0xffffff);
}

void Fireworks::ExplodeUpdate()
{
	for (auto& p : m_fireParts)
	{
		p.m_pos += p.m_vec;
		p.m_vec.y += 0.1f;
		p.m_historyPos.push_back(p.m_pos);
		if (p.m_historyPos.size() > 10)
		{
			p.m_historyPos.pop_back();
		}
	}
	m_frame--;
	if (m_frame == 0)
	{
		//updateFunc_ = &Fireworks::WaitUpdate;
		WaitUpdate();
	}
}

void Fireworks::ExplodeDraw()
{
	for (auto& p : m_fireParts)
	{
		Vec2 lastPos = p.m_pos;
		int thickness = 10;
		for (const auto& hp : p.m_historyPos)
		{
			DrawCircleAA(hp.x, hp.y, (float)thickness * 0.5f, 16, 0xfffff00);
			lastPos = hp;
			thickness--;
		}
		DrawCircleAA(p.m_pos.x, p.m_pos.y, 5, 16, 0xffffff);
	}

}

void Fireworks::WaitUpdate()
{
}

void Fireworks::WaitDraw()
{
}
