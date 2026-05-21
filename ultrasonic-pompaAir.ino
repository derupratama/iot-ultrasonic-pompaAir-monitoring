#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Ultrasonic Pump"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NamaWiFi";
char pass[] = "PasswordWiFi";

#define TRIG_PIN D5
#define ECHO_PIN D6
#define PUMP_PIN D1

long duration;
int distance;

void setup()
{
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PUMP_PIN, OUTPUT);

    digitalWrite(PUMP_PIN, LOW);

    Blynk.begin(auth, ssid, pass);
}

void loop()
{
    Blynk.run();

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    Blynk.virtualWrite(V0, distance);

    if(distance < 10)
    {
        digitalWrite(PUMP_PIN, HIGH);

        Blynk.virtualWrite(V1, 1);

        Serial.println("Pompa Menyala");
    }
    else
    {
        digitalWrite(PUMP_PIN, LOW);

        Blynk.virtualWrite(V1, 0);

        Serial.println("Pompa Mati");
    }

    delay(1000);
}
