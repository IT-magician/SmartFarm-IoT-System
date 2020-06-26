
var WebSocket_Buffer/* = new Uint8Array(3);*/

var reader = new FileReader();
var Interval_Check_Time = 500;
var WAS_PORTNUM = "1234";
var WebSocket_URL = "ws://220.69.244.88:" + WAS_PORTNUM;
var ws;
var isWebSocketConnected = false; // 페이지를 벗어날때, WebSocket종료시 엣지브라우저에서 'WebSocket Error'가 일어나는 것을 해결하기 위한 데이터
var isWindowUnload = false;
var isToldError_when_occured = false;
var isPageMove = false;
var onConnect_CallbackFunction = null;
var onStringMessage;
var onStringMessage_CallbackFunction = null;
var onClose_CallbackFunction = null;
window.onbeforeunload = function (e) {
    isWindowUnload_for_position = true;
    isPageMove_for_position = true;
    ws_for_position.close();

    isWindowUnload = true;
    isPageMove = true;
    ws.close();
    //return '페이지를 나가시겠습니까?';
};
function WebSocket_Connect() {
    ws = new WebSocket(WebSocket_URL);
    ws.onopen = WebSocket_onOpen;
    ws.onmessage = Websocket_onMessage;
    ws.onclose = WebSocket_onClose;
    ws.onerror = WebSocket_onError;
    isToldError_when_occured = false;
}

function WebSocket_onOpen(e) {
    //txtRecv.append( "connected<br>" );
    isWebSocketConnected = true;
    //alert("connected");

    //sessionStorage.setItem("isTold_Open","Yes");
    //if(!sessionStorage.getItem("isTold_Open"))
        alert("IoT시스템과 연결되었습니다.");
    if(onConnect_CallbackFunction != null)
        onConnect_CallbackFunction();
}

function Websocket_onMessage(e) {
    try {
        if (e.data instanceof Blob)
            reader.readAsArrayBuffer(e.data);
        else {
            // if the server sent string(message).
            //console.log(e.data);
            onStringMessage = e.data;
            
            if(onStringMessage_CallbackFunction != null)
                onStringMessage_CallbackFunction()
        }
    }
    catch (e) {
        //console.log("I'm Busy");
    }
}

function WebSocket_onClose(e) {
    isWebSocketConnected = false;
    //alert("closed");
    if (!isPageMove)
        alert("IoT시스템과 연결이 끊어졌습니다.\nIoT시스템의 인터넷 상태 혹은 인터넷 연결을 확인하세요.");
    
    if(onClose_CallbackFunction != null)
        onClose_CallbackFunction();
}

function WebSocket_onError(e) {
    if (!isWebSocketConnected && !isToldError_when_occured) {

        //if (!isPageMove)
        //    alert("임베디드 보드와 연결할 수 없습니다.\n컴퓨터와 임베디드 보드의 인터넷 연결을 확인하세요.");
        isToldError_when_occured = true;
    }
    isWebSocketConnected = false;
}


var WebSocket_Buffer_for_position/* = new Uint8Array(3);*/

var WAS_PORTNUM_for_position = "9000";
var WebSocket_URL_for_position = "ws://" + window.location.host +":" + WAS_PORTNUM_for_position;
var ws_for_position;
var isWebSocketConnected_for_position = false; // 페이지를 벗어날때, WebSocket종료시 엣지브라우저에서 'WebSocket Error'가 일어나는 것을 해결하기 위한 데이터
var isWindowUnload_for_position = false;
var isToldError_when_occured_for_position = false;
var isPageMove_for_position = false;
var onConnect_CallbackFunction_for_position = null;
var onStringMessage_for_position;
var onStringMessage_CallbackFunction_for_position = null;
var onClose_CallbackFunction_for_position = null;
function WebSocket_Connect_for_position() {
    ws_for_position = new WebSocket(WebSocket_URL_for_position);
    ws_for_position.onopen = WebSocket_onOpen_for_position;
    ws_for_position.onmessage = Websocket_onMessage_for_position;
    ws_for_position.onclose = WebSocket_onClose_for_position;
    ws_for_position.onerror = WebSocket_onError_for_position;
    isToldError_when_occured_for_position = false;
}

function WebSocket_onOpen_for_position(e) {
    //txtRecv.append( "connected<br>" );
    isWebSocketConnected_for_position = true;
    //alert("connected");

    //sessionStorage.setItem("isTold_Open","Yes");
    //if(!sessionStorage.getItem("isTold_Open"))
    //    alert("보드와 연결되었습니다.");
    
    if(onConnect_CallbackFunction_for_position != null)
       onConnect_CallbackFunction_for_position();
   ws_for_position.send("Where's RPI");
}

function Websocket_onMessage_for_position(e) {
    if (e.data instanceof Blob)
            {
                
            }
        else {
            // if the server sent string(message).
            //console.log(e.data);
            onStringMessage_for_position = e.data;
            
            if(onStringMessage_CallbackFunction_for_position != null)
                onStringMessage_CallbackFunction_for_position()

            console.log(onStringMessage_for_position);
            if(onStringMessage_for_position != "null")
            {
                WebSocket_URL = "ws://" + onStringMessage_for_position + ":" + WAS_PORTNUM;
                console.log(WebSocket_URL);
                WebSocket_Connect();
            }
            else
                alert("현재 서버의 위치를 알 수 없습니다.\nIoT시스템의 상태를 확인후 재접속하세요.");
        }
}

function WebSocket_onClose_for_position(e) {
    isWebSocketConnected_for_position = false;
    //alert("closed");
    if (!isPageMove_for_position)
        alert("임베디드 보드와 연결이 끊어졌습니다.\n컴퓨터와 임베디드 보드의 인터넷 연결을 확인하세요.");
    
    if(onClose_CallbackFunction_for_position != null)
        onClose_CallbackFunction_for_position();
}

function WebSocket_onError_for_position(e) {
    if (!isWebSocketConnected_for_position && !isToldError_when_occured_for_position) {

        //if (!isPageMove)
        //    alert("임베디드 보드와 연결할 수 없습니다.\n컴퓨터와 임베디드 보드의 인터넷 연결을 확인하세요.");
        isToldError_when_occured_for_position = true;
    }
    isWebSocketConnected_for_position = false;
}

