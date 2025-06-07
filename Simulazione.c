#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h> 

// Funzioni logiche
int NOT(int a) { return 1 - a; }
int AND(int a, int B) { return a * B; }
int OR(int a, int B) { return (a + B) - (a * B); }
int EXOR(int a, int b){ return (a + b) - ((2 * a) * b); }
int NOR(int a, int b) { return NOT(OR(a, b)); }
int NAND(int a, int b) { return NOT(AND(a, b)); }

// Funzioni per 3 o più variabili
int OR3(int a, int b, int c){return OR(OR(a, b), c);}
int AND3(int a, int b, int c){return AND(AND(a, b), c);}
int NOR3(int a, int b, int c){return NOT(OR(OR(a, b), c));}
int NAND3(int a, int b, int c){return NOT(AND(AND(a, b), c));}
int AND1(int a){return a;}
int AND4(int a, int b, int c, int d){return AND(AND(AND(a, b), c), d); }
int NAND4(int a, int b, int c, int d){return NOT(AND(AND(AND(a, b), c), d)); }
int NOR4(int a, int b, int c, int d){return NOT(OR(OR(OR(a, b), c), d));}
int AND5(int a, int b, int c, int d, int e){return AND(AND(AND(AND(a, b), c), d), e);}
int NAND5(int a, int b, int c, int d, int e){return NOT(AND(AND(AND(AND(a, b), c), d), e));}


// ALU
// ALU
void ALU(
    int a0, int b0, int a1, int b1, int a2, int b2, int a3, int b3,
    int z0, int z1, int z2, int z3, int m1, int Cn,
    int* f0, int* f1, int* f2, int* f3, int* A, int* B, int* Cn4
) {
    
   // 1 sezione

     int p0 = NOR3(AND(NOT(b0), z1),AND(z0, b0), AND1(a0));
     int p1 = NOR(AND3(a0, b0, z3), AND3(a0, z2, NOT(b0)));
     
     int p2 = NOR3(AND(NOT(b1), z1),AND(z0, b1), AND1(a1));
     int p3 = NOR(AND3(a1, b1, z3), AND3(a1, z2, NOT(b1)));
  
     int p4 = NOR3(AND(NOT(b2), z1),AND(z0, b2), AND1(a2)); 
     int p5 = NOT(OR(AND3(a2, b2, z3), AND3(a2, z2, NOT(b2)))); 
  
     int p6 = NOR3(AND(NOT(b3), z1),AND(z0, b3), AND1(a3)); 
     int p7 = NOR(AND3(a3, b3, z3), AND3(a3, z2, NOT(b3))); 
     
   // 2 sezione
     
      int M = NOT(m1);
  
*f0 = EXOR(EXOR(p0, p1), NAND(Cn, M));                                  // output 1
 
     int f1a = NOR(AND3(p2, M, Cn), AND(p1, M));                        // output 2
*f1 = EXOR(EXOR(p2, p3), f1a);
 
     int f2a = NOR3(AND4(Cn, p2, p4, M), AND3(p4, p1, M), AND(M, p3));      
*f2 = EXOR(EXOR(p4, p5), f2a);                                          // output 3
 
     int f3d = AND5(Cn, p1, p3, p5, M);
     int f3c = AND4(p3, p5, p1, M);
     int f3b = AND3(p2, M, p5);
     int f3a = AND(p4, M);
*f3 = EXOR(EXOR(p6, p7), NOR4(f3d, f3c, f3b, f3a));                     // output 4

    *A = AND(*f0, *f1);
    *B = AND(*f3, *f2);

  // 3 sezione


 int GY = NOR4(AND1(p6), AND(p7, p4), AND3(p7, p5, p2), AND4(p7, p5, p3, Cn));// output G(negato) or Y 
 
 *Cn4 = OR(NOT(GY), NOT(NAND5(p7, p5, p3, p1, Cn)));                       // output Cn+4 or Cn+4(negato)


}


void REG(
    int f0_in, int f1_in, int f2_in, int f3_in, int f4_in, int f5_in, int f6_in, int f7_in,
    int* Q0, int* Q1, int* Q2, int* Q3, int* Q4, int* Q5, int* Q6, int* Q7
){

    int R;
    R = 1;

    int scelta;
    scelta = 0;
    
    // Loop per operazioni successive
    while (1) {

    if (scelta == 1){ R = 0;}  // RESET
          
          
        *Q0 = f0_in * R;
        *Q1 = f1_in * R;
        *Q2 = f2_in * R;
        *Q3 = f3_in * R;
        *Q4 = f4_in * R;
        *Q5 = f5_in * R;
        *Q6 = f6_in * R;
        *Q7 = f7_in * R;
        
     printf("Dati memorizzati:\nQ0 = %d,\nQ1 = %d,\nQ2 = %d,\nQ3 = %d,\nQ4 = %d,\nQ5 = %d,\nQ6 = %d,\nQ7 = %d,\n", *Q0,*Q1,*Q2,*Q3,*Q4,*Q5,*Q6,*Q7);
     
     

    if (scelta == 1){ printf("Reset effettuato. Tutti i valori del registro sono a valore 0\n");break;}

         else if (scelta == 2) {  // Nuovo SET
         
         int v0, v1, v2, v3, v4, v5, v6, v7;
          
            printf("Inserisci il valore di SET per ogni i flip-flop: ");

           scanf("%d\n", &v0);
           scanf("%d\n", &v1);
           scanf("%d\n", &v2); 
           scanf("%d\n", &v3); 
           scanf("%d\n", &v4);  
           scanf("%d\n", &v5);  
           scanf("%d\n", &v6);  
           scanf("%d\n", &v7);  
           
           
        *Q0 = v0;
        *Q1 = v1;
        *Q2 = v2;
        *Q3 = v3;
        *Q4 = v4;
        *Q5 = v5;
        *Q6 = v6;
        *Q7 = v7;


        } else if (scelta == 3) {
            printf("chiusura interazione\n");
            break;
        } else if(scelta > 3 || scelta < 0){
            printf("Scelta non valida.\n");

      
        printf("\nMenu interazione registri:\n");
        printf("1 - Reset/Clear\n");
        printf("2 - Overwrite con nuovo SET\n");
        printf("3 - Finisci interazione\n");
        scanf("%d", &scelta);

        }
    }
}


// binario -> deimale
long long DEC(const char *VBinO) {// long long per evitare bug causati dagli int
    long long dec = 0;
    int lunghezza = strlen(VBinO);
    
    // converte la stringa da destra verso sinistra seguendo la logica del peso
    for (int i = 0; i < lunghezza; i++) {
        char bit = VBinO[lunghezza - 1 - i]; // sezione che la legge da destra verso sinistra
        
// long long in questo caso rende specifica al pow che è una variabile intera
            dec += (long long)pow(2, i);  // sezione che applica la legge di commutazione
        }
    return dec;
}

// decimale -> binario

void BIN(int A, char* Abin){
    // Gestione del caso 0
    if (A == 0) {
        strcpy(Abin, "0");
        return;
    }

    int i = 0;
    int Arif = A;

    // Estrae i bit e li inserisce nel buffer (in ordine inverso)
    while (Arif > 0){
        if(Arif % 2 == 0){Abin[i] = '0' ;}
        else{Abin[i]= '1' ;}

        Arif /= 2;
        i++;
    }

    Abin[i] = '\0';

    // Inverte la stringa per avere l'ordine corretto dei bit

    int lunghezza = strlen(Abin);
    int j;
    char rif;
    for (i = 0, j = lunghezza - 1; i < j; i++, j--) {
        rif = Abin[i];
        Abin[i] = Abin[j];
        Abin[j] = rif;
    }
}


void DIV(
    char* num_str,
    int* d0,  int* d1,  int* d2,  int* d3,
    int* d4,  int* d5,  int* d6,  int* d7,
    int* d8,  int* d9,  int* d10, int* d11,
    int* d12, int* d13, int* d14, int* d15,
    int* d16, int* d17, int* d18, int* d19,
    int* d20, int* d21, int* d22, int* d23,
    int* d24, int* d25, int* d26, int* d27,
    int* d28, int* d29, int* d30, int* d31
){
    int cifre[32]; // Max 32 bit
    int r0 = 0;

    // Inizializza tutti i valori a 0 prima di assegnare per quando il numero è minore di 32 bit
    for(int i = 0; i < 32; i++){
        cifre[i] = 0;
    }

    // Convertiamo la stringa in array di cifre intere
    while (num_str[r0] != '\0' && r0 < 32) { 
        cifre[r0] = num_str[r0] - '0';  
        r0++;
    }

    printf("\nIl numero di bit = %d\n", r0);

    // Assegna i valori ai puntatori. Se la stringa è più corta, i valori rimangono 0 (per via dell'inizializzazione)
    *d0 = (r0 > 0) ? cifre[0] : 0;
    *d1 = (r0 > 1) ? cifre[1] : 0;
    *d2 = (r0 > 2) ? cifre[2] : 0;
    *d3 = (r0 > 3) ? cifre[3] : 0;
    printf("Le prime quattro cifre del numero sono: %d, %d, %d, %d\n", *d0, *d1, *d2, *d3);

    *d4 = (r0 > 4) ? cifre[4] : 0;
    *d5 = (r0 > 5) ? cifre[5] : 0;
    *d6 = (r0 > 6) ? cifre[6] : 0;
    *d7 = (r0 > 7) ? cifre[7] : 0;
    printf("Le cifre del primo riporto sono: %d, %d, %d, %d\n", *d4, *d5, *d6, *d7);

    *d8 = (r0 > 8) ? cifre[8] : 0;
    *d9 = (r0 > 9) ? cifre[9] : 0;
    *d10 = (r0 > 10) ? cifre[10] : 0;
    *d11 = (r0 > 11) ? cifre[11] : 0;
    printf("Le cifre del secondo riporto sono: %d, %d, %d, %d\n", *d8, *d9, *d10, *d11);

    *d12 = (r0 > 12) ? cifre[12] : 0;
    *d13 = (r0 > 13) ? cifre[13] : 0;
    *d14 = (r0 > 14) ? cifre[14] : 0;
    *d15 = (r0 > 15) ? cifre[15] : 0;
    printf("Le cifre del terzo riporto sono: %d, %d, %d, %d\n", *d12, *d13, *d14, *d15);

    *d16 = (r0 > 16) ? cifre[16] : 0;
    *d17 = (r0 > 17) ? cifre[17] : 0;
    *d18 = (r0 > 18) ? cifre[18] : 0;
    *d19 = (r0 > 19) ? cifre[19] : 0;
    printf("Le cifre del quarto riporto sono: %d, %d, %d, %d\n", *d16, *d17, *d18, *d19);

    *d20 = (r0 > 20) ? cifre[20] : 0;
    *d21 = (r0 > 21) ? cifre[21] : 0;
    *d22 = (r0 > 22) ? cifre[22] : 0;
    *d23 = (r0 > 23) ? cifre[23] : 0;
    printf("Le cifre del quinto riporto sono: %d, %d, %d, %d\n", *d20, *d21, *d22, *d23);

    *d24 = (r0 > 24) ? cifre[24] : 0;
    *d25 = (r0 > 25) ? cifre[25] : 0;
    *d26 = (r0 > 26) ? cifre[26] : 0;
    *d27 = (r0 > 27) ? cifre[27] : 0;
    printf("Le cifre del sesto riporto sono: %d, %d, %d, %d\n", *d24, *d25, *d26, *d27);

    *d28 = (r0 > 28) ? cifre[28] : 0;
    *d29 = (r0 > 29) ? cifre[29] : 0;
    *d30 = (r0 > 30) ? cifre[30] : 0;
    *d31 = (r0 > 31) ? cifre[31] : 0;
    printf("Le cifre del settimo riporto sono: %d, %d, %d, %d\n", *d28, *d29, *d30, *d31);
    
    printf("\nfine divisione di questi valori\n");
}


int main(){
    
    int S0, S1, S2, S3, M, Cn; // selettori calcoli alu
    printf("\n===Simulazione ALU 74181===\n");
    printf("\ntutti i valori a meno che non dichiarato il contrario funzionano su 1 o 0\n");    
    printf("inserisci i valori di riferimento per le operazioni seguendo le tavole di verità fornite nei datasheet.\n");
    
    printf("\ns0:\n");
    scanf("%d", &S0);
    
    printf("\ns1:\n");
    scanf("%d", &S1);
    
    printf("\ns2:\n");
    scanf("%d", &S2);
    
    printf("\ns3:\n");
    scanf("%d", &S3); 
    
    printf("\nM:\n");
    scanf("%d", &M);     
    
    printf("\nCn:\n");
    scanf("%d", &Cn); 
    
    
    
    // sezione input
    int ss1, s1t = 0, s1f = 0; // per le scelte utente
    int ss2, s2b = 0, s2d = 0;

    //input x registri
    char numA[32 + 1];  // +1 per il terminatore di stringa '\0'
    char numB[32 + 1];

    // dichiarazione per registro di A
    int a0, a1, a2, a3;
    int a4, a5, a6, a7;
    int a8, a9, a10, a11;
    int a12, a13, a14, a15;
    int a16, a17, a18, a19;
    int a20, a21, a22, a23;
    int a24, a25, a26, a27;
    int a28, a29, a30, a31;

    // dichiarazione per registro di B
    int b0, b1, b2, b3;
    int b4, b5, b6, b7;
    int b8, b9, b10, b11;
    int b12, b13, b14, b15;
    int b16, b17, b18, b19;
    int b20, b21, b22, b23;
    int b24, b25, b26, b27;
    int b28, b29, b30, b31;


    // zona scelta utente
    while(1){
        printf("Inserimento valori tramite: 1 = manualmente da terminale, 2 = tramite file.\n");
        printf("Scelta: ");
        scanf("%d",&ss1);

        if(ss1 == 1){
            s1t=1;
            break;
        } else if(ss1 == 2){
            s1f=1;
            printf("Funzione 'tramite file' non implementata. Scegli 'manualmente da terminale'.\n");
            
            continue; // Torna all'inizio del loop per chiedere di nuovo in quanto funzione non implementata
        } else {
            printf("Valore sbagliato, ritenta.\n");
        }
    }

    // zona dedicata all'inserimento da terminale
    if(s1t == 1){ // Usare '==' per il confronto
        while(1){
            printf("Tipologia valori: 1 = decimale, 2 = binario.\n");
            printf("Scelta: ");
            scanf("%d",&ss2);

            if(ss2 == 1){
                s2d = 1;
                break;
            } else if(ss2 == 2){
                s2b = 1;
                break;
            } else {
                printf("\nValore sbagliato, ritenta.\n");
            }
        }

        // zona decimale
        if(s2d == 1){
            int A, B;
            char BinA[32 + 1];
            char BinB[32 + 1];

            printf("\nInserisci 2 numeri decimali:\n");
            scanf("%d", &A);
            scanf("%d", &B);

            // Chiama la funzione per convertire i valori
            BIN(A, BinA);
            BIN(B, BinB);

            printf("\nIl numero %d in binario: %s\n", A, BinA);
            
            printf("\nIl numero %d in binario: %s\n", B, BinB);

            // Copia le stringhe binarie in numA e numB
            strncpy(numA, BinA, sizeof(numA) - 1);
            numA[sizeof(numA) - 1] = '\0';
            strncpy(numB, BinB, sizeof(numB) - 1);
            numB[sizeof(numB) - 1] = '\0';
        }

        // zona binaria
        if(s2b == 1){ 
            printf("Inserisci il primo numero (max 32 bit): ");
            scanf("%s", numA);
            printf("Inserisci il secondo numero (max 32 bit): ");
            scanf("%s", numB);
        }

        // Controllo 32 bit
        if ((strlen(numA) > 32) || (strlen(numB) > 32)) {
            printf("Errore: numero inserito supera il limite di 32 bit, overflow.\n");
            return 1; // Termina il programma con un errore se maggiori di 32 bit
        }
    }


    // Chiamata a DIV per dividere i bit nei registri
    DIV(
        numA, // divide i bit di A
        &a0, &a1, &a2, &a3,
        &a4, &a5, &a6, &a7,
        &a8, &a9, &a10, &a11,
        &a12, &a13, &a14, &a15,
        &a16, &a17, &a18, &a19,
        &a20, &a21, &a22, &a23,
        &a24, &a25, &a26, &a27,
        &a28, &a29, &a30, &a31
    );

    DIV(
        numB, // divide i bit di B
        &b0, &b1, &b2, &b3,
        &b4, &b5, &b6, &b7,
        &b8, &b9, &b10, &b11,
        &b12, &b13, &b14, &b15,
        &b16, &b17, &b18, &b19,
        &b20, &b21, &b22, &b23,
        &b24, &b25, &b26, &b27,
        &b28, &b29, &b30, &b31
    );

    //zona calcolo e registri
    
    
    int QA0,QA1,QA2,QA3,QA4,QA5,QA6,QA7,QA8,QA9,QA10,QA11,QA12,QA13,QA14,QA15,QA16,QA17,QA18,QA19,QA20,QA21,QA22,QA23,QA24,QA25,QA26,QA27,QA28,QA29,QA30,QA31;
    
    int QB0,QB1,QB2,QB3,QB4,QB5,QB6,QB7,QB8,QB9,QB10,QB11,QB12,QB13,QB14,QB15,QB16,QB17,QB18,QB19,QB20,QB21,QB22,QB23,QB24,QB25,QB26,QB27,QB28,QB29,QB30,QB31;
    
    
    
    //registri per a
    
    printf("\nSezione di registri per bit di A\n");

    sleep(1000); // 1 sec

    printf("\nRegistro 1\n");
    REG(
         a0, a1, a2, a3, a4, a5, a6, a7,
         &QA0, &QA1, &QA2, &QA3, &QA4, &QA5, &QA6, &QA7
    );

    sleep(1000);

    printf("\nRegistro 2\n");
    REG(
         a8, a9, a10, a11, a12, a13, a14, a15,
         &QA8, &QA9, &QA10, &QA11, &QA12, &QA13, &QA14, &QA15
    );

    sleep(1000);

    printf("\nRegistro 3\n");
    REG(
         a16, a17, a18, a19, a20, a21, a22, a23,
         &QA16, &QA17, &QA18, &QA19, &QA20, &QA21, &QA22, &QA23
    );

    sleep(1000);

    printf("\nRegistro 4\n");
    REG(
         a24, a25, a26, a27, a28, a29, a30, a31,
         &QA24, &QA25, &QA26, &QA27, &QA28, &QA29, &QA30, &QA31
    );
    
    

    //registri per b
    
    printf("\nSezione di registri per bit di B\n");
    
    sleep(1000);

    printf("\nRegistro 1\n");
    REG(
          b0, b1, b2, b3, b4, b5, b6, b7,
          &QB0, &QB1, &QB2, &QB3, &QB4, &QB5, &QB6, &QB7
    );

    sleep(1000);

    printf("\nRegistro 2\n");
    REG(
          b8, b9, b10, b11, b12, b13, b14, b15,
          &QB8, &QB9, &QB10, &QB11, &QB12, &QB13, &QB14, &QB15
    );

    sleep(1000);

    printf("\nRegistro 3\n");
    REG(
          b16, b17, b18, b19, b20, b21, b22, b23,
          &QB16, &QB17, &QB18, &QB19, &QB20, &QB21, &QB22, &QB23
    );

    sleep(1000);

    printf("\nRegistro 4\n");
    REG(
          b24, b25, b26, b27, b28, b29, b30, b31,
          &QB24, &QB25, &QB26, &QB27, &QB28, &QB29, &QB30, &QB31
    );
    
    sleep(1000);
    
    //alu

    
            
    int f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30, f31, A, B; // valori di output
    int Cn4, Cn41, Cn42, Cn43, Cn44, Cn45, Cn46, Cn47;  // carry
            
     


    ALU(// 1
            QA0, QB0, QA1, QB1, QA2, QB2, QA3, QB3,
            S0, S1, S2, S3, M, Cn,
            &f0, &f1, &f2, &f3, &A, &B, &Cn4
    );
    printf("\ncheck valori alu: %d,%d,%d,%d\n", f0, f1, f2, f3);
    printf("\ncheck ugualizanza prima alu: %d=%d\n", A, B);

    ALU(// 2
            QA4, QB4, QA5, QB5, QA6, QB6, QA7, QB7,
            S0, S1, S2, S3, M, Cn4,
            &f4, &f5, &f6, &f7, &A, &B, &Cn41
    );
    printf("\ncheck valori alu: %d,%d,%d,%d\n", f4, f5, f6, f7);
    printf("\ncheck ugualizanza seconda alu: %d=%d\n", A, B);

    ALU(// 3
            QA8, QB8, QA9, QB9, QA10, QB10, QA11, QB11,
            S0, S1, S2, S3, M, Cn41,
            &f8, &f9, &f10, &f11, &A, &B, &Cn42
    );
    printf("\ncheck valori alu: %d,%d,%d,%d\n", f8, f9, f10, f11);
    printf("\ncheck ugualizanza terza alu: %d=%d\n", A, B);

    ALU(// 4
            QA12, QB12, QA13, QB13, QA14, QB14, QA15, QB15,
            S0, S1, S2, S3, M, Cn42,
            &f12, &f13, &f14, &f15, &A, &B, &Cn43
    );
    printf("\ncheck valori alu: %d,%d,%d,%d\n", f12, f13, f14, f15);
    printf("\ncheck ugualizanza quarta alu: %d=%d\n", A, B);
    
    ALU(// 5
            QA16, QB16, QA17, QB17, QA18, QB18, QA19, QB19,
            S0, S1, S2, S3, M, Cn43,
            &f16, &f17, &f18, &f19, &A, &B, &Cn44
    );
    printf("\ncheck valori alu: %d,%d,%d,%d\n", f16, f17, f18, f19);
    printf("\ncheck ugualizanza quinta alu: %d=%d\n", A, B);
    
    ALU(// 6
            QA20, QB20, QA21, QB21, QA22, QB22, QA23, QB23,
            S0, S1, S2, S3, M, Cn44,
            &f20, &f21, &f22, &f23, &A, &B, &Cn45
    );
    printf("\ncheck valori alu: %d,%d,%d,%d\n", f20, f21, f22, f23);
    printf("\ncheck ugualizanza sesta alu: %d=%d\n", A, B);
    
    ALU(// 7
            QA24, QB24, QA25, QB25, QA26, QB26, QA27, QB27,
            S0, S1, S2, S3, M, Cn45,
            &f24, &f25, &f26, &f27, &A, &B, &Cn46
    );
    printf("\ncheck valori alu: %d,%d,%d,%d\n", f24, f25, f26, f27);
    printf("\ncheck ugualizanza settima alu: %d=%d\n", A, B);
    
    ALU(// 8
            QA28, QB28, QA29, QB29, QA30, QB30, QA31, QB31,
            S0, S1, S2, S3, M, Cn46,
            &f28, &f29, &f30, &f31, &A, &B, &Cn47
    );
    printf("\ncheck valori alu: %d,%d,%d,%d\n", f28, f29, f30, f31);
    printf("\ncheck ugualizanza ottava alu: %d=%d\n", A, B);


    // registri di output delle alu
    
    int F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31;
            
    printf("\nSezione di registri gli output dell'alu\n");


    sleep(1000);

    printf("\nRegistro 1\n");
    REG(
          f0, f1, f2, f3, f4, f5, f6, f7,
          &F0, &F1, &F2, &F3, &F4, &F5, &F6, &F7
    );

    sleep(1000);

    printf("\nRegistro 2\n");
    REG(
          f8, f9, f10, f11, f12, f13, f14, f15,
          &F8, &F9, &F10, &F11, &F12, &F13, &F14, &F15
    );

    sleep(1000);


    printf("\nRegistro 3\n");
    REG(
          f16, f17, f18, f19, f20, f21, f22, f23,
          &F16, &F17, &F18, &F19, &F20, &F21, &F22, &F23
    );

    sleep(1000);


    printf("\nRegistro 4\n");
    REG(
          f24, f25, f26, f27, f28, f29, f30, f31,
          &F24, &F25, &F26, &F27, &F28, &F29, &F30, &F31
    );

    sleep(1000);

    char VBinO[32];
    
    if(F0==0){VBinO[0]= '0';} else {VBinO[0]= '1';}
    if(F1==0){VBinO[1]= '0';} else {VBinO[1]= '1';}
    if(F2==0){VBinO[2]= '0';} else {VBinO[2]= '1';}
    if(F3==0){VBinO[3]= '0';} else {VBinO[3]= '1';}
    if(F4==0){VBinO[4]= '0';} else {VBinO[4]= '1';}
    if(F5==0){VBinO[5]= '0';} else {VBinO[5]= '1';}
    if(F6==0){VBinO[6]= '0';} else {VBinO[6]= '1';}
    if(F7==0){VBinO[7]= '0';} else {VBinO[7]= '1';}
    if(F8==0){VBinO[8]= '0';} else {VBinO[8]= '1';}
    if(F9==0){VBinO[9]= '0';} else {VBinO[9]= '1';}
    
    if(F10==0){VBinO[10]= '0';} else {VBinO[10]= '1';}
    if(F11==0){VBinO[11]= '0';} else {VBinO[11]= '1';}
    if(F12==0){VBinO[12]= '0';} else {VBinO[12]= '1';}
    if(F13==0){VBinO[13]= '0';} else {VBinO[13]= '1';}
    if(F14==0){VBinO[14]= '0';} else {VBinO[14]= '1';}
    if(F15==0){VBinO[15]= '0';} else {VBinO[15]= '1';}
    if(F16==0){VBinO[16]= '0';} else {VBinO[16]= '1';}
    if(F17==0){VBinO[17]= '0';} else {VBinO[17]= '1';}
    if(F18==0){VBinO[18]= '0';} else {VBinO[18]= '1';}
    if(F19==0){VBinO[19]= '0';} else {VBinO[19]= '1';}
    
    if(F20==0){VBinO[20]= '0';} else {VBinO[20]= '1';}
    if(F21==0){VBinO[21]= '0';} else {VBinO[21]= '1';}
    if(F22==0){VBinO[22]= '0';} else {VBinO[22]= '1';}
    if(F23==0){VBinO[23]= '0';} else {VBinO[23]= '1';}
    if(F24==0){VBinO[24]= '0';} else {VBinO[24]= '1';}
    if(F25==0){VBinO[25]= '0';} else {VBinO[25]= '1';}
    if(F26==0){VBinO[26]= '0';} else {VBinO[26]= '1';}
    if(F27==0){VBinO[27]= '0';} else {VBinO[27]= '1';}
    if(F28==0){VBinO[28]= '0';} else {VBinO[28]= '1';}
    if(F29==0){VBinO[29]= '0';} else {VBinO[29]= '1';}
    
    if(F30==0){VBinO[30]= '0';} else {VBinO[30]= '1';}
    if(F31==0){VBinO[31]= '0';} else {VBinO[31]= '1';}
    
    VBinO[32] = '\0'; // chiude la stringa
    
    
        
    long long VDecO = DEC(VBinO);
    printf("prodotto delle ALU in binario = %s, in decimale = %lld\n", VBinO, VDecO);













    return 0;
}