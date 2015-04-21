#include "HardwareInfo.c"
#include <SetMotor.h>
#include <SetLCDBack.h>
#include <GetCompassB.h>
#include <GetADScable10.h>
#include <GetUltrasound.h>
#include <GetCompoI3.h>
#include <GetTentacle.h>
#include <SetLCD3Char.h>

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

int main(void)
{
    SetMotor(_MOTOR_NE_, 1, 100);
    SetMotor(_MOTOR_NW_, 1, 100);
    SetMotor(_MOTOR_SE_, 1, 100);
    SetMotor(_MOTOR_SW_, 1, 100);
    //init variables
    
    //ultrasounds
    int ulX = 0;
    int ulY = 0;
    int ulZ = 0;
    char ulH = 0;
    
    //eye
    int eyeFP = 0;
    char eyeFD = 0;
    int eyeBP = 0;
    char eyeBD = 0;
    int eyePP = 0;
    int eyeDR = 0;
    unsigned char eyeCP = 0;
    unsigned char eyeAP = 0;
    int eyeSP = 0;
    
    //cmp
    int cmpR = 0;
    int cmpO = 0;
    //char cmpM = 0;
    
    //scoring
    char strX = 0;
    char strY = 0;
    //char aim[11] = {0,1,1,2,3,0,0,0,1,2,0};
    char aim[11] = {1,1,2,3,3,0,0,1,2,3,0};
    
    //motor
    int traS = 0;
    int traD = 0;
    int rotS = 0;
    char rotD = 0;
    int mtrM = 0;
    char mtrC = 0;
    int mtrP[4] = {0,0,0,0};
    int mtrA[4] = {0,0,0,0};
    int mtrD[4] = {0,0,0,0};
    
    //misc
    char run = 0;
    char lcd = 0;
    char mtrI[46] = {0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0};
    char mtrS[10] = {100,70,47,27,9,-9,-27,-47,-70,-100};
    //int chase[28] = {18,19,20,20,21,22,23,0,1,2,2,3,4,5,6,7,8,8,9,10,11,12,13,14,14,15,16,17};
    //int strafe[28] = {13,15,17,19,21,23,0,0,1,3,5,7,9,11,12,13,14,15,16,17,18,6,7,8,9,10,11,12};
    //experimental 	
    int chase[28] = {12,14,16,18,20,23,0,0,1,3,6,8,10,12,12,12,12,11,10,9,8,8,9,10,11,12,12,12};
    int strafe[28] = {12,12,14,16,18,21,23,1,3,6,8,10,12,12,12,12,3,3,5,6,6,6,6,7,9,9,12,12};
    
    //Define Constants
    
    int ulT = 220;
    int hmX = 40;
    int hmY = 70;
    char eyeCH = 10;
    char eyeSA = 250;
    int eyeSK = 360;
    char cmpM = 2;
    SetLCDBack(1);
    while (1)
    {
        //Startup loop
        begin:
        
        //Reset variables
        lcd = cap(lcd - 1,100);
        traS = 0;
        traD = 0;
        rotS = 0;
        rotD = 0;
        ulH = 0;
        for(int i=0;i<4;i++){
        	mtrP[i]=0;
        }
        mtrM = 100;
        eyeDR = 0;
        cmpO = cmpO * 9 / 10;
        cmpR = GetCompassB(_COMPASS_C_);
        ulX = GetADScable10(_SCABLEAD_X_);
        ulZ = GetADScable10(_SCABLEAD_Z_);
        ulY = GetUltrasound(_ULTRASOUND_Y_);
        //ulX *= 2 ;
        //ulZ *= 2 ;
        
        if( ulX + ulZ > ulT ) {
        	ulH = 1;
        }
        
        if( ulX > 80 && ulZ > 80 && ulH){
        	ulY += 15;
        }
        eyeFP = GetCompoI3(_COMPOUNDEYE3_F_, 9);
        eyeBP = GetCompoI3(_COMPOUNDEYE3_B_, 9);
        if(run ==0){
        	GetCompoI3(_COMPOUNDEYE3_F_, 14);
        	GetCompoI3(_COMPOUNDEYE3_B_, 14);
        	run = GetTentacle(_TOUCH_T_);
        	goto begin;
        }
        if ( eyeFP+eyeBP<eyeCH )
        {
            if ( ulX + hmX > ulZ )
            {
                if ( ulY>hmY )
                {
                    traD = 225;
                }
                else
                {
                    traD = 315;
                }
            }
            else
            {
                if ( ulY>hmY )
                {
                    traD = 135;
                }
                else
                {
                    traD = 45;
                }
            }
            traS=absl(ulX-ulZ+hmX)/2+absl(ulY-hmY)+10;
        }
        else
        {
            eyeSP = GetCompoI3(_COMPOUNDEYE3_F_, 3) + GetCompoI3(_COMPOUNDEYE3_F_, 4) + GetCompoI3(_COMPOUNDEYE3_F_, 5);
            traS = 100;
            if ( eyeSP > eyeSK )
            {
                if ( ulH )
                {
                    strY = cap(ulY/40,4);
                    if ( ulX < ulZ )
                    {
                        strX = cap((ulX-30)/40,2);
                        cmpO = aim[cap(strX*5+strY,11)];
                        traD = cmpO;
                    }
                    else
                    {
                        strX = cap((ulZ-30)/40,2);
                        cmpO = aim[cap(strX*5+strY,11)];
                        traD = 36 - cmpO;
                        cmpO = 0 - cmpO;
                    }
                    cmpO *= cmpM;
                    lcd = 100;
                }
                else
                {
                    traD = 0;;
                }
            }
            else
            {
                eyeFD = GetCompoI3(_COMPOUNDEYE3_F_, 8);
                eyeBD = GetCompoI3(_COMPOUNDEYE3_B_, 8);
                if ( eyeFP>eyeBP )
                {
                    eyeDR=eyeFD;
                    eyePP = eyeFP;
                    //if( eyeFD<3 || eyeFD>5 ){
                    //	traS = 66+(160-eyeFP)/3;
                    //}
                    
                    //eyeFD!=4
                }
                else
                {
                    eyeDR=eyeBD+7;
                    eyePP = eyeBP;
                    //if( eyeBD<3 || eyeBD>5 ){
                    //	traS = 80+(160-eyeBP)/5;
                    //}
                    
                    //eyeFD!=4
                }
                eyeCP = dynEyeRead(eyeDR+1);
                eyeAP = dynEyeRead(eyeDR-1);
                
                eyeDR *= 2;
                
                eyePP += eyeCP + eyeAP;
                if(eyeCP>eyeAP){
                	eyeDR++;
                }
                
                eyeDR -= 2;
                
                if(eyeDR<0){
                	eyeDR += 28;
                }
                
                //Convert eyeDR to 360
                eyeDR = eyeDR*360/28 - 96;
                if(eyeDR < 0) {
                	eyeDR += 360;
                }
                
                //Actual Calculation eyePP < eyeSA
                if(eyePP < eyeSA){
                	//Chase
                	traS = 100;
                	traD = eyeDR;
                } else {
                	//lcd = 20;
                	if(eyeDR < 180){
                		//Ball to the left
                		traD = eyeDR + cap(  (eyeDR) * cap(eyePP - eyeSA,145) / (435-eyeSA) ,90);
                	} else {
                		//Ball to the right
                		traD = eyeDR - cap(  (360 - eyeDR) * cap(eyePP - eyeSA,145) / (435-eyeSA),90);
                	}
                }
            }
        }
        cmpR += cmpO;
        if( cmpR < 0 ) {
        	cmpR += 360;
        } else if ( cmpR > 360 ) {
        	cmpR -= 360 ;
        }
        if ( cmpR < 180 )
        {
            rotD = 1;
            rotS = cmpR;
        }
        else
        {
            rotD = 0;
            rotS = 360 - cmpR;
        }
        SetLCD3Char(9, traD);
        traD = traD/10;
        if(traD > 36){
        	traD -= 36;
        }
        
        traS = cap(traS,100);
        rotS = cap(rotS,100);
        rotS = rotS*rotS / 10;
        //rotS = cap(rotS,100);
        
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
        
        SetLCD3Char(1, eyeDR);
        SetLCD3Char(5,	eyePP);
        //SetLCD3Char(9, traD);
        SetLCD3Char(13, lcd);
        SetLCDBack(lcd == 0);
        
        SetMotor(_MOTOR_NE_, mtrD[0], mtrA[0]);
        SetMotor(_MOTOR_NW_, mtrD[1], mtrA[1]);
        SetMotor(_MOTOR_SE_, mtrD[2], mtrA[2]);
        SetMotor(_MOTOR_SW_, mtrD[3], mtrA[3]);
        
        
        
    }
    return 1;
}

