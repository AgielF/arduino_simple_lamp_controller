const int ledPin = 2;
const int trigPin = 9;
const int echoPin = 10;
const int ldrPin = A0;  // Analog pin for LDR
const int buzzPin = 6;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  Serial.println("test");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);  // Set buzzPin as OUTPUT
  pinMode(ldrPin, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    if (data == '1') {
      digitalWrite(ledPin, HIGH);
    }
    if (data == '2') {
      digitalWrite(ledPin, LOW);
    }
  }

  // Bersihkan trigPin dengan mengaturnya LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set trigPin HIGH selama 10 mikrodetik
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Membaca echoPin, mengembalikan durasi sinyal dalam mikrodetik
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak
  distance = duration * 0.034 / 2; // Kecepatan gelombang suara dibagi 2 (perjalanan bolak-balik)

  // Jika jarak lebih dari batas sensor atau tidak realistis, setel ke 0
  if (distance >= 400 || distance <= 2) {
    distance = 0;
  }

  // Menampilkan jarak pada Serial Monitor
  Serial.print("DIST:");
  Serial.println(distance);

  // Membaca nilai dari sensor LDR
  int ldrValue = analogRead(ldrPin);

  // Tampilkan nilai LDR pada Serial Monitor
  Serial.print("LDR:");
  Serial.println(ldrValue);

  // Jika nilai LDR di bawah threshold, nyalakan LED
  if (ldrValue > 900) { // Adjust threshold value as needed
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Kontrol LED dan buzzer berdasarkan jarak dari sensor ultrasonik
  // if (distance == 0) {
  //   digitalWrite(ledPin, LOW);    // Matikan LED jika jarak 0 cm
  //   digitalWrite(buzzPin, LOW);   // Matikan buzzer jika jarak 0 cm
  // } else if (distance < 5) {
  //   digitalWrite(ledPin, HIGH);
  //   digitalWrite(buzzPin, HIGH);  // Nyalakan buzzer jika jarak di bawah 5 cm
  // } else if (distance < 10) {
  //   digitalWrite(ledPin, HIGH);   // Nyalakan LED jika jarak di bawah 10 cm

  //   digitalWrite(buzzPin, LOW);   // Matikan buzzer jika jarak antara 5 cm dan 10 cm
  // } else {
  //   digitalWrite(ledPin, LOW);    // Matikan LED jika jarak lebih dari 10 cm
  //   digitalWrite(buzzPin, LOW);   // Matikan buzzer jika jarak lebih dari 10 cm
  // }
  // delay(500); // Tunggu 500ms sebelum pembacaan berikutnya
}
