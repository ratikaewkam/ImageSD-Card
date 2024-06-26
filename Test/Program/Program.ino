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
  int fileSize = readSize("IMAGE/PIXEL.BMP");
  Serial.print("BMP File Size: ");
  Serial.print(fileSize);
  Serial.println(" bytes");

  // Read w, h
  int w = readWidth("IMAGE/PIXEL.BMP");
  int h = readHeight("IMAGE/PIXEL.BMP");
  Serial.print("Image: ");
  Serial.print(w);
  Serial.print("x");
  Serial.print(h);
  Serial.println(" px");

  // Read Bit Count
  int bitCount = readBitCount("IMAGE/PIXEL.BMP");
  Serial.print("Bits per pixel: ");
  Serial.println(bitCount);
  
  int data = readDataOffset("IMAGE/PIXEL.BMP");
  Serial.print("Data: ");
  Serial.println(data);

  File f = SD.open("IMAGE/PIXEL.BMP");
  f.seek(0);
  for (int i=0;i<238;i++) {
    uint8_t data = f.read();
    Serial.print(i);
    Serial.print(": ");
    Serial.println(data);
  }
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

  // Read width (4 bytes)
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

  // Read height (4 bytes)
  uint32_t h = file.read();
  
  h |= file.read() << 8;
  h |= file.read() << 16;
  h |= file.read() << 24;

  file.close();

  return h;
}

int readBitCount(char* fileName) {
   File file = SD.open(fileName, FILE_READ);

   if (!file) {
    Serial.println("Failed to open BMP file!");
  }

  file.seek(28); // Start of bit count (2 bytes)

  // Read bit count (2 bytes)
  uint16_t bc = file.read();
  
  bc |= file.read() << 8;

  file.close();

  return bc;
}

int readDataOffset(char* fileName) {
  File file = SD.open(fileName, FILE_READ);

  if (!file) {
    Serial.println("Failed to open BMP file!");
  }

  /*
   * Seek to the position where the data offset is stored in the BMP header
   */
  file.seek(10); // Start of data offset (4 bytes)

  // Read height (4 bytes)
  uint32_t data = file.read();
  
  data |= file.read() << 8;
  data |= file.read() << 16;
  data |= file.read() << 24;

  file.close();

  return data;
}
