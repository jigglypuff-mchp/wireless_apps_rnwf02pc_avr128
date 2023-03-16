/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Microchip Technology Inc

  @File Name
    rnwf_wifi_service.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdio.h>
#include <string.h>

#include "rnwf_interface.h"
#include "rnwf_wifi_service.h"

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */

RNWF_WIFI_CALLBACK_t gWifi_CallBack_Handler;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    RNWF_RESULT_t RNWF_WIFI_SrvCtrl( RNWF_WIFI_SERVICE_t request, uint8_t input) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
RNWF_RESULT_t RNWF_WIFI_SrvCtrl( RNWF_WIFI_SERVICE_t request, void *input)  {
    
    RNWF_RESULT_t result = RNWF_FAIL;
    
    switch (request)
    {
        case RNWF_STA_CONNECT:
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_CONNECT);
            break;
        case RNWF_STA_DISCONNECT:
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_DISCONNECT);
            break;
        case RNWF_SET_WIFI_AP_CHANNEL:
        {            
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_AP_CHANNEL, *(uint8_t *)input);            
            break;
        }          
        case RNWF_SET_WIFI_BSSID:
        {            
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_AP_CHANNEL, (uint8_t *)input);            
            break;
        } 
        case RNWF_SET_WIFI_TIMEOUT:
            break;
        case RNWF_SET_WIFI_HIDDEN:
        {            
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_AP_HIDDEN, *(uint8_t *)input);            
            break;
        }   
        case RNWF_SET_WIFI_PARAMS:  
        {
            RNWF_WIFI_PARAM_t *wifi_config = (RNWF_WIFI_PARAM_t *)input;
            
            if(wifi_config->mode == RNWF_WIFI_MODE_STA)
            {
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_DISCONNECT);
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SOFTAP_DISABLE);
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_STA_SSID, wifi_config->ssid);            
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_STA_PWD, wifi_config->passphrase);
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_STA_SEC, wifi_config->security);
                if(wifi_config->autoconnect)
                {
                    result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_CONNECT);
                }
            }
            else if(wifi_config->mode == RNWF_WIFI_MODE_AP)                
            {                   
                uint8_t default_channel = 6;
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_DISCONNECT);
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SOFTAP_DISABLE);                
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_AP_SSID, wifi_config->ssid);            
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_AP_PWD, wifi_config->passphrase);
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_AP_SEC, wifi_config->security);
                result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SET_AP_CHANNEL, default_channel);    
                if(wifi_config->autoconnect)
                {
                    result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_SOFTAP_ENABLE);
                }
            }
            break;            
        }
        case RNWF_WIFI_PASSIVE_SCAN:
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_PSV_SCAN);
            break;    
            
        case RNWF_WIFI_ACTIVE_SCAN:
            result = RNWF_CMD_SEND_OK_WAIT(NULL, NULL, RNWF_WIFI_ACT_SCAN);
            break;            
            
        case RNWF_WIFI_SET_CALLBACK:
            if(input)
            {
                gWifi_CallBack_Handler = (RNWF_WIFI_CALLBACK_t)input;
                result = RNWF_PASS;
            }
            break;
        default:
            break;
            
    };    
    
    return result;
}


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */



/* *****************************************************************************
 End of File
 */
