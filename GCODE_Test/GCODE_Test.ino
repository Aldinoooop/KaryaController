// #ifdef ESP32
#include <WiFi.h>
#include <WiFiAP.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "FS.h"
#include "SPIFFS.h"
#include <WebSocketsServer.h>

// #include "webmemory.h"
#include "common.h"
// #include "gcodesave.h"
#include "gcode.h"
#include "eprom.h"


unsigned long lastTime = 0;

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
// #endif

// String wifi_ap;
// String wifi_pwd;
// String wifi_dns;

IPAddress fixedip;
IPAddress ip;
IPAddress serverIP;

File fsUploadFile;

int connect_timeout = 10;
int ISWIFIOK = 0;
int uncompress = 0;
bool isconfig, isfirmware;

uint8_t wf[256];
uint8_t wfhead = 0;
uint8_t wftail = 0;
uint8_t wfbuf[256];
char wfb[300];
int wfl = 0;
int bpwf = 0;

int line_done, ack_waiting = 0;
int ct = 0;
uint32_t gt = 0;
int n = 0;

void connectWifi(int ret = 1) {
  if (ret) {
    WiFi.reconnect();
    return;
  }

  //xprintf(PSTR("Try connect wifi AP:%s \n"), wifi_ap);
  WiFi.mode(WIFI_STA);
  if (fixedip[0] > 0) {
    IPAddress gateway;
    gateway = fixedip;
    gateway[3] = 1;
    IPAddress subnet(255, 255, 255, 0);
    WiFi.config(fixedip, gateway, subnet);
  }
  WiFi.begin(wifi_ap, wifi_pwd);

  int cntr = connect_timeout;

  while (WiFi.status() != WL_CONNECTED && cntr > 0) {
    delay(200);
    // #ifdef IR_OLED_MENU
    //     d_clear();
    //     d_text(0, 0, VERSION);
    //     d_text(0, 1, "connecting ... " + String(cntr));
    //     d_text(0, 2, wifi_ap);
    //     d_show();
    // #endif
    cntr--;
    //xprintf(PSTR("."));
    //Serial.print(".");
  }

  //WiFi.setAutoReconnect(true);
  //WiFi.persistent(true);
}

void setupwifi(int num) {
  // NOINTS

  while (1) {
    // xprintf(PSTR("Wifi Initialization\n"));
    Serial.print("Wifi Initialization\n");
    if (num) {
      //xprintf(PSTR("Connected to:%s Ip:%d.%d.%d.%d\n"), wifi_ap, fi(ip[0]), fi(ip[1]), fi(ip[2]), fi(ip[3]) );
      //xprintf(PSTR("Disconnect\n"));
      WiFi.disconnect();
      server.close();
      //servertcp.close();
#ifdef WEBSOCKSERVER
      webSocket.close();
#endif
    }
    if (wifi_ap) connectWifi(0);
    String ipa = String("->") + wifi_ap;
    ISWIFIOK = 0;
    if ((connect_timeout > 0 && WiFi.status() != WL_CONNECTED) || wifi_ap.length() == 0) {
      // xprintf(PSTR("Access Point Mode\n"));
      Serial.print("Access Point Mode\n");
      /*IPAddress local_IP(192, 168, 4, 1);
        IPAddress gateway(192, 168, 4, 9);
        IPAddress subnet(255, 255, 255, 0);
        WiFi.softAPConfig(local_IP, gateway, subnet);
      */
      WiFi.mode(WIFI_AP);
      ISWIFIOK = 0;

      if (wifi_dns == "") wifi_dns = String("ESP_CNC");
      WiFi.softAP(wifi_dns);

      //ip = WiFi.softAPIP();
      //xprintf(PSTR("AP:%s Ip:%d.%d.%d.%d\n"), ((' '<wifi_dns[0]<'Z')?wifi_dns:ssid), fi(ip[0]), fi(ip[1]), fi(ip[2]), fi(ip[3]));
      ipa = String(wifi_dns) + String(" : 4.1");
      Serial.print(ipa);
    }

    // #ifdef IR_OLED_MENU
    //     extern String IPA;
    //     IPA = ipa;
    //     Serial.end();
    //     hasSerial = 0;
    // #endif

    // server.on("/setconfig", HTTP_GET, []() {  // if the client requests the upload page
    //   // NOINTS
    //   wifi_dns = server.arg("name");
    //   wifi_ap = server.arg("ap");
    //   wifi_pwd = server.arg("pw");
    //   server.send(200, "text/html", "OK");
    //   // saveconfigs();
    //   delay(1000);
    //   ESP.restart();
    //   // INTS
    // });

    // server.on("/gcode", HTTP_GET, []() {  // if the client requests the upload page
    //   if (!uncompress) {
    //     char gc[100];
    //     server.arg("t").toCharArray(gc, 99);
    //     for (int i = 0; i < strlen(gc); i++) {
    //       buf_push(wf, gc[i]);
    //     }
    //     buf_push(wf, '\n');
    //     server.send(200, "text/html", "OK");
    //   } else {
    //     server.send(200, "text/plain", "ERR");
    //   }
    // });

    // server.on("/speed", HTTP_GET, []() {  // if the client requests the upload page
    //   extern uint8_t head, tail, tailok;
    //   char gc[10];
    //   server.arg("t").toCharArray(gc, 9);
    //   extern float f_multiplier;
    //   f_multiplier = atoi(gc) * 0.01;
    //   tailok = tail + 5;  // need to replanning all moves
    //   server.send(200, "text/html", "OK");

    // });

    // server.on("/tool", HTTP_GET, []() {  // if the client requests the upload page
    //   int v = server.arg("t").toInt();
    //   extern void testLaser(void);
    //   if (v == 125) testLaser();
    //   else set_tool(v);
    //   server.send(200, "text/html", "OK");
    // });

    // server.on("/updatefirmware", HTTP_GET, []() {  // if the client requests the upload page
    //   server.send(200, "text/html", "OK");
    //   updateFirmware();
    // });

    server.on("/getconfig", HTTP_GET, []() {  // if the client requests the upload page
      String st = "disconnected";
      if (WiFi.status() == WL_CONNECTED)
        st = "connected";
      server.send(200, "text/html", String("['") + wifi_ap + "','" + wifi_pwd + "','" + wifi_dns + "','" + st + "']");
    });

    server.on("/scanwifi", HTTP_GET, []() {
      int n = WiFi.scanNetworks();
      String res = "[";
      if (n == 0) {
      } else {
        for (int i = 0; i < n; ++i) {
          // Print SSID and RSSI for each network found
          if (i)
            res += ",";
          res += "['" + WiFi.SSID(i) + "','" + WiFi.RSSI(i) + "',";
          if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN)
            res += "''";
          else
            res += "'*'";
          res += "]";
        }
      }
      res += "]";
      server.send(200, "text/html", res);
    });

    // #ifdef ANALOG_THC
    //     server.on("/thc", HTTP_GET, []() {
    //       extern String formatthc();
    //       String res = formatthc();
    //       server.send(200, "text/html", res);
    //     });
    // #endif

    // #ifdef PLOTTING
    //     server.on("/temp", HTTP_GET, []() {
    //       extern String formattemp();
    //       String res = formattemp();
    //       server.send(200, "text/html", res);
    //     });
    //     server.on("/velo", HTTP_GET, []() {
    //       extern String formatvelo();
    //       String res = formatvelo();
    //       server.send(200, "text/html", res);
    //     });
    // #endif

    // server.on("/pauseprint", HTTP_GET, []() {  // if the client requests the upload page
    //   //NOINTS
    //   if (uncompress) {
    //     ispause = ispause == 0 ? 1 : 0;
    //     extern int8_t PAUSE;
    //     PAUSE = ispause;
    //     server.send(200, "text/html", ispause == 1 ? "PAUSED" : "RESUMED");
    //   } else {
    //     server.send(200, "text/plain", "ERR");
    //   }
    //   //INTS
    // });

    // server.on("/probe", HTTP_GET, []() {
    //   //NOINTS
    //   if (!uncompress) {
    //     docheckendstop(1);
    //     extern int16_t endstopstatus;
    //     server.send(200, "text/html", endstopstatus < 0 ? "HIGH" : "LOW");
    //   } else {
    //     server.send(200, "text/plain", "ERR");
    //   }
    //   //INTS
    // });

    // server.on("/resumeprint", HTTP_GET, []() {  // if the client requests the upload page
    //   //NOINTS
    //   if (uncompress) {
    //     ispause = 0;
    //     extern int8_t PAUSE;
    //     PAUSE = ispause;
    //     server.send(200, "text/html", "OK");
    //   } else {
    //     server.send(200, "text/plain", "ERR");
    //   }
    //   //INTS
    // });

    // server.on("/startprint", HTTP_GET, []() {  // if the client requests the upload page
    //   NOINTS
    //   if (uncompress) {
    //     server.send(200, "text/html", "FAIL, STILL PRINTING");
    //   } else {
    //     server.send(200, "text/html", "OK");
    //     beginuncompress("/gcode.gcode", false, 0);
    //   }
    //   INTS
    // });

    // server.on("/startjob", HTTP_GET, []() {  // if the client requests the upload page
    //   NOINTS
    //   if (uncompress) {
    //     server.send(200, "text/html", "FAIL, STILL PRINTING");
    //   } else {
    //     extern String jobname;
    //     jobname = server.arg("jobname");
    //     beginuncompress(jobname, false, 0);
    //     server.send(200, "text/html", "Start Ok");
    //   }
    //   INTS
    // });

    // server.on("/previewjob", HTTP_GET, []() {  // if the client requests the upload page
    //   NOINTS
    //   if (uncompress) {
    //     server.send(200, "text/html", "FAIL, STILL PRINTING");
    //   } else {
    //     extern String jobname;
    //     jobname = server.arg("jobname");
    //     extern void check_job();
    //     extern void runpreview();
    //     check_job();
    //     runpreview();
    //   }
    //   // INTS
    // });

    // server.on("/removejob", HTTP_GET, []() {  // if the client requests the upload page
    //   NOINTS
    //   if (uncompress) {
    //     server.send(200, "text/html", "FAIL, STILL PRINTING");
    //   } else {
    //     deletejob(server.arg("jobname"));
    //     server.send(200, "text/html", "Delete Ok");
    //   }
    //   INTS
    // });

    // server.on("/renamejob", HTTP_GET, []() {  // if the client requests the upload page
    //   NOINTS
    //   if (uncompress) {
    //     server.send(200, "text/html", "FAIL, STILL PRINTING");
    //   } else {
    //     SPIFFS.rename(server.arg("jobname"), server.arg("newname"));
    //     SPIFFS.rename(server.arg("jobname") + ".jpg", server.arg("newname") + ".jpg");
    //     server.send(200, "text/html", "Rename Ok");
    //   }
    //   INTS
    // });

    // server.on("/getfree", HTTP_GET, []() {
    //   if (!uncompress) {
    //     FSInfo fs_info;
    //     SPIFFS.info(fs_info);
    //     int tBytes = fs_info.totalBytes;
    //     int uBytes = fs_info.usedBytes;
    //     server.send(200, "text/plain", "[" + String(tBytes) + "," + String(uBytes) + "]");
    //   }
    // });

    // server.on("/clearjobs", HTTP_GET, []() {
    //   NOINTS
    //   Dir dir = SPIFFS.openDir("/");
    //   while (dir.next()) {
    //     String s = dir.fileName();
    //     if (s.endsWith(".gcode") || s.endsWith(".jpg")) {
    //       SPIFFS.remove(s);
    //     }
    //   }
    //   server.send(200, "text/plain", "Ok");
    //   INTS
    // });

    //     server.on("/getjobs", HTTP_GET, []() {
    //       NOINTS
    //       if (!uncompress) {
    //         String str = "[";
    // #ifdef ESP32
    //         File dir = SPIFFS.open("/");
    //         File file = dir.openNextFile();
    //         while (file) {
    //           String s = file.name();
    //           if (s.endsWith(".gcode")) {
    //             if (str.length() > 2)
    //               str += ",";
    //             str += "['";
    //             str += file.name();
    //             str += "',";
    //             str += file.size();
    //             str += "]";
    //           }
    //           file = dir.openNextFile();
    //         }
    // #elif ESP8266
    //           Dir dir = SPIFFS.openDir("/");
    //           while (dir.next()) {
    //             String s = dir.fileName();
    //             if (s.endsWith(".gcode")) {
    //               if (str.length() > 2) str += ",";
    //               str += "['";
    //               str += dir.fileName();
    //               str += "',";
    //               str += dir.fileSize();
    //               str += "]";
    //             }
    //           }
    // #endif

    //         str += "]";
    //         server.send(200, "text/plain", str);
    //       } else {
    //         server.send(200, "text/plain", "ERR");
    //       }
    //       INTS
    //     });

    // server.on("/stopprint", HTTP_GET, []() {  // if the client requests the upload page
    //   if (!uncompress) {
    //     server.send(200, "text/html", "FAIL, NOT PRINTING");
    //   } else {
    //     server.send(200, "text/html", "OK");
    //     extern void stopmachine();
    //     stopmachine();
    //   }
    // });

    // server.on("/home", HTTP_GET, []() {  // if the client requests the upload page
    //   addmove(100, 0, 0, 10, 0, 1, 1);
    //   addmove(100, 0, 0, 10, 0, 1, 0);
    //   addmove(100, 0, 0, 0, 0, 1, 0);
    //   server.send(200, "text/html", "OK");
    //   //homing();
    // });

    // server.on("/jogmove", HTTP_GET, []() {  // if the client requests the upload page
    //   server.send(200, "text/html", "OK");
    //   if (!uncompress) {
    //     float x, y, z;
    //     x = server.arg("x").toFloat();
    //     y = server.arg("y").toFloat();
    //     z = server.arg("z").toFloat();
    //     addmove(100, x, y, z, 0, 1, 1);
    //   }
    // });


    // server.on("/t", HTTP_GET, []() {  // if the client requests the upload page
    //   serverIP = server.client().remoteIP();
    //   server.send(200, "text/plain", "OK");
    //   sendTelegram("test");
    // });

    server.on("/upload", HTTP_GET, []() {  // if the client requests the upload page
      //xprintf(PSTR("Handle UPLOAD \n"));
      serverIP = server.client().remoteIP();
      //serverIP=String(ip[0])+"."+String(ip[1])+"."+String(ip[2])+"."+String(ip[3]);

      server.send(200, "text/html", "<form method=\"post\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"name\"> <input class=\"button\" type=\"submit\" value=\"Upload\"></form>");
    });

    // server.on("/delete", HTTP_GET, []() {  // if the client requests the upload page
    //   //xprintf(PSTR("Handle UPLOAD \n"));
    //   String s = server.arg("fn");
    //   SPIFFS.remove(s);
    //   server.send(200, "text/html", "Delete " + server.arg("fn"));
    //   if (s.endsWith(".ini")) readconfigs();
    // });
    // server.on("/rename", HTTP_GET, []() {  // if the client requests the upload page
    //   //xprintf(PSTR("Handle UPLOAD \n"));
    //   SPIFFS.rename(server.arg("fn"), server.arg("fnew"));
    //   server.send(200, "text/html", "Rename to " + server.arg("fnew"));
    // });

    server.on(
      "/upload", HTTP_POST,  // if the client posts to the upload page
      []() {
        server.sendHeader("Access-Control-Expose-Headers", "Access-Control-*");
        server.sendHeader("Access-Control-Allow-Headers", "Access-Control-*, Origin, X-Requested-With, Content-Type, Accept");
        server.sendHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS, HEAD");
        server.sendHeader("Access-Control-Allow-Origin", "*");
        server.send(200);
      },                // Send status 200 (OK) to tell the client we are ready to receive
      handleFileUpload  // Receive and save the file
    );

    server.onNotFound([]() {                                 // If the client requests any URI
      if (!handleFileRead(server.uri()))                     // send it if it exists
        server.send(404, "text/plain", "404: Not Found ?");  // otherwise, respond with a 404 (Not Found) error
    });

    server.begin();

    //if (MDNS.begin(wifi_ap)) {
    //Serial.println("MDNS responder started");
    //}

    // #ifdef TCPSERVER
    //     servertcp.begin();
    // #endif

    // #ifdef WEBSOCKSERVER
    webSocket.begin();                  // start the websocket server
    webSocket.onEvent(webSocketEvent);  // if there's an incomming websocket message, go to function 'webSocketEvent'
    // #endif

    //     if (num)
    //       return;
    //     // loadmeshleveling();
    //     touchserver(1, String(wifi_dns));

    // #ifdef DISABLESERIAL
    //     //Serial.end();
    // #endif


    // if (ip[2] == 1) {
    //downloadFile("http://192.168.1.13:8888/esp/websocket.js","/websocket.js");
    //downloadFile("http://192.168.1.13:8888/esp/jobs.html","/jobs.html");
    //downloadFile("http://192.168.1.13:8888/esp/cnc.html","/cnc.html");
    //downloadFile("http://192.168.1.13:8888/esp/karyaconfig.html","/karyaconfig.html");
    //downloadFile("http://192.168.1.13:8888/esp/test.gcode","/test.gcode");
    //downloadFile("http://192.168.1.13:8888/esp/config.ini","/config.ini");
    // }


    // #ifdef USEOTA
    //     ArduinoOTA.onStart([]() {
    //       String type;
    //       if (ArduinoOTA.getCommand() == U_FLASH)
    //         type = "sketch";
    //       else  // U_SPIFFS
    //         type = "filesystem";

    //       // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    //       //Serial.println("Start updating " + type);
    //     });
    //     ArduinoOTA.onEnd([]() {
    //       //Serial.println("\nEnd");
    //     });
    //     ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //       //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    //     });
    //     ArduinoOTA.onError([](ota_error_t error) {
    //       /*Serial.printf("Error[%u]: ", error);
    //         if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    //         else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    //         else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    //         else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    //         else if (error == OTA_END_ERROR) Serial.println("End Failed");
    //       */
    //     });
    //     ArduinoOTA.begin();
    // #endif

    break;
  }
  //  return;

  // INTS
}

bool handleFileRead(String path) {  // send the right file to the client (if it exists)

  //NOINTS
  if (SPIFFS.exists(path + ".html"))
    path += ".html";
  else if (path == "/config") {
    path = "/karyaconfig.html";  // If a folder is requested, send the index file
    if (!SPIFFS.exists(path)) {
      server.send(200, "text/html", web_config);
      return true;
    }
  } else if (path == "/karyacnc.7z" || path == "/karyacnc.zip") {

#ifdef karyacnc_zip_len
    server.sendHeader("Content-Disposition", "attachment; filename=karyacnc.7z");
    server.send(200, "application/x-zip", karyacnc_zip, karyacnc_zip_len);
    return true;
#endif
  } else if (path == "/config.ini") {
    if (!SPIFFS.exists(path)) {
      server.send(200, "text/plain", web_configini);
      return true;
    }
  } else if (path == "/--gcodex.js") {
    if (!SPIFFS.exists(path)) {
      server.send(200, "application/javascript", web_gcodex);
      return true;
    }
  } else if (path == "/websocket.js") {
    if (!SPIFFS.exists(path)) {
      server.send(200, "application/javascript", web_websocket);
      return true;
    }
  } else if (path.endsWith("/cnc")) {
    path = "/cnc.html";  // If a folder is requested, send the index file
    if (!SPIFFS.exists(path)) {
      server.send(200, "text/html", web_cnc);
      return true;
    }
  }

  else if (path.endsWith("/")) {
    path = "/jobs.html";  // If a folder is requested, send the index file
    if (!SPIFFS.exists(path)) {
      server.send(200, "text/html", web_index);
      return true;
    }
  }


  //xprintf(PSTR("handleFileRead: %s\n"), path.c_str());
  String contentType = getContentType(path);  // Get the MIME type
  String pathWithGz = path + ".gz";
  bool gz = SPIFFS.exists(pathWithGz);
  if (gz || SPIFFS.exists(path)) {                         // If the file exists, either as a compressed archive, or normal
    File file = SPIFFS.open(gz ? pathWithGz : path, "r");  // Open the file
    size_t sent = server.streamFile(file, contentType);    // Send it to the client
    file.close();                                          // Close the file again
    //xprintf(PSTR("\tSent file: %s\n"), path.c_str());
    return true;
  }
  //else
  //xprintf(PSTR("\tFile Not Found: %s\n"), path.c_str()); // If the file doesn't exist, return false

  //INTS
  return false;
}

String getContentType(String filename) {  // convert the file extension to the MIME type
  if (filename.endsWith(".html"))
    return "text/html";
  else if (filename.endsWith(".css"))
    return "text/css";
  else if (filename.endsWith(".js"))
    return "application/javascript";
  else if (filename.endsWith(".ico"))
    return "image/x-icon";
  else if (filename.endsWith(".gz"))
    return "application/x-gzip";
  return "text/plain";
}

void handleFileUpload() {  // upload a new file to the SPIFFS
  // NOINTS
  if (uncompress) {
    server.send(500, "text/plain", "Still PRINTING");
  } else {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      String filename = upload.filename;
      if (filename == "")
        filename = "/gcode.gcode";
      if (!filename.startsWith("/"))
        filename = "/" + filename;
      // always rename any config to config.ini, except custom.ini
      isconfig = filename.endsWith(".ini");
      isfirmware = filename.endsWith(".bin");
      if (isconfig && !filename.startsWith("/custom")) filename = "/config.ini";
      if (isfirmware) filename = "/firmware.bin";
      // xprintf(PSTR("handleFileUpload Name: %s\n"), filename.c_str());
      Serial.println("handleFileUpload Name: " + String(filename));
      fsUploadFile = SPIFFS.open(filename, "w");  // Open the file for writing in SPIFFS (create if it doesn't exist)
      filename = String();
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      // do temploop to avoid overheating
      // temp_loop(micros());
      if (fsUploadFile)
        fsUploadFile.write(upload.buf, upload.currentSize);  // Write the received bytes to the file
    } else if (upload.status == UPLOAD_FILE_END) {
      if (fsUploadFile) {      // If the file was successfully created
        fsUploadFile.close();  // Close the file again
        //xprintf(PSTR("handleFileUpload Size: %d\n"), upload.totalSize);
        server.sendHeader("Location", "/upload");  // Redirect the client to the success page
        server.send(303);
        // if (isconfig)readconfigs();
      } else {
        server.send(500, "text/plain", "500: couldn't create file");
      }
    }
  }
  // INTS
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t lenght) {  // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:  // if the websocket is disconnected
      // xprintf(PSTR("[%d] Disconnected!\n"), fi(num));
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {  // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        // xprintf(PSTR("[%d] Connected from %d.%d.%d.%d url: %s\n"), fi(num), fi(ip[0]), fi(ip[1]), fi(ip[2]), fi(ip[3]), payload);

        // Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // on connect, send the scale
        // zprintf(PSTR("EPR:3 185 %f Lscale\n"), ff(Lscale));
      }
      break;
    case WStype_TEXT:  // if new text data is received

      // Serial.printf("[%u] get Text: %s\n", num, payload);

      //xprintf(PSTR("%s"),payload);

      //webSocket.sendTXT(num, payload);
      // if runnning job, ignore command from all channel

      // if (!uncompress) {
      for (int i = 0; i < lenght; i++) {
        buf_push(wf, payload[i]);
      }
      // }

      //webSocket.broadcastTXT(payload);
      break;
  }
}

char gcode_loop() {

#ifndef ISPC


  char c = 0;
  if (waitexecute) {
    if (tryexecute()) {
      ack_waiting = 1;
      if (ack_waiting) {
        //zprintf(PSTR("ok\n"));
        ack_waiting = 0;
      }

#ifdef timingG
      zprintf(PSTR("Gcode:%dus\n"), fi(micros() - gt));
#endif
    }

  } else {
    if (ack_waiting) {
      //zprintf(PSTR("ok\n"));
      ack_waiting = 0;
      n = 1;
    }
    // wifi are first class
#ifdef WIFISERVER
    if (buf_canread(wf)) {
      buf_pop(wf, c);
    } else
#endif
    {
      if (serialav()) {
        if (n) {
          gt = micros();
          n = 0;
        }
        serialrd(c);
      }
    }

    if (c) {
      if (c == '\n') {
        lineprocess++;
      }

      gcode_parse_char(c);
    }
    //motionloop();
  }
#else
#endif
  return c;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SPIFFS.begin(true);
  setupwifi(0);
  initmotion();
  init_gcode();
  // init_temp();
  // reload_eeprom();
  timer_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  webSocket.loop();
  char c = 0;
  c = gcode_loop();
  motionloop();
  // if (millis() - lastTime >= 1000) {
  //   Serial.println(c);
  //   lastTime = millis();
  // }
}
