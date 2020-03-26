#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
const char* ssid = "";
const char* password = "";

LiquidCrystal_I2C lcd(0x3F, 16, 2);

//certificacion https
const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIEsTCCA5mgAwIBAgIQBOHnpNxc8vNtwCtCuF0VnzANBgkqhkiG9w0BAQsFADBs\n" \
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n" \
"d3cuZGlnaWNlcnQuY29tMSswKQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5j\n" \
"ZSBFViBSb290IENBMB4XDTEzMTAyMjEyMDAwMFoXDTI4MTAyMjEyMDAwMFowcDEL\n" \
"MAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZMBcGA1UECxMQd3d3\n" \
"LmRpZ2ljZXJ0LmNvbTEvMC0GA1UEAxMmRGlnaUNlcnQgU0hBMiBIaWdoIEFzc3Vy\n" \
"YW5jZSBTZXJ2ZXIgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC2\n" \
"4C/CJAbIbQRf1+8KZAayfSImZRauQkCbztyfn3YHPsMwVYcZuU+UDlqUH1VWtMIC\n" \
"Kq/QmO4LQNfE0DtyyBSe75CxEamu0si4QzrZCwvV1ZX1QK/IHe1NnF9Xt4ZQaJn1\n" \
"itrSxwUfqJfJ3KSxgoQtxq2lnMcZgqaFD15EWCo3j/018QsIJzJa9buLnqS9UdAn\n" \
"4t07QjOjBSjEuyjMmqwrIw14xnvmXnG3Sj4I+4G3FhahnSMSTeXXkgisdaScus0X\n" \
"sh5ENWV/UyU50RwKmmMbGZJ0aAo3wsJSSMs5WqK24V3B3aAguCGikyZvFEohQcft\n" \
"bZvySC/zA/WiaJJTL17jAgMBAAGjggFJMIIBRTASBgNVHRMBAf8ECDAGAQH/AgEA\n" \
"MA4GA1UdDwEB/wQEAwIBhjAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIw\n" \
"NAYIKwYBBQUHAQEEKDAmMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2Vy\n" \
"dC5jb20wSwYDVR0fBEQwQjBAoD6gPIY6aHR0cDovL2NybDQuZGlnaWNlcnQuY29t\n" \
"L0RpZ2lDZXJ0SGlnaEFzc3VyYW5jZUVWUm9vdENBLmNybDA9BgNVHSAENjA0MDIG\n" \
"BFUdIAAwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29tL0NQ\n" \
"UzAdBgNVHQ4EFgQUUWj/kK8CB3U8zNllZGKiErhZcjswHwYDVR0jBBgwFoAUsT7D\n" \
"aQP4v0cB1JgmGggC72NkK8MwDQYJKoZIhvcNAQELBQADggEBABiKlYkD5m3fXPwd\n" \
"aOpKj4PWUS+Na0QWnqxj9dJubISZi6qBcYRb7TROsLd5kinMLYBq8I4g4Xmk/gNH\n" \
"E+r1hspZcX30BJZr01lYPf7TMSVcGDiEo+afgv2MW5gxTs14nhr9hctJqvIni5ly\n" \
"/D6q1UEL2tU2ob8cbkdJf17ZSHwD2f2LSaCYJkJA69aSEaRkCldUxPUd1gJea6zu\n" \
"xICaEnL6VpPX/78whQYwvwt/Tv9XBZ0k7YXDK/umdaisLRbvfXknsuvCnQsH6qqF\n" \
"0wGjIChBWUMo0oHjqvbsezt3tkBigAVBRQHvFwY+3sAzm2fTYS5yh+Rp/BIAV0Ae\n" \
"cPUeybQ=\n" \
"-----END CERTIFICATE-----\n";

 byte chica[8] = { B00100, B01110, B11111, B00100, B01111, B00100, B01010, B10001 };
byte  chico[8] = { B01110, B01110, B01110, B00100, B11111, B00100, B01010, B01010 };



void setup() {
   // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
   Serial.begin(115200);
  lcd.print("HOLA MUNDO");
  delay(1000);
 lcd.clear();
 lcd.createChar(1,chica);
 lcd.createChar(2,chico);
 lcd.clear();
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");

}

String dato="";
void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin("https://coronavirus-tracker-api.herokuapp.com/v2/locations?country_code=AR", root_ca); //Specify the URL and certificate
    int httpCode = http.GET();                                                  //Make the request
 
    if (httpCode > 0) { //Check for the returning code
    
        String payload = http.getString();
      dato=payload;
      //  Serial.println(httpCode);
     //  Serial.println(payload);
    
      
       
    
      
      }
 
    else {
      //Serial.println("Error on HTTP request");
      lcd.setCursor(0, 0);
      lcd.print("ERROR TIMEOUT REQUEST");
      lcd.clear();
      delay(2000);
      dato="";
    }
   
       
    http.end(); //Free the resources
  }
 
       
      
  delay(8000);
  //posicion de los datos infectados
  int confirm = dato.indexOf("confirmed");
  int posConfirm= confirm + 11;
  int finPos = dato.indexOf(',');
  
  //posicion de los datos muertos
  int death = dato.indexOf("deaths"); 
  int posDeath= death + 8;
  int finDeath = dato.indexOf (',', finPos + 1);
  
  //posicion de los datos Año
  int dates = dato.indexOf("last_updated");
  int posDates= dates + 15;
  int finDates = dato.indexOf('T');
 
 //posicion de los datos hora
  int tim = dato.indexOf('T');
  int posTim= tim + 1 ;
  int finTim= dato.indexOf('Z'); ;  
      
       lcd.setCursor(0, 0);
       lcd.print("CORONAVIRUS-ARG");
       lcd.setCursor(0, 1); 
       lcd.print("INF:");
       lcd.setCursor(4, 1);
       lcd.print(dato.substring(posConfirm,finPos));
       lcd.setCursor(8, 1);
       lcd.print("DEATH:");
       lcd.setCursor(14, 1);
       lcd.print(dato.substring(posDeath,finDeath));
       delay(4000);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("DATE:");
       lcd.setCursor(5, 0);
       lcd.print(dato.substring(posDates,finDates));
       lcd.setCursor(0, 1);
       lcd.print("HOUR:");
       lcd.print(dato.substring(posTim,finTim)); 
       delay(4000);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("DIVORCIOS:");
       lcd.setCursor(11, 0);
       lcd.print("0");
       delay(2500);
       lcd.clear();
       lcd.setCursor(7,1);
       lcd.write(byte(1));
       for(int i = 7; i< 17; i++)
        {
        lcd.setCursor(i,1); 
        lcd.write(byte(2));
        delay(500);
        lcd.setCursor(6,1); 
        lcd.write(byte(1));
        delay(500);
        lcd.clear();
        } 
      
       delay(3000);
       //limpio lcd
       lcd.clear();
       //limpio variable
       dato="";
}
