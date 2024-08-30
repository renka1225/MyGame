#pragma once
#include <vector>
#include <string>

class Text1
{
public:
	Text1();
	~Text1();
	void Init();
	void Update();
	void Draw();
	void LoadCsv(); // CSVファイルを読み込む

private:
	std::vector<std::string> m_text; // CSVファイルから読み込んだテキストを保存する
	float m_textPosY; // テキスト位置
	int m_time;		  // 経過時間
};

