#include "HardwareInfo.c"
#include <SetMotor.h>
#include <GetCompassB.h>
#include <GetADScable10.h>
#include <GetUltrasound.h>
#include <GetCompoI3.h>
#include <SetLCDBack.h>
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
    char ulX = 0;
    char ulY = 0;
    char ulZ = 0;
    char ulH = 0;
    
    //eye
    int eyeFP = 0;
    char eyeFD = 0;
    int eyeBP = 0;
    char eyeBD = 0;
    int eyePP = 0;
    int eyeDR = 0;
    char eyeCP = 0;
    char eyeAP = 0;
    int eyeSP = 0;
    
    //cmp
    int cmpR = 0;
    int cmpO = 0;
    
    //motor
    int traS = 0;
    char traD = 0;
    int rotS = 0;
    char rotD = 0;
    int mtrM = 0;
    char mtrC = 0;
    int mtrP[4] = {0,0,0,0};
    int mtrA[4] = {0,0,0,0};
    int mtrD[4] = {0,0,0,0};
    
    //misc
    int run = 0;
    int mtrI[30] = {0,0,0,0,0,0,0,1,2,3,4,5,6,6,6,6,6,6,6,5,4,3,2,1,0,0,0,0,0,0};
    int mtrS[7] = {100,58,27,0,-27,-58,-100};
    int chase[28] = {18,19,20,20,21,22,23,0,1,2,2,3,4,5,6,7,8,8,9,10,11,12,13,14,14,15,16,17};
    int strafe[28] = {13,15,17,19,21,23,0,0,1,3,5,7,9,11,12,13,14,15,16,17,18,6,7,8,9,10,11,12};
    //experimental 
    //int strafe[28] = {12,14,16,18,20,22,0,0,2,4,6,8,10,12,13,14,15,16,17,18,18,6,6,7,8,9,10,11};
    
    //Define Constants
    
    char ulT = 90;
    char hmX = 60;
    char hmY = 60;
    char eyeCH = 10;
    int eyeSA = 200;
    int eyeSK = 360;
    while (1)
    {
        //Startup loop
        begin:
        
        //Reset variables
        traS = 0;
        traD = 0;
        rotS = 0;
        rotD = 0;
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
        
        if( ulX > 30 && ulZ > 30 ){
        	ulY += 25;
        }
        eyeFP = GetCompoI3(_COMPOUNDEYE3_F_, 9);
        eyeBP = GetCompoI3(_COMPOUNDEYE3_B_, 9);
        if(run ==0){
        	GetCompoI3(_COMPOUNDEYE3_F_, 14);
        	GetCompoI3(_COMPOUNDEYE3_B_, 14);
        	run = GetTentacle(_TOUCH_T_);
        	goto begin;
        }
        SetLCDBack(1);
        if ( eyeFP+eyeBP<eyeCH )
        {
            if ( ulX>hmX )
            {
                if ( ulY>hmY )
                {
                    traD = 15;
                }
                else
                {
                    traD = 21;
                }
            }
            else
            {
                if ( ulY>hmY )
                {
                    traD = 9;
                }
                else
                {
                    traD = 3;
                }
            }
            traS=absl(ulX-hmX)+absl(ulY-hmY)+10;
        }
        else
        {
            eyeSP = GetCompoI3(_COMPOUNDEYE3_F_, 3) + GetCompoI3(_COMPOUNDEYE3_F_, 4) + GetCompoI3(_COMPOUNDEYE3_F_, 5);
            
            if ( eyeSP > eyeSK )
            {
                traD = 0;;
                traS = 100;
            }
            else
            {
                eyeFD = GetCompoI3(_COMPOUNDEYE3_F_, 8);
                eyeBD = GetCompoI3(_COMPOUNDEYE3_B_, 8);
                if ( eyeFP>eyeBP )
                {
                    eyeDR=eyeFD;
                    eyePP = eyeFP;
                }
                else
                {
                    eyeDR=eyeBD+7;
                    eyePP = eyeBP;
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
                
                if ( eyePP > eyeSA )
                {
                    traD = strafe[eyeDR];
                    traS = 50;
                }
                else
                {
                    traD = chase[eyeDR];
                    traS = 100;
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
        traS = cap(traS,100);
        rotS = cap(rotS,100);
        
        mtrP[0] = mtrP[3] = traS * mtrS[ mtrI[ traD+6 ] ] / 100;
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
        
        SetLCD3Char(1, eyeFP);
        SetLCD3Char(5, eyeBP);
        SetLCD3Char(9, 0);
        SetLCD3Char(13, eyeFD);
        
        
        SetMotor(_MOTOR_NE_, mtrD[0], mtrA[0]);
        SetMotor(_MOTOR_NW_, mtrD[1], mtrA[1]);
        SetMotor(_MOTOR_SE_, mtrD[2], mtrA[2]);
        SetMotor(_MOTOR_SW_, mtrD[3], mtrA[3]);
        
        
        
    }
    return 1;
}

