
# include <Siv3D.hpp> // OpenSiv3D v0.2.8


struct CommonData
{
	Optional<String>  scene;
	Font font{ 50 };
	int32 score = 0;
};

class SceneBase
{
public:
	SceneBase() {  }
	virtual  ~SceneBase()
	{
		
	}

	virtual void update(CommonData& common) = 0;
	virtual void draw(const CommonData& common) const = 0;
};

class Opening:public SceneBase
{
public:
	Opening()
	{
		
	}
	~Opening()
	{
		
	}

	void update(CommonData& common) override
	{
		if (MouseL.down())
		{
			common.scene.emplace(U"Game");
		}
	}

	void draw(const CommonData& common) const override
	{
		common.font(U"なわとびげええええむ").drawAt(Window::Center());
	}
private:

};

class Game: public SceneBase
{
public:

	Game()
	{
		
	}
	~Game()
	{

	}

	void update(CommonData& common) override
	{
		if (MouseR.down())
		{
			common.scene.emplace(U"Opening");
		}
		if (MouseL.down())
		{
			common.scene.emplace(U"Result");
		}

		if (KeySpace.down())
		{
			++common.score;
		}
	}

	void draw(const CommonData& common) const override
	{
		Rect(Window::Size()).draw(Palette::Skyblue);
		Rect(Size(0, 400), Size(Window::Size().x, 300)).draw(Palette::Gray);


		common.font(U"score: ", common.score).drawAt(Window::Center() + Vec2(0.0, -200), Palette::Black);

	}
private:
};

class Result:public SceneBase
{
public:
	Result()
	{
		
	}

	~Result()
	{
		
	}

	void update(CommonData& common) override
	{
		
	}

	void draw(const CommonData& common) const override
	{
		common.font(U"スコアは", common.score, U"").drawAt(Window::Center());
	}
private:
};

void Main()
{
	CommonData common;
	
	std::unique_ptr<SceneBase> scene = std::make_unique<Opening>();

	HashTable<String, std::function<std::unique_ptr<SceneBase>()>> factories;
	factories[U"Opening"] =  ([&]() {return std::make_unique<Opening>(); }) ;
	factories[U"Game"] = ([&]() {return std::make_unique<Game>(); });
	factories[ U"Result" ] = ([&]() {return std::make_unique<Result>(); });

	while (System::Update())
	{
		if(common.scene.has_value())
		{
			scene = factories[ common.scene.value() ]();
			common.scene.reset();
			Print << U"kirikawari ";
		}
		scene->update(common);
		scene->draw(common);
	}
}
