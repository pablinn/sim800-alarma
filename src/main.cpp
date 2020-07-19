
#define DEBUG Serial.println(debug())
#define deb true  // modo true muestras respuestas modo false solo salidas logicas


#include <Arduino.h>

#include <SoftwareSerial.h>
SoftwareSerial sim800l(10,11); //RX - TX  


int sl=1000;
  
bool res_at(char *buf,char *patern)
{ 
  char *ptr;
  ptr = strstr(buf, patern);

   if (ptr !=0){
               return true;
               }else{
               return false;
               }
}

char *debug()
{

char cad[255]="";
//char c='\n';

        int i=0;
        strcpy(cad,"");
        while(sim800l.available()>0)
        {
         char c=sim800l.read();
         cad[i]=c;
         i++;
        }
       cad[i+1]='\r\n';
return cad;
}


//devuelve true o false  segun la cadena de respuesta con opcion a debug
bool depurar(char *ret1){
	
	
    	#if deb
	     char cad[100];     
		 strcpy(cad,debug());
		 Serial.println(cad);
	     if (res_at(cad,ret1)){ return true;} else {return false ;}    
		#else
	     if (res_at(debug(),ret1)){ return true;} else {return false ;}    
		#endif
}

////////////////////////////////primitivas//////////////////////////////////////////////////////////

bool CSTT( char *APN, char *USR, char *PAS){
	//AT+CSTT=\"wap.gprs.unifon.com.ar\",\"wap\",\"wap\"")
	
	char cad[100];
	
	    strcpy(cad,"AT+CSTT=\"");
	    strcat(cad,APN);
	    strcat(cad,"\",\"");
	    strcat(cad,USR);
	    strcat(cad,"\",\"");
	    strcat(cad,PAS);
	    strcat(cad,"\"");
	    
	    
	    sim800l.println(cad);
	    delay(5000);
        return depurar("OK");
	}
	
bool CMGF(){
		sim800l.println(F("AT+CMGF=1"));
		delay(sl);
	    return depurar("OK");
}	
 

bool FMOPEN() {
		sim800l.println(F("AT+FMOPEN=0"));
		delay(sl);
		return depurar("OK");
	}
	
	
bool FMFREQ(){ 

		sim800l.println(F("AT+FMFREQ=1011"));
		delay(sl);
		return depurar("OK");
}


bool FMCLOSE(){
		sim800l.println(F("AT+FMCLOSE"));
		delay(sl);
		return depurar("OK");
}

bool ATA(){
		sim800l.println(F("ATA"));
		delay(sl);
		return depurar("OK");
}


bool CHFA(){
		sim800l.println(F("AT+CHFA=0"));
		delay(sl);
		return depurar("OK");
}

bool CMIC(){
		sim800l.println(F("AT+CMIC=0,15"));
		delay(sl);
		return depurar("OK");
}


bool CSDH(){
		sim800l.println(F("AT+CSDH=1"));
		delay(sl);
		return depurar("OK");
}

bool CMGR(){	
		sim800l.println(F("AT+CMGR=1"));
		delay(sl);
		return depurar("OK");
}

bool CPMS(){

		sim800l.println(F("AT+CPMS?"));
		delay(sl);
		return depurar("OK");
    
}

bool  CNTPCID(){
	
		sim800l.println(F("AT+CNTPCID=1"));
		delay(sl);
		return depurar("OK");
}

bool CNTP(){
	
		sim800l.println(F("AT+CNTP"));
		delay(sl);
		return depurar("OK");
}	

bool CCLK(){
		sim800l.println(F("AT+CCLK?"));
		delay(sl);
		return depurar("OK");
}
////////////////////////////////////////////////////////////////////////////////////
 
 bool COPS(){
		sim800l.println(F("AT+COPS?"));
		delay(sl);
	    return depurar("OK");
}	

bool COPS1(){
		sim800l.println(F("AT+COPS=?"));
		delay(sl);
	    return depurar("OK");
}	

bool CMGS_SMS(char *num , char *txt){
	 //envia un sms +pais-area-celular 140 caracteres
 char cad_n[70]	;
 
		
		
		//AT+CMGS=\"+542996321848\"
		strcpy(cad_n,"AT+CMGS=\"");
		strcat(cad_n,num);
		strcat(cad_n,"\"");
	    
		if (CMGF()){
                   
                   sim800l.println(cad_n); 
                   delay(sl); 
                   
				   if(res_at(debug(),">")){					   
					   
                     sim800l.println(txt);
                     delay(sl);
                     sim800l.println();
                     delay(sl);
                     sim800l.write(0x1A); //^Z
                     delay(sl);
                     //return depurar("OK SEND");
                     
                    }
	               return true;      
	         }else {return false;}
	         
}	
		
bool ATD(char *num){
 //llamadas
 	char cad[30];
 	
		strcpy(cad,"ATD");
		strcat(cad,num),
		strcat(cad,";"),
	
		sim800l.println(cad);
		delay(sl);
		return depurar("OK");
  
}	
	
bool CIICR(){	
		
		
		sim800l.println(F("AT+CIICR"));
		delay(sl*5);
		return depurar("OK");
   } 
   
bool CIFSR(){   
		sim800l.println(F("AT+CIFSR"));
		delay(sl);
		return depurar("OK");
	
}


bool CIPSHUT(){
	
		sim800l.println(F("AT+CIPSHUT"));
		delay(sl);
		return depurar("SHUT OK");
}


bool CPIN(){
		sim800l.println(F("AT+CPIN?"));
		delay(sl);
		return depurar("READY");		
		
}

bool CGREG(){
	    sim800l.println(F("AT+CGREG=1"));
		delay(sl);
		return depurar("OK");			
}


bool CSQ(){
//intensidad de la señal dBm RSSI
		sim800l.println(F("AT+CSQ"));
		delay(sl);
		return depurar("OK");		
}


void strtokk(char *cad,int par){

char *word;
int i;

	word = strtok(cad, ",");
	Serial.println(word);
	
	for (i=0;i<par;i++){
    
	word = strtok(NULL, ",");
	Serial.print("Parametro -->");
	Serial.print(word);
	//Serial.println(uni[i]);
	}
}

void CBC(){
//alimentacion 1 , 2(% bat) , 3(mV)  ->4200 ideal
String uni[]={" %"," mV"};
char *word;
char cad[100];
int i;

		sim800l.println(F("AT+CBC"));
		delay(sl);			
		strcpy(cad,debug());
        
		word = strtok(cad, ",\r\n");
		word = strtok(NULL, ",\r\n");
		word = strtok(NULL, ",\r\n");
		
        for(i=0;i<2;i++)
        {
		Serial.print(word);		
	    Serial.println(uni[i]);	 
	    word = strtok(NULL, ",\r\n");
	    
		}
		
}


bool CADC(){
// ? corriente

	sim800l.println(F("AT+CADC?"));
    delay(sl);
    return depurar("OK");
}

bool CCID(){
// sim ccid

	sim800l.println(F("AT+CCID"));
    delay(sl);
    return depurar("OK");
}


bool CIPGSMLOC(){
	
// lat long fecha y hora +CIPGSMLOC: 0,-67.798958,-37.881168,2016/09/25,21:41:30 
//GPS funcion

		sim800l.println(F("AT+CIPGSMLOC=1,1"));
		delay(sl);
        return depurar("OK");
}



bool CGATT_0(){
		
		sim800l.println(F("AT+CGATT=0"));
		delay(sl);
		return depurar("OK");

}	
	
bool CGATT_1(){
		
		sim800l.println(F("AT+CGATT=1"));
		delay(sl);
		return depurar("OK");

}		






bool SAPBR_0(){
 	
		sim800l.println(F("AT+SAPBR=0,1"));
		delay(sl);
		return depurar("OK");
}

bool SAPBR_1(){
 	
		sim800l.println(F("AT+SAPBR=1,1"));
		delay(sl);
		return depurar("OK");
}

bool SAPBR_2(){
 	
		sim800l.println(F("AT+SAPBR=2,1"));
		delay(sl);
		return depurar("OK");
}


bool SAPBR_3(char *cad1, char *cad2){
	
	char cad[100];
	//sim800l.println(F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""));
	
	    strcpy(cad,"");
        strcpy(cad,"AT+SAPBR=3,1,");
        strcat(cad,"\"");
        strcat(cad,cad1); 
        strcat(cad,"\",\"");
        strcat(cad,cad2); 
        strcat(cad,"\"");
	
		sim800l.println(cad);
		
		delay(sl);
		return depurar("OK");
    
}


/*Primitivas TCP*/   

bool CIPCLOSE(){
		sim800l.println(F("AT+CIPCLOSE"));
		delay(sl);
		return depurar("OK");
    }
    
bool CIPSTART(char *proto,char *ip,char *port){
	
	    char cad[30];
	    //sim800l.println(F("AT+CIPSTART=\"TCP\",\"www.google.com.ar\",\"80\""));
	    strcpy(cad,"");
	    strcat(cad,"AT+CIPSTART=\"");
	    strcpy(cad,proto);
	    strcpy(cad,"\",\"");
	    strcpy(cad,ip);
	    strcpy(cad,"\",\"");
	    strcpy(cad,port);
	    strcpy(cad,"\"");
	    
	    sim800l.println(cad);
		delay(sl);
		return depurar("OK");
   } 
        
bool CIPSEND(){

		sim800l.println(F("AT+CIPSEND=14"));
		delay(sl);
        if(res_at(debug(),">")){
			Serial.println(F("GET / HTTP/1.1"));	
			sim800l.println(F("GET / HTTP/1.1"));
			delay(sl);
			sim800l.println();
			delay(sl);
			sim800l.write(0x1A);
			delay(sl);
         }
     
        return depurar("SEND OK");
     
     
}



/*Primitivas HTTP*/   
bool HTTPINIT(){
	
		sim800l.println(F("AT+HTTPINIT"));
		delay(sl);
		return depurar("OK");
}
    

bool HTTPPARA_CID(){
		sim800l.println(F("AT+HTTPPARA=\"CID\",1"));
		delay(sl);
		return depurar("OK");
}

bool HTTPPARA_REDIR(){
		sim800l.println(F("AT+HTTPPARA=\"REDIR\",1"));
		delay(sl);
		return depurar("OK");
}

bool HTTPPARA_BR(){
		sim800l.println(F("AT+HTTPPARA=\"BREAK\",2000"));
		delay(sl);
		return depurar("OK");
}

bool HTTPPARA_IP(char *ip){
char cad[100];
	
		strcpy(cad,"");
		strcat(cad,"AT+HTTPPARA=\"PROIP\",\"");
		strcat(cad,ip);
		strcat(cad,"\"");
		
		sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}
bool HTTPPARA_PORT(char *port){
char cad[100];
	
		strcpy(cad,"");
		strcat(cad,"AT+HTTPPARA=\"PROPORT\",\"");
		strcat(cad,port);
		strcat(cad,"\"");
		
		sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}

bool HTTPPARA_URL(char *url){

char cad[100];
		
		strcpy(cad,"");
		strcat(cad,"AT+HTTPPARA=\"URL\",\"");
		strcat(cad,url);
		strcat(cad,"\"");
		sim800l.println(cad);
		//sim800l.println(F("AT+HTTPPARA=\"URL\",\"www.adafruit.com/testwifi/index.html"));
		delay(sl);
		return depurar("OK");
}


bool HTTPACTION(){
		sim800l.println(F("AT+HTTPACTION=0"));
		delay(sl*6);
		//return depurar("OK");
		DEBUG;
 
}


bool HTTPACTION_1(){
		sim800l.println(F("AT+HTTPACTION=1"));
		delay(sl);
		return depurar("OK");
		DEBUG;
 
}


bool HTTPSTATUS(){
		sim800l.println(F("AT+HTTPSTATUS?"));
		delay(sl);
		return depurar("OK");
 
}

bool HTTPDATA(){
		sim800l.println(F("AT+HTTPDATA=100,10000"));
		delay(sl);
		return depurar("OK");
 
}


bool HTTPREAD(){

		sim800l.println(F("AT+HTTPREAD"));
		delay(sl*6);
		return depurar("OK");
		DEBUG;
		DEBUG;			
	int length=75;
	
	 while (length > 0) {
          while (sim800l.available()) {
            char c = sim800l.read();

            // Serial.write is too slow, we'll write directly to Serial register!
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
            loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until data register empty. */
            UDR0 = c;
#else
            Serial.write(c);
#endif
            length--;
            if (! length) break;
          }
        }
        Serial.println(F("\n****"));
       // fona.HTTP_GET_end();
       // break;
      }
		


bool HTTPTERM(){
		sim800l.println(F("AT+HTTPTERM"));
		delay(sl);
		return depurar("OK");
}
   

/*Primitivas FTP*/   
bool FTPCID(){
		sim800l.println(F("AT+FTPCID=1"));
		delay(sl);
		return depurar("OK");
}

   
bool FTPSERV(char *ip){
	    char cad[50];
	    
	    strcpy(cad,"");
	    strcat(cad,"AT+FTPSERV=");
	    strcat(cad,"\"");
	    strcat(cad,ip);
	    strcat(cad,"\"");
	    sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}

bool FTPUN(char *user){
	    char cad[50];
	    
	    strcpy(cad,"");
	    strcat(cad,"AT+FTPUN=");
	    strcat(cad,"\"");
	    strcat(cad,user);
	    strcat(cad,"\"");
	    sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}


bool FTPPW(char *pass){
	    char cad[50];
	    
	    strcpy(cad,"");
	    strcat(cad,"AT+FTPPW=");
	    strcat(cad,"\"");
	    strcat(cad,pass);
	    strcat(cad,"\"");
	    sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}

bool FTPGETNAME(char *arch){
	    char cad[50];
	    
	    strcpy(cad,"");
	    strcat(cad,"AT+FTPGETNAME=");
	    strcat(cad,"\"");
	    strcat(cad,arch);
	    strcat(cad,"\"");
	    sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}

bool FTPGETPATH(char *path){
         char cad[30];
	    
	    strcpy(cad,"");
	    strcat(cad,"AT+FTPGETPATH=");
	    strcat(cad,"\"");
	    strcat(cad,path); // --> /
	    strcat(cad,"\"");
	    sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}

bool FTPGET_1(){
	    sim800l.println(F("AT+FTPGET=1"));
		delay(sl);
		return depurar("OK");
}

bool FTPGET_2(){
	    sim800l.println(F("AT+FTPGET=2,1024"));
		delay(sl);
		return depurar("OK");
}

bool FTPPUTNAME(char *arch){
	    char cad[30];
	    
	    strcpy(cad,"");
	    strcat(cad,"AT+FTPPUTNAME=");
	    strcat(cad,"\"");
	    strcat(cad,arch);
	    strcat(cad,"\"");
	    sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}

bool FTPPUTPATH(char *path){
	    char cad[30];
	    
	    strcpy(cad,"");
	    strcat(cad,"AT+FTPPUTPATH=");
	    strcat(cad,"\"");
	    strcat(cad,path); // --> /
	    sim800l.println(cad);
		delay(sl);
		return depurar("OK");
}

bool FTPPUT_1(){
	    sim800l.println(F("AT+FTPPUT=1"));
		delay(sl);
		return depurar("OK");
}

bool FTPPUT_2(){
	    sim800l.println(F("AT+FTPPUT=2,1024"));
		delay(sl);
		return depurar("OK");
}

bool FTPDELE(){
	    sim800l.println(F("AT+FTPDELE"));
		delay(sl);
		return depurar("OK");
}

bool FTPSIZE(){
	    sim800l.println(F("AT+FTPSIZE"));
		delay(sl);
		return depurar("OK");
}


bool FTPMKD(){
	    sim800l.println(F("AT+FTPMKD"));
		delay(sl);
		return depurar("OK");
}

bool FTPRMD(){
	    sim800l.println(F("AT+FTPRMD"));
		delay(sl);
		return depurar("OK");
}


bool FTPLIST(){
	    sim800l.println(F("AT+FTPLIST"));
		delay(sl);
		return depurar("OK");
}

bool FTPLIST_1(){
	    sim800l.println(F("AT+FTPLIST=2,1024"));
		delay(sl);
		return depurar("OK");
}



///////////////////////////Implementaciones////////////////////////////////////////////////////////////////////////////////


/*GPRS FUNCTIONS*/

void conf_br(){
	
		SAPBR_3("Contype","GPRS");
		SAPBR_3("APN","wap.gprs.unifon.com.ar");
		SAPBR_3("USER","wap");	    
		SAPBR_3("PWD","wap");	
		CSTT("wap.gprs.unifon.com.ar","wap","wap");    
		SAPBR_1();//enable gprs
		SAPBR_2();// ret ip
        CIICR();
        //SAPBR_0(); fin
}


void act_gprs(){
//activa el GPRS para poder usar TCP UDP o HTTP(get/post) usando una APN
  		
	CIPSHUT();
	    
  	CGATT_1();
  	
  	SAPBR_3("Contype","GPRS");
    SAPBR_3("APN","wap.gprs.unifon.com.ar");	
    
	CSTT("wap.gprs.unifon.com.ar","wap","wap");
	    
    SAPBR_3("USER","wap");	
    
    SAPBR_3("PWD","wap");	
       

    SAPBR_0();
    	
	CIICR();	

}

void des_gprs(){
	//desactiva el GPRS al iniciar por si hay alguna falla luego hay q activarlo
	CIPSHUT();
    SAPBR_0();	 
	CGATT_0();	
    
}


void apn_gprs(){
		
		
	CSTT("wap.gprs.unifon.com.ar","wap","wap");
        
    CIICR();
        
    CIFSR();
    
}


void fin_br(){
		SAPBR_0();
		HTTPTERM();
}


/*HTTP FUNCTIONS*/

void http_get(){
 HTTPINIT();
 HTTPPARA_CID();    //="CID",1   //2p
 HTTPPARA_URL("www.mercadolibre.com.ar/index.html");
 HTTPACTION();
 HTTPREAD(); //devuelve cantidad de byte al UART
 HTTPTERM();
}



void http_post(){
 HTTPINIT();
 HTTPPARA_CID();   //="CID",1   //2p
 HTTPPARA_URL("www.adafruit.com/testwifi/index.html");    //="URL","www.google.com.ar"   //2p
 HTTPDATA();       //=100,10000    //100 bytes 10000 miliseg
 HTTPACTION_1();   //=1
 
 HTTPTERM();
}


void http_get_proxy(){
 HTTPINIT();
 HTTPPARA_CID();  
 HTTPPARA_URL("www.adafruit.com/testwifi/index.html");
 HTTPPARA_IP("192.168.51.24"); 
 HTTPPARA_PORT("80");
 HTTPACTION();
 HTTPREAD();
 HTTPTERM();
}


void http_redirection(){
 HTTPINIT();
 HTTPPARA_CID();
 HTTPPARA_REDIR();
 HTTPPARA_URL("www.google.com.ar/index.html");
 HTTPACTION();
 HTTPREAD();
 HTTPTERM();
}


void http_get_break(){
 HTTPINIT();
 HTTPPARA_CID();
 HTTPPARA_URL("www.google.com.ar/xxxxx.gif");
 HTTPPARA_BR();
 HTTPACTION();
 HTTPREAD();
 HTTPTERM();
}


void http_status(){
 HTTPINIT();
 HTTPPARA_CID();
 HTTPPARA_URL("www.google.com.ar");
 HTTPACTION();
 HTTPSTATUS();
 HTTPACTION_1();
 HTTPSTATUS();
 HTTPTERM();
}



/*FTP FUNCTIONS*/

void ftp_get(){
		FTPCID();
		FTPSERV("156.123.45.8");
		FTPUN("user");
		FTPPW("pass");
		FTPGETNAME("123.jpg");
		FTPGETPATH("/");
		FTPGET_1();		
		FTPGET_2();

}

void ftp_put(){
		FTPCID();
		FTPSERV("156.123.45.8");
		FTPUN("user");
		FTPPW("pass");		
		FTPPUTNAME("file");
		FTPPUTPATH("/");
		FTPPUT_1();
		FTPPUT_2();
		
		//AT+FTPPUT=2,0 //no show

}

void ftp_del(){
		FTPCID();
		FTPSERV("156.123.45.8");
		FTPUN("user");
		FTPPW("pass");		
		FTPGETNAME("123.jpg");
		FTPGETPATH("/");		
		FTPDELE();
}


void ftp_size_file(){
		FTPCID();
		FTPSERV("156.123.45.8");
		FTPUN("user");
		FTPPW("pass");		
		FTPGETNAME("123.jpg");
		FTPGETPATH("/");		
		FTPSIZE();

}

void ftp_mkdir(){
		FTPCID();
		FTPSERV("156.123.45.8");
		FTPUN("user");
		FTPPW("pass");		
		FTPGETNAME("123.jpg");
		FTPGETPATH("/");		
		FTPMKD();

}

void ftp_rm(){
	FTPCID();
		FTPSERV("156.123.45.8");
		FTPUN("user");
		FTPPW("pass");		
		FTPGETNAME("123.jpg");
		FTPGETPATH("/");		
		FTPRMD();

}


void ftp_list(){
	    FTPCID();
		FTPSERV("156.123.45.8");
		FTPUN("user");
		FTPPW("pass");		
		FTPGETNAME("123.jpg");
		FTPGETPATH("/");		
		FTPLIST();
		FTPLIST_1();
}



/*TCP FUNCTIONS*/   


void tcp_cli_con(){
		CPIN();  
		CSQ();   
		//CREG?();
        //CGATT?();
        CSTT("wap.gprs.unifon.com.ar","wap","wap");
		CIICR();
		CIFSR();
        CIPSTART("TCP","www.google.com.ar","80");
        CIPSEND ();  // //> control Z 0x1A send ok
        CIPCLOSE();      
}


void udp_cli_con(){
	CPIN();  
		CSQ();   
		//CREG?();
        //CGATT?();
        CSTT("wap.gprs.unifon.com.ar","wap","wap");
		CIICR();
		CIFSR();
		CIPSTART("UDP","www.google.com.ar","80");
		CIPSEND ();  // //> control Z 0x1A send ok
        CIPCLOSE();      
}



void tcp_ser_con(){
		CPIN();  
		CSQ();   
		//CREG?();
        //CGATT?();

//AT+CIPSERVER=1,1024
		CIFSR();
//AT+CIPSTATUS

		CIPSEND();

//AT+CIPSERVER=0
		CIPCLOSE();
}



/*EMAIL FUNCTIONS */




void listo(){
		
	CPIN();    
    CGREG();     
	CSQ();
	CBC();
	CIPGSMLOC();
}

 


void tcp_gprs_cli(){    
    des_gprs();
    act_gprs();
    apn_gprs();       
         
     CIPSTART("TCP","www.google.com.ar","80");
    
    CIPSEND();   
 
	CIPCLOSE();   
   
	CIPSHUT();
}


void fm_on()// encender radio fm M Freq (eg 1011 == 101.1 MHz): 1011
{
	
	
	FMOPEN();
	
	FMFREQ();

	}

void fm_off()//apagar radio fm
{
	
	FMCLOSE();
}




void cor_llam() //cortar llamdaa
{
	
	CHFA();
	CMIC();
	
}
	
void ate_llam() //atender llamada
{
	ATA();

}


void cant_sms()
{
	CMGF();
	CPMS();
}
	
void lee_sms()
{
	CMGF();
	CSDH();
	CMGR();
	
}	
	

/*
bool env_sms() //envia un sms +pais-area-celular 140 caracteres
{
 sim800l.println(F("AT+CMGF=1"));
 delay(sl);
 if (res_at(debug(),"OK")){
 sim800l.println(F("AT+CMGS=\"+542996321848\""));
 delay(500); 
   if(res_at(debug(),">")){
     sim800l.println(F("ardu rack"));
     delay(sl);
     sim800l.println();
     delay(sl);
     sim800l.write(0x1A); //^Z
     delay(sl);
     return true;
    }
  }else{
	  return false;}
}
*/ 

	
void ntp_time()//hora ntp funciona con gprs activado
{
	CNTPCID();
	CNTP();
	CCLK();
	
	}	






void setup() {
		Serial.begin(115200);
		sim800l.begin(9600);
		Serial.println("************************");
		
		conf_br();
		http_get();
		
		
		
		
		//CMGS_SMS("+542996321848","Hola Mundo");
		/*COPS();
		COPS1();
		
		ATD("+573116133002﻿");//+573114378590  //+573116133002﻿
		delay(10000);
		DEBUG;
		//cor_llam();
	*/
		
    

}

void loop() {
 
 //sim800l 002        cel+573114378590
 
 
 //cel 002   sim800 590
 
 
 
  // put your main code here, to run repeatedly
        
/*switch(estado)
{
	case LISTO:{
		        if (listo())
		        {
				 estado=ACT_GPRS;
				 break;
				 }
		       }
		       
	case ACT_GPRS:{
		         if(act_gprs())	       
		         {
					estado= HAC_LLAM;
					break;
				 }	
			   }	
}*/


}
