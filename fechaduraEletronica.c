// CONFIGURAÇÃO DO PORT
sbit LCD_RS at RD3_bit;
sbit LCD_EN at RD2_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

// CONFIGURAÇÃO DO TRIST
sbit LCD_RS_Direction at TRISD3_bit;
sbit LCD_EN_Direction at TRISD2_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;


char keypadPort at PORTB;                        // Teclado é configurado para o PORTB
char teclas[4][4] = {{'1', '2', '3', 'A'},
                     {'4', '5', '6', 'B'},
                     {'7', '8', '9', 'C'},
                     {'*', '0', '#', 'd'}};
char senhadigitada[4];                           // Receberá 4 valores da matriz teclas
char senhamestre[4] = {'1', '2', '3', '4'};
int i=0, m=0, kp, cfm = 0, x;

/*
i = usado na hora de "pegar" o valor selecionado no teclado e no preenchimento do display
m = usado para avaliar se a senha está correta ou incorreta
kp = usado para leitura do teclado
cfm = usado para ativar a função de COMPARAR SENHA
x = representa a posição de cada CHAR e comparar as mesmas posições           */


void Buzzer_Curto() {
     int a;
     for(a = 0; a < 4; a++) {
           delay_ms(100);
           RE0_bit = ~RE0_bit;
           delay_ms(150);
     }
}

void Buzzer_Longo() {
     int b;
     for(b = 0; b < 2; b++) {
           delay_ms(100);
           RE0_bit = ~RE0_bit;
           delay_ms(500);
     }
}



void Destravar() {
     PORTA.RA0 = ~PORTA.RA0;
}

void Travar() {
     PORTA.RA0 = 0;
}


void confirmar(char senha1[], char senha2[]) {
     for(x = 0; x < 4; x++) {
               if(senha1[x] == senha2[x]) {
                 m++;
               }
     }
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Out_CP("Verificando...");
     delay_ms(1000);
     
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     Lcd_Cmd(_LCD_SECOND_ROW);
     
     if(m == 4) {
              delay_ms(200);
              Lcd_Out_CP("Senha correta!");
              delay_ms(2000);
              Lcd_Cmd(_LCD_CLEAR);
              Lcd_Cmd(_LCD_SECOND_ROW);
              Lcd_Out_CP("Liberado");
              Buzzer_Curto();
              Destravar();
              m = 0;
     } else {
              delay_ms(200);
              Buzzer_Longo();
              Lcd_Out_CP("Senha incorreta!");
              delay_ms(2000);
              Lcd_Cmd(_LCD_CLEAR);
              Lcd_Out_CP("Insira a senha: ");
              Lcd_Cmd(_LCD_SECOND_ROW);
              i = 0;
              m = 0;
     }
}


void SenhaNoDisplay(){                      // PREENCHE * NO DISPLAY
           if(i == 0){
                         Lcd_Chr(2, 1, '*');
                         Lcd_Chr(2, 2, ' ');
           }
           if(i == 1){
                         Lcd_Chr(2, 3, '*');
                         Lcd_Chr(2, 4, ' ');
           }
           if(i == 2){
                         Lcd_Chr(2, 5, '*');
                         Lcd_Chr(2, 6, ' ');
           }
           if(i == 3){
                         Lcd_Chr(2, 7, '*');
                         Lcd_Chr(2, 8, ' ');
           }
}


void DigitarSenha() {
     Keypad_Init();
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);


     do{
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Out_CP("Insira a senha: ");
     Lcd_Cmd(_LCD_SECOND_ROW);
     Lcd_Cmd(_LCD_CURSOR_OFF);

        do{
               kp = 0;
               cfm = 0;

               do{
                  kp = Keypad_Key_Click();
               } while(!kp);

               switch(kp) {
                   case  1:                          // 1
                                senhadigitada[i] = teclas[0][0];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case  2:                          // 2
                                senhadigitada[i] = teclas[0][1];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case  3:                          // 3
                                senhadigitada[i] = teclas[0][2];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case  4:                         // A - sem função
                                break;
                   case  5:                         // 4
                                senhadigitada[i] = teclas[1][0];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case  6:                         // 5
                                senhadigitada[i] = teclas[1][1];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case  7:                         // 6
                                senhadigitada[i] = teclas[1][2];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case  8:                         // B - sem função
                                break;
                   case  9:                         // 7
                                senhadigitada[i] = teclas[2][0];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case 10:                         // 8
                                senhadigitada[i] = teclas[2][1];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case 11:                         // 9
                                senhadigitada[i] = teclas[2][2];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case 12:                         // C - sem função
                                break;
                   case 13:                         // * - função CONFIRMAR SENHA (compara senha digitada)
                                delay_ms(50);
                                cfm = 1;
                                if(cfm == 1) {
                                          confirmar(senhadigitada, senhamestre);
                                }
                                break;
                   case 14:                          // 0
                                senhadigitada[i] = teclas[4][1];
                                SenhaNoDisplay();
                                i++;
                                break;
                   case 15:                          // # - função BLOQUEAR (retornar ao estágio inicial)

                                Lcd_Cmd(_LCD_CLEAR);
                                Lcd_Cmd(_LCD_CURSOR_OFF);
                                Lcd_Out_CP("Bloqueando...");
                                delay_ms(1000);
                                Travar();
                                Lcd_Cmd(_LCD_CLEAR);
                                Lcd_Out_CP("Insira a senha: ");
                                Lcd_Cmd(_LCD_SECOND_ROW);
                                i = 0;
                                break;
                   case 16:                          // D - sem função
                                break;
                   }
        } while(1);
     } while(1);
}









void main() {
     ADCON1 = 0xFF;
     TRISA0_bit = 0;
     PORTA.RA0 = 0;
     TRISD = 0x00;
     TRISE = 0b1000;
     PORTE = 0b1000;
     
     DigitarSenha();

}