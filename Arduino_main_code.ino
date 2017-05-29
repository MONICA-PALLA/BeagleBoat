#include <SoftwareSerial.h>
#include <TinyGPS.h>
//////////////////////////////////
#include<dht.h> 
dht DHT;
#define DHT11_PIN 3
//////////////////////////////////
// Define which pins you will use on the Arduino to communicate with your 
// GPS. In this case, the GPS module's TX pin will connect to the 
// Arduino's RXPIN which is pin 3.
#define RXPIN 2
#define TXPIN 3
//Set this value equal to the baud rate of your GPS
#define GPSBAUD 4800

// Create an instance of the TinyGPS object
TinyGPS gps;
// Initialize the NewSoftSerial library to the pins you defined above
SoftwareSerial uart_gps(RXPIN, TXPIN);

// This is where you declare prototypes for the functions that will be 
// using the TinyGPS library.
void getgps(TinyGPS &gps);

// In the setup function, you need to initialize two serial ports; the 
// standard hardware serial port (Serial()) to communicate with your 
// terminal program an another serial port (NewSoftSerial()) for your 
// GPS.
void setup()
{
  // This is the serial rate for your terminal program. It must be this 
  // fast because we need to print everything before a new sentence 
  // comes in. If you slow it down, the messages might not be valid and 
  // you will likely get checksum errors.
  Serial.begin(115200);
  //Sets baud rate of your GPS
  uart_gps.begin(GPSBAUD);
  
  //Serial.println("");
  //Serial.println("GPS Shield QuickStart Example Sketch v12");
  Serial.print(";");
  //Serial.println("");
}

// This is the main loop of the code. All it does is check for data on 
// the RX pin of the ardiuno, makes sure the data is valid NMEA sentences, 
// then jumps to the getgps() function.
void loop()
{
 int chk = DHT.read11(DHT11_PIN);
 //Serial.println(" Hu ; " );
 //Serial.println(DHT.humidity, 1);
 //Serial.println(" Te ; ");
 //Serial.println(DHT.temperature, 1);
 //delay(2000); 
 
  while(uart_gps.available())     // While there is data on the RX pin...
  {
      int c = uart_gps.read();    // load the data into a variable...
      if(gps.encode(c))      // if there is a new valid sentence...
      {
        getgps(gps);         // then grab the data.
        delay(100);
        Serial.print("Hu;" );
        Serial.print(DHT.humidity, 1);
        Serial.print(";");
        Serial.print("Te;");
        Serial.print(DHT.temperature, 1);
        Serial.print(";");
      }
  }
  //while(!uart_gps.available())
    //  {
      //  Serial.print("LT;");
        //Serial.print("NA"); 
  //Serial.print(",");
       /* Serial.print(";");
         Serial.print("LN;"); 
         Serial.print("NA");
         Serial.print(";");
         Serial.print("Da;");
         Serial.print("NA");
         Serial.print(";");
         Serial.print("Time;");
         Serial.print("NA");
         Serial.print(";");
        //Serial.print("Data Invalid;");  
        Serial.print("Hu;" );
        Serial.print(DHT.humidity, 1);
        Serial.print(";");
        Serial.print("Te;");
        Serial.print(DHT.temperature, 1);
        Serial.print(";");        
   
      }*/
}

// The getgps function will get and print the values we want.
void getgps(TinyGPS &gps)
{
  // To get all of the data into varialbes that you can use in your code, 
  // all you need to do is define variables and query the object for the 
  // data. To see the complete list of functions see keywords.txt file in 
  // the TinyGPS and NewSoftSerial libs.
  
  // Define the variables that will be used
  float LT, LN;
  // Then call this function
  gps.f_get_position(&LT, &LN);
  // You can now print variables latitude and longitude
  //Serial.print("Lat/Long; "); 
  Serial.print("LT;");
  Serial.print(LT,5);
  Serial.print(";"); 
  //Serial.print(",");
  Serial.print("LN;"); 
  Serial.print(LN,5);
  Serial.print(";");
  
  // Same goes for date and time
  int year;
  byte month, day, hour, minute, second, hundredths;
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  // Print data and time
  Serial.print("Dt;"); 
  Serial.print("5"); 
  Serial.print("/"); 
  Serial.print("26"); 
  Serial.print("/"); 
  Serial.print("2017");
  Serial.print(";");
  Serial.print("Time;"); 
  Serial.print(hour+6, DEC); 
  Serial.print(":"); 
  Serial.print(minute, DEC); 
  Serial.print(":"); 
  Serial.print(second, DEC); 
  Serial.print(";");
  //Serial.print("."); 
  //Serial.println(hundredths, DEC);
  //Since month, day, hour, minute, second, and hundr
  
  // Here you can print the altitude and course values directly since 
  // there is only one value for the function
  //Serial.print("Altitude (meters); "); 
  //Serial.println(gps.f_altitude());  
  // Same goes for course
  //Serial.print("Course (degrees); "); 
  //Serial.println(gps.f_course()); 
  // And same goes for speed
  //Serial.print("Speed(kmph); "); Serial.println(gps.f_speed_kmph());
  //Serial.println();
  
  // Here you can print statistics on the sentences.
  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
  //Serial.print("Failed Checksums: ");Serial.print(failed_checksum);
  //Serial.println(); Serial.println();
}
