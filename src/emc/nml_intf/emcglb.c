/********************************************************************
* Description: emcglb.c
*   Globals initialized to values in emccfg.h
*
*   Derived from a work by Fred Proctor & Will Shackleford
*
* Author:
* License: GPL Version 2
* System: Linux
*    
* Copyright (c) 2004 All rights reserved.
*
* Last change:
* $Revision$
* $Author$
* $Date$
********************************************************************/

#include <string.h>		/* strcpy() */
#include "emcglb.h"		/* these decls */
#include "emccfg.h"		/* their initial values */
#include "emcpos.h"		/* EmcPose */

char EMC_INIFILE[EMC_INIFILE_LEN] = DEFAULT_EMC_INIFILE;

char EMC_NMLFILE[EMC_NMLFILE_LEN] = DEFAULT_EMC_NMLFILE;

char RS274NGC_STARTUP_CODE[RS274NGC_STARTUP_CODE_MAX] =
    DEFAULT_RS274NGC_STARTUP_CODE;

int EMC_DEBUG = 0;		/* initially no debug messages */

double EMC_TASK_CYCLE_TIME = DEFAULT_EMC_TASK_CYCLE_TIME;

double EMC_IO_CYCLE_TIME = DEFAULT_EMC_IO_CYCLE_TIME;

char TOOL_TABLE_FILE[TOOL_TABLE_FILE_LEN] = DEFAULT_TOOL_TABLE_FILE;

double TRAJ_DEFAULT_VELOCITY = DEFAULT_TRAJ_DEFAULT_VELOCITY;
double TRAJ_MAX_VELOCITY = DEFAULT_TRAJ_MAX_VELOCITY;

double AXIS_MAX_VELOCITY[EMC_AXIS_MAX] = { 0.0 };

double SPINDLE_OFF_WAIT = DEFAULT_SPINDLE_OFF_WAIT;
double SPINDLE_ON_WAIT = DEFAULT_SPINDLE_ON_WAIT;

int ESTOP_SENSE_INDEX = DEFAULT_ESTOP_SENSE_INDEX;
int LUBE_SENSE_INDEX = DEFAULT_LUBE_SENSE_INDEX;

int ESTOP_SENSE_POLARITY = DEFAULT_ESTOP_SENSE_POLARITY;
int LUBE_SENSE_POLARITY = DEFAULT_LUBE_SENSE_POLARITY;

int LUBE_WRITE_INDEX = DEFAULT_LUBE_WRITE_INDEX;
int LUBE_WRITE_POLARITY = DEFAULT_LUBE_WRITE_POLARITY;

int SPINDLE_ON_INDEX = DEFAULT_SPINDLE_ON_INDEX;
double MIN_VOLTS_PER_RPM = DEFAULT_MIN_VOLTS_PER_RPM;
double MAX_VOLTS_PER_RPM = DEFAULT_MAX_VOLTS_PER_RPM;

int SPINDLE_FORWARD_INDEX = DEFAULT_SPINDLE_FORWARD_INDEX;
int SPINDLE_REVERSE_INDEX = DEFAULT_SPINDLE_REVERSE_INDEX;
int SPINDLE_BRAKE_INDEX = DEFAULT_SPINDLE_BRAKE_INDEX;
int SPINDLE_DECREASE_INDEX = DEFAULT_SPINDLE_DECREASE_INDEX;
int SPINDLE_INCREASE_INDEX = DEFAULT_SPINDLE_INCREASE_INDEX;
int SPINDLE_ENABLE_INDEX = DEFAULT_SPINDLE_ENABLE_INDEX;
int MIST_COOLANT_INDEX = DEFAULT_MIST_COOLANT_INDEX;
int FLOOD_COOLANT_INDEX = DEFAULT_FLOOD_COOLANT_INDEX;
int ESTOP_WRITE_INDEX = DEFAULT_ESTOP_WRITE_INDEX;

int SPINDLE_FORWARD_POLARITY = DEFAULT_SPINDLE_FORWARD_POLARITY;
int SPINDLE_REVERSE_POLARITY = DEFAULT_SPINDLE_REVERSE_POLARITY;
int MIST_COOLANT_POLARITY = DEFAULT_MIST_COOLANT_POLARITY;
int FLOOD_COOLANT_POLARITY = DEFAULT_FLOOD_COOLANT_POLARITY;
int SPINDLE_DECREASE_POLARITY = DEFAULT_SPINDLE_DECREASE_POLARITY;
int SPINDLE_INCREASE_POLARITY = DEFAULT_SPINDLE_INCREASE_POLARITY;
int ESTOP_WRITE_POLARITY = DEFAULT_ESTOP_WRITE_POLARITY;
int SPINDLE_BRAKE_POLARITY = DEFAULT_SPINDLE_BRAKE_POLARITY;
int SPINDLE_ENABLE_POLARITY = DEFAULT_SPINDLE_ENABLE_POLARITY;
int EMCLOG_INCLUDE_HEADER = DEFAULT_EMCLOG_INCLUDE_HEADER;

EmcPose TOOL_CHANGE_POSITION;	/* no defaults */
unsigned char HAVE_TOOL_CHANGE_POSITION = 0;	/* default is 'not there' */
EmcPose TOOL_HOLDER_CLEAR;	/* no defaults */
unsigned char HAVE_TOOL_HOLDER_CLEAR;	/* default is 'not there' */

int taskplanopen = 0;

void emcInitGlobals()
{
    int t;

    for (t = 0; t < EMC_AXIS_MAX; t++) {
	AXIS_MAX_VELOCITY[t] = DEFAULT_AXIS_MAX_VELOCITY;
    }
}
