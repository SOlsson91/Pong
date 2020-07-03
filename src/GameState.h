#pragma once
#include "./StateMachine.h"

class GameState: public State
{
private:

public:
	GameState();
	~GameState();
	void OnEnter() override;
	void OnExit() override;
	void Update(float deltaTime) override;
	void Render() override;
	void ProcessInput() override;
}
