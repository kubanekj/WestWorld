#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_atBar,
  Msg_letsFight,
  Msg_out,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_atBar:

	  return "atBar";

  case Msg_letsFight:

	  return "letsFight";

  case Msg_out:

	  return "knockedOut";

  default:

    return "Not recognized!";
  }
}

#endif