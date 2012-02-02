#ifndef BARFLY_OWNED_STATES_H
#define BARFLY_OWNED_STATES_H

#include "fsm/State.h"

class BarFly;
//------------------------------------------------------------------------
// Carousing: In the Carousing state, Henry will raise his intoxication
// level by one at each update. When it reaches the drunkeness threshold
// of 10, he will change his state to FightinDrunk.
//------------------------------------------------------------------------
class Carousing : public State<BarFly>
{
private:
  
  Carousing(){}

  //copy ctor and assignment should be private
  Carousing(const Carousing&);
  Carousing& operator=(const Carousing&);
 
public:

  //this is a singleton
  static Carousing* Instance();

  virtual void Enter(BarFly* pBarFly);

  virtual void Execute(BarFly* pBarFly);

  virtual void Exit(BarFly* pBarFly);

  virtual bool OnMessage(BarFly* agent, const Telegram& msg);
};

class FightingDrunk : public State<BarFly>
{
private:
  
  FightingDrunk(){}

  //copy ctor and assignment should be private
  FightingDrunk(const FightingDrunk&);
  FightingDrunk& operator=(const FightingDrunk&);
 
public:

  //this is a singleton
  static FightingDrunk* Instance();

  virtual void Enter(BarFly* pBarFly);

  virtual void Execute(BarFly* pBarFly);

  virtual void Exit(BarFly* pBarFly);

  virtual bool OnMessage(BarFly* agent, const Telegram& msg);
};


class Fighting : public State<BarFly>
{
private:
  
  Fighting(){}

  //copy ctor and assignment should be private
  Fighting(const Fighting&);
  Fighting& operator=(const Fighting&);
 
public:

  //this is a singleton
  static Fighting* Instance();

  virtual void Enter(BarFly* pBarFly);

  virtual void Execute(BarFly* pBarFly);

  virtual void Exit(BarFly* pBarFly);

  virtual bool OnMessage(BarFly* agent, const Telegram& msg);
};

class OutCold : public State<BarFly>
{
private:
  
  OutCold(){}

  //copy ctor and assignment should be private
  OutCold(const OutCold&);
  OutCold& operator=(const OutCold&);
 
public:

  //this is a singleton
  static OutCold* Instance();

  virtual void Enter(BarFly* pBarFly);

  virtual void Execute(BarFly* pBarFly);

  virtual void Exit(BarFly* pBarFly);

  virtual bool OnMessage(BarFly* agent, const Telegram& msg);
};

class BarFlyGlobalState : public State<BarFly>
{  
private:
  
  BarFlyGlobalState(){}

  //copy ctor and assignment should be private
  BarFlyGlobalState(const BarFlyGlobalState&);
  BarFlyGlobalState& operator=(const BarFlyGlobalState&);
 
public:

  //this is a singleton
  static BarFlyGlobalState* Instance();
  
  virtual void Enter(BarFly* pBarFly){}

  virtual void Execute(BarFly* pBarFly);

  virtual void Exit(BarFly* pBarFly){}

  virtual bool OnMessage(BarFly* pBarFly, const Telegram& msg);
};


// insert states Fightin, and OutCold here.

#endif