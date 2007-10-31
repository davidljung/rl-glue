/* 
* Copyright (C) 2007, Adam White
* 
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. */

#include <Network/RL_network.h>

static int agentConnection = 0;

int rlDidAgentConnect()
{
  return agentConnection != 0;
}

void rlCloseAgentConnection()
{
  rlBuffer theBuffer = {0};

  rlBufferCreate(&theBuffer, 8);
  rlSendBufferData(agentConnection, &theBuffer, kRLTerm);

  rlClose(agentConnection);
  agentConnection = 0;

  rlBufferDestroy(&theBuffer);
}

void rlSetAgentConnection(int connection)
{
  if (rlDidAgentConnect())
    rlCloseAgentConnection();

  agentConnection = connection;
}

int rlGetAgentConnection()
{
  return agentConnection;
}

