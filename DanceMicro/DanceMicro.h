#ifndef _DANCEMICRO_H_
#define _DANCEMICRO_H_

#include <LUFA/Drivers/USB/USB.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/wdt.h>

#include "ADCSensors.h"
#include "Descriptors.h"

// Report descriptor for joystick
typedef struct {
  int8_t X;
  int8_t Y;
  int8_t Z;
  uint8_t Button;  // Actual used part
} USB_JoystickReport_Data_t;

void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);
void EVENT_USB_Device_StartOfFrame(void);

bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, uint8_t* const ReportID,
    const uint8_t ReportType, void* ReportData, uint16_t* const ReportSize);
void CALLBACK_HID_Device_ProcessHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, const uint8_t ReportID,
    const uint8_t ReportType, const void* ReportData,
    const uint16_t ReportSize);

#endif