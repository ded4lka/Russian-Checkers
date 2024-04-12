#pragma once
/*
 *
 *  This class simulates a game table and is used by AI
 *  to calculate MiniMax
 *
 */

#include "TableBase.h"

class AITable : public TableBase {
public:

	AITable();

	AITable(TableBase& t);

	AITable(AITable& t);

};
