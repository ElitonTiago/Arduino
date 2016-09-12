#define YP A3 // Y+ is on Analog1
#define XM A2 // X- is on Analog2
#define YM 9 // Y- is on Digital7
#define XP 8 // X+ is on Digital6
  
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
  
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);
 
//Definicao de cores
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF
  
//PP_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Armazena o estado dos botões
bool valor_botao1 = 0;
bool valor_botao2 = 0;
bool valor_botao3 = 0;
bool valor_botao4 = 0;

void iniciaTFT(){
  Serial.println("TFT Test");
  //identifier == 0x9341;
  tft.reset();
  delay(500);
  //uint16_t identifier = tft.readRegister(0x0);
  //Serial.print("Driver encontrado: ");
  //Serial.println(identifier, HEX);
  
 tft.begin(0x9341);
  //tft.initDisplay();
  tft.fillScreen(BLACK);
  tft.setRotation(3);
  
  // Inicio - Texto e botoes
  tft.drawRoundRect(5, 5, 312, 35, 5, WHITE);
  tft.drawRoundRect(255, 5, 62, 35, 5, WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(15, 15);
  tft.println("Lampada esta");  
      
}

void loopTFT(){
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
  pinMode(YM, OUTPUT);
  digitalWrite(YM, LOW);
  pinMode(XP, OUTPUT);
  digitalWrite(XP, HIGH);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = tft.width() - (map(p.x, TS_MINX, TS_MAXX, tft.width(), 0));
    p.y = tft.height() - (map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
    if (p.y > 200)
    {
      Serial.print("py: ");
      Serial.print(p.y);
      Serial.print(" px: ");
      Serial.println(p.x);
  
      //Testa botao amarelo
      if (p.x > 250 & p.x < 305)
      {
        if(digitalRead(statusLampada)){
          desligaLampada();
        }else{
          ligaLampada();
        }
        yield();
      }
      delay(200);
    }
  }
  
}

void alteraIndicacao(){
  if(digitalRead(statusLampada)){
        tft.fillRoundRect(256, 5, 60, 34, 5, WHITE);
          mostra_on(269, 15);
          valor_botao1 = !valor_botao1;
  }else{
    tft.fillRoundRect(256, 6, 60, 32, 5, BLACK);
          mostra_off(260, 15);
          valor_botao1 = !valor_botao1;
  }
  tft.fillRoundRect(15, 45, 300, 190, 0, BLACK);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.setCursor(0, 45);
  tft.print(" Luz = ");
  tft.println(luminosidade);
  tft.print(" Desejada = ");
  tft.println(valorLuzDesejada);
  tft.print(" Movimento = ");
  tft.println(movimento);
  tft.print(" Wb = ");
  tft.println(Wb);
  tft.print(" Wl = ");
  tft.println(Wl);
  tft.print(" Wm = ");
  tft.println(Wm);
  
}
  
void mostra_on(int x, int y)
{
  tft.setTextColor(BLACK);
  tft.setCursor(x, y);
  tft.println("ON");
  delay(100);
}
  
void mostra_off(int x, int y)
{
  tft.setTextColor(WHITE);
  tft.setCursor(x, y);
  tft.println("OFF");
  delay(100);
}

