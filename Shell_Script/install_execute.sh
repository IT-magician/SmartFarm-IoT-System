#!/bin/bash

MEDIATOR_IP_ADDRESS=220.69.244.50

args=("$@")
if [ $# -gt 0 ];then
        MEDIATOR_IP_ADDRESS=${args[0]}
fi

mkdir /home/pi/doorLock
cd /home/pi/doorLock
wget https://raw.githubusercontent.com/jangsungLee/SmartFarm-IoT-System/Shell_Script/master/install-qt_build_environment.sh
chmod +x install-qt_build_environment.sh
sudo ./install-qt_build_environment.sh

echo "중재자 IP를 ${MEDIATOR_IP_ADDRESS}으로 설정합니다."

wget https://github.com/jangsungLee/SmartFarm-IoT-System/Shell_Script/raw/master/doorLock_System
chmod +x doorLock_System
sudo sed -i 's/@xscreensaver -no-splash/@sudo \/home\/pi\/doorLock\/doorLock_System '"$MEDIATOR_IP_ADDRESS"'\n@xscreensaver -no-splash/g' /etc/xdg/lxsession/LXDE-pi/autostart