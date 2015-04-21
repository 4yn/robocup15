#include "HardwareInfo.c"
#include <SetMotor.h>
#include <SetLCDBack.h>
#include <GetCompassB.h>
#include <GetADScable10.h>
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

int min(int a,int b){
	if(a>b){
		return b;
	} else {
		return a;
	}
}

int main(void)
{
    SetMotor(_MOTOR_NE_, 1, 100);
    SetMotor(_MOTOR_NW_, 1, 100);
    SetMotor(_MOTOR_SE_, 1, 100);
    SetMotor(_MOTOR_SW_, 1, 100);
    //Define Constants
    
    int ulT = 220;
    int hmX = -40;
    int hmY = 90;
    char eyeCH = 10;
    int eyeSA = 60;
    int eyeSB = 130;
    int eyeSK = 300;
    int traBC = 55;
    char cmpM = 4;
    char run = 100;
    int lcd = 100;
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
    int d1 = 0;
    int d2 = 0;
    int d3 = 0;
    char mtrI[46] = {0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,9,9,9,9,9,9,9,9,9,8,7,6,5,4,3,2,1,0,0,0,0,0,0,0,0,0,0};
    char mtrS[10] = {100,70,47,27,9,-9,-27,-47,-70,-100};
    //chase and strafe subroutines
    int chase[36] = {0,10,20,40,50,70,90,100,110,130,140,140,150,150,160,160,170,170,180,190,190,200,200,210,210,220,220,230,250,260,270,290,310,320,340,350};
    int strafe[36] = {0,10,30,70,100,130,150,180,190,190,190,190,190,220,230,240,260,270,270,90,100,120,130,140,170,170,170,170,170,180,210,230,260,290,330,350};
    
    
    
    
    SetLCDBack(1);
    while (1)
    {
        //Startup loop
        begin:
        
        //Reset variables
        lcd = cap(lcd - 1,1000);
        traS = 100;
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
        //cmpO = 30;
        cmpR = GetCompassB(_COMPASS_C_);
        ulX = GetADScable10(_SCABLEAD_X_);
        ulZ = GetADScable10(_SCABLEAD_Z_);
        ulY = GetADScable10(_SCABLEAD_Y_);
        //ulX *= 2 ;
        //ulZ *= 2 ;
        
        if( ulX + ulZ > ulT ) {
        	ulH = 1;
        }
        
        if( ulX > 80 && ulZ > 80 && ulH){
        	ulY += 30;
        }
        eyeFP = GetCompoI3(_COMPOUNDEYE3_F_, 9);
        eyeBP = GetCompoI3(_COMPOUNDEYE3_B_, 9);
        if(run !=0){
        	GetCompoI3(_COMPOUNDEYE3_F_, 14);
        	GetCompoI3(_COMPOUNDEYE3_B_, 14);
        	run = lcd;
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
            if(traS<15){
            	traS = 0;
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
                if( eyeFD<3 || eyeFD>5 ){
                	traS = 66+(160-eyeFP)/3;
                }
                
                //eyeFD!=4
            }
            else
            {
                eyeDR=eyeBD+7;
                eyePP = eyeBP;
                if( eyeBD<3 || eyeBD>5 ){
                	traS = 80+(160-eyeBP)/5;
                }
                
                //eyeFD!=4
            }
            eyeCP = dynEyeRead(eyeDR+1);
            eyeAP = dynEyeRead(eyeDR-1);
            if(eyeFP>eyeBP){
            	eyeDR = 240+(30*eyeFD);
            } else {
            	eyeDR = 60+(30*eyeBD);
            }
            //eyePP += eyeCP + eyeAP;
            eyeDR = (((eyeCP-eyeAP)/4)+eyeDR)%360;
            //SetLCD3Char(9, eyeDR);
            //down to 36 directional
            eyeDR = eyeDR/10%36;
            //SetLCD3Char(13, eyeDR);
            SetLCD3Char(1, traS);
            //Actual Calculation eyePP < eyeSA
            if(eyePP < eyeSA){
            	//Chase
            	traS = 100;
            	traD = chase[eyeDR];
            } else if (eyePP < eyeSB){ //eyePP < eyeSB
            	d1 = eyeSB - eyePP;
            	d2 = eyePP - eyeSA;
            	d3 = d1+d2;
            	if(eyeDR < 180){
            		//Ball to the left
            		//traD = eyeDR + cap(  (eyeDR) * cap(eyePP - eyeSA,145) / (435-eyeSA) ,90);
            		traD = 360 - ( (360 - chase[eyeDR]) * d1 / d3 + (360 - strafe[eyeDR]) * d2 / d3);
            	} else {
            		//Ball to the right
            		//traD = eyeDR - cap(  (360 - eyeDR) * cap(eyePP - eyeSA,145) / (435-eyeSA),90);
            		traD = chase[eyeDR] * d1 / d3 + strafe[eyeDR] * d2 / d3;
            	}
            	traS = 100*d1/d3 + traS*d2/d3;
            } else{
            	traD = strafe[eyeDR];
            }
            SetLCD3Char(5, traS);
        }
        if ( ulH )
        {
            if ( ulX < ulZ )
            {
                if ( traD > 210 && traD < 330 )
                {
                    mtrM = (ulX - traBC) * 4;
                }
            }
            else
            {
                if ( traD > 30 && traD < 150 )
                {
                    mtrM = (ulZ -traBC) * 4;
                }
            }
            mtrM = cap(mtrM,100);
            traS *= mtrM / 100;
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
        traD = traD/10;
        if(traD > 36){
        	traD -= 36;
        }
        
        traS = cap(traS,100);
        rotS = cap(rotS,100);
        //rotS = rotS*rotS / 10;
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
        
        
        //SetLCD3Char(1, ulX);
        //SetLCD3Char(5,	ulZ);
        SetLCD3Char(9, traS);
        SetLCD3Char(13, traD);
        
        SetLCDBack(lcd == 0);
        
        SetMotor(_MOTOR_NE_, mtrD[0], mtrA[0]);
        SetMotor(_MOTOR_NW_, mtrD[1], mtrA[1]);
        SetMotor(_MOTOR_SE_, mtrD[2], mtrA[2]);
        SetMotor(_MOTOR_SW_, mtrD[3], mtrA[3]);
        
        
        
    }
    return 1;
}

