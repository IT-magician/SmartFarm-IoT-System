    #include "controlpanel.h"
    #include "ui_controlpanel.h"
    
    #include <QtDebug>
    
    #define BUBLS "Bubls"
    #define HOT_BUBLS "Hot_Bubls"
    #define PDLC "PDLC"
    #define WATER_PUMP "Water_Pump"
    #define DOOR_MOTOR "Door_Motor"
    
    void makeButtonOff(QPushButton *buttonPointer, QPalette pal)
    {
        pal.setColor(QPalette::Button, QColor(Qt::transparent));
        buttonPointer->setPalette(pal);
    }
    void makeButtonOn(QPushButton *buttonPointer, QPalette pal)
    {
        pal.setColor(QPalette::Button, QColor(181, 217, 232));
        buttonPointer->setPalette(pal);
    }
    
    ControlPanel::ControlPanel(Status *_status, QWidget *_windows[], QWidget *parent) :
        windows(_windows),
        QWidget(parent),
        ui(new Ui::ControlPanel)
    {
        QPushButton *buttonPointer = nullptr;
        QPalette pal;
        ui->setupUi(this);
        setWindowTitle("Control Panel");
        status = _status;
    
    #if defined(__linux__) && defined(SET_ALL_PAGE_PIGPIO_INIT)
        int __result = gpioInitialise();
    #endif
    #ifdef SET_RELEASE_MODE
        setWindowState(Qt::WindowFullScreen);
        #ifdef HIDE_MOUSE
            setCursor(Qt::BlankCursor);
        #endif
    #endif
    
        ui->horizontalSlider_waterPumpSlider->setValue(status->currentWaterPower);
        ui->horizontalSlider_doorLock->setValue(status->currentDoorPower);
        if(status->currentWaterPower > 0)
        {
            buttonPointer = ui->pushButton_waterPump;
            pal = buttonPointer->palette();
            // make turn on
            makeButtonOn(buttonPointer, pal);
            turnOnWaterPump();
        }
    #ifdef __linux__ // Set Default PWM Signal
            if(ui->radioButton->isChecked())
            {
                gpioWrite(WATER_PUMP_FB_SIGNAL, MOTOR_FORWARD);
                status->isWaterPump_Forward = true;
            }
            else
            {
                gpioWrite(WATER_PUMP_FB_SIGNAL, MOTOR_BACKWARD);
                status->isWaterPump_Forward = false;
            }
    #endif
        if(status->currentDoorPower > 0)
        {
            buttonPointer = ui->pushButton_doorMotor;
            pal = buttonPointer->palette();
            // make turn on
            makeButtonOn(buttonPointer, pal);
            turnOnDoorMotor();
        }
    #ifdef __linux__  // Set Default PWM Signal
            if(ui->radioButton_3->isChecked())
            {
                gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_FORWARD);
                status->isDoorMotor_Forward = true;
            }
            else
            {
                gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_BACKWARD);
                status->isDoorMotor_Forward = false;
            }
    #endif
    
        QString ipAddressAll = "*** My Interface IP Address ***\n";
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            {
    
                ipAddressAll += address.toString() + "\n";
            }
            else
            {
    
            }
    
        }
        ui->Qlabel_IPADDRESS->setText(ipAddressAll);
    
        m_pTimer = new QTimer();
        connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc1()));
        m_pTimer->start(CheckCycleTime);
        m_pTimer2 = new QTimer();
        connect(m_pTimer2, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc2()));
        //m_pTimer2->start(CheckCycleTime);
    
    
    
    #ifdef _WIN32
       //define something for Windows (32-bit and 64-bit, this part is common)
       //#ifdef _WIN64
          //define something for Windows (64-bit only)
       //#endif
        qDebug() << "iT's Windows";
    
    
    #elif __linux__
        // linux
        qDebug() << "iT's linux, I'm Targeted at Raspberry Pi";
    
    
    //#elif __unix__ // all unices not caught above
        // Unix
    
    //#elif defined(_POSIX_VERSION)
        // POSIX
    
    #else
    #   error "Unknown compiler"
    #endif
    }
    
    ControlPanel::~ControlPanel()
    {
        delete ui;
    #if defined(__linux__) && defined(SET_ALL_PAGE_PIGPIO_INIT)
        gpioTerminate();
    #endif
    }
    
    
    
    void ControlPanel::on_pushButton_bulbs_clicked() // 전구
    {
        ButtonControl(BUBLS);
    }
    
    void ControlPanel::on_pushButton_hotBulbs_clicked() // 열전구
    {
        ButtonControl(HOT_BUBLS);
    }
    
    void ControlPanel::on_pushButton_PDLC_clicked() // PDLC
    {
        ButtonControl(PDLC);
    }
    
    void ControlPanel::on_horizontalSlider_waterPumpSlider_valueChanged(int value) // Slider : 물펌프
    {
        QPushButton *buttonPointer = ui->pushButton_waterPump;
        QPalette pal = buttonPointer->palette();
        if(value > 0)
        {
            makeButtonOn(buttonPointer, pal);
            status->isOn_waterPump = true;
        }
        else
        {
            makeButtonOff(buttonPointer, pal);
            status->isOn_waterPump = false;
        }
        ui->slider_waterPump->setText(QString::number(value) + "%");
        ui->slider_waterPump->setFont(QFont("",15));
        status->currentWaterPower = (status->isPull_Up/*pull-up state*/?100 - value:value);
    #ifdef __linux__
            gpioPWM(WATER_PUMP_PWM, status->currentWaterPower);
    #endif
    }
    
    void ControlPanel::on_pushButton_waterPump_clicked() // 물펌프
    {
        ButtonControl(WATER_PUMP);
    }
    
    void ControlPanel::on_horizontalSlider_doorLock_valueChanged(int value) // Slider : 도어락
    {
        QPushButton *buttonPointer = ui->pushButton_doorMotor;
        QPalette pal = buttonPointer->palette();
        if(value > 0)
        {
            makeButtonOn(buttonPointer, pal);
            status->isOn_doorMotor = true;
        }
        else
        {
            makeButtonOff(buttonPointer, pal);
            status->isOn_doorMotor = false;
        }
        ui->slider_doorLockMotor->setText(QString::number(value) + "%");
        ui->slider_doorLockMotor->setFont(QFont("",15));
        status->currentDoorPower = (status->isPull_Up/*pull-up state*/?100 - value:value);
    #ifdef __linux__
            gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower);
    #endif
    }
    
    void ControlPanel::on_pushButton_doorMotor_clicked() // 도어락
    {
        ButtonControl(DOOR_MOTOR);
    }
    
    int ControlPanel::ButtonControl(QString button_name)
    {
        QPushButton *buttonPointer = nullptr;
        QPalette pal;
    
        if(button_name == BUBLS)
        {
            buttonPointer = ui->pushButton_bulbs;
            pal = buttonPointer->palette();
    
            if((status->Current_LED_Status_Value & 0x0f) > 0)
            {
                // make turn off
                makeButtonOff(buttonPointer, pal);
                turnOffBulb();
    
            }
            else
            {
                // make turn on
                makeButtonOn(buttonPointer, pal);
                turnOnBulb();
    
            }
        }
        else if(button_name == HOT_BUBLS)
        {
            buttonPointer = ui->pushButton_hotBulbs;
            pal = buttonPointer->palette();
    
            if((status->Current_LED_Status_Value & 0xf0) > 0)
            {
                // make turn off
                makeButtonOff(buttonPointer, pal);
                turnOffHotBulb();
    
            }
            else
            {
                // make turn on
                makeButtonOn(buttonPointer, pal);
                turnOnHotBulb();
    
            }
    
        }
        else if(button_name == PDLC)
        {
            buttonPointer = ui->pushButton_PDLC;
            pal = buttonPointer->palette();
    
            if(status->isOn_PDLC)
            {
                // make turn off
                makeButtonOff(buttonPointer, pal);
                turnOffPDLC();
            }
            else
            {
                // make turn on
                makeButtonOn(buttonPointer, pal);
                turnOnPDLC();
            }
    
    
        }
        else if(button_name == WATER_PUMP)
        {
            buttonPointer = ui->pushButton_waterPump;
            pal = buttonPointer->palette();
    
            if(!status->isPull_Up)
            {
                if(status->currentWaterPower > 0)
                    status->isOn_waterPump = true;
                else
                    status->isOn_waterPump = false;
            }
            else
            {
                if(status->currentWaterPower < 100)
                    status->isOn_waterPump = true;
                else
                    status->isOn_waterPump = false;
            }
            
            if(status->isOn_waterPump)
            {
                // make turn off
                makeButtonOff(buttonPointer, pal);
                turnOffWaterPump();
                //status->currentWaterPower = 0;
            }
            else
            {
                // make turn on
                makeButtonOn(buttonPointer, pal);
                turnOnWaterPump();
                //status->currentWaterPower = status->PIN_HIGH * WATER_PUMP_DEFAULT_POWER;
            }
        }
        else if(button_name == DOOR_MOTOR)
        {
            buttonPointer = ui->pushButton_doorMotor;
            pal = buttonPointer->palette();
    
            if(!status->isPull_Up)
            {
                if(status->currentDoorPower > 0)
                    status->isOn_doorMotor = true;
                else
                    status->isOn_doorMotor = false;
            }
            else
            {
                if(status->currentDoorPower < 100)
                    status->isOn_doorMotor = true;
                else
                    status->isOn_doorMotor = false;
            }
            
            if(status->isOn_doorMotor)
            {
                // make turn off
                makeButtonOff(buttonPointer, pal);
                turnOffDoorMotor();
                //status->currentWaterPower = 0;
            }
            else
            {
                // make turn on
                makeButtonOn(buttonPointer, pal);
                turnOnDoorMotor();
                //status->currentWaterPower = status->PIN_HIGH * WATER_PUMP_DEFAULT_POWER;
            }
            
        }
    
       // buttonPointer->update();
    
        return 0;
    }
    
    void ControlPanel::OnTimerCallbackFunc1() // Check Cycle
    {
        QPushButton *buttonPointer;
        QPalette pal;
        int isOn = 1;
        // 문 열기와 닫기를 중단하려면 간단하게 Motor에 전달하는 PWM 신호를 0으로 똑같이 주면 됨.
    #ifdef __linux__
        isOn = gpioRead(DOORLOC_CHECK_OPEN_SW);
    #endif
    
        QLabel *doorLock_OpenSW = ui->doorLock_OpenSW;
        doorLock_OpenSW->setAutoFillBackground(true);
        pal = doorLock_OpenSW->palette();
    
        if(isOn == DOORLOCK_SW_CLOSE_VALUE)
        {
             // 문 완전히 개방됨
            pal.setColor(QPalette::Window, QColor(181, 217, 232));
            status->isDoorOpen = true;
            status->isDoorClose = false;
            if(status->switch_oc_delay < 0)
            {
                if(!status->isIgnoreOpenSW_Status && !status->isNeedToDoorClose) // Stop Door Lock Motor
                {
                    status->currentDoorPower = status->PIN_LOW * 100;// LOW (For interoperability with Pull-up)
                    status->isOn_doorMotor = false;
    #ifdef __linux__
                    gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower);
    #endif
                    ui->horizontalSlider_doorLock->setValue(0);
                    ui->slider_doorLockMotor->setText(QString::number(0) + "%");
                    ui->slider_doorLockMotor->setFont(QFont("",15));
                    
                    QPushButton *pushButton_doorMotor_Pointer = ui->pushButton_doorMotor;
                    pushButton_doorMotor_Pointer->setAutoFillBackground(true);
                    QPalette palOff = ui->doorLock_OpenSW->palette();
                    palOff.setColor(QPalette::Button, QColor(Qt::transparent));
                    pushButton_doorMotor_Pointer->setPalette(palOff);
                    
                    if(status->waitTime_DoorClose == 0)
                    {
                        m_pTimer2->stop();
                        status->waitTime_DoorClose = DOORLOCK_DOOL_CLOSE_TIME;
                        //qDebug() << "waitTime_DoorClose, Ready to Start m_pTimer2";
                    }
                    else if(status->waitTime_DoorClose > 0){ // Close Door After Specific Time.
                        status->waitTime_DoorClose -= CheckCycleTime;
                        //qDebug() << "waitTime_DoorClose, Wait m_pTimer2 (Time : " << status->waitTime_DoorClose << "ms)";
                        
                        if(status->waitTime_DoorClose <= 0)
                        {
                            status->waitTime_DoorClose = -255;
                            m_pTimer2->start(CheckCycleTime * 50);
                            //qDebug() << "waitTime_DoorClose, Start m_pTimer2";
                        }
                    }
                }
                
                
                
                
                
                
                status->switch_oc_delay = CONTROL_PANEL_CHECK_CYCLE_TIME;
    
            }
            else
                status->switch_oc_delay -= CheckCycleTime;
        }
        else
        {
            pal.setColor(QPalette::Window, QColor(Qt::transparent));
            if(status->waitTime_DoorClose > 0 || status->waitTime_DoorClose == -255) // Stand by for next close door
            {
                status->waitTime_DoorClose = 0;
                m_pTimer2->stop();
            }
        }
        doorLock_OpenSW->setPalette(pal);
        
        if(status->isNeedToDoorClose)
        {
            // connection with OnTimerCallbackFunc2()
            if(status->waitTime_DoorClose < 0 && (-255 + CheckCycleTime / 10 * 5) < status->waitTime_DoorClose)
            {
                status->isNeedToDoorClose = false;
                status->waitTime_DoorClose = 0;
                //qDebug() << "Door Closing Action is started!!";
            }
            else if(status->waitTime_DoorClose < 0)
            {
                status->waitTime_DoorClose += CheckCycleTime / 10; // wait that the door is started to move door.
                //qDebug() << "Wait for Door Closing Action";
            }
        }
    
    #ifdef __linux__
            isOn = gpioRead(DOORLOC_CHECK_CLOSE_SW);
    #endif
    
            QLabel *doorLock_CloseSW = ui->doorLock_closeSW;
            doorLock_CloseSW->setAutoFillBackground(true);
            pal = ui->doorLock_closeSW->palette();
    
            if(isOn == DOORLOCK_SW_CLOSE_VALUE)
            {
                // 문 완전히 닫힘
                pal.setColor(QPalette::Window, QColor(181, 217, 232));
                status->isDoorOpen = false;
                status->isDoorClose = true;
                if(status->switch_oc_delay < 0)
                {
                    if(!status->isIgnoreCloseSW_Status) // Stop Door Lock Motor
                    {
                        status->currentDoorPower = status->PIN_LOW * 100;// LOW (For interoperability with Pull-up)
                        status->isOn_doorMotor = false;
         #ifdef __linux__
                        gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower);
         #endif
                        ui->horizontalSlider_doorLock->setValue(0);
                        ui->slider_doorLockMotor->setText(QString::number(0) + "%");
                        ui->slider_doorLockMotor->setFont(QFont("",15));
                    }
                    status->isDoorOpen = false;
                    status->waitTime_DoorClose = DOORLOCK_DOOL_CLOSE_TIME;
                    //qDebug() << "Door is Closed";
                }
                else
                    status->switch_oc_delay -= CheckCycleTime;
    
            }
            else
            {
                pal.setColor(QPalette::Window, QColor(Qt::transparent));
            }
            ui->doorLock_closeSW->setPalette(pal);
    
    
    
        if(status->isWaterPump_Forward)
        {
            ui->radioButton->setChecked(true);
        }
        else
        {
            ui->radioButton_2->setChecked(true);
        }
        if(status->isDoorMotor_Forward)
        {
            ui->radioButton_3->setChecked(true);
        }
        else
        {
            ui->radioButton_4->setChecked(true);
        }
                /*if(status->isOn_bulb1)
                {
                    status->Current_LED_Status_Value |= 0x01;
                }
                else
                {
                    status->Current_LED_Status_Value &=~ 0x01;
                }
                
                if(status->isOn_bulb2)
                {
                    status->Current_LED_Status_Value |= 0x02;
                }
                else
                {
                    status->Current_LED_Status_Value &=~ 0x02;
                }
                
                if(status->isOn_bulb3)
                {
                    status->Current_LED_Status_Value |= 0x04;
                }
                else
                {
                    status->Current_LED_Status_Value &=~ 0x04;
                }
                
                if(status->isOn_bulb4)
                {
                    status->Current_LED_Status_Value |= 0x08;
                }
                else
                {
                    status->Current_LED_Status_Value &=~ 0x08;
                }
                if(status->isOn_hotBulb1)
                {
                    status->Current_LED_Status_Value |= 0x10;
                }
                else
                {
                    status->Current_LED_Status_Value &=~ 0x10;
                }
                
                if(status->isOn_hotBulb2)
                {
                    status->Current_LED_Status_Value |= 0x20;
                }
                else
                {
                    status->Current_LED_Status_Value &=~ 0x20;
                }
                
                if(status->isOn_hotBulb3)
                {
                    status->Current_LED_Status_Value |= 0x40;
                }
                else
                {
                    status->Current_LED_Status_Value &=~ 0x40;
                }*/
    
            if(!status->isPull_Up)
            {
                if(status->currentWaterPower > 0)
                    status->isOn_waterPump = true;
                else
                    status->isOn_waterPump = false;
                if(status->currentDoorPower > 0)
                    status->isOn_doorMotor = true;
                else
                    status->isOn_doorMotor = false;
            }
            else
            {
                if(status->currentWaterPower < 100)
                    status->isOn_waterPump = true;
                else
                    status->isOn_waterPump = false;
                if(status->currentDoorPower < 100)
                    status->isOn_doorMotor = true;
                else
                    status->isOn_doorMotor = false;
            }
            
            QLabel *isWaterValid = ui->isWaterValid;
            isWaterValid->setAutoFillBackground(true);
            pal = isWaterValid->palette();
            if(status->isWaterValid < 1)
            {
                status->currentWaterPower = status->PIN_LOW * 100;// LOW (For interoperability with Pull-up)
                status->isOn_waterPump = false;
                ui->horizontalSlider_waterPumpSlider->setValue(0);
                ui->slider_waterPump->setText(QString::number(0) + "%");
                ui->slider_waterPump->setFont(QFont("",15));
    #ifdef __linux__
                gpioPWM(WATER_PUMP_PWM, status->currentWaterPower);
    #endif
                pal.setColor(QPalette::Window, QColor(Qt::transparent));
                isWaterValid->setPalette(pal);
            }
            else{
                pal.setColor(QPalette::Window, QColor(181, 217, 232));
                isWaterValid->setPalette(pal);
            }
    
            //if(isCheckPower_Cycle)
            {
                if(status->isOn_bulb1 || status->isOn_bulb2 || status->isOn_bulb3 || status->isOn_bulb4)
                {
                    buttonPointer = ui->pushButton_bulbs;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(181, 217, 232));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
                else if(status->isOn_bulb1 == false && status->isOn_bulb2 == false && status->isOn_bulb3 == false && status->isOn_bulb4 == false)
                {
                    buttonPointer = ui->pushButton_bulbs;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::transparent));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
    
                if(status->isOn_hotBulb1 || status->isOn_hotBulb2 || status->isOn_hotBulb3)
                {
                    buttonPointer = ui->pushButton_hotBulbs;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(181, 217, 232));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
                else if(status->isOn_hotBulb1 == false && status->isOn_hotBulb2 == false && status->isOn_hotBulb3 == false)
                {
                    buttonPointer = ui->pushButton_hotBulbs;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::transparent));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
    
                if(status->isOn_PDLC)
                {
                    buttonPointer = ui->pushButton_PDLC;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(181, 217, 232));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
                else
                {
                    buttonPointer = ui->pushButton_PDLC;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::transparent));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
    
                if(status->isOn_waterPump)
                {
                    buttonPointer = ui->pushButton_waterPump;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(181, 217, 232));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
                else
                {
                    buttonPointer = ui->pushButton_waterPump;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::transparent));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
    
                if(status->isOn_doorMotor)
                {
                    buttonPointer = ui->pushButton_doorMotor;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(181, 217, 232));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
                else
                {
                    buttonPointer = ui->pushButton_doorMotor;
                    pal = ui->doorLock_OpenSW->palette();
                    pal.setColor(QPalette::Button, QColor(Qt::transparent));
                    buttonPointer->setPalette(pal);
                    buttonPointer->setAutoFillBackground(true);
                }
            }
    
            if(!status->isPull_Up)
            {
                if(status->currentWaterPower != ui->horizontalSlider_waterPumpSlider->value())
                {
                    ui->horizontalSlider_waterPumpSlider->setValue(status->currentWaterPower);
                    ui->slider_waterPump->setText(QString::number(status->currentWaterPower) + "%");
                    ui->slider_waterPump->setFont(QFont("",15));
                }
                if(status->currentDoorPower != ui->horizontalSlider_doorLock->value())
                {
                    ui->horizontalSlider_doorLock->setValue(status->currentDoorPower);
                    ui->slider_doorLockMotor->setText(QString::number(status->currentDoorPower) + "%");
                    ui->slider_doorLockMotor->setFont(QFont("",15));
                }
            }
            else
            {
                if(100 - status->currentWaterPower != ui->horizontalSlider_waterPumpSlider->value())
                {
                    ui->horizontalSlider_waterPumpSlider->setValue(100 - status->currentWaterPower);
                    ui->slider_waterPump->setText(QString::number(100 - status->currentWaterPower) + "%");
                    ui->slider_waterPump->setFont(QFont("",15));
                }
                if(100 - status->currentDoorPower != ui->horizontalSlider_doorLock->value())
                {
                    ui->horizontalSlider_doorLock->setValue(100 - status->currentDoorPower);
                    ui->slider_doorLockMotor->setText(QString::number(100 - status->currentDoorPower) + "%");
                    ui->slider_doorLockMotor->setFont(QFont("",15));
                }
 
            }
    
    }
    
    
    
    void ControlPanel::OnTimerCallbackFunc2()
    {
        
        status->isDoorOpen = false;
        status->isDoorClose = false;
        status->isNeedToDoorClose = true;
        status->isIgnoreCloseSW_Status = false;
        status->currentDoorPower = status->PIN_HIGH * DOORLOCK_DEFAULT_POWER;// HIGH (For interoperability with Pull-up)
            status->isOn_doorMotor = true;
    #ifdef __linux__
        gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_BACKWARD);
        gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower); 
    #endif
        status->isDoorMotor_Forward = false;
            ui->horizontalSlider_doorLock->setValue(DOORLOCK_DEFAULT_POWER);
            ui->slider_doorLockMotor->setText(QString::number(DOORLOCK_DEFAULT_POWER) + "%");
            ui->slider_doorLockMotor->setFont(QFont("",15));
        m_pTimer2->stop();
        //qDebug()<<"Time's Up, Door will be closing";
        
    }
    
    
    void ControlPanel::on_radioButton_clicked() // 물펌프 순방향
    {
    #ifdef __linux__
                gpioWrite(WATER_PUMP_FB_SIGNAL, MOTOR_FORWARD);
    #endif
                status->isWaterPump_Forward = true;
    }
    
    void ControlPanel::on_radioButton_2_clicked() // 물펌프 역방향
    {
    #ifdef __linux__
                gpioWrite(WATER_PUMP_FB_SIGNAL, MOTOR_BACKWARD);
    #endif
                status->isWaterPump_Forward = false;
    }
    
    void ControlPanel::on_radioButton_3_clicked() // 도어락 모터 순방향
    {
    #ifdef __linux__
                gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_FORWARD);
    #endif
                status->isDoorMotor_Forward = true;
    }
    
    void ControlPanel::on_radioButton_4_clicked() // 도어락 모터 역방향
    {
    #ifdef __linux__
                gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_BACKWARD);
    #endif
                status->isDoorMotor_Forward = false;
    }
    
    void ControlPanel::on_checkBox_stateChanged(int arg1)
    {
        if(arg1)
        {
            status->isIgnoreOpenSW_Status = true;
        }
        else
        {
            status->isIgnoreOpenSW_Status = false;
        }
    }
    void ControlPanel::on_checkBox_2_stateChanged(int arg1)
    {
        if(arg1)
        {
            status->isIgnoreCloseSW_Status = true;
        }
        else
        {
            status->isIgnoreCloseSW_Status = false;
        }
    }
    
    
    
    void ControlPanel::turnOnBulb(void)
    {
    #ifdef __linux__
            gpioWrite(BUBL1, RELAY_SW_PIN_HIGH);
            gpioWrite(BUBL2, RELAY_SW_PIN_HIGH);
            gpioWrite(BUBL3, RELAY_SW_PIN_HIGH);
            gpioWrite(BUBL4, RELAY_SW_PIN_HIGH);
    #endif
                status->isOn_bulb1 = true;
                status->isOn_bulb2 = true;
                status->isOn_bulb3 = true;
                status->isOn_bulb4 = true;
                    status->Current_LED_Status_Value |= 0x01;
                    status->Current_LED_Status_Value |= 0x02;
                    status->Current_LED_Status_Value |= 0x04;
                    status->Current_LED_Status_Value |= 0x08;
                    
    }
    void ControlPanel::turnOffBulb(void)
    {
    #ifdef __linux__
            gpioWrite(BUBL1, RELAY_SW_PIN_LOW);
            gpioWrite(BUBL2, RELAY_SW_PIN_LOW);
            gpioWrite(BUBL3, RELAY_SW_PIN_LOW);
            gpioWrite(BUBL4, RELAY_SW_PIN_LOW);
    #endif
                status->isOn_bulb1 = false;
                status->isOn_bulb2 = false;
                status->isOn_bulb3 = false;
                status->isOn_bulb4 = false;
                    status->Current_LED_Status_Value &=~ 0x01;
                    status->Current_LED_Status_Value &=~ 0x02;
                    status->Current_LED_Status_Value &=~ 0x04;
                    status->Current_LED_Status_Value &=~ 0x08;
    }
    void ControlPanel::turnOnHotBulb(void)
    {
    #ifdef __linux__
           gpioWrite(HOT_BUBL1, RELAY_SW_PIN_HIGH);
           gpioWrite(HOT_BUBL2, RELAY_SW_PIN_HIGH);
           gpioWrite(HOT_BUBL3, RELAY_SW_PIN_HIGH);
    #endif
                status->isOn_hotBulb1 = true;
                status->isOn_hotBulb2 = true;
                status->isOn_hotBulb3 = true;
                    status->Current_LED_Status_Value |= 0x10;
                    status->Current_LED_Status_Value |= 0x20;
                    status->Current_LED_Status_Value |= 0x40;
    }
    void ControlPanel::turnOffHotBulb(void)
    {
    #ifdef __linux__
           gpioWrite(HOT_BUBL1, RELAY_SW_PIN_LOW);
           gpioWrite(HOT_BUBL2, RELAY_SW_PIN_LOW);
           gpioWrite(HOT_BUBL3, RELAY_SW_PIN_LOW);
    #endif
                status->isOn_hotBulb1 = false;
                status->isOn_hotBulb2 = false;
                status->isOn_hotBulb3 = false;
                    status->Current_LED_Status_Value &=~ 0x10;
                    status->Current_LED_Status_Value &=~ 0x20;
                    status->Current_LED_Status_Value &=~ 0x40;
    }
    
    void ControlPanel::turnOnPDLC(void)
    {
    
    #ifdef __linux__
            gpioWrite(PDLC_PIN, RELAY_SW_PIN_HIGH);
    #endif
            status->isOn_PDLC = true;
    }
    void ControlPanel::turnOffPDLC(void)
    {
    
    #ifdef __linux__
            gpioWrite(PDLC_PIN, RELAY_SW_PIN_LOW);
    #endif
            status->isOn_PDLC = false;
    }
    void ControlPanel::turnOnWaterPump(void)
    {
        status->currentWaterPower = status->PIN_HIGH * WATER_PUMP_DEFAULT_POWER;// HIGH (For interoperability with Pull-up)
        status->isOn_waterPump = true;
    #ifdef __linux__
            gpioPWM(WATER_PUMP_PWM, status->currentWaterPower);
    #endif
        
        ui->horizontalSlider_waterPumpSlider->setValue(WATER_PUMP_DEFAULT_POWER);
        ui->slider_waterPump->setText(QString::number(WATER_PUMP_DEFAULT_POWER) + "%");
        ui->slider_waterPump->setFont(QFont("",15));
    
    }
    void ControlPanel::turnOffWaterPump(void)
    {
        status->currentWaterPower = status->PIN_LOW * 100;// LOW (For interoperability with Pull-up)
        status->isOn_waterPump = false;
    #ifdef __linux__
            gpioPWM(WATER_PUMP_PWM, status->currentWaterPower);
    #endif
            ui->horizontalSlider_waterPumpSlider->setValue(0);
            ui->slider_waterPump->setText(QString::number(0) + "%");
            ui->slider_waterPump->setFont(QFont("",15));
    }
    void ControlPanel::turnOnDoorMotor(void)
    {
        status->currentDoorPower = status->PIN_HIGH * DOORLOCK_DEFAULT_POWER;// HIGH (For interoperability with Pull-up);
        status->isOn_doorMotor = true;
    #ifdef __linux__
            gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower); 
    #endif
            ui->horizontalSlider_doorLock->setValue(DOORLOCK_DEFAULT_POWER);
            ui->slider_doorLockMotor->setText(QString::number(DOORLOCK_DEFAULT_POWER) + "%");
            ui->slider_doorLockMotor->setFont(QFont("",15));
    }
    void ControlPanel::turnOffDoorMotor(void)
    {
        status->currentDoorPower = status->PIN_LOW * 100;// LOW (For interoperability with Pull-up)
        status->isOn_doorMotor = false;
    #ifdef __linux__
            gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower);
            
            
    #endif
            ui->horizontalSlider_doorLock->setValue(0);
            ui->slider_doorLockMotor->setText(QString::number(0) + "%");
            ui->slider_doorLockMotor->setFont(QFont("",15));
    }
    
    
    void ControlPanel::on_backButton_clicked()
    {
        this->setWindowState(Qt::WindowMaximized);
        windows[SECURITY_WINDOW]->show();
        windows[SECURITY_WINDOW]->raise();
        windows[SECURITY_WINDOW]->setWindowState(Qt::WindowFullScreen);
    }
    
    void ControlPanel::on_pushButton_clicked()
    {
        m_pTimer->stop();
    }
    
    void ControlPanel::on_pushButton_2_clicked()
    {
        m_pTimer->start(CheckCycleTime);
    }
    
    void ControlPanel::on_checkBox_pullUp_stateChanged(int arg1)
    {
        QMessageBox msgBox;
        msgBox.setText("물펌프, 도어락 관련 핀만 반전됩니다.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        
        if(arg1)
        {
            status->PIN_HIGH = 0;
            status->PIN_LOW = 1;
            status->isPull_Up = true;
        }
        else
        {
            status->PIN_HIGH = 1;
            status->PIN_LOW = 0;
            status->isPull_Up = false;
        }
        turnOffBulb();
        turnOffHotBulb();
        turnOffPDLC();
        turnOffWaterPump();
        if(MOTOR_FORWARD == 1)
        {
            ui->radioButton_2->setChecked(true);
            ui->radioButton_4->setChecked(true);
            status->isWaterPump_Forward = false;
            status->isDoorMotor_Forward = false;
        }
        else
        {
            ui->radioButton->setChecked(true);
            ui->radioButton_3->setChecked(true);
            status->isWaterPump_Forward = true;
            status->isDoorMotor_Forward = true;
            
        }
#ifdef __linux__
        gpioWrite(WATER_PUMP_FB_SIGNAL, status->PIN_LOW);
        gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, status->PIN_LOW );
#endif
        turnOffDoorMotor();
    }
    
