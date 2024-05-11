#include <SPI.h>
#include <SD.h>

const int cs = 4; // Chip select pin

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for Serial Monitor to open
  }

  if (!SD.begin(cs)) {
    Serial.println("SD card initialization failed!");
    return;
  }

  Serial.println("SD card initialized.");

  // Read BMP file size
  int fileSize = readSize("IMAGE/TABLE.BMP");
  Serial.print("BMP File Size: ");
  Serial.print(fileSize);
  Serial.println(" bytes");

  int w = readWidth("IMAGE/TABLE.BMP");
  int h = readHeight("IMAGE/TABLE.BMP");
  Serial.print("Image: ");
  Serial.print(w);
  Serial.print("x");
  Serial.print(h);
  Serial.println(" px");
}

void loop() {
  
}

int readSize(char* fileName) {
  File file = SD.open(fileName, FILE_READ);

  if (!file) {
    Serial.println("Failed to open BMP file!");
  }

  /*
   Seek to the position where the file 
   size is stored in the BMP header
  */
  file.seek(2); // Start of file size (2 bytes)

  // Read file size (4 bytes)
  uint32_t fileSize = file.read();
  
  fileSize |= file.read() << 8;
  fileSize |= file.read() << 16;
  fileSize |= file.read() << 24;

  file.close();

  return fileSize;
}

int readWidth(char* fileName) {
  File file = SD.open(fileName, FILE_READ);

  if (!file) {
    Serial.println("Failed to open BMP file!");
  }

  /*
   * Seek to the position where the width is stored in the BMP header
   */
  file.seek(18); // Start of width (4 bytes)

  // Read file size (4 bytes)
  uint32_t w = file.read();
  
  w |= file.read() << 8;
  w |= file.read() << 16;
  w |= file.read() << 24;

  file.close();

  return w;
}

int readHeight(char* fileName) {
  File file = SD.open(fileName, FILE_READ);

  if (!file) {
    Serial.println("Failed to open BMP file!");
  }

  /*
   * Seek to the position where the height is stored in the BMP header
   */
  file.seek(22); // Start of height (4 bytes)

  // Read file size (4 bytes)
  uint32_t h = file.read();
  
  h |= file.read() << 8;
  h |= file.read() << 16;
  h |= file.read() << 24;

  file.close();

  return h;
}
