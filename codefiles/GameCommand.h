#ifndef GAMECOMMAND_H
#define GAMECOMMAND_H

#include "Model.h"
#include "Input_Handling.h"
using namespace std;

  void DoMoveCommand(Model & model, int trainer_id, Point2D p1);
  void DoMoveToCenterCommand(Model & model, int trainer_id, int center_id);
  void DoMoveToGymCommand(Model & model, int trainer_id, int gym_id);
  void DoStopCommand(Model & model, int trainer_id);
  void DoBattleCommand(Model & model, int trainer_id, unsigned int battles);
  void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int_potions_needed);
  void DoAdvanceCommand(Model& model, View& view);
  void DoRunCommand(Model& model, View& view);
  void DoNewCommand(Model& model, char type, int in_id, int x, int y);

#endif
