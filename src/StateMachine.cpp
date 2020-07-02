#include "./StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::AddState(std::unique_ptr<State> newState)
{
	if (!this->m_States.empty())
	{
		this->m_States.top()->OnExit();
	}
	this->m_States.push(std::move(newState));
	this->m_States.top()->OnEnter();
}

void StateMachine::PopState()
{
	this->m_States.top()->OnExit();
	this->m_States.pop();
}

void StateMachine::RemoveState()
{
	this->m_States.top()->OnExit();
	this->m_States.pop();
	if (!this->m_States.empty())
	{
		this->m_States.top()->OnEnter();
	}
}

void StateMachine::Update(float deltaTime)
{
	if (!this->m_States.empty())
	{
		this->m_States.top()->Update(deltaTime);
	}
}

void StateMachine::Render()
{
	if (!this->m_States.empty())
	{
		this->m_States.top()->Render();
	}
}

void StateMachine::ProcessInput()
{
	if (!this->m_States.empty())
	{
		this->m_States.top()->ProcessInput();
	}
}

State& StateMachine::GetActiveState()
{
	return *this->m_States.top();
}

std::string StateMachine::GetActiveStateName()
{
	return this->m_States.top()->GetName();
}
