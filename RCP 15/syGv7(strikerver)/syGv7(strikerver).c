#include "HardwareInfo.c"
//global includes
#include <SetMotor.h>
#include <SetLCDBack.h>
#include <GetCompassB.h>
#include <GetADScable10.h>
#include <GetUltrasound.h>
#include <GetCompoI3.h>
#include <GetTentacle.h>
#include <SetLCD3Char.h>

//global functions
int dynEyeRead(int port){
	if((port>0&&port<8)||port==15){
		if(port==15) port = 1;
		return GetCompoI3(_COMPOUNDEYE3_F_, port);
	} else {
		if(port == 0) port = 14;
		port -= 7;
		return GetCompoI3(_COMPOUNDEYE3_B_, port);
	}
}

int state(int a){
	if(a>0){
		return 0;
	} else {
		return 2;
	}	
}

int absl(int a){
	if(a>0){
		return a;
	} else {
		return -a;
	}	
}

int cap(int value,int upperbnd){
	if(value>upperbnd){
		return upperbnd;
	} else if (value < 0){
		return 0;
	} else {
		return value;
	}
}

int min(int a,int b){
	if(a>b){
		return b;
	} else {
		return a;
	}
}

int main(void)
{
    //define constants
    
    //ultrasound constants
    int ulT = 240;			//horizontal treshold
    int ulBCy = 30;		//vertical border control vertical back treshold
    int hmX = 30;			//relative x home coordinate
    int hmY = 150;			//y home coordinate
    
    //compound eye constants
    char eyeCH = 20;	//begin chase
    int eyeSA = 30;		//begin track
    int eyeSB = 0;		//end chase when in front
    int eyeSK = 300;		//start striking
    
    //movement constants
    int traBC = 85;		//border control treshold
    char cmpM = 30;		//striking compass multiplier
    char mtrMX = 100;
    char rotL = 25; 		//limit to only compass
    char LR = 0;			//leftright 0 = left , 1 = right
    
    
    //arrays
    //motor index
    char mtrI[46] = 
    {0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,9,9,9,9,
    9,9,9,9,9,8,7,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0};
    //motor speed
    //char mtrS[10] = {100,70,47,27,9,-9,-27,-47,-70,-100};
    char mtrS[10] = {100,80,60,40,20,-20,-40,-60,-80,-100};
    //strafe	hash
    int strafe[36] = 
    {0,10,30,70,100,130,150,180,190,190,190,190,190,220,230,240,260,270,
    270,90,100,120,130,140,170,170,170,170,170,180,210,230,260,290,330,350};
    //chase hash
    int chase[36] = 
    {0,10,20,40,50,70,90,100,110,130,140,140,150,150,160,160,170,170,
    180,190,190,200,200,210,210,220,220,230,250,260,270,290,310,320,340,350};
    //aim hash
    //char aim[11] = {0,1,1,2,3,0,0,0,1,2,0};
    char aim[11] = {0,1,1,2,3,0,0,1,2,2,0};
    //sensor variables
    
    //ultrasounds
    int ulX = 0; 			//ultrasound left
    int ulY = 0;			//ultrasound back
    int ulZ = 0;			//ultrasound right
    char ulH = 0;		//ultrasound horizontal conditional
    
    //compound eye
    int eyeFP = 0;		//compound eye front power
    char eyeFD = 0;	//compound eye front direction
    int eyeBP = 0;		//compound eye back power
    char eyeBD = 0;	//compound eye back direction
    int eyePP = 0;		//compound eye top power
    int eyeDR = 0;		//compound eye direction
    unsigned char eyeCP = 0;	//compound eye clockport power
    unsigned char eyeAP = 0;	//compound eye anticlockport power
    int eyeSP = 0;		//compound eye striking power
    
    //cmp
    int cmpR = 0;		//compass read
    int cmpO = 0;		//compass offset
    //movement variables
    
    //scoring
    char strX = 0;		//striking x/z coordinate
    char strY = 0;		//striking y coordinate
    
    //motor
    int traS = 0;			//translational movement speed
    int traD = 0;		//translational movement direction
    int rotS = 0;			//rotational movement speed
    char rotD = 0;		//rotational movement direction
    int mtrM = 0;		//motor border control multiplier
    char mtrC = 0;		//motor power cap
    int mtrP[4] = {0,0,0,0};	//motor power
    int mtrA[4] = {0,0,0,0};	//motor absolute power
    int mtrD[4] = {0,0,0,0};	//motor state
    
    //misc
    int d1 = 0;			//chase portion
    int d2 = 0;			//strafe portion
    int d3 = 0;			//total portion
    char run = 0;		//program run conditional
    int lcd = 0;			//lcd light on/off
    SetLCDBack(1);	//setup lcd light
    while (1)
    {
        //startup loop header
        begin:
        
        //reset variables
        lcd = cap(lcd - 1,1000);
        traS = 0;
        traD = 0;
        rotS = 0;
        rotD = 0;
        ulH = 0;
        d3 = traBC;
        for(int i=0;i<4;i++){
        	mtrP[i]=0;
        }
        mtrM = 100;
        eyeDR = 0;
        cmpO = cmpO * 4 / 5;
        //compass and ultrasound read
        cmpR = GetCompassB(_COMPASS_C_);
        ulX = GetADScable10(_SCABLEAD_X_);
        ulZ = GetADScable10(_SCABLEAD_Z_);
        ulY = GetADScable10(_SCABLEAD_Y_);
        
        //ultrasound derived values and LR
        if( ulX + ulZ > ulT && ulX + ulZ < 400) {
        	ulH = 1;
        	if(ulX<ulZ){
        		LR = 0;
        	} else {
        		LR = 1;
        	}
        }
        
        if(ulX>400) ulX = 0;
        if(ulZ>400) ulZ = 0;
        
        if( ulX > 80 && ulZ > 80 && ulH){
        	ulY += 40;
        }
        
        //compound eye Read
        eyeFP = GetCompoI3(_COMPOUNDEYE3_F_, 9);
        eyeBP = GetCompoI3(_COMPOUNDEYE3_B_, 9);
        
        //startup loopback
        if(run ==0){
        	GetCompoI3(_COMPOUNDEYE3_F_, 14);
        	GetCompoI3(_COMPOUNDEYE3_B_, 14);
        	run = GetTentacle(_TOUCH_T_);
        	goto begin;
        }
                
                
                
        //scoring?
        eyeSP =
        GetCompoI3(_COMPOUNDEYE3_F_, 3)
        + GetCompoI3(_COMPOUNDEYE3_F_, 4)
        + GetCompoI3(_COMPOUNDEYE3_F_, 5);
        traS = 100;
        
        if ( eyeSP > eyeSK )
        {
            //striking
            if ( ulH ) {
            	strY = cap(ulY/45,4); //y coordinate
            	if ( ulX < ulZ ) {
            		//striking from left
            		strX = cap((ulX-30)/40,2); //x coordinate from x
            		cmpO = aim[cap(strX*5+strY,11)]; //pull aim
            		traD = cmpO*10;//modify movement
            		cmpO = 0 - cmpO;//reverse cmpO
            	} else {
            		//striking from right
            		strX = cap((ulZ-30)/40,2);//x coordinate from z
            		cmpO = aim[cap(strX*5+strY,11)];//pull aim
            		traD = 360 - cmpO*10;//modify movement
            	}
            	cmpO *= cmpM;
            	//lcd = 10; //lcd off
            } else {
            	traD = 0;
            }
            
        }
        else
        {
            //compound eye parsing
            eyeFD = GetCompoI3(_COMPOUNDEYE3_F_, 8);
            eyeBD = GetCompoI3(_COMPOUNDEYE3_B_, 8);
            if ( eyeFP>eyeBP ) {
            	eyeDR=eyeFD;
            	eyePP =eyeFP;
            	if( eyeFD<3 || eyeFD>5 ){
            		traS = 66+(160-eyeFP)/3;
            	}
            	traS = 5 - absl(4-eyeFD);
            	traS = 100 - 10*traS + traS * (145 - eyeFP) / 3;
            } else {
            	eyeDR=eyeBD+7;
            	eyePP =eyeBP;
            	if( eyeBD<3 || eyeBD>5 ){
            		traS = 80+(160-eyeBP)/5;
            	}
            }
            eyeCP = dynEyeRead(eyeDR+1);
            eyeAP = dynEyeRead(eyeDR-1);
            
            if(eyeFP>eyeBP){
            	eyeDR = 240+(30*eyeFD);
            } else {
            	eyeDR = 60+(30*eyeBD);
            }
            eyeDR = (((eyeCP-eyeAP)/4)+eyeDR)%360;
            d2 = eyeSA;
            if(ulY>200){
            	d2 += eyeSB;
            }
            
            if ( eyePP<d2 && (eyeDR<90||eyeDR>270) )
            {
                if(absl(ulY-hmY<15)&&eyePP>eyeCH){
                	traS = cap(absl(ulY-hmY),40);
                	if(eyeDR>180){
                		if ( ulY>hmY ){
                			traD = 260;
                		} else {
                			traD = 280;
                		}
                		traS += 2*cap(eyeDR,25);
                	} else {
                		if ( ulY>hmY ){
                			traD = 100;
                		} else {
                			traD = 80;
                		}
                		traS += 2*cap(360-eyeDR,25);
                	}
                	d3 *= 5/3;
                } else {
                	if ( ulX + hmX > ulZ ){
                		if ( ulY>hmY ){
                			traD = 220;
                		} else {
                			traD = 320;
                		}
                	} else {
                		if ( ulY>hmY ){
                			traD = 140;
                		} else {
                			traD = 40;
                		}
                	}
                	traS=cap(absl(ulX-ulZ+hmX)+absl(ulY-hmY)+10,50); //align to base power
                	traS = 0;
                }
                if(traS<20){
                	traS = 0; //stop if distance less than 20
                }
                lcd = 5;
                
            }
            else
            {
                if(eyeDR<90||eyeDR>270){
                	//sechs
                	if ( eyeDR<=60 ) d1=eyeDR*2/3;
                	else d1=eyeDR>=300?(360-eyeDR)*2/3:90;
                	if ( eyeDR<=180) traD=eyeDR+cap((d1*eyePP)/60,95);
                	else if ( eyeDR>180 ) traD=eyeDR-cap((d1*eyePP)/60,95);
                	else traD=eyeDR;
                
                } else {
                	//neil aog
                	if ( eyeDR<=60 ) d1=eyeDR*2/3;
                	else d1=eyeDR>=300?(360-eyeDR)*2/3:90;
                	if ( eyeDR<=180) traD=eyeDR+cap((d1*eyePP)/135,95);
                	else if ( eyeDR>180 ) traD=eyeDR-cap((d1*eyePP)/135,95);
                	else traD=eyeDR;
                }
                
                cmpO = 0;
            }
            //horizontal border control and lr
            //border control
            if ( LR==0 ) {
            	if ( traD > 180 && traD < 360 ){
            		mtrM = cap((ulX - d3) * 4,100);
            	} else if(ulX+ulZ< 100&&ulX+ulZ>80){ //ulX+ulZ< 100&&ulX+ulZ>80
            		if (ulY < ulBCy && traD > 90) {
            			mtrM = cap((ulY - ulBCy) * 4,100);
            		}
            	}
            } else {
            	if (traD > 0 && traD < 180 ){ 
            		mtrM = cap((ulZ - d3)* 4,100);
            	} else if (ulX+ulZ< 100&&ulX+ulZ>80){//ulX+ulZ< 100&&ulX+ulZ>80
            		if (ulY < ulBCy && traD < 270 ){
            			mtrM = cap((ulY - ulBCy) * 4,100);
            		}
            	}
            }
            traS *= mtrM / 100;
        }
        //compass align
        //cmpR += cmpO/10;
        cmpR = cmpR%360;
        if ( cmpR < 180 ) {
        	rotD = 1;
        	rotS = cmpR;
        } else {
        	rotD = 0;
        	rotS = 360 - cmpR;
        }
        
        if(rotS>rotL){
        	traS = 0;
        }
        //parse movment commands to raw power
        traD = traD/10%36;
        
        traS = cap(traS,mtrMX);
        rotS = cap(rotS,30);
        rotS = rotS * rotS / 20;
        
        //calibrate compass prog;
        /*
        traD = 0;
        traS = 5;
        rotD = 1;
        rotS = 3;
        */
        
        mtrP[0] = mtrP[3] = traS * mtrS[ mtrI[ traD+9 ] ] / 100;
        mtrP[1] = mtrP[2] = traS * mtrS[ mtrI[ traD ] ] / 100;
        
        if(rotD == 0){
        	mtrP[0] -= rotS;
        	mtrP[1] += rotS;
        	mtrP[2] -= rotS;
        	mtrP[3] += rotS;
        } else {
        	mtrP[0] += rotS;
        	mtrP[1] -= rotS;
        	mtrP[2] += rotS;
        	mtrP[3] -= rotS;
        }
        
        //scale movement
        for(int i=0;i<4;i++){
        	mtrA[i] = absl(mtrP[i]);
        	mtrD[i] = state(mtrP[i]);
        }
        
        mtrC = traS +  rotS;
        
        if( mtrC > 100 ){
        	for(int i=0;i<4;i++){
        		mtrA[i] = mtrA[i] * 100 / mtrC;
        	}
        }
        
        //send movement
        SetMotor(_MOTOR_NE_, mtrD[0], mtrA[0]);
        SetMotor(_MOTOR_NW_, mtrD[1], mtrA[1]);
        SetMotor(_MOTOR_SE_, mtrD[2], mtrA[2]);
        SetMotor(_MOTOR_SW_, mtrD[3], mtrA[3]);
        
        //lcd stuffs
        SetLCD3Char(1,ulY);
        SetLCD3Char(5,traD);
        SetLCD3Char(9,traS);
        SetLCD3Char(13, mtrM);
        
        //SetLCDBack(lcd == 0);
        SetLCDBack(lcd);
    }
    return 1;
}

