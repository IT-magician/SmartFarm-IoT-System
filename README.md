# 라즈베리파이를 타겟으로 한 IoT System  
(학부생때 만든 프로젝트를 여기 github에 통합을 하려고 합니다. ssafy에서 git을 실제로 사용하고, 다른 사람들이 사용하는 방법을 보면서 git을 포트폴리오로 사용하기 위해 fork합니다.)
설명 : 현장뿐만 아니라 웹(웹페이지)에서도 제어할 수 있도록 만듬.  
(본 프로젝트는 pigpio라는 라이브러리를 사용합니다. pigpio라이브러리는 2020년05월27일 라즈비안 버전에 기본설치가 되어있습니다. 그리고 이 프로젝트 또한 2020년05월27일 라즈비안 버전을 사용하였습니다. 여기서 요점은 pigpio라이브러리가 설치가 되어있어야하며, 2020년05월27일 라즈비안 버전 이후는 기본설치가 되어있을것입니다.)
    
## 사용전 설정 되어야할 것들  
  1. requred_program폴더에 있는 것들  
  2. Water_TEMPERATURE_HUMIDITY폴더에 있는 스케치를 아두이노에 업로드한 다음, 라즈베리파이에 연결한 다음에 QT Project 실행  
     (터미널에 "dmesg|tail|grep tty*"의 명령어를 쳐서 attached 상태인지 확인을 해봐야함)  
  
## 라즈베리파이의 실행파일(QT Project) 빌드방법  
  조건 : 디렉토리 위치를 "QT_Project"으로 이동되었다고 가정  
  초기 : qmake && make  
    ==> 1&#126;5분정도 소요  
  그 이후 : sudo make clean && sudo make  
    ==> 1&#126;5분정도 소요  
  
## 라즈베리파이가 관리(제어)하는 요소  
  8채널 릴레이 스위치, mdd10a(2채널 모터드라이버), md10c, 리미티드 스위치  
  ==> 8채널 릴레이 스위치 : 일반 LED전구  
                           열전구  
                           PDLC필름  
      2채널 모터드라이버 : 자동문을 제어하는 모터 2개(mdd10a에 입력되는 PWM핀과 DIR핀은 똑같음)  
      1채널 모터드라이버 : 물펌프  
  
  
## 라즈베리파이 핀맵  
### For BULB  
   4(BCM - Name : BULB 1)          ===        		Relay_Switch_S_Pin    
  17(BCM - Name : BULB 2)          ===        		Relay_Switch_S_Pin    
  27(BCM - Name : BULB 3)          ===        		Relay_Switch_S_Pin  
  22(BCM - Name : BULB 4)                		    Relay_Switch_S_Pin  
   
### For HOT BULB  
   5(BCM - Name : HOT BULB 1)	   ===		        Relay_Switch_S_Pin   
   6(BCM - Name : HOT BULB 2)	   ===              Relay_Switch_S_Pin    
  13(BCM - Name : HOT BULB 3)	   ===              Relay_Switch_S_Pin    

### For PDLC
   19(BCM - NAME : PDLC)		   ===              Relay_Switch_S_Pin  

### For Door Open/Close (Motor)
   23(BCM - NAME : FORWARD/BACKWARD Singal)	      ===      MDD10A_DIR_PIN1, MDD10A_DIR_PIN2  
   24(BCM - NAME : PWM)				                    ===      MDD10A_PWM_PIN1, MDD10A_PWM_PIN2  
   25(BCM - NAME : SWITCH FOR OPEN  DETECTION)	  ===      SWITCH_ONE_OF_OUT_SIDE(LIMITED SWITCH)  
   12(BCM - NAME : SWITCH FOR CLOSE DETECTION)	  ===      SWITCH_ONE_OF_OUT_SIDE(LIMITED SWITCH)  
   ![Switch Connection](https://github.com/jangsungLee/SmartFarm-IoT-System/blob/master/QT_Project/door_sw_pin.jpg)   

### For Water Pump
   26(BCM - NAME : PWM)				                    ===     MD10C_PWM_PIN  
   18(BCM - NAME : FORWARD/BACKWARD Signal)	      ===     MD10C_DIR_PIN  
     
  
## 아두이노가 관찰하는 센서
  SHT1X(온습도 센서), DFRobot_VEML7700(광측정 센서), 비접촉식 물감지 센서  
  
### For Sensor(Arduino)  
### Sketch(.ino)
[See Source Code](https://github.com/jangsungLee/SmartFarm-IoT-System/blob/master/Water_TEMPERATURE_HUMIDITY/Water_TEMPERATURE_HUMIDITY.ino)  
### Non Contact Water Sensor Connection
![Non Contact Water Sensor Connection](https://github.com/jangsungLee/SmartFarm-IoT-System/raw/master/QT_Project/FIT0212_Connection(Non-Contact%20Water-Level%20Sensor).png?raw=true)  
### SHT1x(Temperature and Humidity Sensor) Connection  
A2    ===   SDA  
A3    ===   SCL  
아래 그림은 이해를 돕기 위한 그림이며, SDA와 SCL의 위치가 좀 다름  
![SHT1x Connection](https://github.com/jangsungLee/SmartFarm-IoT-System/raw/master/QT_Project/SHT1X%20Connection.png?raw=true)  
### Brightness Sensor  
A4    ===   SDA  
A5    ===   SCL  

![DFRobot_VEML7700 Connection](https://github.com/jangsungLee/SmartFarm-IoT-System/raw/master/QT_Project/SEN0228_Arduino_Connection.png?raw=true)  
