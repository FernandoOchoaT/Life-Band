#include <Wire.h>
#include <U8g2lib.h>

// Configura la pantalla con U8G2_SH1106_128X64_NONAME_F_HW_I2C para SH1106
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 26, /* data=*/ 25);

void setup() {
  // Inicializa la pantalla
  u8g2.begin();
  // Configura el tamaño de la fuente
  u8g2.setFont(u8g2_font_ncenB08_tr);
}

void loop() {
  // Limpia la pantalla
  u8g2.clearBuffer();
  // Configura la posición del cursor
  u8g2.setCursor(0, 20);
  // Imprime el mensaje en el buffer
  u8g2.print("Hola, Mundo!");
  // Envía el buffer a la pantalla
  u8g2.sendBuffer();
  // Espera un segundo
  delay(1000);
}
