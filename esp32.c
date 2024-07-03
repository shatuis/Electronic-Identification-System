#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ABA MAXDRONE";
const char *password = "123arduino123";

String currentValue = "";
String readBuffer = "";
String webSite, javaScript, XML;

ESP8266WebServer server(80);

voidhandleRoot()
{
    server.send(200, "text/html", currentValue);
}

void setup()
{
    delay(1000);
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    // WiFi.softAP(ssid, password);
    IPAddressip(192, 168, 1, 4);
    IPAddressgateway(192, 168, 1, 1);
    IPAddresssubnet(255, 255, 255, 0);
    WiFi.config(ip, gateway, subnet);
    // 192.168.4.1
    server.on("/", handleWebsite);
    server.on("/data", handleData);
    server.on("/boton", handleBoton);
    server.begin();
}

void loop()
{
    server.handleClient();
    yield();
}

voidhandleData()
{
    buildXML();
    server.send(200, "text/xml", XML);
}

voidhandleBoton()
{
    Serial.write('A');
    delay(500);
    Serial.write('?');
    delay(500);
    int t = 0;
    while (t == 0)
    {
        if (Serial.available() > 0)
        {
            charinChar = (char)Serial.read();
            if (inChar == '\n')
            {
                currentValue = readBuffer;
                readBuffer = "";
                t = 1;
            }
            else
            {
                readBuffer += inChar;
            }
        }
    }
    server.send(200, "text/xml", "<?xml version='1.0'?><response>" + currentValue + "</response>");
}

voidbuildXML()
{
    XML = "<?xml version='1.0'?>";
    XML += "<response>";
    XML += currentValue;
    XML += "</response>";
}

voidhandleWebsite()
{
    buildWebsite();
    server.send(200, "text/html", webSite);
}

voidbuildWebsite()
{ // webSite+="\n";
    buildJavascript();
    webSite = "<!DOCTYPE html>\n";
    webSite += "<html lang=\"es\">\n";
    webSite += "<head>\n";
    webSite += "<meta charset=\"UTF-8\">\n";
    webSite += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    webSite += "<title>Identificador #DAA0004 - MaxDrone Venezuela</title>\n";
    webSite += "<style>\n";
    webSite += "@charset \"UTF-8\";.notice,body{background-color:#FFF}body{font-family:\"Open Sans\",Arial,Helvetica,sans-serif;font-size:14px;font-weight:400;line-height:1.4;color:#525252;margin:0}.container,main{width:inherit;max-width:1200px;margin:0 auto;padding:0 35px}.box,.notice,.panel,p{margin-bottom:10px}@media (max-width:800px){.container,main{padding:0 10px}}footer{margin:15px 0;padding:5px 0}hr{margin:20px 0;border:0;border-top:1px solid #f7f7f7}.row:after,.row:before{content:\" \";display:table}.row:after{clear:both}.box{float:left;margin-left:1.25%;margin-right:1.25%}@media (max-width:800px){.box{width:100%!important;margin-left:auto;margin-right:auto;display:block;float:none}}.box.col-4{width:30.8333333333%}.box.col-6{width:47.5%}img{margin:0}.notice{display:block;padding:16px 20px;font-size:16px;border:1px solid #f7f7f7;border-left-width:5px;border-left-color:#525252;-webkit-border-radius:2px;-moz-border-radius:2px;-ms-border-radius:2px;border-radius:2px}.notice.mxd{border-left-color:#163090}.notice.mxd b,.notice.mxd h4,.notice.mxd strong{color:#163090}.notice.mxdY{border-left-color:#F9B122}.notice.mxdY b,.notice.mxdY h4,.notice.mxdY strong{color:#F9B122}.panel{border:1px solid #fff;overflow:hidden;-webkit-border-radius:2px;-moz-border-radius:2px;-ms-border-radius:2px;border-radius:2px}.panel .panel-head{padding:10px 20px 9px;border-bottom:1px solid #163090;background:#525252;font-weight:700;color:#FFF}.panel .panel-body{padding:15px 20px 14px;background:#FFF}.panel.mxd{border:1px solid #163090}.panel.mxd .panel-head{background:#163090;border-bottom:1px solid #163090}.panel.mxdY{border:1px solid #F9B122}.panel.mxdY .panel-head{background:#F9B122;border-bottom:1px solid #F9B122}b,strong{font-weight:700}.btn{font:inherit;font-weight:700;padding:6px 16px;margin-bottom:5px;color:#525252;text-align:center;border:1px solid #f7f7f7;background:#163090;cursor:pointer;-webkit-transition:background .1s;-moz-transition:background .1s;-o-transition:background .1s;transition:background .1s;-webkit-border-radius:2px;-moz-border-radius:2px;-ms-border-radius:2px;border-radius:2px;display:-moz-inline-stack;display:inline-block}.btn.error{color:#FFF;border:1px solid #F9B122;background:#F9B122}.btn.error:active,.btn.error:hover{border:1px solid #F9B122;background:#F9B122}.btn.error.clean{color:#F9B122;border:2px solid #F9B122;background:0 0}.btn.error.clean:active,.btn.error.clean:hover{color:#F9B122;border:2px solid #F9B122}footer{text-align: center; color: #F9B122}\n";
    webSite += "</style>\n";
    webSite += "</head>\n";
    webSite += javaScript;
    webSite += "<body onload='process()' style=background-color:#163090>\n";
    webSite += "<main class=\"main\">\n";
    webSite += "<div align=\"center\">\n";
    webSite += "<img width=\"256\" height=\"135\" src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAQAAAACHCAYAAAD5sIeyAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAA4ZpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuNi1jMTMyIDc5LjE1OTI4NCwgMjAxNi8wNC8xOS0xMzoxMzo0MCAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wTU09Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9tbS8iIHhtbG5zOnN0UmVmPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VSZWYjIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtcE1NOk9yaWdpbmFsRG9jdW1lbnRJRD0ieG1wLmRpZDo1MjhlZDEwYy01YjI0LTQzOWMtOWI5MS1jNTM0OTg4ZmFkNWQiIHhtcE1NOkRvY3VtZW50SUQ9InhtcC5kaWQ6RjQ5OEExMDQ3MjEyMTFFNjhGM0I5NTJDMDdEQkIwNjUiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6RjQ5OEExMDM3MjEyMTFFNjhGM0I5NTJDMDdEQkIwNjUiIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIENDIDIwMTUgKE1hY2ludG9zaCkiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDo0YWM5NDMzYy0yOTFlLTRmNjMtODk0MC1hNGM5YjQxMDJkZGMiIHN0UmVmOmRvY3VtZW50SUQ9ImFkb2JlOmRvY2lkOnBob3Rvc2hvcDo1OTAyOTM2Zi1iYTczLTExNzktYTRh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\"<br>\n";
    webSite += "</div>\n";
    webSite += "<hr>\n";
    webSite += "<div class=\"notice mxdY\">\n";
    webSite += "<strong>Identificador</strong> - version 0.1 - Drone: <strong>DAA0004</strong> - MaxDrone Venezuela\n";
    webSite += "</div>\n";
    webSite += "<hr>\n";
    webSite += "<button onclick=\"prueba()\"  class=\"btn error\">SolicitarMatricula</button>\n";

    webSite += "<div class=\"row\">\n";

    webSite += "<div class=\"box col-4\">\n";
    webSite += "<div class=\"panel mxdY\">\n";
    webSite += "<div class=\"panel-head\">Matricula</div>\n";
    webSite += "<div class=\"panel-body\">\n";
    webSite += "<a id='fecha'>.</a>\n";
    webSite += "</div>\n";
    webSite += "</div>\n";
    webSite += "</div>\n";
    webSite += "</div>\n";
    webSite += "<hr>\n";
    webSite += "<footer>\n";
    webSite += "<p>&copy; 2016 MaxDrone Venezuela &mdash; JORGE GOMEZ  &mdash; DepartamentoI+D+i</p>\n";
    webSite += "</footer>\n";
    webSite += "</main>\n";
    webSite += "</body>\n";
    webSite += "</html>\n";
}

voidbuildJavascript()
{
    javaScript = "<script>\n";
    javaScript += "varxmlHttp=createXmlHttpObject();\n";

    javaScript += "function createXmlHttpObject(){\n";
    javaScript += " if(window.XMLHttpRequest){\n";
    javaScript += "    xmlHttp=new XMLHttpRequest();\n";
    javaScript += " }else{\n";
    javaScript += "    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n";
    javaScript += " }\n";
    javaScript += " return xmlHttp;\n";
    javaScript += "}\n";

    javaScript += "function prueba(){\n";
    javaScript += " if(xmlHttp.readyState==0 || xmlHttp.readyState==4){\n";
    javaScript += "   xmlHttp.open('PUT','boton',true);\n";
    javaScript += "   xmlHttp.onreadystatechange=handleServerResponse;\n";
    javaScript += "   xmlHttp.send(null);\n";
    javaScript += " }\n";
    javaScript += "}\n";

    javaScript += "function handleServerResponse(){\n";
    javaScript += " if(xmlHttp.readyState==4 &&xmlHttp.status==200){\n";
    javaScript += "   xmlResponse=xmlHttp.responseXML;\n";
    javaScript += "   xmldoc = xmlResponse.getElementsByTagName('response');\n";
    javaScript += "   message = xmldoc[0].firstChild.nodeValue;\n";
    javaScript += " document.getElementById('fecha').innerHTML=message;\n";
    javaScript += " }\n";
    javaScript += "}\n";
    javaScript += "</script>\n";
}
