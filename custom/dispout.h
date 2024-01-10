/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __LV_GUI_H_
#define __LV_GUI_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"


 void Dispout_Task(void * pvParameters);

 void dispout_gui_setup_demo(void);
 void dispout_gui_disp_set_text(const char * text);
 void dispout_gui_disp_add_text(const char * text);



#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
