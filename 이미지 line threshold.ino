### 가. 이진화에 대한 코드 ###
#define TSL1401_CLK 22       // TSL1401의 클럭 신호에 사용할 핀 번호를 22번으로 설정
#define TSL1401_SI 23        // TSL1401의 SI(Serial Input) 신호에 사용할 핀 번호를 23번으로 설정
#define TSL1401_AO A0        // TSL1401의 AO(Analog Output) 신호에 사용할 아날로그 핀을 A0으로 설정
#define NPIXELS 128          // 픽셀의 총 개수를 128개로 설정

byte Pixel[NPIXELS];         // 128개의 픽셀 데이터를 저장할 배열을 선언

#define FASTADC 1            // ADC(Analog-to-Digital Converter)의 속도를 빠르게 하기 위한 옵션 설정

byte threshold_data[NPIXELS]; // 임계값에 따라 이진화된 픽셀 데이터를 저장할 배열

// 픽셀 데이터를 임계값으로 이진화하는 함수
void line_threshold(int threshold) 
{
  for(int i = 0; i < NPIXELS; i++) // 128개의 픽셀을 순회하면서
  {
    threshold_data[i] = (Pixel[i] > threshold) ? 255 : 0; // 픽셀 값이 임계값보다 크면 255(흰색), 작으면 0(검정색)으로 설정
  }
}

void setup() 
{
    Serial.begin(115200);  // 시리얼 통신을 초당 115200 baud rate로 시작
    pinMode(TSL1401_CLK, OUTPUT); // TSL1401의 클럭 핀을 출력으로 설정
    pinMode(TSL1401_SI, OUTPUT);  // TSL1401의 SI 핀을 출력으로 설정
  
    #if FASTADC
      sbi(ADCSRA, ADPS2); // ADC 속도를 빠르게 하기 위한 설정, ADPS2 비트 설정
      cbi(ADCSRA, ADPS1); // ADPS1 비트를 클리어하여 분주비 조정
      cbi(ADCSRA, ADPS0); // ADPS0 비트를 클리어하여 분주비 조정
    #endif
}

// TSL1401 카메라로부터 픽셀 데이터를 읽는 함수
void read_TSL1401_camera() 
{
    digitalWrite(TSL1401_SI, HIGH); // SI 신호를 HIGH로 하여 데이터 전송 시작 신호를 보냄
    digitalWrite(TSL1401_CLK, HIGH); // 클럭 신호를 HIGH로 하여 첫 번째 픽셀 데이터 준비
    delayMicroseconds(1);            // 신호의 안정화를 위해 약간의 지연
    digitalWrite(TSL1401_CLK, LOW);  // 클럭 신호를 LOW로 하여 데이터를 읽을 준비
    digitalWrite(TSL1401_SI, LOW);   // SI 신호를 LOW로 하여 데이터 전송 종료 신호를 보냄
    delayMicroseconds(1);            // 신호 안정화를 위한 지연

    // 128개의 픽셀 데이터를 읽어 Pixel 배열에 저장
    for(int i = 0; i < NPIXELS; i++) 
    {
        digitalWrite(TSL1401_CLK, HIGH); // 클럭 신호를 HIGH로 하여 데이터를 읽을 준비
        delayMicroseconds(1);            // 클럭 신호가 안정화될 때까지 대기
        Pixel[i] = analogRead(TSL1401_AO);  // AO 핀에서 아날로그 값을 읽어 Pixel 배열에 저장
        digitalWrite(TSL1401_CLK, LOW);   // 클럭 신호를 LOW로 하여 다음 픽셀로 이동
        delayMicroseconds(1);             // 신호 안정화를 위한 지연
    }
}

// 카메라 데이터를 시리얼로 전송하는 함수
void send_camera_data_serial() 
{
    // 128개의 픽셀 데이터와 이진화된 데이터를 시리얼로 전송
    for(int i = 0; i < NPIXELS; i++) 
    {
        Serial.print(Pixel[i]);    // 원본 픽셀 값을 출력
        Serial.print(",");         // 데이터 구분을 위한 쉼표 출력
        Serial.println(threshold_data[i]); // 이진화된 데이터를 출력
    }

    // 추가적인 데이터 전송 (64개 0값을 전송)
    for(int i = 0; i < 64; i++) 
    {
        Serial.print(0);           // 0값을 출력
        Serial.print(",");         // 쉼표 출력
        Serial.println(0);         // 0값 출력
    }
}

// 메인 루프
void loop() 
{
    read_TSL1401_camera();  // 카메라로부터 데이터를 읽음
    line_threshold(150);    // 임계값 150을 적용하여 이진화 처리
    send_camera_data_serial();  // 시리얼 통신으로 데이터를 전송
    delay(100);  // 100ms 대기 후 반복
}
