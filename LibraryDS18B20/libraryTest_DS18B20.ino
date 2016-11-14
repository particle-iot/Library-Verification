// This #include statement was automatically added by the Particle IDE.
#include "DS18B20/DS18B20.h"

#define NONE_KEY    0
#define SHORT_KEY   1
#define LONG_KEY    2

#define UPDATE_INTERVAL 1000     //



DS18B20 ds18b20 = DS18B20(D4);

// EXAMPLE USAGE
void button_handler(system_event_t event, int duration, void* )
{
    if(!duration)
    { // just pressed
        RGB.control(true);
        RGB.color(255, 0, 255); // MAGENTA
    }
    else
    { // just released
        RGB.control(false);
    }
}


uint8_t buttonProcess(void)
{
    static uint8_t keyStatus=0;
    uint8_t button=0;
    switch(keyStatus)
    {
        case 0:     //detect a button press action
                if(System.buttonPushed()>1)
                    keyStatus=1;
                else
                    keyStatus=0;
                button=NONE_KEY;
                break;
        case 1:     //debounce,make sure it's valid press
                if(System.buttonPushed()>10)
                    keyStatus=2;
                else
                    keyStatus=0;
                button=NONE_KEY;
                break;
        case 2:
                if(System.buttonPushed()>20)
                {
                    keyStatus=3;
                    button=SHORT_KEY;
                }
                else
                {
                    keyStatus=0;
                    button=NONE_KEY;
                }
                break;
        case 3:
                if(System.buttonPushed()>=1500)
                {
                    keyStatus=4;
                    button=LONG_KEY;
                }
                else
                {
                    keyStatus=0;    //go back to the inital stage
                }
                break;
        case 4:
                if(System.buttonPushed()>=1600) //didnot release the button yet
                {
                    keyStatus=4;
                    button=NONE_KEY;
                }
                break;
        default:break;
    }
    return button;
}
void setup()
{
    System.on(button_status, button_handler);
    Serial.begin(9600);
}


static uint8_t testStep=0;
static uint8_t lastTestStep=0;
unsigned long updateTime=0;
uint8_t sensorDetect=0;
double temperature=0;
uint8_t retryTime=0;

void loop()
{

    if(buttonProcess()==SHORT_KEY)      //increase the test step when press the button
        testStep++;
    else
    if(buttonProcess()==LONG_KEY)       //goback to the initial test step once
        testStep=0;

    if(testStep!=lastTestStep)
    {
        lastTestStep=testStep;
        switch(testStep)
        {
            case 0:
                Serial.println("Plesae press the SETUP button to start the library test!");
                break;
            case 1:
                Serial.println("step 1: Verify the chip verion");//Support DS18B20,DS18S20.DS1822
                break;
            case 2:
                Serial.println("step 2: Verify the temperature value. Make sure the vaule is the same as ambient temperature");
                break;
            case 3:
                Serial.println("step 3: Veify the temperature value when sensor is close to a heat source.Make sure the value is bigger than last step!");
                break;
            case 4:
                Serial.println("step 4: Verify the temperature value when sensor is close to a cool source. Make sure tha value is smaller than step2!");
                break;
            case 5:
                Serial.println("step 5: Verify the temperature value when sensor is powered by DataPin. Make sure VCC pin is connected with GND pin");
                break;
            case 6:
                Serial.println("go back to stage 1");
                testStep=1;
                break;
            default:
                break;
        }
        delay(1000);    //make a delay here so that
    }
    if((millis()-updateTime)>UPDATE_INTERVAL)
    {
        updateTime=millis();
        switch(testStep)
        {
            case 1:
                if(ds18b20.search())
                {
                    Serial.printf("This chip type is: %x\r\n",ds18b20.getChipType());
                    Serial.printf("This sensor name is: %s\r\n",ds18b20.getChipName());
                    ds18b20.resetsearch();          //why need this sentence for re-search the sensor????????
                    sensorDetect=1;     //a sensor had been detected.
                }
                else
                {
                    Serial.println("Cannot find a temperature sensor online");
                    sensorDetect=0;
                }
                break;
            case 2:
                if(sensorDetect==1)
                {
                    temperature = ds18b20.getTemperature();
                    if(!ds18b20.crcCheck()&&(retryTime<4))
                    {
                        Serial.printf("Get a bad value.Retry %d times\r\n",retryTime+1);
                        retryTime++;
                        if(retryTime==4)
                        {
                            testStep=1;    //go back to the last step
                            Serial.println("No temperature sensor is online now! Will go back to stage1 to find out the sensor");
                        }
                    }
                    else
                    {
                        retryTime=0;
                        Serial.print("Current temperature is:");
                        Serial.print(temperature);
                        Serial.println(" celcuis");
                    }
                }
                break;
            case 3:
                if(sensorDetect==1)
                {
                    temperature = ds18b20.getTemperature();
                    if(!ds18b20.crcCheck()&&(retryTime<4))
                    {
                        Serial.printf("Get a bad value.Retry %d times\r\n",retryTime+1);
                        retryTime++;
                        if(retryTime==4)
                        {
                            testStep=1;    //go back to the last step
                            Serial.println("No temperature sensor is online now! Will go back to stage1 to find out the sensor");
                        }
                    }
                    else
                    {
                        retryTime=0;
                        Serial.print("Current temperature is:");
                        Serial.print(temperature);
                        Serial.println(" celcuis");
                        Serial.println("Which should be HIGHER than last step's");
                    }
                }
                break;
            case 4:
                if(sensorDetect==1)
                {
                    temperature = ds18b20.getTemperature();
                    if(!ds18b20.crcCheck()&&(retryTime<4))
                    {
                        Serial.printf("Get a bad value.Retry %d times\r\n",retryTime+1);
                        retryTime++;
                        if(retryTime==4)
                        {
                            testStep=1;    //go back to the last step
                            Serial.println("No temperature sensor is online now! Will go back to stage1 to find out the sensor");
                        }
                    }
                    else
                    {
                        retryTime=0;
                        Serial.print("Current temperature is:");
                        Serial.print(temperature);
                        Serial.println(" celcuis");
                        Serial.println("Which should be LOWER than last step's");
                    }
                }
                break;
            case 5:
                if(sensorDetect==1)
                {
                    temperature = ds18b20.getTemperature();
                    if(!ds18b20.crcCheck()&&(retryTime<4))
                    {
                        Serial.printf("Get a bad value.Retry %d times\r\n",retryTime+1);
                        retryTime++;
                        if(retryTime==4)
                        {
                            testStep=1;    //go back to the last step
                            Serial.println("No temperature sensor is online now! Will go back to stage1 to find out the sensor");
                        }
                    }
                    else
                    {
                        retryTime=0;
                        Serial.print("Current temperature is:");
                        Serial.print(temperature);
                        Serial.println(" celcuis");
                        Serial.println("Which should be the same as when in the same environment");
                        if(ds18b20.readPowerSupply())
                            Serial.println("The sensor works in parasite power mode now");
                        else
                            Serial.println("The sensor isn't work in parasite powerw mode,please check the wire connection");
                    }
                }
                break;
            default:
                break;
        }
    }
}
