#include <eduardino.hpp>
#include <device/SPI/apa102/apa102.hpp>
#include <in_flash.hpp>
#include <font.hpp>

static APA102 mAPA102(8);

void setup() {
  mAPA102.begin();
  mAPA102.update({b:0xFF, g:0x00, r:0x00 });
  delay_ms(100);
  mAPA102.update({b:0x00, g:0xFF, r:0x00 });
  delay_ms(100);
  mAPA102.update({b:0x00, g:0x00, r:0xFF });
  delay_ms(100);
  mAPA102.update({b:0x00, g:0x00, r:0x00 });
  delay_ms(100); }

const u8 mensaje[] PROGMEM = "FARMACIA";

void loop() {
  cu16 delay = 25;
  for(iRange(sizeof(mensaje)-1)) {
    u8 caracter = pgm_read_byte(&mensaje[i]);

    for(jRange(5)) {
      u8 columna = pgm_read_byte((u16)&font[caracter - 0x20] + (u16)j);

      mAPA102.startFrame();

      for(kRange(8)) {
        mAPA102.sendFrame((columna & 0x01) ? (color_t) {
          0xFF,0x00,0x00 } : (color_t) {
          0,0,0 });
        columna >>= 1; }

      mAPA102.endFrame();

      delay_ms(delay); }

    mAPA102.update({b:0x00, g:0x00, r:0x00 });
    delay_ms(delay); }

  mAPA102.update({b:0x00, g:0x00, r:0x00 });
  delay_ms(500); }

