
# include <Siv3D.hpp> // OpenSiv3D v0.2.8


enum class State
{
	Opening,
	Game,
	Result,
};

struct CommonData
{
	State scene = State::Opening;
	Font font {50};
	int32 score=0;
};

void Opening(CommonData& common)
{
	common.font(U"なわとびげええええむ").drawAt(Window::Center());


	if (MouseL.down())
	{
		common.scene = State::Game;
	}
}

void Game(CommonData& common)
{
	Rect(Window::Size()).draw(Palette::Skyblue);
	Rect(Size(0, 400), Size(Window::Size().x, 300)).draw(Palette::Gray);
	if (MouseR.down())
	{
		common.scene = State::Opening;
	}
	if(MouseL.down())
	{
		common.scene = State::Result;
	}

	if(KeySpace.down())
	{
		++common.score;
	}
}

void Result(CommonData& common)
{
	common.font(U"スコアは", common.score, U"").drawAt(Window::Center());
}

void Main()
{

	CommonData common;

	while (System::Update())
	{
		switch (common.scene)
		{
		case State::Opening:
		{
			Opening(common);
			break;
		}
		case State::Game:
			Game(common);
			break;
		case State::Result:
			Result(common);
			break;
		default: ;
		}
	}
}
