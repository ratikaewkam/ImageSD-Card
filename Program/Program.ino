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
  Serial.println("bytes");
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
