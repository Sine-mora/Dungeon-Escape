#ifndef STATES_H
#define STATES_H


// Player not defined

class IState
{
public:
	IState(Player* ptrOwner) : m_ptrOwner(ptrOwner)
	{}
	/* State-specific behavior */
	/* Update the state */
	virtual void Update(float fDeltaTime) = 0;
	/* Any entry transition code */
	virtual void OnEnter() = 0;
	/* Any exit transition code */
	virtual void OnExit() = 0;
	/* Getter for string name of this state */
	virtual const char* GetName() const = 0;

protected:
	/* The Player this state belongs to */
	Player* m_ptrOwner;
};

class MainMenuState : public IState
{
public:
	MainMenuState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "MainMenuState"; }
};

class GamePlayState : public IState
{
public:
	GamePlayState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "GamePlayState"; }
};

class DeathState : public IState
{
public:
	DeathState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "Death"; }
};

class SettingsState : public IState
{
public:
	SettingsState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "SettingsState"; }
};

class GameWinState : public IState
{
public:
	GameWinState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "GameWinState"; }
};

class MultiplayerState : public IState
{
public:
	MultiplayerState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "MultiplayerState"; }
};

class LoadLevelState : public IState
{
public:
	LoadLevelState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "LoadLevelState"; }
};

class GameOverState : public IState
{
public:
	GameOverState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "GameOverState"; }
};

class GamePausedState : public IState
{
public:
	GamePausedState(Player* ptrOwner);

	/* Override with behaviors for this state */
	virtual void Update(float fDeltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual const char* GetName() const override { return "GamePausedState"; }
};

#endif // !STATES_H