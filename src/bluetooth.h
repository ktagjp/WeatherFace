///////////////////////////////////////////////////////////////////////////////////////
//																				                                        	 //
// This file is added by ktagjp for viblation on bluetooth connection state changing //
//																				                                        	 //
//                                                         Created       8/23/2015	 //
//                                                         Last modified 8/23/2015	 //
//																				                                        	 //
///////////////////////////////////////////////////////////////////////////////////////

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

void UpdateConnection(bool Connected);
void bluetooth_enable_alert(void);
void bluetooth_disable_alert(void);

extern bool Is_BT_Connected_Flag;
extern bool Is_BT_Alert_Enable_Flag;

#endif
