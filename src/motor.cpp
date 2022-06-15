//Motor


//forward


if(duty>0)
for(i=0; i<=duty;i++)
    {
        digitalWrite(Pin1; HIGH); //Pin on
        delay(1);
    }
    for(i=0; i<=(tau-duty);i++)
    {
        digitalWrite(Pin1; LOW); //Pin off
        delay(1);
    }
digitalWrite(Pin2; LOW);