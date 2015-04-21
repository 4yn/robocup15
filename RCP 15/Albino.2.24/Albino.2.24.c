#include "HardwareInfo.c"
#include "JMLib.c"
#include <GetCompoI3.h>
#include <SetLCD3Char.h>
#include <SetLCD5Char.h>
#include <GetAdUltrasound.h>
#include <GetCompassB.h>
#include <SetMotor.h>
//signed char VectorDynamics[361][2]={{100,100},{100,97},{100,93},{100,90},{100,87},{100,84},{100,81},{100,78},{100,75},{100,73},{100,70},{100,67},{100,65},{100,62},{100,60},{100,58},{100,55},{100,53},{100,51},{100,49},{100,47},{100,45},{100,42},{100,40},{100,38},{100,36},{100,34},{100,32},{100,31},{100,29},{100,27},{100,25},{100,23},{100,21},{100,19},{100,18},{100,16},{100,14},{100,12},{100,11},{100,9},{100,7},{100,5},{100,3},{100,2},{100,0},{100,-2},{100,-3},{100,-5},{100,-7},{100,-9},{100,-11},{100,-12},{100,-14},{100,-16},{100,-18},{100,-19},{100,-21},{100,-23},{100,-25},{100,-27},{100,-29},{100,-31},{100,-32},{100,-34},{100,-36},{100,-38},{100,-40},{100,-42},{100,-45},{100,-47},{100,-49},{100,-51},{100,-53},{100,-55},{100,-58},{100,-60},{100,-62},{100,-65},{100,-67},{100,-70},{100,-73},{100,-75},{100,-78},{100,-81},{100,-84},{100,-87},{100,-90},{100,-93},{100,-97},{100,-100},{97,-100},{93,-100},{90,-100},{87,-100},{84,-100},{81,-100},{78,-100},{75,-100},{73,-100},{70,-100},{67,-100},{65,-100},{62,-100},{60,-100},{58,-100},{55,-100},{53,-100},{51,-100},{49,-100},{47,-100},{45,-100},{42,-100},{40,-100},{38,-100},{36,-100},{34,-100},{32,-100},{31,-100},{29,-100},{27,-100},{25,-100},{23,-100},{21,-100},{19,-100},{18,-100},{16,-100},{14,-100},{12,-100},{11,-100},{9,-100},{7,-100},{5,-100},{3,-100},{2,-100},{0,-100},{-2,-100},{-3,-100},{-5,-100},{-7,-100},{-9,-100},{-11,-100},{-12,-100},{-14,-100},{-16,-100},{-18,-100},{-19,-100},{-21,-100},{-23,-100},{-25,-100},{-27,-100},{-29,-100},{-31,-100},{-32,-100},{-34,-100},{-36,-100},{-38,-100},{-40,-100},{-42,-100},{-45,-100},{-47,-100},{-49,-100},{-51,-100},{-53,-100},{-55,-100},{-58,-100},{-60,-100},{-62,-100},{-65,-100},{-67,-100},{-70,-100},{-73,-100},{-75,-100},{-78,-100},{-81,-100},{-84,-100},{-87,-100},{-90,-100},{-93,-100},{-97,-100},{-100,-100},{-100,-97},{-100,-93},{-100,-90},{-100,-87},{-100,-84},{-100,-81},{-100,-78},{-100,-75},{-100,-73},{-100,-70},{-100,-67},{-100,-65},{-100,-62},{-100,-60},{-100,-58},{-100,-55},{-100,-53},{-100,-51},{-100,-49},{-100,-47},{-100,-45},{-100,-42},{-100,-40},{-100,-38},{-100,-36},{-100,-34},{-100,-32},{-100,-31},{-100,-29},{-100,-27},{-100,-25},{-100,-23},{-100,-21},{-100,-19},{-100,-18},{-100,-16},{-100,-14},{-100,-12},{-100,-11},{-100,-9},{-100,-7},{-100,-5},{-100,-3},{-100,-2},{-100,0},{-100,2},{-100,3},{-100,5},{-100,7},{-100,9},{-100,11},{-100,12},{-100,14},{-100,16},{-100,18},{-100,19},{-100,21},{-100,23},{-100,25},{-100,27},{-100,29},{-100,31},{-100,32},{-100,34},{-100,36},{-100,38},{-100,40},{-100,42},{-100,45},{-100,47},{-100,49},{-100,51},{-100,53},{-100,55},{-100,58},{-100,60},{-100,62},{-100,65},{-100,67},{-100,70},{-100,73},{-100,75},{-100,78},{-100,81},{-100,84},{-100,87},{-100,90},{-100,93},{-100,97},{-100,100},{-97,100},{-93,100},{-90,100},{-87,100},{-84,100},{-81,100},{-78,100},{-75,100},{-73,100},{-70,100},{-67,100},{-65,100},{-62,100},{-60,100},{-58,100},{-55,100},{-53,100},{-51,100},{-49,100},{-47,100},{-45,100},{-42,100},{-40,100},{-38,100},{-36,100},{-34,100},{-32,100},{-31,100},{-29,100},{-27,100},{-25,100},{-23,100},{-21,100},{-19,100},{-18,100},{-16,100},{-14,100},{-12,100},{-11,100},{-9,100},{-7,100},{-5,100},{-3,100},{-2,100},{0,100},{2,100},{3,100},{5,100},{7,100},{9,100},{11,100},{12,100},{14,100},{16,100},{18,100},{19,100},{21,100},{23,100},{25,100},{27,100},{29,100},{31,100},{32,100},{34,100},{36,100},{38,100},{40,100},{42,100},{45,100},{47,100},{49,100},{51,100},{53,100},{55,100},{58,100},{60,100},{62,100},{65,100},{67,100},{70,100},{73,100},{75,100},{78,100},{81,100},{84,100},{87,100},{90,100},{93,100},{97,100},{100,100}};
//int maxi(int a, int b){
//    return a>b?a:b;
//}
//double MPS(int Ma,int Mb, int Mc, int Md){
//    double highestPow=maxi(maxi(Ma,Mb),maxi(Mc,Md));
//    if(highestPow>0) return (double)(100/highestPow);
//    else return 0;
//}
//int absolutely(int a){
//	return a>0?a:a*-1;
//}

//Drive direction arrays
//{(NW and SE Motor Powers),(NE and SW Motor Powers)}
//-ve movement is backwards
//0 deg to 360 deg
signed int vectordynamics[361][2]={{100,100},{100,97},{100,93},{100,90},{100,87},{100,84},{100,81},{100,78},{100,75},{100,73},{100,70},{100,67},{100,65},{100,62},{100,60},{100,58},{100,55},{100,53},{100,51},{100,49},{100,47},{100,45},{100,42},{100,40},{100,38},{100,36},{100,34},{100,32},{100,31},{100,29},{100,27},{100,25},{100,23},{100,21},{100,19},{100,18},{100,16},{100,14},{100,12},{100,11},{100,9},{100,7},{100,5},{100,3},{100,2},{100,0},{100,-2},{100,-3},{100,-5},{100,-7},{100,-9},{100,-11},{100,-12},{100,-14},{100,-16},{100,-18},{100,-19},{100,-21},{100,-23},{100,-25},{100,-27},{100,-29},{100,-31},{100,-32},{100,-34},{100,-36},{100,-38},{100,-40},{100,-42},{100,-45},{100,-47},{100,-49},{100,-51},{100,-53},{100,-55},{100,-58},{100,-60},{100,-62},{100,-65},{100,-67},{100,-70},{100,-73},{100,-75},{100,-78},{100,-81},{100,-84},{100,-87},{100,-90},{100,-93},{100,-97},{100,-100},{97,-100},{93,-100},{90,-100},{87,-100},{84,-100},{81,-100},{78,-100},{75,-100},{73,-100},{70,-100},{67,-100},{65,-100},{62,-100},{60,-100},{58,-100},{55,-100},{53,-100},{51,-100},{49,-100},{47,-100},{45,-100},{42,-100},{40,-100},{38,-100},{36,-100},{34,-100},{32,-100},{31,-100},{29,-100},{27,-100},{25,-100},{23,-100},{21,-100},{19,-100},{18,-100},{16,-100},{14,-100},{12,-100},{11,-100},{9,-100},{7,-100},{5,-100},{3,-100},{2,-100},{0,-100},{-2,-100},{-3,-100},{-5,-100},{-7,-100},{-9,-100},{-11,-100},{-12,-100},{-14,-100},{-16,-100},{-18,-100},{-19,-100},{-21,-100},{-23,-100},{-25,-100},{-27,-100},{-29,-100},{-31,-100},{-32,-100},{-34,-100},{-36,-100},{-38,-100},{-40,-100},{-42,-100},{-45,-100},{-47,-100},{-49,-100},{-51,-100},{-53,-100},{-55,-100},{-58,-100},{-60,-100},{-62,-100},{-65,-100},{-67,-100},{-70,-100},{-73,-100},{-75,-100},{-78,-100},{-81,-100},{-84,-100},{-87,-100},{-90,-100},{-93,-100},{-97,-100},{-100,-100},{-100,-97},{-100,-93},{-100,-90},{-100,-87},{-100,-84},{-100,-81},{-100,-78},{-100,-75},{-100,-73},{-100,-70},{-100,-67},{-100,-65},{-100,-62},{-100,-60},{-100,-58},{-100,-55},{-100,-53},{-100,-51},{-100,-49},{-100,-47},{-100,-45},{-100,-42},{-100,-40},{-100,-38},{-100,-36},{-100,-34},{-100,-32},{-100,-31},{-100,-29},{-100,-27},{-100,-25},{-100,-23},{-100,-21},{-100,-19},{-100,-18},{-100,-16},{-100,-14},{-100,-12},{-100,-11},{-100,-9},{-100,-7},{-100,-5},{-100,-3},{-100,-2},{-100,0},{-100,2},{-100,3},{-100,5},{-100,7},{-100,9},{-100,11},{-100,12},{-100,14},{-100,16},{-100,18},{-100,19},{-100,21},{-100,23},{-100,25},{-100,27},{-100,29},{-100,31},{-100,32},{-100,34},{-100,36},{-100,38},{-100,40},{-100,42},{-100,45},{-100,47},{-100,49},{-100,51},{-100,53},{-100,55},{-100,58},{-100,60},{-100,62},{-100,65},{-100,67},{-100,70},{-100,73},{-100,75},{-100,78},{-100,81},{-100,84},{-100,87},{-100,90},{-100,93},{-100,97},{-100,100},{-97,100},{-93,100},{-90,100},{-87,100},{-84,100},{-81,100},{-78,100},{-75,100},{-73,100},{-70,100},{-67,100},{-65,100},{-62,100},{-60,100},{-58,100},{-55,100},{-53,100},{-51,100},{-49,100},{-47,100},{-45,100},{-42,100},{-40,100},{-38,100},{-36,100},{-34,100},{-32,100},{-31,100},{-29,100},{-27,100},{-25,100},{-23,100},{-21,100},{-19,100},{-18,100},{-16,100},{-14,100},{-12,100},{-11,100},{-9,100},{-7,100},{-5,100},{-3,100},{-2,100},{0,100},{2,100},{3,100},{5,100},{7,100},{9,100},{11,100},{12,100},{14,100},{16,100},{18,100},{19,100},{21,100},{23,100},{25,100},{27,100},{29,100},{31,100},{32,100},{34,100},{36,100},{38,100},{40,100},{42,100},{45,100},{47,100},{49,100},{51,100},{53,100},{55,100},{58,100},{60,100},{62,100},{65,100},{67,100},{70,100},{73,100},{75,100},{78,100},{81,100},{84,100},{87,100},{90,100},{93,100},{97,100},{100,100}};
hundredsine[91]={0,2,3,5,7,9,10,12,14,16,17,19,21,22,24,26,28,29,31,33,34,36,37,39,41,42,44,45,47,48,50,52,53,54,56,57,59,60,62,63,64,66,67,68,69,71,72,73,74,75,77,78,79,80,81,82,83,84,85,86,87,87,88,89,90,91,91,92,93,93,94,95,95,96,96,97,97,97,98,98,98,99,99,99,99,100,100,100,100,100,100};

int main(void)
{
    X1RCU_Init();
    unsigned int gsn = 0;
    unsigned int gse = 0;
    unsigned int gss = 0;
    unsigned int gsw = 0;
    int cval = 0;
    unsigned int caspeed = 0;
    unsigned int firval = 0;
    unsigned int birval = 0;
    unsigned int firno = 0;
    unsigned int birno = 0;
    int lus = 0;
    int bus = 0;
    int rus = 0;
    unsigned int usoffset = 0;
    unsigned int p = 0;
    unsigned int nextp = 0;
    unsigned int clockp = 0;
    unsigned int anticlockp = 0;
    int ballpos = 0;
    int balldist = 0;
    int drivedir = 0;
    unsigned int NEd = 0;
    unsigned int NWd = 0;
    unsigned int SEd = 0;
    unsigned int SWd = 0;
    unsigned int NEs = 0;
    unsigned int NWs = 0;
    unsigned int SEs = 0;
    unsigned int SWs = 0;
    int NE = 0;
    int NW = 0;
    int SE = 0;
    int SW = 0;
    double powerscale = 0;
    unsigned int powerscaling = 0;
    unsigned int basepower = 0;
    unsigned int baspeed = 0;
    int NEv = 0;
    int NWv = 0;
    int SEv = 0;
    int SWv = 0;
    unsigned int baNE = 0;
    unsigned int baNW = 0;
    unsigned int baSE = 0;
    unsigned int baSW = 0;
    unsigned int chomed = 358;
    unsigned int chomeu = 2;
    unsigned int compamt = 0;
    unsigned int chomex = 180;
    unsigned int fp3 = 0;
    unsigned int fp4 = 0;
    unsigned int fp5 = 0;
    unsigned int fpt = 0;
    unsigned int castate = 0;
    unsigned int test = 0;
    int cvalmod = 0;
    int compamtmod = 0;
    int latdist = 0;
    int bcscale = 0;
    unsigned int var0 = 0;
    unsigned int NEm = 0;
    unsigned int NWm = 0;
    unsigned int SEm = 0;
    unsigned int SWm = 0;
    int bc = 0;
    unsigned int camod = 0;
    int freeze = 0;
    while (1)
    {
        GetCompoI3(_COMPOUNDEYE3_f_, 14);
        GetCompoI3(_COMPOUNDEYE3_b_, 14);
        SetLCD3Char(127, 0, 0);
        SetLCD5Char(127, 0, 0);
        firval = GetCompoI3(_COMPOUNDEYE3_f_, 9);
        birval = GetCompoI3(_COMPOUNDEYE3_b_, 9);
        lus = GetAdUltrasound(_ADULTRASOUND_l_);
        bus = GetAdUltrasound(_ADULTRASOUND_b_);
        rus = GetAdUltrasound(_ADULTRASOUND_r_);
        lus/=10;
        rus/=10;
        bus/=10;
        if(lus>145)
        {
        lus=145;
        }
        if(rus>145)
        {
        rus=145;
        }
        if(bus>145)
        {
        bus=145;
        }
        /*if(rus>=170)
        {
        	rus=145;
        }
        if(rus-80<lus<rus+80)
        {
        	bus+=20;
        }
        if(lus+rus<155)
        {
        	if(rus-lus>=25||lus-rus>=25)
        	{
        		if(lus<rus)
        		{
        			lus+=(160-lus-rus);
        		}
        		else
        		{
        			rus+=(160-lus-rus);
        		}
        	}
        	else
        	{
        		usoffset=(160-lus-rus)/2;
        		lus+=usoffset;
        		rus+=usoffset;
        	}
        }*/
        freeze=0;
        
        cvalmod=0;
        if ( firval<5&&birval<5 )
        {
            chomed=355;
            chomeu=5;
            castate=0;
            basepower=0;
            test=0;
            cvalmod=0;
            camod=6;
            /*if(lus>rus&&bus>50)
            {
            drivedir=225;
            basepower=(bus-50);
            }
            if(rus>lus&&bus>50)
            {
            drivedir=135;
            basepower=(bus-50);
            }
            if(lus>rus&&bus<50)
            {
            drivedir=315;
            basepower=(50-bus);
            }
            if(rus>lus&&bus<50)
            {
            drivedir=45;
            basepower=(50-bus)+20;
            if(basepower>100)
            {
            basepower=100;
            }
            }*/
            if(bus>42)
            {
            NE=NW=SE=SW=-(bus-42)*3;
            }
            if(bus<38)
            {
            NE=NW=SE=SW=(38-bus)*3;
            }
            if(lus>(rus+20))
            {
            NE+=(lus-rus)/2;
            SW+=(lus-rus)/2;
            NW-=(lus-rus)/2;
            SE-=(lus-rus)/2;
            }
            if(lus<(rus-20))
            {
            NE-=(rus-lus)/2;
            SW-=(rus-lus)/2;
            NW+=(rus-lus)/2;
            SE+=(rus-lus)/2;
            }
            //SetLCD3Char(0,2,NE);
            //SetLCD3Char(30,2,NW);
            NE=NE*2/3;
            NW=NW*2/3;
            SE=SE*2/3;
            SW=SW*2/3;
            bc=0;
            //SetLCD3Char(0,4,NE);
            //SetLCD3Char(30,4,NW);
            //SetLCD3Char(0,6,lus);
            //SetLCD3Char(30,6,bus);
            //SetLCD3Char(60,6,rus);
        }
        else
        {
            if ( firval>birval )
            {
                firno = GetCompoI3(_COMPOUNDEYE3_f_, 8);
                ballpos=(firno-4)*30;
                balldist=firval;
                p=firno;
            }
            else
            {
                birno = GetCompoI3(_COMPOUNDEYE3_b_, 8);
                ballpos=birno*30+60;
                balldist=birval;
                p=birno+7;
            }
            //getting clock and anticlock values
            if(p==14)
            {
            	clockp=GetCompoI3(_COMPOUNDEYE3_f_,1);
            }
            if(p==7)
            {
            	clockp=GetCompoI3(_COMPOUNDEYE3_b_,1);
            }
            if(p<7)
            {
            	clockp=GetCompoI3(_COMPOUNDEYE3_f_,firno+1);
            }
            if(p>7&&p<14)
            {
            	clockp=GetCompoI3(_COMPOUNDEYE3_b_,birno+1);
            }
            if(p==1)
            {
            	anticlockp=GetCompoI3(_COMPOUNDEYE3_b_,7);
            }
            if(p==8)
            {
            	anticlockp=GetCompoI3(_COMPOUNDEYE3_f_,7);
            }
            if(p<1&&p<8)
            {
            	anticlockp=GetCompoI3(_COMPOUNDEYE3_f_,firno-1);
            }
            if(p>8)
            {
            	anticlockp=GetCompoI3(_COMPOUNDEYE3_b_,birno-1);
            }
            //getting precise directions
            if(clockp>anticlockp)
            {
            	ballpos+=8;
            }
            else
            {
            	ballpos-=7;
            }
            if(p==4&&clockp<anticlockp+20&&clockp>anticlockp-20)
            {
            	ballpos=0;
            }
            if(p==11&&clockp<anticlockp+20&&clockp>anticlockp-20)
            {
            	ballpos=180;
            }
            if(p==7&&clockp>anticlockp)
            {
            	ballpos=90;
            }
            if(p==8&&clockp<anticlockp)
            {
            	ballpos=90;
            }
            if(p==14&&clockp>anticlockp)
            {
            	ballpos=270;
            }
            if(p==1&&clockp<anticlockp)
            {
            	ballpos=270;
            }
            //keep ball pos in range
            if(ballpos<0||ballpos>360)
            {
            	while(ballpos<0)
            	{
            		ballpos+=360;
            	}
            	while(ballpos>360)
            	{
            		ballpos-=360;
            	}
            }
            fp3 = GetCompoI3(_COMPOUNDEYE3_f_, 3);
            fp4 = GetCompoI3(_COMPOUNDEYE3_f_, 4);
            fp5 = GetCompoI3(_COMPOUNDEYE3_f_, 5);
            fpt=fp3+fp4+fp5;;
            if ( fpt>=300&&(ballpos<=23||ballpos>=338) )
            {
                if(lus>60&&lus<110)
                {
                	drivedir=0;
                }
                else
                {
                	if(lus<=60)
                	{
                		drivedir=(bus-50)*12/17;
                		chomed=25;
                		chomeu=35;
                		castate=1;
                		cvalmod=-30;
                	}
                	if(rus<60)
                	{
                		drivedir=360-(bus-50)*12/17;
                		chomed=325;
                		chomeu=335;
                		castate=2;
                		cvalmod=30;
                	}
                }
                basepower=100;
            }
            else
            {
                if ( ballpos>=270||ballpos<=90 )
                {
                    /*if(latdist>30)
                    {
                    if(ballpos>180)
                    {
                    drivedir=270;
                    }
                    else
                    {
                    drivedir=90;
                    }
                    }
                    else */
                    	if(ballpos>180)
                    	{
                    		balldist-=50;
                    		if(balldist<0)
                    		{
                    			balldist=0;
                    		}
                    		compamtmod=40-balldist;
                    		if(compamtmod<0)
                    		{
                    		compamtmod=0;
                    		}
                    		//compamt=2*(360-ballpos);
                    		compamt=10*(compamtmod)/50;
                    		drivedir=ballpos-compamt;
                    		test=1;
                    	}
                    	else
                    	{
                    		balldist-=50;
                    		if(balldist<0)
                    		{
                    			balldist=0;
                    		}
                    		
                    		//compamt=2*ballpos;
                    		compamtmod=40-balldist;
                    		if(compamtmod<0)
                    		{
                    		compamtmod=0;
                    		}
                    		compamt=10*(compamtmod)/50;
                    		drivedir=ballpos+compamt;
                    		test=2;
                    	}
                    	basepower=100;
                    cvalmod=0;
                    if(lus<=60&&balldist>100)
                    {
                    	cvalmod=-30;
                    }
                    if(rus<60&&balldist>100)
                    {
                    	cvalmod=30;
                    }
                }
                else
                {
                    freeze=1;
                }
            }
            if(drivedir<0||drivedir>360)
            {
            	while(drivedir<0)
            	{
            		drivedir+=360;
            	}
            	while(drivedir>360)
            	{
            		drivedir-=360;
            	}
            }
            NW=vectordynamics[drivedir][0];
            SE=vectordynamics[drivedir][0];
            NE=vectordynamics[drivedir][1];
            SW=vectordynamics[drivedir][1];
            bc=1;
            camod=2;
            if(freeze==1)
            {
            NE=NW=SE=SW=0;
            }
        }
        cval = GetCompassB(_COMPASS_1_);
        cval+=cvalmod;
        while(cval>360)
        {
        cval-=360;
        }
        while(cval<0)
        {
        cval+=360;
        }
        if ( cval>355||cval<5 )
        {
        }
        else
        {
            if ( cval>180 )
            {
                caspeed=(360-cval)*camod/9+10;
                NEv=SEv=-caspeed;
                NWv=SWv=caspeed;
            }
            else
            {
                caspeed=cval*camod/9+10;
                NEv=SEv=caspeed;
                NWv=SWv=-caspeed;
            }
        }
        NE+=NEv;
        NW+=NWv;
        SE+=SEv;
        SW+=SWv;
        //preparing for compounding
        if ( NE>=0 )
        {
        	NEd=0;
        	NEs=NE;
        }
        else
        {
        	NEd=2;
        	NEs=-NE;
        }
        if ( NW>=0 )
        {
        	NWd=0;
        	NWs=NW;
        }
        else
        {
        	NWd=2;
        	NWs=-NW;
        }
        if ( SE>=0 )
        {
        	SEd=0;
        	SEs=SE;
        }
        else
        {
        	SEd=2;
        	SEs=-SE;
        }
        if ( SW>=0 )
        {
        	SWd=0;
        	SWs=SW;
        }
        else
        {
        	SWd=2;
        	SWs=-SW;
        }
        NEs=NEs/2;
        NWs=NWs/2;
        SEs=SEs/2;
        SWs=SWs/2;
        if ( basepower==0||NEs>100&&NWs>100&&SEs>100&&SWs>100 )
        {
        }
        else
        {
            if(NEs>NWs&&NEs>SEs&&NEs>SWs)
            {
            NWs=NWs*basepower/NEs;
            SEs=SEs*basepower/NEs;
            SWs=SWs*basepower/NEs;
            NEs=basepower;
            }
            if(NWs>NEs&&NWs>SEs&&NWs>SWs)
            {
            NEs=NEs*basepower/NWs;
            SEs=SEs*basepower/NWs;
            SWs=SWs*basepower/NWs;
            NWs=basepower;
            }
            if(SEs>NEs&&SEs>NWs&&SEs>SWs)
            {
            NWs=NWs*basepower/SEs;
            NEs=NEs*basepower/SEs;
            SWs=SWs*basepower/SEs;
            SEs=basepower;
            }
            if(SWs>NEs&&SWs>NWs&&SWs>SEs)
            {
            NWs=NWs*basepower/SWs;
            SEs=SEs*basepower/SWs;
            NEs=NEs*basepower/SWs;
            SWs=basepower;
            }
            
            NWs=NWs*9/10;
            SWs=SWs*9/10;
        }
        lus = GetAdUltrasound(_ADULTRASOUND_l_);
        bus = GetAdUltrasound(_ADULTRASOUND_b_);
        rus = GetAdUltrasound(_ADULTRASOUND_r_);
        lus/=10;
        rus/=10;
        bus/=10;
        if(lus>145)
        {
        lus=145;
        }
        if(rus>145)
        {
        rus=145;
        }
        if(bus>145)
        {
        bus=145;
        }
        if(bc==1)
        {
        /*SetLCD3Char(0,0,lus);
        SetLCD3Char(30,0,bus);
        SetLCD3Char(60,0,rus);
        SetLCD3Char(30,6,NEs);
        SetLCD3Char(60,6,NWs);*/
        if((lus+rus)>140)
        {
        	if(drivedir>180)
        	{
        		bcscale=(lus-30)*3;
        		//SetLCD5Char(0,2,bcscale);
        		if(bcscale<0)
        		{
        			bcscale=0;
        		}
        		if(bcscale<100)
        		{
        			NEs=NEs*bcscale/100;
        			NWs=NWs*bcscale/100;
        			SEs=SEs*bcscale/100;
        			SWs=SWs*bcscale/100;
        		}
        	}
        	else
        	{
        		bcscale=(rus-30)*3;
        		//SetLCD5Char(30,2,bcscale);
        		if(bcscale<0)
        		{
        		bcscale=0;
        		}
        				if(bcscale<100)
        		{
        			NEs=NEs*bcscale/100;
        			NWs=NWs*bcscale/100;
        			SEs=SEs*bcscale/100;
        			SWs=SWs*bcscale/100;
        		}
        	}
        }
        if((lus+rus)>90&&bus<60)
        {
        	if(drivedir>180)
        	{
        		bcscale=(lus-30)*3;
        		//SetLCD5Char(0,2,bcscale);
        		if(bcscale<0)
        		{
        			bcscale=0;
        		}
        		if(bcscale<100)
        		{
        			NEs=NEs*bcscale/100;
        			NWs=NWs*bcscale/100;
        			SEs=SEs*bcscale/100;
        			SWs=SWs*bcscale/100;
        		}
        	}
        	else
        	{
        		bcscale=(rus-30)*3;
        		//SetLCD5Char(30,2,bcscale);
        		if(bcscale<0)
        		{
        		bcscale=0;
        		}
        				if(bcscale<100)
        		{
        			NEs=NEs*bcscale/100;
        			NWs=NWs*bcscale/100;
        			SEs=SEs*bcscale/100;
        			SWs=SWs*bcscale/100;
        		}
        	}
        }
        if((lus+rus)>90&&bus>140)
        {
        	if(drivedir>180)
        	{
        		bcscale=(lus-30)*3;
        		//SetLCD5Char(0,2,bcscale);
        		if(bcscale<0)
        		{
        			bcscale=0;
        		}
        		if(bcscale<100)
        		{
        			NEs=NEs*bcscale/100;
        			NWs=NWs*bcscale/100;
        			SEs=SEs*bcscale/100;
        			SWs=SWs*bcscale/100;
        		}
        	}
        	else
        	{
        		bcscale=(rus-30)*3;
        		//SetLCD5Char(30,2,bcscale);
        		if(bcscale<0)
        		{
        		bcscale=0;
        		}
        		if(bcscale<100)
        		{
        			NEs=NEs*bcscale/100;
        			NWs=NWs*bcscale/100;
        			SEs=SEs*bcscale/100;
        			SWs=SWs*bcscale/100;
        		}
        	}
        }
        if(90<=drivedir<=270&&(lus<35||rus<35))
        {
        	bcscale=(bus-35)*3;
        	if(bcscale<0)
        		{
        			bcscale=0;
        		}
        		if(bcscale<100)
        		{
        			NEs=NEs*bcscale/100;
        			NWs=NWs*bcscale/100;
        			SEs=SEs*bcscale/100;
        			SWs=SWs*bcscale/100;
        		}
        }
        if((drivedir<=90||drivedir>=270)&&(lus<35||rus<35))
        {
        	bcscale=(bus-35)*3;
        	if(bcscale<0)
        		{
        			bcscale=0;
        		}
        		if(bcscale<100)
        		{
        			NEs=NEs*bcscale/100;
        			NWs=NWs*bcscale/100;
        			SEs=SEs*bcscale/100;
        			SWs=SWs*bcscale/100;
        		}
        }
        //SetLCD3Char(0,4,bcscale);
        //SetLCD3Char(30,4,NEs);
        //SetLCD3Char(60,4,NWs);
        }
        
        SetMotor(_MOTOR_ne_, NEd, NEs);
        SetMotor(_MOTOR_nw_, NWd, NWs);
        SetMotor(_MOTOR_se_, SEd, SEs);
        SetMotor(_MOTOR_sw_, SWd, SWs);
        SetLCD3Char(0,0,freeze);
    }
    return 1;
}

