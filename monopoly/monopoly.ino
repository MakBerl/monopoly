#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
LiquidCrystal_I2C lcd(0x27,16,2);
char key;
char keys[4][4] = 
{
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};
byte rowPins[] = {8, 7, 6, 5};                                           
byte colPins[] = {4, 3, 2, 1};                                           
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4 );      
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
struct player                                                           
{
    unsigned long uid=0;
    long int balance=0;
};
unsigned long uidDec, uidDecTemp;
player CardUIDeEPROMread[8];     
int index = 0;
int mode=0;
bool forcleaning=true;
bool forcancel=false;
long int moneyforcircle=0;
byte StrelkaDown0[8] = 
{
    0b11111,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110
};
byte StrelkaDown1[8] = 
{
    0b11111,0b01111,0b01111,0b01111,0b01111,0b01111,0b01111,0b01111
};
byte StrelkaDown2[8] = 
{
    0b11110,0b11110,0b10000,0b10000,0b11000,0b11100,0b11110,0b11111
};
byte StrelkaDown3[8] = 
{
    0b01111,0b01111,0b00001,0b00001,0b00011,0b00111,0b01111,0b11111
};
byte StrelkaUp0[8] = 
{
    0b11111,0b11110,0b11100,0b11000,0b10000,0b10000,0b11110,0b11110
};
byte StrelkaUp1[8] = 
{
    0b11111,0b01111,0b00111,0b00011,0b00001,0b00001,0b01111,0b01111
};
byte StrelkaUp2[8] = 
{
    0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11111
};
byte StrelkaUp3[8] = 
{
    0b01111,0b01111,0b01111,0b01111,0b01111,0b01111,0b01111,0b11111
};
byte Circle0[8] = 
{
    0b11111,0b11111,0b11111,0b11110,0b11100,0b11001,0b11001,0b11001
};
byte Circle1_6[8] = 
{
    0b11111,0b11111,0b11111,0b00000,0b00000,0b11111,0b11111,0b11111
};
byte Circle2[8] = 
{
    0b11111,0b11011,0b11001,0b00000,0b00000,0b11001,0b11011,0b11111
};
byte Circle3[8] = 
{
    0b11111,0b11111,0b11111,0b01111,0b00111,0b10011,0b10011,0b10011
};
byte Circle4[8] = 
{
    0b11001,0b11001,0b11001,0b11100,0b11110,0b11111,0b11111,0b11111
};
byte Circle5[8] = 
{
    0b11111,0b11011,0b10011,0b00000,0b00000,0b10011,0b11011,0b11111
};
byte Circle7[8] = 
{
    0b10011,0b10011,0b10011,0b00111,0b01111,0b11111,0b11111,0b11111
};
byte NFC0[8] = 
{
    0b00000,0b00001,0b00011,0b00100,0b01000,0b01000,0b10000,0b10000
};
byte NFC1[8] = 
{
    0b01111,0b10000,0b00000,0b00000,0b00000,0b00010,0b00001,0b01001
};
byte NFC2[8] = 
{
    0b11110,0b00001,0b00100,0b00010,0b10001,0b01001,0b01001,0b01001
};
byte NFC3[8] = 
{
    0b00000,0b10000,0b11000,0b00100,0b00010,0b00010,0b00001,0b00001
};
byte NFC4[8] = 
{
    0b10000,0b10000,0b01000,0b01000,0b00100,0b00011,0b00001,0b00000
};
byte NFC5[8] = 
{
    0b01001,0b00001,0b00010,0b00000,0b00000,0b00000,0b10000,0b01111
};
byte NFC6[8] = 
{
    0b01001,0b01001,0b01001,0b10001,0b00010,0b00100,0b00001,0b11110
};
byte NFC7[8] = 
{
    0b00001,0b00001,0b00010,0b00010,0b00100,0b11000,0b10000,0b00000
};
byte Galka0[8] = 
{
  0b11111,0b11111,0b11111,0b11111,0b11111,0b11110,0b11100,0b11000
};
byte Galka1[8] = 
{
  0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b01110
};
byte Galka2[8] = 
{
  0b11111,0b11110,0b11100,0b11000,0b10000,0b00000,0b00000,0b00000
};
byte Galka3[8] = 
{
  0b11111,0b01111,0b00111,0b00011,0b00111,0b01111,0b11111,0b11111
};
byte Galka4[8] = 
{
  0b11000,0b11100,0b11110,0b11111,0b11111,0b11111,0b11111,0b11111
};
byte Galka5[8] = 
{
    0b00000,0b00000,0b00000,0b00000,0b00000,0b10001,0b11011,0b11111
};
byte Galka6[8] = 
{
  0b00011,0b00111,0b01111,0b11111,0b11111,0b11111,0b11111,0b11111
};
byte full[8] = 
{
  0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111
};
void setup()
{
    lcd.init();        
    lcd.backlight();
    SPI.begin();
    mfrc522.PCD_Init();
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("PLAYERS");
    lcd.setCursor(0,1);
    lcd.print(": | | | | | | | ");
}
bool SearchSame(unsigned long ID)
{
    for (index = 0; index<8; index++)
    {
        if(CardUIDeEPROMread[index].uid==ID)
            return true;
    }
    return false;
}
void Setter(int i)
{
    switch(i)
    {
        case 0:
        {
            lcd.setCursor(1,1);
            break;
        }
        case 1:
        {
            lcd.setCursor(3,1);
            break;
        }
        case 2:
        {
            lcd.setCursor(5,1);
            break;
        }
        case 3:
        {
            lcd.setCursor(7,1);
            break;
        }
        case 4:
        {
            lcd.setCursor(9,1);
            break;
        }
        case 5:
        {
            lcd.setCursor(11,1);
            break;
        }
        case 6:
        {
            lcd.setCursor(13,1);
            break;
        }
        case 7:
        {
            lcd.setCursor(15,1);
            break;
        }
    }
}
void OchistkaDlyaSimvola()
{
    for (int p=12;p<16;p++)
    {
        lcd.setCursor(p,0);
        lcd.print(" ");
        lcd.setCursor(p,1);
        lcd.print(" ");
    }
}
void PrintSymbols(int ind)
{
    switch(ind)
    {
        case 0:
        {
            lcd.createChar(0,StrelkaUp0);
            lcd.createChar(1,StrelkaUp2);
            lcd.createChar(2,StrelkaUp1);
            lcd.createChar(3,StrelkaUp3);
            lcd.createChar(4,StrelkaDown0);
            lcd.createChar(5,StrelkaDown2);
            lcd.createChar(6,StrelkaDown1);
            lcd.createChar(7,StrelkaDown3);
            break;
        }
        case 1:
        {
            lcd.createChar(0,full);
            lcd.createChar(1,full);
            lcd.createChar(2,StrelkaDown0);
            lcd.createChar(3,StrelkaDown2);
            lcd.createChar(4,StrelkaDown1);
            lcd.createChar(5,StrelkaDown3);
            lcd.createChar(6,full);
            lcd.createChar(7,full);
            break;
        }
        case 2:
        {
            lcd.createChar(0,full);
            lcd.createChar(1,full);
            lcd.createChar(2,StrelkaUp0);
            lcd.createChar(3,StrelkaUp2);
            lcd.createChar(4,StrelkaUp1);
            lcd.createChar(5,StrelkaUp3);
            lcd.createChar(6,full);
            lcd.createChar(7,full);
            break;
        }
        case 3:
        {
            lcd.createChar(0,Circle0);
            lcd.createChar(1,Circle4);
            lcd.createChar(2,Circle1_6);
            lcd.createChar(3,Circle5);
            lcd.createChar(5,Circle1_6);
            lcd.createChar(6,Circle3);
            lcd.createChar(7,Circle7);
            break;
        }
        case 4:
        {
            lcd.createChar(0,Galka0);
            lcd.createChar(1,Galka4);
            lcd.createChar(2,Galka1);
            lcd.createChar(3,Galka5);
            lcd.createChar(4,Galka2);
            lcd.createChar(5,Galka6);
            lcd.createChar(6,Galka3);
            lcd.createChar(7,full);
            break;
        }
        case 5:
        {
            lcd.createChar(0,NFC0);
            lcd.createChar(1,NFC4);
            lcd.createChar(2,NFC1);
            lcd.createChar(3,NFC5);
            lcd.createChar(4,NFC2);
            lcd.createChar(5,NFC6);
            lcd.createChar(6,NFC3);
            lcd.createChar(7,NFC7);
            break;
        }
    }
        lcd.setCursor(12,0);
        lcd.print('\0');
        lcd.setCursor(12,1);
        lcd.print('\1');
        lcd.setCursor(13,0);
        lcd.print('\2');
        lcd.setCursor(13,1);
        lcd.print('\3');
        lcd.setCursor(14,0);
        lcd.print('\4');
        lcd.setCursor(14,1);
        lcd.print('\5');
        lcd.setCursor(15,0);
        lcd.print('\6');
        lcd.setCursor(15,1);
        lcd.print('\7');
}
void UptForEnter()
{
    for (int g=0; g < 12; g++)
    {
        lcd.setCursor(g,1);
        lcd.print(' ');
    }
    lcd.setCursor(0,1);
}
void UptForTransfer()
{
    for (int g=0; g < 12; g++)
    {
        lcd.setCursor(g,0);
        lcd.print(' ');
    }
    lcd.setCursor(0,1);
}
long int Enter(long int limit=1000000)
{   
    String str_schet = "";
    key=' ';
    while(1)
    {
        if(key!=NO_KEY)
        {
        
        if(str_schet.length()<11)
        {
            if (key=='0'||key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9')
            {
                str_schet = str_schet+key;
                UptForEnter();
                lcd.print(str_schet);
            }
        }
        if (key == 'B')
        {
            str_schet = "";
            UptForEnter();
            lcd.print(str_schet);
        }
        if (key == 'C')
        {
            String new_str_schet="";
            for (unsigned int u=0; u < str_schet.length() - 1; u++)
            {
                new_str_schet=new_str_schet+str_schet[u];
            }
            str_schet=new_str_schet;
            UptForEnter();
            lcd.print(str_schet);
        }
        if (key == '#')
        {
            if ( str_schet.length() < 5)
            {
                str_schet=str_schet+"000000";
                UptForEnter();
                lcd.print(str_schet);
            }
        }
        if (key == '*')
        {
            if ( str_schet.length() < 8)
            {
                str_schet=str_schet+"000";
                UptForEnter();
                lcd.print(str_schet);
            }
        }
        if (key=='D')
        {   long int chislo=str_schet.toInt();
            if(chislo!=0 && chislo<=limit)
            {
            return chislo;
            }
        }
        if (key=='A' && mode==3)
        {
            return -1;
        }
        }
        key = keypad.getKey();
    }
}
void transfer(long int chislo)
{
    if (chislo>0)
    {
        while (1)
        {
            PrintSymbols(5);
            if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
            {  
                for (byte i = 0; i < mfrc522.uid.size; i++) 
                {
                    uidDecTemp = mfrc522.uid.uidByte[i];
                    uidDec = uidDec * 256 + uidDecTemp;
                }
                if (SearchSame(uidDec))
                {   
                    int from=index;
                    int to;
                    UptForTransfer();
                    lcd.setCursor(0,0);
                    lcd.print(from+1);
                    lcd.print("--->");
                    while(1)
                    {   
                        if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
                        {  
                            for (byte i = 0; i < mfrc522.uid.size; i++) 
                            {
                                uidDecTemp = mfrc522.uid.uidByte[i];
                                uidDec = uidDec * 256 + uidDecTemp;
                            }
                            if (SearchSame(uidDec)&& uidDec!=CardUIDeEPROMread[from].uid)
                            {
                                to=index;
                                lcd.setCursor(5,0);
                                lcd.print(to+1);
                                CardUIDeEPROMread[from].balance=CardUIDeEPROMread[from].balance-chislo;
                                CardUIDeEPROMread[to].balance=CardUIDeEPROMread[to].balance+chislo;
                                PrintSymbols(4);
                                delay(2500);
                                return;
                            }
                        }
                        if(key=='A')
                        {
                            return;
                        }
                        key=keypad.getKey();
                    }    
                }
            }
            if (key=='A')
            {
                return;
            }
            key=keypad.getKey();
        }
    }
    else 
    {
        return;
    }
}
void transaction(bool znak,int chislo)
{
    while(1)
    {
        if (chislo>0)
        {
            PrintSymbols(5);
            if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
            {
                for (byte i = 0; i < mfrc522.uid.size; i++) 
                {
                    uidDecTemp = mfrc522.uid.uidByte[i];
                    uidDec = uidDec * 256 + uidDecTemp;
                }
                if (SearchSame(uidDec))
                {
                    if(znak)
                    {
                        CardUIDeEPROMread[index].balance=CardUIDeEPROMread[index].balance+chislo;
                        PrintSymbols(4);
                        delay(2500);
                        return;
                    }
                    else
                    {
                        CardUIDeEPROMread[index].balance=CardUIDeEPROMread[index].balance-chislo;
                        PrintSymbols(4);
                        delay(2500);
                        return;
                    }
                }
                else
                {
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("Player not found");
                    delay(3000);
                }
            }
            if (key=='A')
            {
                chislo=-1;
            }
            key=keypad.getKey();
        }
        else
            { 
                return;
            }
    }
}
void preStartDisplay()
{
    if (mode==0)
    {
        for (int in=0; in <8; in++)
        {
            Setter(in);
            if (CardUIDeEPROMread[in].uid==0)
            {
                lcd.print(" ");
            }
            else
            {
                lcd.print(in+1);
            }
        }
    }
}
void preStart()
{
    if (mode == 0) 
    {
        key = keypad.getKey();
        delay(750);
        if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
        {
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            {
                uidDecTemp = mfrc522.uid.uidByte[i];
                uidDec = uidDec * 256 + uidDecTemp;
            }
            if (mode == 0) 
            {
                if (key != 'D') //key != 'D'
                {
                    if (SearchSame(uidDec)) 
                    {
                        CardUIDeEPROMread[index].uid = 0;
                    } else 
                    {
                        short int i = 0;
                        bool FreeSpace = false;
                        for (i = 0; i < 8; i++) 
                        {
                            if (CardUIDeEPROMread[i].uid == 0) 
                            {
                                FreeSpace = true;
                                break;
                            }
                        }
                        if (FreeSpace == true) 
                        {
                            CardUIDeEPROMread[i].uid = uidDec;
                        } else 
                        {
                            lcd.setCursor(15, 0);
                            lcd.print("-");
                        }
                    }
                }
            }
        }
        else if (key == 'D') 
        {
            mode=1;
        }
    }
}
void Money_for_Players()                  
{
    if (mode == 1)
    {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Start balance:");        
        long int MfP=Enter(1000000);         
         for (int i = 0; i < 8; i++)       
            {
                CardUIDeEPROMread[i].balance = MfP;
            }
        mode = 2;                            
    }
}
void Money_For_Circle()                       
{
    if (mode == 2)
    {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Circle money:");
        moneyforcircle = Enter(1000000);      
        lcd.clear();
        mode = 3;                            
    }
}
void Game()
{
    if (mode == 3)
    {   
        key = keypad.getKey();
        if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial())
        {
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            {
                uidDecTemp = mfrc522.uid.uidByte[i];
                uidDec = uidDec * 256 + uidDecTemp;
            }
            if (SearchSame(uidDec)==true)
                {
                    lcd.clear();
                    lcd.setCursor(0,0);
                    lcd.print("Plr:");
                    lcd.setCursor(4,0);
                    lcd.print(index+1);
                    lcd.setCursor(0,1);
                    lcd.print("Blc:");
                    lcd.setCursor(4,1);
                    lcd.print(CardUIDeEPROMread[index].balance);
                    delay(2000);
                    lcd.clear();
                }
            if (SearchSame(uidDec)==false)
            {
                lcd.clear();
                lcd.setCursor(5,0);
                lcd.print("Error!");
                lcd.setCursor(1,1);
                lcd.print("Incorrect Card");
                delay(2000);
                lcd.clear();
            }
        }
        if (key=='A')
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Transfer:");
            PrintSymbols(0);
            delay(1500);
            OchistkaDlyaSimvola();
            transfer(Enter(1000000000));
            lcd.clear();
        }
        if (key=='B')
        {   
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Get:");
            PrintSymbols(1);
            delay(1500);
            OchistkaDlyaSimvola();
            transaction(true,Enter(1000000000));
            lcd.clear();
        }
        if (key=='C')
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Spend:");
            PrintSymbols(2);
            delay(1500);
            OchistkaDlyaSimvola();
            transaction(false,Enter(1000000000));
            lcd.clear();
        }
        if (key=='D')
        {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Crl money:");
            PrintSymbols(3);
            delay(1500);
            OchistkaDlyaSimvola();
            transaction(true,moneyforcircle);
            lcd.clear();
        }
        lcd.setCursor(0,0);
        lcd.print("Waiting");
        lcd.setCursor(0,1);
        lcd.print("for operation");
    }
}
void loop()
{
    preStart();
    preStartDisplay();
    Money_for_Players();
    Money_For_Circle();
    Game();
}
