// Código para ler e printar os dados do BMS


void setup(){
    Serial.begin(9600);
}

void loop(){
    BMS_decode();
    
}

void BMS_decode()
{
    // Declaração das variaveis locais
    int BMS_byte[58], celula, estado_de_carga, temperatura_celula, temperatura_minima, temperatura_maxima;
    float tensao_total, corrente_entrada, corrente_saida, tensao_celula, tensao_minima, tensao_maxima;
    

    //Coleta dos dados até o Byte 58 do BMS
    if (Serial.available())
    {
        BMS_byte[i] = Serial.read();
        x = BMS_byte[i];
        send();

        Serial.print(x);
        Serial.print(" ");

        i++;
    }

    // Calculo e print dos dados recebidos
    if (i >= 58)
    {
        tensao_total = (BMS_byte[1] * 256 + BMS_byte[2]) * 0.005;
        corrente_entrada = (BMS_byte[4] * 256 + BMS_byte[5]) * 0.125;
        corrente_saida = (BMS_byte[7] * 256 + BMS_byte[8]) * 0.125;
        tensao_minima = (BMS_byte[12] * 256 + BMS_byte[13]) * 0.005;
        tensao_maxima = (BMS_byte[15] * 256 + BMS_byte[16]) * 0.005;
        temperatura_minima = (BMS_byte[18] * 256 + BMS_byte[19]) - 276;
        temperatura_maxima = (BMS_byte[21] * 256 + BMS_byte[22]) - 276;
        celula = BMS_byte[24];
        tensao_celula = (BMS_byte[26] * 256 + BMS_byte[27]) * 0.005;
        temperatura_celula = (BMS_byte[28] * 256 + BMS_byte[29]) - 276;
        estado_de_carga = BMS_byte[40];

        Serial.print(tensao_total);
        Serial.print(",");
        Serial.print(corrente_entrada);
        Serial.print(",");
        Serial.print(corrente_saida);
        Serial.print(",");
        Serial.print(tensao_minima);
        Serial.print(",");
        Serial.print(tensao_maxima);
        Serial.print(",");
        Serial.print(estado_de_carga);
        Serial.println();

        i = 0;
    }
}