#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
 
 //baseHP1: hp knight 99->999
 //wp1: wp of knight 0->3
 //baseHp2: hp warrior 88->888
 //wp2: wp of warrior 0->3
 //ground: 1-> 999

double p(int realHp1, int realHp2);
int calRealHp1(int baseHp1, int wp1, int ground, int& mithril1);
int calRealHp2(int baseHp2, int wp2, int ground, int& mithril2);
int main ()
{
    

//    // mo mot file trong che do write.
//    ofstream outfile;
//    outfile.open("vietjack.dat");

//    cout << "Ghi du lieu toi file!" << endl;
//    cout << "Nhap ten cua ban: "; 
//    cin.getline(data, 100);

//    // ghi du lieu da nhap vao trong file.
//    outfile << data << endl;

//    cout << "Nhap tuoi cua ban: "; 
//    cin >> data;
//    cin.ignore();
   
//    // ghi du lieu da nhap vao trong file.
//    outfile << data << endl;

//    // dong file da mo.
//    outfile.close();
    
   // mo mot file trong che do read.
   int state = 0;
   int baseHp1, wp1;
   int baseHp2, wp2;
   int ground; 

   double result=0;
   ifstream infile;
   string tmpTxt;
   int tmpInt; 
   infile.open("file.txt"); 
   //check 1 trong 2 dung mithril, tuc la wpi == 2
   int mithril1=0, mithril2=0;

   cout << "\n===========================\n" ;
   cout << "Doc du lieu co trong file!" << endl; 
   //eof() check xem con tro file co dang nam cuoi file ko?
   //tuc la doc het file chua ? 
   // neu 1 trong 2 dung mithril thi chi co hoa tro len.
   // > 0.5 them 1 bien xem 1 trong 2 co dung mithril hay ko?
   int count=1;
   while(!infile.eof())
   {
      if(state < 5)
      {
         getline(infile, tmpTxt);
         if(tmpTxt.compare("") == 0)
            break;
         tmpInt = stoi(tmpTxt);
      }

      switch (state)
      {
         case 0: baseHp1 = tmpInt;break;
         case 1: wp1 = tmpInt; break;
         case 2: baseHp2 = tmpInt; break;
         case 3: wp2 = tmpInt; break;
         case 4: ground = tmpInt; break;
         default:
            break;
      }
      if(state == 5)
      {
         
         int realHp1 = calRealHp1(baseHp1, wp1, ground, mithril1);
         int realHp2 = calRealHp2(baseHp2, wp2, ground, mithril2);
         // cout << "Probability R: " << p(realHp1, realHp2) << endl;
         if(mithril1>0 || mithril2 >0)
         {
            //Knight thang khi P > 0.5
            //Saxon thawng khi P < 0.5
            //Saxxon dung mithril thi ko the thua duoc:
            // P<=0.5
            //Neu Knight dung mithril thi ko the thua dc:
            //P>=0.5
            double tmpResult = p(realHp1, realHp2);
            if(mithril1)
               result = max(0.5, tmpResult);
            if(mithril2)
               result = min(0.5, tmpResult);
            if(mithril1 == mithril2)
               result = 0.5;
         }
         else{
            result = p(realHp1, realHp2);
         }
         cout << "(" <<count++<<")" "Prop R: " <<setprecision(2) << result
                << fixed << endl;
         mithril1 = 0, mithril2 = 0;
         state = -1;
      }
      state++;
   }
   // dong file da mo.
   infile.close();

   return 0;
}

double p(int realHP1, int realHP2){
   return (realHP1 - realHP2 + 999)/2000.0;
}

int calRealHp1(int baseHp1, int wp1, int ground, int& mithril1)
{
   //For Knight:
   //Allow to use Excalibu sword
   const int maxhp = 999;
   const int minhp = 99;
   //rule i)
   int realHp1=baseHp1;
   //rule ii)
   if(wp1 == 0)
      realHp1 /= 10;
   //rule iii)   
   if(ground == baseHp1)
   {
      realHp1 += realHp1*10 / 100;
   }
   //rule iv)
   if(wp1 == 2)
   {
      mithril1 = 1;
   }
   //rule v)
   if(wp1 == 3)
      realHp1 *= 2;
   if(realHp1 > maxhp)
      realHp1 = maxhp;
   // cout<<"realhp1:"<<realHp1<<endl;
   return realHp1;

}
int calRealHp2(int baseHp2, int wp2, int ground, int& mithril2)
{
   const int maxhp = 888;
   const int minhp = 88;
   //For Knight:
   //Allow to use Excalibu sword

   //rule i)
   int realHp2=baseHp2;
   //rule ii)
   if(wp2 == 0)
      realHp2 /= 10;
   //rule iii)   
   if(ground == baseHp2)
   {
      realHp2 += realHp2*10 / 100;
   }
   //rule iv)
   if(wp2 == 2)
   {
      mithril2 = 1;
   }
   // cout<<"realhp2:"<<realHp2<<endl;
   return realHp2;
}