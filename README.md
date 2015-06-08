# ESP8266_sparkfun_wrapper
Simple ESP8266 wrapper for sending data to data.sparkfun.com

**Requires ESP8266Wifi lib** (included in ESP8266 SDK, www.esp8266.com)

Send commands via serial:

- Conenct to wifi access point: ```connect <ssid>:<password>```

- Set data.sparkfun.com private key: ```privatekey <key>```

- Set data.sparkfun.com public key: ```publickey <key>```

- Data to be send to data.sparkfun.com: ```data "key1":"value1","key2":"value2",...```

Have fun ;)
