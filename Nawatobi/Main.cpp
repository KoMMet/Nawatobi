
# include <Siv3D.hpp> // OpenSiv3D v0.2.8


enum class State
{
	Opening,
	Game,
	Result,
};

void Main()
{

	State scene = State::Opening;
	Font font{ 50 };
	int32 score = 0;

	const auto Opening = [&]()
	{
		font(U"なわとびげええええむ").drawAt(Window::Center());


		if (MouseL.down())
		{
			scene = State::Game;
		}
	};

	const auto Game = [&]()
	{
		Rect(Window::Size()).draw(Palette::Skyblue);
		Rect(Size(0, 400), Size(Window::Size().x, 300)).draw(Palette::Gray);
		if (MouseR.down())
		{
			scene = State::Opening;
		}
		if (MouseL.down())
		{
			scene = State::Result;
		}

		if (KeySpace.down())
		{
			++score;
		}
	};
	const auto Result=[&]()
	{
		font(U"スコアは", score, U"").drawAt(Window::Center());
	};

	Array<std::function<void()>> functions{Opening, Game, Result};

	while (System::Update())
	{
		functions[static_cast<size_t>(scene)]();
	}
}
