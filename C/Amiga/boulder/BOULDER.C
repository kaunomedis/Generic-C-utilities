/* =================================================================
   =  BOULDER DASH MAIN BODY. ©1993 by SAVELSOFTWARE inc.          =
   =  Idea: Peter Liepa., C coding: Levas Vabolis.                 =
   =  (In Fact real BOULDER DASH is © by First Star Soft. )        =
   ================================================================= */
#include ":BOULDER0.C" /* graphics */
#include ":BOULDER3.C" /* man */
#include ":LEVELS.C"   /* Lygiai */
#include ":ROTATE.C"   /* color cycle */
/* #include "music.c"*/ /* Sound routines V1.0 or higher */
STATIC UBYTE bummx[30],bummy[30],bummi[30],Adzin,Abum,Adz,Adb;
STATIC USHORT BUMPOINT,clos,fillalready,oldclos,levl,MAXLEVL;
STATIC ULONG HSCORE;
SHORT NextLevel();
titrai()
{
SetAPen(&rastport,5L); RectFill(&rastport,20L,0L,619L,11L);
PrntI(30,1,16); PrntI(40,1,18); PrntI(90,1,10); PrntI(100,1,11);
PrntI(110,1,12); PrntI(120,1,13); PrntI(130,1,5); PrntI(140,1,18);
PrntI(190,1,5); PrntI(200,1,14); PrntI(210,1,0); PrntI(220,1,15);
PrntI(230,1,13); PrntI(240,1,18); PrntI(320,1,17); PrntI(330,1,11);
PrntI(340,1,5); PrntI(350,1,14); PrntI(360,1,0); PrntI(370,1,15);
PrntI(380,1,13); PrntI(390,1,18); PrntL(400,1,HSCORE);
PrntI(470,1,11); PrntI(480,1,16); PrntI(490,1,18);
Prnt(500,1,ITEMS);  PrntI(540,1,14); PrntI(550,1,12); PrntI(560,1,18);
Prnt(570,1,levl); Prnt(150,1,LIVES); PrntL(250,1,SCORE); Prnt(50,1,0);
}
main()
{
 MAXLEVL=maximum();
 levl=0;
 pasiruosk(); WaitTOF(); AudioON();
 scena(&rastport); Makegraphics(); titrai();
 while(pekb(0xBFEC00)!=117)
 {
   rotate();
   if(man2())
   {
    if(levl>0 && hx==-1) { levl--; }
    if(levl<MAXLEVL && hx==1) {levl++; }
    Prnt(570,1,levl); Delay(20);
   }
   if(fire())
   {
    LIVES=2;
    Play(); scena(&rastport); Makegraphics(); titrai();
   }
   Delay(1);
 }
AudioOFF();
FreeMemory();
} /* End of Main */
Play()
{
SHORT n,x,y,i;
BUMPOINT=0; HSCORE=10000; FINISH=0;
level(levl); SCORE=0;
SetRast(&rastport,0L); Makegraphics();
show();
titrai(); ALIVE=15;
fillalready=0; oldclos=0;
for(n=TIM;n>0;n--) {   ALIVE--;
  for(x=0;x<29;x++) {
   for(y=12;y>=0;y--) { 
     if(Adb || Adz) {   if(Adz){ --Adz; Audiodzin2(Adz);}
                        if(Adb){ --Adb; Audiopirst2(Adb);}
                    }
    if (k(x,y)<9)
       analize(x,y);
    else { k(x,y)=k(x,y)/10; }
   } /* NEXT Y */
  }  /* NEXT X */
  if(Adzin) {Audiodzin(); Adz=64;}
  if(Abum && !Adzin) {Audiopirst(); Abum=0; Adb=64; }
  Adzin=0;
  if(!oldclos) { fillalready=1; }
  if(oldclos>HMAGMA && !fillalready) { ffill(); }
  if(!clos && !fillalready) { ffill(); }
  oldclos=0; clos=0;
  bumm2();
  if(!ALIVE) { if(LIVES>0) {LIVES--; ALIVE=15; Death(); n=TIM; } }
  Prnt(50,1,n/10); PrntL(250,1,SCORE);
  Prnt(500,1,ITEMS);
  if(!LIVES && !ALIVE) { n=0; }
  i=pekb(0xbfec00);
  if(i==117 || n<2)           /* ESC klavisas */
   {
    n=0;
    if(LIVES>0)
     {
      WaitTOF(); LIVES--; n=TIM; Prnt(150,1,LIVES);
      Death();
     }
   }
  if(FINISH){ LIVES++; n=NextLevel(n); oldclos=0; fillalready=0; }
  rotate();
}    /* NEXT N */

Delay(5);
hide();
Delay(50);

} /* End of Play */

SHORT NextLevel(m)
SHORT m;
{
SHORT i,n=0;
 Audiodzin();
 for(i=m;i>0;i-=20) {
     SCORE+=10; PrntL(250,1,SCORE);
     rotate();
     if(n)
      Audiopip(10);
     else
      {Audiodzin2(10); }
       n=!n;
                    } Audiodzin2(0);
 if(SCORE>HSCORE) {HSCORE=SCORE; PrntL(400,1,HSCORE);}
 levl++; if(levl>MAXLEVL) {levl=0;}
 Delay(50); hide(); level(levl); show(); titrai(); Delay(10);
 FINISH=0; return(TIM);
} /* end of n=NextLevel(n) */
Death()
{
  Delay(60); hide(); level(levl); show(); titrai();
  fillalready=0; oldclos=0;
}
ffill()
{
SHORT x,y,fff=3;

fillalready=1;
if(oldclos>CRISTAL) {fff=2;}
for(x=1;x<30;x++)
 {
  for(y=1;y<12;y++)
   {
    if(e(x,y)==6) {set(x,y,fff); }
   }
 }
}
analize(x,y)
SHORT x,y;
{
LONG kq,jj;
SHORT q,c1,c2,c3,c4,p,kz,i,j,bb,zz,uzz,manhere,os;
SHORT ez[5];
q=e(x,y);
if (q==10) { man(x,y); ALIVE++; return(); }
if(q==9 && !ITEMS) {set(x,y,0); WaitTOF(); set(x,y,11);
  WaitTOF(); WaitTOF(); set(x,y,9); e(x,y)=12; }
if(q<2) { return(); }
if(q==7) {return(); }
c1=x+1; c2=x-1; c3=y-1; c4=y+1;
p=e(x,c4);
if (q==2 || q==3)
 {
  if (p==0) { set(x,c4,q); set(x,y,0); k(x,c4)=1; return(); }
  if (p==2 || p==3 || p==8) {
   if(!e(c2,y) && !e(c2,c4))
    { set(c2,y,q); set(x,y,0); k(c2,y)=0; return();}
   if(!e(c1,y) && !e(c1,c4))
    { set(c1,y,q); set(x,y,0); k(c1,y)=9; return();}
  }
  if (k(x,y)>0) {
    if(p==4 || p==10) { bumm(x,y,0); }
    if(p==5) { bumm(x,y,3); }
   }
  if(q==3 && k(x,y)!=0) {Adzin=1;}
  k(x,y)=0;
  return();
 }
bb=0; manhere=0; uzz=1; ez[0]=7; ez[5]=7;
ez[1]=e(c1,y); ez[2]=e(x,c3); ez[3]=e(c2,y);
ez[4]=e(x,c4);
if(k(x,c3)==1) {ez[2]=6;}
 for(i=1; i<=5; i++)
 {
  if (ez[i]==6) {bb=1;}
  if (ez[i]==10) { manhere=1; }
  if (!ez[i]) {uzz=0;}
 }
if (manhere) {bb=1;}
/* if (uzz && !manhere) {return(); } */
if (q==4) {
    if (bb) { bumm(x,c3,0); return(); }
    jj=4L; zz=0; ;kz=0; if(k(x,y)>1) {kz=k(x,y)-1;}
    while (jj>0L && !zz)
    { kq=jj+kz-3L;
      if (kq>4) {kq-=4;}
      if (kq<1) {kq+=4;}
      if(!ez[kq]) { zz=1; go(c1,c2,c3,c4,kq,q,x,y); }
      jj--;
    }  return();
 }
if (q==5) {
   if (bb) {bumm(x,c3,3); return(); }
   jj=1L; zz=0; kz=0;
  if (k(x,y)>1) { kz=k(x,y)-1; }
  while (jj<5L && !zz)
  { kq=jj+kz-2L;
   if (kq>4) {kq-=4; }
   if (kq<1) {kq+=4; }
   if (!ez[kq]) {zz=1; go(c1,c2,c3,c4,kq,q,x,y); }
   jj++;
  } return();
}
if(q==6) {
  os=0;
  for(i=1;i<5;i++) {
    if (ez[i]<2) { os=1; j=i; }
   }
  clos+=os; oldclos++;
  if (os && (!ez[j] || ez[j])) {
    if( galima(21) )
      { mgo(j,x,y,c1,c2,c3,c4); }
   }
 }
if(q==15) /* Judanti Siena */
 {
  if(!e(c2,y)) {set(c2,y,15); return();}
  if(!e(c1,y)) {set(c1,y,15); k(c1,y)=9; return();}
 }
if(q==16) /* Neauganti magma */
 {
  if(!e(x,c4)) { q=e(x,c3); if(q==2 || q==3)
  { if(galima(11)) { set(x,c4,q); set(x,c3,0); } } }
  return();
 }
j=e(x,c4);
if(q==17) /* Dzin-Dzin Siena */
 {
  q=e(x,c3); if(k(x,c3)==1)
  {
   if(q==2) {set(x,c3,0); if(!j){set(x,c4,3); }}
   if(q==3) {set(x,c3,0); if(!j){set(x,c4,2); }}
  } return();
 }
if(q==18) /* Akmenu generatorius */
 { if(!j) {set(x,c4,2); } }
if(q==19) /* Bril. generatorius */
 { if(!j) {set(x,c4,3); } }
if(q==21) { if(k(x,c3)==1) { bumm(x,y,0); } } /* BOMBA */

return();
}

bumm(x,y,i)
SHORT x,y,i;
{
 SHORT j,z;
 BUMPOINT++; bummi[BUMPOINT]=i; bummx[BUMPOINT]=x;
 bummy[BUMPOINT]=y;  Abum=1;
 for(j=x-1;j<x+2;j++)
 {
  for(z=y;z<y+3;z++)
  {
   if (e(j,z)!=7) {set(j,z,11); }
  }
 }
}
bumm2()
{
SHORT n;
for(n=1;n<=BUMPOINT;n++) { b2(n); }
BUMPOINT=0; }

b2(n)
SHORT n;
{
SHORT x,y,i,j,z;
 x=bummx[n]; y=bummy[n]; i=bummi[n];
 WaitTOF();
 for(j=x-1;j<x+2;j++)
  {
   for(z=y;z<y+3;z++)
    {
     if (ek[z*30+j]!=7) {set(j,z,i); }
    }
  }
}

