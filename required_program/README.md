# QT Project가 실행되기전에 실행되어야하는 부가 프로그램
## Mediator Server, Web Server는 필수이며, 카메라 관련 프로그램은 카메라 관련 작업을 보고 싶을 때 켜면 됨.
1. Mediator Server : Mediator(RPI Position Teller)\Position.exe    
2. Web Server : IIS  
            1. "IIS 사이트 > 처리기 매핑 > 스크립트 매핑 추가"에서 아래의 항목을 그대로 입력  
      
            요청한 경로:  
            *.asp  
      
            실행 파일:  
            %windir%\system32\inetsrv\asp.dll  
      
            이름:  
            ASPClassic  
      
            2. HTML에서 ASP가 실행되도록 확장자 등록  
      
            "IIS 사이트 > 처리기 매핑 > 스크립트 매핑 추가"에서 아래의 항목을 그대로 입력  
            요청한 경로:  
            *.html  
      
            실행 파일:  
            %windir%\system32\inetsrv\asp.dll  
      
            이름:  
            ASPhtml  
  
      참고URL : https://itstudyblog.tistory.com/122  

      3. Web_Page폴더를 IIS의 사이트로 등록
        
3. HLS Server : nginx-rtmp\nginx.exe    
      (Stop ==> nginx-rtmp\01_STOP.bat)   
4. Camera Live Streamer : OBS Studio  
       (설정은 "실시간 카메라 관련 설정법.docx"에 나와있는대로 하면 됨.)
5. HLS To MP4 : Release\HLS_TO_MP4.exe  
      (실시간 카메라 영상을 HLS로 전달받아서 저장하는데, 다른 파티션(다른 저장장치)에 영상을 저장하기 때문에 Visual Studio Project\HLS_TO_MP4을 실행하여 Program.cs의 내용을 수정해주어야함. 수정해주어야하는 변수는 URL과 FolderPath변수(9번째 줄)의 내용중 "E:\\"를 수정해주면 됨.)   
6. 저장된 영상 Streaming : Apache Tomcat's webapps ==> Eclipse_Project\eclipse-workspace\Video Streaming Server\src\Streaming.java의 내용을 .war으로 만들어주면 되며 "실시간 카메라 관련 설정법.docx"에 나와있음  
