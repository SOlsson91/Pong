#include <string>
#include <memory>
#include <stack>

class State
{
private:
	std::string m_Name;
public:
	virtual ~State() {};
	virtual std::string GetName() { return this->m_Name; };
	virtual void OnEnter() {};
	virtual void OnExit() {};
	virtual void Update(float) {};
	virtual void Render() {};
	virtual void ProcessInput() {};
};

class StateMachine
{
private:
	std::stack<std::unique_ptr<State>> m_States;
public:
	StateMachine();
	~StateMachine();
    void AddState(std::unique_ptr<State> newState);
	void PopState();
	void RemoveState();
	void Update(float deltaTime);
	void Render();
	void ProcessInput();
	State& GetActiveState();
	std::string GetActiveStateName();
};
