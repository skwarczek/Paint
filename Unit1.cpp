//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop               // Za�adowanie bibliotek

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
TForm1 *Form1;
int startx,starty,endx,endy,szerokosc;  //deklaracja zmiennych
enum tryb{wybor,linia,liniastart,kwadrat,kwadratstart,kolo,kolostart,
wypelnienie,olowek,olowekstart,gumka,gumkastart}t,oldt;  //deklarowania sta�ych liczbowych w trybie wyliczeniowym

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  DoubleBuffered=true;   //Podw�jne buforowanie naprawia migotanie obrazu
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender,   //Zdarzenia po nacisnieciu klawisza myszy
      TMouseButton Button, TShiftState Shift, int X, int Y)
{


  if (t==linia){   //Narz�dzie rysowania Lini przypisanie wsp�rz�dnych X i Y
   oldt=t;
   t=liniastart;
   startx=endx=X;
   starty=endy=Y;
  }

  if (t==kwadrat){    //Narz�dzie rysowania Kwadratu przypisanie wsp�rz�dnych X i Y
   oldt=t;
   t=kwadratstart;
   startx=endx=X;
   starty=endy=Y;
  }

  if (t==kolo){   //Narz�dzie rysowania Ko�a przypisanie wsp�rz�dnych X i Y
   oldt=t;
   t=kolostart;
   startx=endx=X;
   starty=endy=Y;
  }

  if (t==wypelnienie){     //Narz�dzie wype�nienia obiekt�w przypisanie wsp�rz�dnych X i Y
        Image1->Canvas->Brush->Color=CColorGrid1->ForegroundColor;
        Image1->Canvas->FloodFill(X, Y, Image1->Canvas->Pixels[X][Y],fsSurface);
}

  if (t==olowek){  //Narz�dzie rysowania O��wek przypisanie wsp�rz�dnych X i Y
     oldt=t;
     t=olowekstart;
      Image1->Canvas->MoveTo(X,Y);

}

  if (t==gumka){   //Narz�dzie gumka przypisanie wsp�rz�dnych X i Y
      oldt=t;
      t=gumkastart;
      Image1->Canvas->MoveTo(X,Y);
}      

}

//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
     t=linia;    //Przypisanie do przycisku funkcji Lini
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)                 //Zdarzenia podczas ruszania myszk�
{

if (t==liniastart){
      Image1->Canvas->Pen->Color=clRed;
      Image1->Canvas->Pen->Mode=pmXor;
      Image1->Canvas->MoveTo(startx,starty);
      Image1->Canvas->LineTo(endx,endy);
      Image1->Canvas->MoveTo(startx,starty);
      Image1->Canvas->LineTo(X,Y);
      endx=X;
      endy=Y;
}

if (t==kwadratstart){
        Image1->Canvas->Pen->Color=clRed;
        Image1->Canvas->Brush->Style=bsClear;
        Image1->Canvas->Pen->Mode=pmXor;
        Image1->Canvas->Rectangle(startx,starty,endx,endy);
        Image1->Canvas->Rectangle(startx,starty,X,Y);
        endx=X;
        endy=Y;
}

if(t==kolostart){
      Image1->Canvas->Pen->Color=clRed;
      Image1->Canvas->Brush->Style=bsClear;
      Image1->Canvas->Pen->Mode=pmXor;
      Image1->Canvas->Ellipse(startx,starty,endx,endy);
      Image1->Canvas->Ellipse(startx,starty,X,Y);
      endx=X;
      endy=Y;
  }

if (t==olowekstart){
       Image1->Canvas->Pen->Width=szerokosc;
       Image1->Canvas->Pen->Color=clBlack;
       Image1->Canvas->Pen->Mode=pmCopy;
       Image1->Canvas->Pen->Color=CColorGrid1->ForegroundColor;
       Image1->Canvas->LineTo(X,Y);
}

if (t==gumkastart){
       Image1->Canvas->Pen->Width=20;
       Image1->Canvas->Pen->Color=clWhite;
       Image1->Canvas->LineTo(X,Y);
}
  }
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)           //zdarzenia po zwolnieniu przycisku myszy
{
   if (t==liniastart){
      Image1->Canvas->Pen->Width=szerokosc;
      Image1->Canvas->Pen->Color=CColorGrid1->ForegroundColor;
      Image1->Canvas->Pen->Mode=pmCopy;
      Image1->Canvas->MoveTo(startx,starty);
      Image1->Canvas->LineTo(X,Y);
      t=oldt;
}

if (t==kwadratstart){
        Image1->Canvas->Pen->Width=szerokosc;
        Image1->Canvas->Pen->Color=CColorGrid1->ForegroundColor;
        Image1->Canvas->Pen->Mode=pmCopy;
        Image1->Canvas->Brush->Style=bsClear;
        Image1->Canvas->Rectangle(startx,starty,endx,endy);
        endx=X;
        endy=Y;
        t=oldt;
}

if (t==kolostart){
       Image1->Canvas->Pen->Width=szerokosc;
       Image1->Canvas->Pen->Color=CColorGrid1->ForegroundColor;
       Image1->Canvas->Pen->Mode=pmCopy;
       Image1->Canvas->Brush->Style=bsClear;
       Image1->Canvas->Ellipse(startx,starty,X,Y);
       endx=X;
       endy=Y;
       t=oldt;
}

if (t==olowekstart){
      t=oldt;
}

if (t==gumkastart){
      t=oldt;
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
szerokosc=ComboBox1->Text.ToInt();  //funkcja grubosci rysowanych obiekt�w      
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
t=kwadrat;  //Przypisanie do przycisku funkcji kwadratu
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
t=kolo; //Przypisanie do przycisku funkcji ko�a
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
t=wypelnienie;  //Przypisanie do przycisku funkcji wype�nienia
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
t=olowek;  //Przypisanie do przycisku funkcji o��wka

}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
t=gumka;  //Przypisanie do przycisku funkcji gumki
}
//---------------------------------------------------------------------------

void __fastcall TForm1::New1Click(TObject *Sender)
{                                                //Funkcja tworzenia nowego dokumentu
Image1->Canvas->Brush->Style=bsSolid;
        Image1->Canvas->Brush->Color=clWhite;
        Image1->Canvas->Rectangle(-1,-1,Image1->Width+10,Image1->Height+50);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
Close(); //Funkcja zamykania programu
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Open1Click(TObject *Sender)
{                                        //funkcja Otwierania dokumentu
OpenPictureDialog1->Execute();
        Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Save1Click(TObject *Sender)
{                                              //funkcja zapisywania dokumentu
SavePictureDialog1->Execute();
        Image1->Picture->SaveToFile(SavePictureDialog1->FileName + ".bmp");        
}
//---------------------------------------------------------------------------

