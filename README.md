# ESP8266_sparkfun_wrapper
Simple ESP8266 wrapper for sending data to data.sparkfun.com

**Requires ESP8266Wifi lib** (included in ESP8266 SDK, www.esp8266.com)

Send commands via serial:

- Conenct to wifi access point: ```connect <ssid>:<password>```

- Set data.sparkfun.com private key: ```privatekey <key>```

- Set data.sparkfun.com public key: ```publickey <key>```

- Data to be send to data.sparkfun.com: ```data "key1":"value1","key2":"value2",...```

ESP8266 GPIO2 is used as indication to master. When pin is HIGH the ESP8266 is ready for new command. When pin is LOW previous command is not finnished and master should wait.

Have fun ;)
