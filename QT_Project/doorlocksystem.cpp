#include "doorlocksystem.h"
#include "ui_doorlocksystem.h"

#include <QMovie>
#include <QtCore/QDebug>
#include <QFile>

// 현장에서 비밀번호 입력 및 수정(*123*), 클라우드에서 비밀번호 변경 및 임시비밀번호 발급, 임시비밀번호 1회 사용시 폐기, 일정 시간이 지나면 키입력 값 초기화, 윈도우 raise()

DoorLockSystem::DoorLockSystem(Status *_status, QWidget *_windows[]) :
    windows(_windows),
    ui(new Ui::DoorLockSystem)
{
    ui->setupUi(this);
    setWindowTitle("Door Lock System");
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

    m_pTimer = new QTimer();
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc()));

    m_pTimer1 = new QTimer();
    connect(m_pTimer1, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc1()));
    m_pTimer1->start(CycleTime);


    //this->raise();
    ui->LCD_Display->setAlignment(Qt::AlignCenter);
    ui->LCD_Display->setText("");

    if(!QFile::exists("password.bin"))
    {
        QFile file("password.bin");
        qDebug() << "not exist file";
        memcpy(status->password,initialPassword,strlen(initialPassword));
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "opened file";
            QTextStream out(&file);
            for(int i = 0;i<strlen(initialPassword);i++)
                out << status->password[i];
            file.close();
        }
    }
    else
    {
        QFile file("password.bin");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "not open file";
        }
        else
        {
            qDebug() << "read file";
            QTextStream stream(&file);
            strcpy(status->password, stream.readLine().toStdString().c_str());
            file.close();
        }
    }



    QMovie *movie = new QMovie(":/new/prefix1/a.gif");
    movie->setScaledSize(ui->label_2->size());
    ui->label_2->setMovie(movie);
    movie->start();
}

DoorLockSystem::~DoorLockSystem()
{
    delete ui;
#if defined(__linux__) && defined(SET_ALL_PAGE_PIGPIO_INIT)
    gpioTerminate();
#endif
}

void DoorLockSystem::OnTimerCallbackFunc()
{
    this->Clear();
    m_pTimer->stop();
}

void DoorLockSystem::OnTimerCallbackFunc1()
{
    if(status->isSet_TemporaryPassword && status->current_temporary_password_expiredTime > 0)
    {
        status->current_temporary_password_expiredTime -= CycleTime;

    }
    else
    {
        status->isSet_TemporaryPassword = false;
        memset(status->temporary_password, 0, MAX_PASSWORD_COUNT);
        status->current_temporary_password_expiredTime = status->password_expiredTime;
    }
}

void DoorLockSystem::on_pushButton_1_clicked() // button '1'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '1';
        input_value[number_index++] = '1';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_2_clicked() // button '2'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '2';
        input_value[number_index++] = '2';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_3_clicked() // button '3'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '3';
        input_value[number_index++] = '3';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_4_clicked() // button '4'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '4';
        input_value[number_index++] = '4';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_5_clicked() // button '5'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '5';
        input_value[number_index++] = '5';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_6_clicked() // button '6'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '6';
        input_value[number_index++] = '6';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_7_clicked() // button '7'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '7';
        input_value[number_index++] = '7';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_8_clicked() // button '8'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '8';
        input_value[number_index++] = '8';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_9_clicked() // button '9'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '9';
        input_value[number_index++] = '9';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_20_clicked() // button '0'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '0';
        input_value[number_index++] = '0';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_19_clicked() // button '*'
{
    QMovie *movie;
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
        {
            if(input_value[0] != '*')
                display_letters[i] = encrypted_character;
            else
                display_letters[i] = input_value[i];
        }
        display_letters[number_index] = '*';
        input_value[number_index++] = '*';

        ui->LCD_Display->setText(display_letters);




        if(status->isChaging_CurrentPassword){
            if(number_index < 4/*when input number is 4*/)
                return;

            input_value[number_index - 1] = NULL;

            if(strstr(input_value, "*") == NULL)
            {
                movie = new QMovie(":/new/prefix1/e.gif");
                memcpy(status->password,input_value,number_index);
                QFile file("password.bin");
                qDebug() << "make new password1(file)";
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    qDebug() << "opened file";
                    QTextStream out(&file);
                    for(int i = 0;i<number_index;i++)
                        out << status->password[i];
                    file.close();
                }
            }
            else
            {
                movie = new QMovie(":/new/prefix1/d.gif");
            }

            connect(movie, &QMovie::frameChanged, [=](int frameNumber){ // just play at once.
                if(frameNumber == movie->frameCount() - 1){
                    movie->stop();
                    movie->deleteLater();

                    this->Clear();
                    this->changeInitImage();
                }
            });


            movie->setScaledSize(ui->label_2->size());
            ui->label_2->setMovie(movie);
            movie->start();
            status->isChaging_CurrentPassword = false;
            return;
        }
        else if(input_value[0] != '*')
        {
            input_value[number_index - 1] = NULL;
            if(strncmp(input_value, status->password, number_index) == 0
                    || (status->isSet_TemporaryPassword && strncmp(input_value, status->temporary_password, number_index) == 0))
            {
                if(strncmp(input_value, status->temporary_password, number_index) == 0)
                {
                    status->isSet_TemporaryPassword = false;
                    memset(status->temporary_password,0, MAX_PASSWORD_COUNT);
                }
                movie = new QMovie(":/new/prefix1/c.gif");

                // status->isDoorOpening = true;
                
                status->isIgnoreOpenSW_Status = false;
                status->currentDoorPower = status->PIN_HIGH * DOORLOCK_DEFAULT_POWER;// HIGH (For interoperability with Pull-up);
                status->isOn_doorMotor = true;
#ifdef __linux__
                gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_FORWARD);
                gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower);
#endif
                status->isDoorMotor_Forward = true;
        

                connect(movie, &QMovie::frameChanged, [=](int frameNumber){ // just play at once.
                    if(frameNumber == movie->frameCount()-1){
                        movie->stop();
                        movie->deleteLater();

                        /*QMovie *movie = new QMovie(":/new/prefix1/a.gif");
                        movie->setScaledSize(ui->label_2->size());
                        ui->label_2->setMovie(movie);
                        movie->start();*/
                        this->changeInitImage();
                    }
                });

                qDebug() << "Matched";
            }
            else
            {
                movie = new QMovie(":/new/prefix1/d.gif");

                connect(movie, &QMovie::frameChanged, [=](int frameNumber){ // just play at once.
                    if(frameNumber == movie->frameCount() - 1){
                        movie->stop();
                        movie->deleteLater();

                        QMovie *movie = new QMovie(":/new/prefix1/a.gif");
                        movie->setScaledSize(ui->label_2->size());
                        ui->label_2->setMovie(movie);
                        movie->start();
                    }
                });

                qDebug() << "UnMatched";
            }


            movie->setScaledSize(ui->label_2->size());
            ui->label_2->setMovie(movie);
            movie->start();
            this->Clear();
            return;
        }
        else if(strncmp(input_value, changePassword, strlen(changePassword)) == 0)
        {
            this->Clear();
            ui->label_2->setText("Input The Password You Want To Change!!");
            ui->label_2->setFont(QFont("",15));
            ui->label_2->setAlignment(Qt::Alignment::enum_type::AlignCenter);
            status->isChaging_CurrentPassword = true;
            m_pTimer->start(resetTime);
        }
        else if(strcmp(input_value, systemSetting) == 0)
        {
            this->Clear();

            // windows[SYSTEM_CONTROL]->show();
            this->setWindowState(Qt::WindowMaximized);
            windows[SYSTEM_CONTROL]->show();
            windows[SYSTEM_CONTROL]->raise();
            windows[SYSTEM_CONTROL]->setWindowState(Qt::WindowFullScreen);
        }
        else if(strcmp(input_value, controllPanel) == 0)
        {
            // windows[CONTROL_PANEL]->show();
            this->setWindowState(Qt::WindowMaximized);
            windows[CONTROL_PANEL]->show();
            windows[CONTROL_PANEL]->raise();
            windows[CONTROL_PANEL]->setWindowState(Qt::WindowFullScreen);
        }
        else if(strcmp(input_value, program_exit) == 0)
        {

#ifdef __linux__
            // set Pin Power off
            gpioWrite(BUBL1, RELAY_SW_PIN_LOW);
            gpioWrite(BUBL2, RELAY_SW_PIN_LOW);
            gpioWrite(BUBL3, RELAY_SW_PIN_LOW);
            gpioWrite(BUBL4, RELAY_SW_PIN_LOW);


            gpioWrite(HOT_BUBL1, RELAY_SW_PIN_LOW);
            gpioWrite(HOT_BUBL2, RELAY_SW_PIN_LOW);
            gpioWrite(HOT_BUBL3, RELAY_SW_PIN_LOW);

            gpioWrite(PDLC_PIN, RELAY_SW_PIN_LOW);

            gpioWrite(WATER_PUMP_FB_SIGNAL, status->PIN_LOW);
            gpioWrite(WATER_PUMP_PWM, status->PIN_LOW);


            gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, status->PIN_LOW);
            gpioWrite(DOORLOC_MOTOR_PWM, status->PIN_LOW);

            if(status->fd > -1)
                serClose(status->fd);

            gpioTerminate();
#endif
            exit(0);
        }
        else
            m_pTimer->start(resetTime);
    }
}

void DoorLockSystem::on_pushButton_21_clicked() // button '#'
{
    if(number_index < display_count)
    {
        for(int i = 0;i<number_index;i++)
            display_letters[i] = encrypted_character;
        display_letters[number_index] = '#';
        input_value[number_index++] = '#';

        ui->LCD_Display->setText(display_letters);

        m_pTimer->start(resetTime);
    }

}

void DoorLockSystem::Clear()
{
    number_index = 0;
    memset(display_letters, 0, sizeof(display_letters));
    memset(input_value, 0, sizeof(input_value));
    ui->LCD_Display->setText("");
    if(status->isChaging_CurrentPassword)
    {
        status->isChaging_CurrentPassword = false;
        changeInitImage();
    }
}
void DoorLockSystem::changeInitImage()
{
    QMovie *movie = new QMovie(":/new/prefix1/a.gif");
    movie->setScaledSize(ui->label_2->size());
    ui->label_2->setMovie(movie);
    movie->start();
}

