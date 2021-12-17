// # ARDUINO ALBA--GIORNO-TRAMOMTO con strip led digitale tipo  WS2811 a 99 IC LED

#include <Adafruit_NeoPixel.h>
#define LED_PIN 4
#define Led_StrisciaWS2811 99
#define BRIGHTNESS 254
Adafruit_NeoPixel StrisciaWS2811 = Adafruit_NeoPixel(Led_StrisciaWS2811, LED_PIN, NEO_BRG + NEO_KHZ800);

#define PARTI_NOTTE_BLU 1
#define PARTI_AlbaBLU_GialloTENUE 2
#define PARTI_AlbaGialloTENUE_FORTE 3
#define PARTI_ATTESA_GIORNO 4
#define PARTI_TRAMONTO_GialloFORTE_GialloTENUE 5
#define PARTI_TRAMONTO_GialloTENUE_BLU 6
byte FASE = 0;

#define SpostareLedDX 15 // Nr. IC da spostare SOLO ALBA a DX, (verso Inizio striscia)
#define SpostareLedSX 8 // Nr. IC da spostare SOLO TRAMONTO a SX, (verso Fine striscia)
#define FinirePrimaFasiSX 14 // Nr. IC da NON fare a SX, SOLO PER fase ALBA da BLU a Giallo TENUE!


// *********************************************************************
//  ***********    VARIABILI DA MODIFICARE: ****************************
// *********************************************************************
int AttesaTraCILCI = 5000; //# 50000msec. di attesa TRA I CICLI!
byte LuminositaBluNOTTE = 25; // 30 LUMINOSITA BLU NOTTE!!!
byte LuminositaBluALBA = 25; // 30 LUMINOSITA BLU ALBA!!!

int DurataBluNOTTE = 6500; //# 65000 Durata msec. NOTTE BLU per INIZIO.
int DurataGIORNO = 20000; //# 20.000 Durata msec. GIORNO. max.32700(Deve includere anche il FADE IN BIANCHI!!!

int velocitaAlbaGialloTENUE = 300; //# 300 velocita dal BLU al giallo TENUE.
int velocitaAlbaGialloFORTE = 280; //# 200 velocita dal giallo TENUE al giallo FORTE.

int velocitaTRAMONTOGialloFORTE = 400; //# 400 velocita dal giallo FORTE al giallo TENUE
int velocitaTRAMONTOBLU = 400 ; //# 400 velocita dal giallo TENUE al BLU

int LedBLU = 0; // NON modificare (Serve x variabile "void FASE_PARTI_NOTTE_BLU()")
int DxStripAlbaGialloTENUE = 0; // NON modificare, si sistema da solo.
int SxStripAlbaGialloTENUE = 0; // NON modificare, si sistema da solo.
int DxStripAlbaGialloFORTE = 0; // NON modificare, si sistema da solo.
int SxStripAlbaGialloFORTE = 0; // NON modificare, si sistema da solo.
int FineStripGialloTENUE = 0; // NON modificare, si sistema da solo.
int InizioStripGialloTENUE = 0; // NON modificare, si sistema da solo.
int FineStripBLU = 0; // NON modificare, si sistema da solo.
int InizioStripBLU = 0; // NON modificare, si sistema da solo.
byte CICLO = 1; // NON modificare

// # AVVIO ACCENDO BLU
void AVVIO_ACCENDO_BLU()
{ for (LedBLU = 0; LedBLU < Led_StrisciaWS2811; LedBLU++)
  { StrisciaWS2811.setPixelColor(LedBLU, 0, 0, LuminositaBluNOTTE);
  }  StrisciaWS2811.show();
}   // Fine AVVIO_ACCENDO_BLU(

// # INIZIO: Notte BLU per xx Secondi
void FASE_PARTI_NOTTE_BLU()
{ for (LedBLU = 0; LedBLU < Led_StrisciaWS2811; LedBLU++)
    { StrisciaWS2811.setPixelColor(LedBLU, 0, 0, LuminositaBluNOTTE);
    }  StrisciaWS2811.show();
  if (LedBLU == Led_StrisciaWS2811)
   {
   delay(DurataBluNOTTE); // # Durata BLU NOTTE dopo accensione BLU
   FASE = PARTI_AlbaBLU_GialloTENUE; //# fa partire ciclo ALBA
   }
}   // Fine FASE_PARTI_NOTTE_BLU FISSO


// ** ALBA2: dal BLU al Giallo TENUE, Parte dal CENTRO
void FASE_AlbaBLU_GialloTENUE()
{ drawMantieneBLU(); // #drawMantieneBLU
  drawAlbaGialloTENUE(); } //#Parte dal CENTRO, dal BLU a GialloTENUE

// # START: TUTTO BLU
void drawMantieneBLU() // # MantieneBLU
{ for (int i = 0; i < Led_StrisciaWS2811; i++)
  { StrisciaWS2811.setPixelColor(i, 0, 0, LuminositaBluALBA); }// # BLU
} // # FINE MantieneBLU  


// # ALBA GialloTenue (Parte dal CENTRO)
void drawAlbaGialloTENUE()// # ALBA Fase1 GialloTENUE
{ if (SxStripAlbaGialloTENUE < (Led_StrisciaWS2811))
  { 

  for ( SxStripAlbaGialloTENUE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX); SxStripAlbaGialloTENUE <= (Led_StrisciaWS2811-FinirePrimaFasiSX); SxStripAlbaGialloTENUE++)
    
    { StrisciaWS2811.setPixelColor(SxStripAlbaGialloTENUE, 127, 25, 0); // # ALBA Fase1 Giallo TENUE 
      StrisciaWS2811.setPixelColor(DxStripAlbaGialloTENUE--, 127, 25, 0); // # ALBA Fase1 Giallo TENUE
      StrisciaWS2811.show();
      delay(velocitaAlbaGialloTENUE); // velocizza apparizione AlbaGialloTENUE
    }
  }  FASE = PARTI_AlbaGialloTENUE_FORTE;
} //#  FINE ALBA BLU mantiene AlbaGialloTENUE 



// ** ALBA3: dal Giallo TENUE a GialloFORTE/ROSINO , Parte dal CENTRO
void FASE_AlbaGialloTENUE_FORTE()
{ drawMantieneAlbaGialloTENUE(); // #drawMantieneGialloTENUE
  drawAlbaGialloFORTE(); } //#Parte dal CENTRO, toglie il GialloTENUE e mette GialloFORTE


// # °°°°°°°°° INIZIO: Giallo TENUE°°°°°°°
void drawMantieneAlbaGialloTENUE() // # °°°°°°°°° Giallo TENUE
{ for (int i = 0; i < Led_StrisciaWS2811; i++)
  { StrisciaWS2811.setPixelColor(i, 127, 25, 0); // # Giallo TENUE ALBA 
  }
} // # FINE MantieneGialloTENUE -----------------------------------

// # ALBA GialloFORTE (Parte dal CENTRO)
void drawAlbaGialloFORTE()// # ALBA GialloFORTE
{ if (SxStripAlbaGialloFORTE < (Led_StrisciaWS2811))
  { for ( SxStripAlbaGialloFORTE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX); SxStripAlbaGialloFORTE <= (Led_StrisciaWS2811); SxStripAlbaGialloFORTE++)
    { 
    StrisciaWS2811.setPixelColor(SxStripAlbaGialloFORTE, 255, 40, 25); // # ALBA Fase2  ROSINO
    StrisciaWS2811.setPixelColor(DxStripAlbaGialloFORTE--, 255, 40, 25); // # ALBA Fase2 ROSINO
      StrisciaWS2811.show();
      delay(velocitaAlbaGialloFORTE);
    } // velocizza apparizione Alba FASE2 (rosino) AlbaGialloFORTE
  } 
   
   FASE = PARTI_ATTESA_GIORNO;
}//#  FINE  AlbaGialloTENUE mantiene Giallo  FORTE -----------------------------


// **********************************************************************************
// ** FASE TRAMONTO dal GIALLO FORTE al Giallo TENUE dai due estremi!: ***
// **********************************************************************************

void FASE_TRAMONTO_GialloFORTE_GialloTENUE()
{ drawMantieneGialloFORTE(); // # MantieneGialloFORTE
  drawTRAMONTOGialloFORTE(); } //# Parte dai DUE ESTREMI, toglie il Giallo FORTE e mette il Giallo TENUE


//# INIZIO: Mantiene Giallo FORTE
void drawMantieneGialloFORTE() // # Mantiene GialloFORTE
{ for (int i = 0; i < Led_StrisciaWS2811; i++) 
  { StrisciaWS2811.setPixelColor(i, 255, 55, 0); // # GialloFORTE TRAMONTO
  } 
} // # FINE MantieneGialloFORTE -----------------------------------

// # TRAMONTO SOLE GialloFORTE (Parte dai DUE ESTREMI)
void drawTRAMONTOGialloFORTE()// # TRAMONTO SOLE GialloFORTE;
{ if (InizioStripGialloTENUE != ((Led_StrisciaWS2811 / 2) + SpostareLedSX))
  { for ( InizioStripGialloTENUE = 0; InizioStripGialloTENUE < ((Led_StrisciaWS2811 / 2) + SpostareLedSX); InizioStripGialloTENUE++)
    { StrisciaWS2811.setPixelColor(FineStripGialloTENUE--, 127, 20, 0, 0); // # GialloTENUE Tramonto
      StrisciaWS2811.setPixelColor(InizioStripGialloTENUE, 127, 20, 0, 0); // # GialloTENUE Tramonto
      StrisciaWS2811.show();
      delay(velocitaTRAMONTOGialloFORTE); // velocizza apparizione giallo TENUE
    }
  } FASE = PARTI_TRAMONTO_GialloTENUE_BLU;
} //#  FINE CICLO Giallo Tenue
// ------------ FINE  TRAMONTO dal Giallo FORTE al Giallo TENUE -----------
// *************************************************************************



// *FASE TRAMONTO ***********FASE TRAMONTO *********FASE TRAMONTO ***********FASE TRAMONTO ********FASE TRAMONTO ***********FASE TRAMONTO ********
// ***********************************************************************
void FASE_TRAMONTO_GialloTENUE_BLU()
{ drawMantieneGialloTENUE(); // #drawMantieneGialloTENUE
  drawTRAMONTOBLU(); } //#Parte dai DUE ESTREMI, toglie il GialloTENUE e mette il BLU


// #  INIZIO: Mantiene GialloTENUE
void drawMantieneGialloTENUE() // #  MantieneGIALLOforte
{ for (int i = 0; i < Led_StrisciaWS2811; i++)
  { StrisciaWS2811.setPixelColor(i, 127, 20, 0); // # GialloTENUE
  }
} // # FINE MantieneGialloTENUE -----------------------------------

// # TRAMONTO BLU (Parte dai DUE ESTREMI e va verso il centro striscia)
void drawTRAMONTOBLU()// # TRAMONTO BLU
{ if (InizioStripBLU != ((Led_StrisciaWS2811 / 2) + SpostareLedSX))
  { for ( InizioStripBLU = 0; InizioStripBLU < ((Led_StrisciaWS2811 / 2) + SpostareLedSX); InizioStripBLU++)
    { StrisciaWS2811.setPixelColor(FineStripBLU--, 0, 0, LuminositaBluNOTTE); // # BLU
      StrisciaWS2811.setPixelColor(InizioStripBLU, 0, 0, LuminositaBluNOTTE); // # BLU
      StrisciaWS2811.show();
      delay(velocitaTRAMONTOBLU);
    }
  }
} // Fine CICLO BLU

// ------------ FINE FASE TRAMONTO dal Giallo TENUE al BLU. -----------------
// FASE TRAMONTO ***********FASE TRAMONTO 
void off()  // #SPEGNE TUTTO
{ for (int i = 0; i < Led_StrisciaWS2811; i++)
  { StrisciaWS2811.setPixelColor(i, 0, 0, 0, 0);
  } StrisciaWS2811.show(); }


void FASE_ATTESA_GIORNO()
{ delay(5000);
for (int i = 0; i < Led_StrisciaWS2811; i++) 
  { StrisciaWS2811.setPixelColor(i, 255, 55, 0); StrisciaWS2811.show();}  // #AMBIA LA STRISCIA DA ROSINO A GialloFORTE TRAMONTO
  delay(DurataGIORNO-5000);
  
  FASE = PARTI_TRAMONTO_GialloFORTE_GialloTENUE;
}


// # ========== SETUP ==============
void setup()
{
//seriale-Serial.begin(9600);
delay(200); // #DFplayer ritardo di 1sec.
  StrisciaWS2811.setBrightness(BRIGHTNESS);
  StrisciaWS2811.begin();
  StrisciaWS2811.show(); // #SPEGNE tutta la stiscia

  DxStripAlbaGialloTENUE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX);
  SxStripAlbaGialloTENUE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX);
  DxStripAlbaGialloFORTE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX);
  SxStripAlbaGialloFORTE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX);

  InizioStripGialloTENUE = 0;
  FineStripGialloTENUE = (Led_StrisciaWS2811 + SpostareLedSX);
  InizioStripBLU = 0;
  FineStripBLU = (Led_StrisciaWS2811 + SpostareLedSX);

  FASE = PARTI_NOTTE_BLU; // # SELEZIONE FASE DI PARTENZA
 

delay(300); // #DFplayer ritardo di 1sec.
AVVIO_ACCENDO_BLU();
delay(650); // #DFplayer ritardo di 1sec.

} // # Fine SETUP ----------------------


// # ========== *********************LOOP******************************* ==============
void loop() {

  if (CICLO <= 15)  //# CAMBIARE il numero x cambio nr cicli da FARE !!
  { // cicla:

    //  NOTTE =======================================================
    if (PARTI_NOTTE_BLU == FASE)
    { //seriale-Serial.print(millis()); Serial.println(" FASE_PARTI_NOTTE_BLU ");
      FASE_PARTI_NOTTE_BLU(); }
    //  ALBA =======================================================
    if (PARTI_AlbaBLU_GialloTENUE == FASE)
    { //seriale-Serial.print(millis()); Serial.println(" Inizio_FASE_AlbaBLU_GialloTENUE ");
      FASE_AlbaBLU_GialloTENUE(); }

    if (PARTI_AlbaGialloTENUE_FORTE == FASE)
    { //seriale-Serial.print(millis()); Serial.println(" Inizio_FASE_AlbaGialloTENUE_FORTE ");
      FASE_AlbaGialloTENUE_FORTE(); }


    if (PARTI_ATTESA_GIORNO == FASE)
    { //seriale-Serial.print(millis()); Serial.print(" Inizio_FASE_GIORNO: "); Serial.println(DurataGIORNO);
      FASE_ATTESA_GIORNO();   }

    //  TRAMONTO =======================================================
    if (PARTI_TRAMONTO_GialloFORTE_GialloTENUE == FASE)
    { //seriale-Serial.print(millis()); Serial.println(" Inizio_FASE_TRAMONTO_GialloFORTE_GialloTENUE ");
      FASE_TRAMONTO_GialloFORTE_GialloTENUE();  }

    if (PARTI_TRAMONTO_GialloTENUE_BLU == FASE)
    { //seriale-Serial.print(millis()); Serial.println(" Inizio_FASE_TRAMONTO_GialloTENUE_BLU ");
      FASE_TRAMONTO_GialloTENUE_BLU();
      //seriale-Serial.print(millis()); Serial.println(" Fine_Salita_BLU_MANTIENE_BLU_NOTTE");
    }


if (FASE == 9) { off(); StrisciaWS2811.show(); }

delay(AttesaTraCILCI);

// # RESET NECESSARIO PER FAR RIPARTIRE IL CICLO! ===============================
    CICLO = CICLO + 1;

    DxStripAlbaGialloTENUE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX);
    SxStripAlbaGialloTENUE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX);
    DxStripAlbaGialloFORTE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX);
    SxStripAlbaGialloFORTE = ((Led_StrisciaWS2811 / 2) - SpostareLedDX);
    InizioStripGialloTENUE = 0;
    FineStripGialloTENUE = (Led_StrisciaWS2811 + SpostareLedSX);
    InizioStripBLU = 0;
    FineStripBLU = (Led_StrisciaWS2811 + SpostareLedSX);
    FASE = PARTI_NOTTE_BLU; // # Riparte da FASE NOTTE BLU
 } // Fine IF CICLO

} // FINE Loop
