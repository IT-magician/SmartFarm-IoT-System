@echo off
echo.
nginx -s quit
echo.
echo.
echo. 종료 재확인
Taskkill /IM nginx.exe /F
echo.
echo. nginx 종료 되었습니다
echo.
pause