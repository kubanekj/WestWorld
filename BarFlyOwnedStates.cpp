#include "BarFlyOwnedStates.h"
#include "fsm/State.h"
#include "BarFly.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

BarFlyGlobalState* BarFlyGlobalState::Instance()
{
  static BarFlyGlobalState instance;

  return &instance;
}


void BarFlyGlobalState::Execute(BarFly* pBarFly)
{
}

bool BarFlyGlobalState::OnMessage(BarFly* pBarFly, const Telegram& msg)
{
  SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
  case 1:
	  cout << "PlaceHolder";
  default:
   return true;

  }//end switch

  return false;
}
//------------------------------------------------------------------------methods for Carousing
Carousing* Carousing::Instance()
{
  static Carousing instance;

  return &instance;
}


void Carousing::Enter(BarFly* pBarFly)
{
	if (!pBarFly->Drunk())
	{
		cout << "\n" << GetNameOfEntity(pBarFly->ID()) << ": " << "Drinkin' away my sorrows.";
	}
}

void Carousing::Execute(BarFly* pBarFly)
{
  pBarFly->IncrementIntoxication(1);
  if(pBarFly->Sober()){
	cout << "\n" << GetNameOfEntity(pBarFly->ID()) << ": " << "Drinkin' some brew.";
  }

  //if drunk stop drinking
  if (pBarFly->Drunk())
  {
	cout << "\n" << GetNameOfEntity(pBarFly->ID()) << ": " << "I'm A little intoxicated.";
    pBarFly->GetFSM()->ChangeState(FightingDrunk::Instance());
  }
}

void Carousing::Exit(BarFly* pBarFly)
{
}


bool Carousing::OnMessage(BarFly* pBarFly, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

//------------------------------------------------------------------------methods for FightingDrunk

FightingDrunk* FightingDrunk::Instance()
{
  static FightingDrunk instance;

  return &instance;
}


void FightingDrunk::Enter(BarFly* pBarFly)
{
	/*if (!pBarFly->Drunk())
	{
		cout << "\n" << GetNameOfEntity(pBarFly->ID()) << ": " << "Drinkin' away my sorrows.";
	}*/
}

void FightingDrunk::Execute(BarFly* pBarFly)
{
}

void FightingDrunk::Exit(BarFly* pBarFly)
{
}

bool FightingDrunk::OnMessage(BarFly* pBarFly, const Telegram& msg)
{
  switch(msg.Msg)
  {
	case Msg_atBar:
	{
	   cout << "\nMessage handled by " << GetNameOfEntity(pBarFly->ID()) << " at time: " 
       << Clock->GetCurrentTime();

		 SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pBarFly->ID()) << 
          ": You dirty miner, Bob.";

		
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                              pBarFly->ID(),        //ID of sender
                              ent_Miner_Bob,            //ID of recipient
                              Msg_letsFight,   //the message
                              NO_ADDITIONAL_INFO);    


		pBarFly->GetFSM()->ChangeState(Fighting::Instance());
		return true;
	}
	}
  return false;
}
//------------------------------------------------------------------------methods for Fighting
Fighting* Fighting::Instance()
{
  static Fighting instance;

  return &instance;
}


void Fighting::Enter(BarFly* pBarFly)
{
	cout << "\n" << GetNameOfEntity(pBarFly->ID()) << 
          ": Put 'em up!";
}

void Fighting::Execute(BarFly* pBarFly)
{
	cout << "\n" << GetNameOfEntity(pBarFly->ID()) << 
          ": Let's fight, Bob.";
}

void Fighting::Exit(BarFly* pBarFly)
{
}


bool Fighting::OnMessage(BarFly* pBarFly, const Telegram& msg)
{
	switch(msg.Msg)
	{
		case Msg_out:
		{
			cout << "\nMessage handled by " << GetNameOfEntity(pBarFly->ID()) << " at time: " 
			<< Clock->GetCurrentTime();

			SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);

			cout << "\n" << GetNameOfEntity(pBarFly->ID()) << 
			": I'm not feeling so good.";

			 pBarFly->GetFSM()->ChangeState(OutCold::Instance());
			 return true;
		}
	}
  //send msg to global message handler
  return false;
}

//-------------------------------------------------OutCold

OutCold* OutCold::Instance()
{
  static OutCold instance;

  return &instance;
}


void OutCold::Enter(BarFly* pBarFly)
{
	cout << "Help!\n\n";
}

void OutCold::Execute(BarFly* pBarFly)
{ 
  pBarFly->DecrementIntoxication(1);
  if(pBarFly->Sober()){
	cout << "\n" << GetNameOfEntity(pBarFly->ID()) << ": " << "ZZZzzzZZZzzz.";
  }
  else
  {
	  cout << "\n" << GetNameOfEntity(pBarFly->ID()) << ": " << "What happened.";
      pBarFly->GetFSM()->ChangeState(Carousing::Instance());
  }
}

void OutCold::Exit(BarFly* pBarFly)
{
  cout << "\n" << GetNameOfEntity(pBarFly->ID()) << ": " 
       << "Back to drinkin'";
}


bool OutCold::OnMessage(BarFly* pBarFly, const Telegram& msg)
{
  //send msg to global message handler
  return false;
}

