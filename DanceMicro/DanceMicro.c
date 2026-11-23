#include "DanceMicro.h"

// Used for reducing report sends
static uint8_t PrevReportBuffer[sizeof(USB_JoystickReport_Data_t)];

USB_ClassInfo_HID_Device_t Joystick_HID_Interface = {
    .Config =
        {
            .InterfaceNumber = INTERFACE_ID_Joystick,
            .ReportINEndpoint =
                {
                    .Address = JOYSTICK_EPADDR,
                    .Size = JOYSTICK_EPSIZE,
                    .Banks = 1,
                },
            .PrevReportINBuffer = PrevReportBuffer,
            .PrevReportINBufferSize = sizeof(PrevReportBuffer),
        },
};

int main(void) {
  // Disable watchdog
  MCUSR &= ~(1 << WDRF);
  wdt_disable();
  // Set clock division scale to 1
  clock_prescale_set(clock_div_1);

  adc_init();
  USB_Init();
  GlobalInterruptEnable();

  for (;;) {
    HID_Device_USBTask(&Joystick_HID_Interface);
    USB_USBTask();
  }
}

void EVENT_USB_Device_ConfigurationChanged(void) {
  HID_Device_ConfigureEndpoints(&Joystick_HID_Interface);
  USB_Device_EnableSOFEvents();  // For millisecond_elapsed
}
void EVENT_USB_Device_ControlRequest(void) {
  HID_Device_ProcessControlRequest(&Joystick_HID_Interface);
}
void EVENT_USB_Device_StartOfFrame(void) {
  HID_Device_MillisecondElapsed(&Joystick_HID_Interface);
}

bool CALLBACK_HID_Device_CreateHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, uint8_t* const ReportID,
    const uint8_t ReportType, void* ReportData, uint16_t* const ReportSize) {
  USB_JoystickReport_Data_t* r = (USB_JoystickReport_Data_t*)ReportData;

  // Actual scan
  r->Button = scan_sensors(); 

  *ReportSize = sizeof(USB_JoystickReport_Data_t);
  return false;
}
void CALLBACK_HID_Device_ProcessHIDReport(
    USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo, const uint8_t ReportID,
    const uint8_t ReportType, const void* ReportData,
    const uint16_t ReportSize) {
  // For host --> device reports
}