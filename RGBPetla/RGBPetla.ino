/*
 Name:		RGBPetla.ino
 Created:	11/6/2021 3:45:36 PM
 Author:	kryst
*/

#define NIEBIESKI 3
#define ZIELONY 5
#define CZERWONY 6
#define petla 10
#define przerwa 1000
int czerwonyWartosc, zielonyWartosc, niebieskiWartosc;

void setup()
{
    pinMode(CZERWONY, OUTPUT);
    pinMode(ZIELONY, OUTPUT);
    pinMode(NIEBIESKI, OUTPUT);
    digitalWrite(CZERWONY, HIGH);
    digitalWrite(ZIELONY, LOW);
    digitalWrite(NIEBIESKI, LOW);
    Serial.begin(9600);
    czerwonyWartosc = 0;
}

void loop()
{
    // CZERWONY
    zielonyWartosc = 0;
    niebieskiWartosc = 0;
    for (int i = 0; i < 255; i++)
    {
        if (czerwonyWartosc == 255)
            break;
        else {
            czerwonyWartosc += 1;
            analogWrite(CZERWONY, czerwonyWartosc);
            delay(petla);
        }
    }
    delay(przerwa);

    // FIOLET
    czerwonyWartosc = 255;
    zielonyWartosc = 0;
    niebieskiWartosc = 0;
    for (int i = 0; i < 255; i++)
    {
        niebieskiWartosc += 1;
        analogWrite(NIEBIESKI, niebieskiWartosc);
        delay(petla);
    }
    delay(przerwa);

    // NIEBIESKI
    czerwonyWartosc = 255;
    zielonyWartosc = 0;
    niebieskiWartosc = 255;
    for (int i = 0; i < 255; i++)
    {
        czerwonyWartosc -= 1;
        analogWrite(CZERWONY, czerwonyWartosc);
        delay(petla);
    }
    delay(przerwa);

    // NIEBIESKO - ZIELONY
    czerwonyWartosc = 0;
    zielonyWartosc = 0;
    niebieskiWartosc = 255;
    for (int i = 0; i < 255; i++)
    {
        zielonyWartosc += 1;
        analogWrite(ZIELONY, zielonyWartosc);
        delay(petla);
    }
    delay(przerwa);

    // ZIELONY
    czerwonyWartosc = 0;
    zielonyWartosc = 255;
    niebieskiWartosc = 255;
    for (int i = 0; i < 255; i++)
    {
        niebieskiWartosc -= 1;
        analogWrite(NIEBIESKI, niebieskiWartosc);
        delay(petla);
    }
    delay(przerwa);

    // ZOLTY
    czerwonyWartosc = 0;
    zielonyWartosc = 255;
    niebieskiWartosc = 0;
    for (int i = 0; i < 255; i++)
    {
        czerwonyWartosc += 1;
        analogWrite(CZERWONY, czerwonyWartosc);
        delay(petla);
    }
    delay(przerwa);

    // CZERWONY
    czerwonyWartosc = 255;
    zielonyWartosc = 255;
    niebieskiWartosc = 0;
    for (int i = 0; i < 255; i++)
    {
        zielonyWartosc -= 1;
        analogWrite(ZIELONY, zielonyWartosc);
        delay(petla);
    }
    delay(przerwa);
}