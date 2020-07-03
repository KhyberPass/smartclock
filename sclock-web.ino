
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#endif
#if defined(ESP32)
#include <WebServer.h>
#endif

#if defined(ESP8266)
ESP8266WebServer server(80);
#else
WebServer server(80);
#endif

String getPage(){
//  String page = ""
  String page = R"=====(
<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN' 'http://www.w3.org/TR/html4/loose.dtd'>
<html><head><meta name='viewport' content='width=device-width, initial-scale=1'/>
<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css' integrity='sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh' crossorigin='anonymous'>
<script src='https://code.jquery.com/jquery-3.5.1.min.js' integrity='sha256-9/aliU8dGd2tb6OSsuzixeV4y/faTqgFtohetphbbj0=' crossorigin='anonymous'></script>
<script src='https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/js/bootstrap.min.js' integrity='sha384-OgVRvuATP1z7JjHLkuOU7Xw704+h835Lr+6QL9UvYjZE3Ipu6Tp75j7Bh/kR0JKI' crossorigin='anonymous'></script>

<script>
$(document).ready(function () {
$('.btn').on('click', function () {
    var Status = 1;//$(this).val();
  $.ajax({
    url: '/',
    data: {
      Status: Status
    },
    dataType : 'json',
    error: function() {
      alert('Error');
    },
    'success' : function(data) {
      if (data == 'success') {
        alert('request sent!');
      }
    }
  });
});
});
</script>
<title>SmartClock</title></head><body>
<div class='container-fluid'>
  <div class='row'>
    <div class='col-md-12' align='center'>
      <div class='jumbotron'>
        <h2>SmartClock</h2>
        <p>Current Time</p>
        <p>12:30</p>
      </div>
    </div>
  </div>
  <div class='row' align='center'>
    <div class='col-md-4'>
      <button type='button' class='btn btn-success btn-lg OnClick=xxtest value=xxtest'>Alarms</button>
    </div>
    <div class='col-md-4'>
      <button type='button' class='btn btn-success btn-lg'>Config</button>
    </div>
    <div class='col-md-4'>
      <button type='button' class='btn btn-success btn-lg'>About</button>
    </div>
  </div>
</div>
</body></html>
)=====";

//page += sclockTimeGet();
//page += ""

  return page;
} 

void handleRoot() {
  // Check for actions
  Serial.println("Web - uri: " + server.uri());
  for (uint8_t i = 0; i < server.args(); i++) {
    Serial.println("Web - args: " + i + server.argName(i) + ": " + server.arg(i));
  }


  if (server.args() > 0) {
    server.send(204);
    return;
  }

  server.send(200, "text/html", getPage());
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void sclockWebSetup(void)
{

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  
}

void sclockWebLoop(void)
{
  server.handleClient();
}
