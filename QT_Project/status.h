#ifndef STATUS_H
#define STATUS_H

#define BUBL1 4
#define BUBL2 17
#define BUBL3 27
#define BUBL4 22

#define HOT_BUBL1 5
#define HOT_BUBL2 6
#define HOT_BUBL3 13

#define PDLC_PIN 19

#define WATER_PUMP_FB_SIGNAL 26
#define WATER_PUMP_PWM 18

#define DOORLOC_MOTOR_FB_SIGNAL 23
#define DOORLOC_MOTOR_PWM 24
#define DOORLOC_CHECK_OPEN_SW 25
#define DOORLOC_CHECK_CLOSE_SW 12
#define DOORLOCK_SW_CLOSE_VALUE 1


#define RELAY_SW_PIN_HIGH 0
#define RELAY_SW_PIN_LOW  1

#define MOTOR_FORWARD 1
#define MOTOR_BACKWARD 0


#define MAX_PASSWORD_COUNT 20

#define SECURITY_WINDOW 0
#define CONTROL_PANEL 1
#define SYSTEM_CONTROL 2

#define DOORLOCK_TEMPORARY_PASSWORD_EXPIRED_DUTY_TIME 1000 * 60 * 30
#define DOORLOCK_DOOL_CLOSE_TIME 1000 * 10

#define WATER_PUMP_DEFAULT_POWER 100
#define DOORLOCK_DEFAULT_POWER 100

#define CONTROL_PANEL_CHECK_CYCLE_TIME 250

#ifdef __linux__
#define SET_ALL_PAGE_PIGPIO_INIT
#define SET_RELEASE_MODE
#define HIDE_MOUSE
#endif
//#define SHOW_SERIAL_COMMUNICATION_READ_BUFFER_CONTENT


class Status
{
public:
    Status();
    int PIN_HIGH = 1;
    int PIN_LOW = 0;
    bool isPull_Up = false;

    int fd = -1;
    char device[2][1024] = {"/dev/ttyUSB0", "/dev/ttyACM0"};
    float isWaterValid = 0, tempC = 0, humidity = 0, Lux = 0; // 123.1234 ==> 123.123398
    bool stopWhile = false;

    bool isOn_bulb1 = false, isOn_bulb2 = false, isOn_bulb3 = false, isOn_bulb4 = false;
    bool isOn_hotBulb1 = false, isOn_hotBulb2 = false, isOn_hotBulb3 = false, isOn_PDLC = false;
    bool isOn_waterPump = false, isOn_doorMotor = false;
    bool isWaterPump_Forward = false, isDoorMotor_Forward = false;
    bool isDoorOpen = false, isDoorClose = false, isDoorOpening = false, isIgnoreOpenSW_Status = false, isIgnoreCloseSW_Status = false, isNeedToDoorClose = false;
    int Current_LED_Status_Value = 0, currentWaterPower = 0, currentDoorPower = 0;
    int waitTime_DoorClose = 0/*DOORLOCK_DOOL_CLOSE_TIME*/, switch_oc_delay = CONTROL_PANEL_CHECK_CYCLE_TIME;


    bool isSet_TemporaryPassword = false, isChanged_CurrentPassword = false, isChaging_CurrentPassword = false;
    const int password_expiredTime = DOORLOCK_TEMPORARY_PASSWORD_EXPIRED_DUTY_TIME;
    int current_password_len = 0, current_temporary_password_len = 0, current_temporary_password_expiredTime = password_expiredTime;
    char password[MAX_PASSWORD_COUNT], temporary_password[MAX_PASSWORD_COUNT];
};

#endif // STATUS_H
