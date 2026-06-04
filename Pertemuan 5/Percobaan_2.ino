#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Struktur data sensor
struct readings {
  int temp;
  int h;
};

// Membuat queue
QueueHandle_t my_queue;

// Deklarasi task
void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {

  Serial.begin(9600);

  // Pin LED sesuai rangkaian sebelumnya
  pinMode(8, OUTPUT);   // LED suhu
  pinMode(7, OUTPUT);   // LED humidity

  // Membuat queue
  my_queue = xQueueCreate(1, sizeof(struct readings));

  // Membuat task
  xTaskCreate(
    read_data,
    "read sensors",
    128,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    display,
    "display",
    128,
    NULL,
    1,
    NULL
  );
}

void loop() {
}

/*
   Task membaca data sensor
*/
void read_data(void *pvParameters) {

  struct readings x;

  for (;;) {

    // Simulasi data sensor
    x.temp = 54;
    x.h = 30;

    // Kirim data ke queue
    xQueueSend(my_queue, &x, portMAX_DELAY);

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

/*
   Task menampilkan data dan kontrol LED
*/
void display(void *pvParameters) {

  struct readings x;

  for (;;) {

    // Terima data dari queue
    if (xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {

      Serial.print("Temp = ");
      Serial.println(x.temp);

      Serial.print("Humidity = ");
      Serial.println(x.h);

      // LED pin 8 untuk suhu
      if (x.temp > 50) {
        digitalWrite(8, HIGH);
      } else {
        digitalWrite(8, LOW);
      }

      // LED pin 7 untuk humidity
      if (x.h > 25) {
        digitalWrite(7, HIGH);
      } else {
        digitalWrite(7, LOW);
      }
    }
  }
}
