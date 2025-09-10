//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "jpeg.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
if (OpenPictureDialog1->Execute())
  {
    AnsiString CurrentFile = OpenPictureDialog1->FileName;
    Image1->Picture->LoadFromFile(CurrentFile);
  }
  Image1->Visible=true;        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
if (OpenPictureDialog1->Execute())
  {
    AnsiString CurrentFile = OpenPictureDialog1->FileName;
    Image2->Picture->LoadFromFile(CurrentFile);
  }
  Image2->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
ADOTable1->Edit();
       TMemoryStream* strm = new TMemoryStream();
       Image1->Picture->Graphic->SaveToStream(strm);
       ((TGraphicField*)Form1->ADOTable1->FieldByName("Img_1"))->LoadFromStream(strm);
       delete strm;
       Form1->ADOTable1->Post();
        Image1->Visible=true;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
ADOTable1->Edit();
       TMemoryStream* strm = new TMemoryStream();
       Image2->Picture->Graphic->SaveToStream(strm);
       ((TGraphicField*)Form1->ADOTable1->FieldByName("Img_2"))->LoadFromStream(strm);
       delete strm;
       Form1->ADOTable1->Post();
        Image2->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1CellClick(TColumn *Column)
{
 if(!(TBlobField*)ADOTable1->FieldByName("Img_1")->IsNull){
       if(!Image1->Visible)Image1->Visible=true;
       TMemoryStream* strm = new TMemoryStream;
       TJPEGImage *ptJpg=new TJPEGImage;
        ((TGraphicField*)ADOTable1->FieldByName("Img_1"))->SaveToStream(strm);
        strm->Seek(0,0);
        if (*(Word*)strm->Memory == 0xD8FF)Image1->Picture->Graphic=ptJpg;
        Image1->Picture->Graphic->LoadFromStream(strm);
        delete strm;
        delete ptJpg;
      }else
      // видимость картинки
      Image1->Visible=false;

  if(!(TBlobField*)ADOTable1->FieldByName("Img_2")->IsNull){
       if(!Image2->Visible)Image2->Visible=true;
       TMemoryStream* strm = new TMemoryStream;
       TJPEGImage *ptJpg=new TJPEGImage;
        ((TGraphicField*)ADOTable1->FieldByName("Img_2"))->SaveToStream(strm);
        strm->Seek(0,0);
        if (*(Word*)strm->Memory == 0xD8FF)Image2->Picture->Graphic=ptJpg;
        Image2->Picture->Graphic->LoadFromStream(strm);
        delete strm;
        delete ptJpg;
      }else
      // видимость картинки
      Image2->Visible=false;



}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
 Image1->Visible=false;
 Image2->Visible=false;
 
//Ширина столбцов
DBGrid1->Columns->Items[0]->Width =50;
DBGrid1->Columns->Items[0]->Visible=false;

DBGrid1->Columns->Items[1]->Width =300;
DBGrid1->Columns->Items[1]->Title->Caption = "Видеокарта";

DBGrid1->Columns->Items[2]->Width =80;
DBGrid1->Columns->Items[2]->Title->Caption = "Количество";

DBGrid1->Columns->Items[3]->Width =80;
DBGrid1->Columns->Items[3]->Title->Caption = "Цена";

DBGrid1->Columns->Items[4]->Width =150;
DBGrid1->Columns->Items[4]->Title->Caption = "Интерфейс";

DBGrid1->Columns->Items[5]->Width =220;
DBGrid1->Columns->Items[5]->Title->Caption = "Производитель графического процессора";

DBGrid1->Columns->Items[6]->Width =150;
DBGrid1->Columns->Items[6]->Title->Caption = "Графический процессор";

DBGrid1->Columns->Items[7]->Width =150;
DBGrid1->Columns->Items[7]->Title->Caption = "Частота граф. процессора";

DBGrid1->Columns->Items[8]->Width =110;
DBGrid1->Columns->Items[8]->Title->Caption = "Количество потоков";

DBGrid1->Columns->Items[9]->Width =120;
DBGrid1->Columns->Items[9]->Title->Caption = "Объем видеопамяти";

DBGrid1->Columns->Items[10]->Width =100;
DBGrid1->Columns->Items[10]->Title->Caption = "Тип видеопамяти";

DBGrid1->Columns->Items[11]->Width =150;
DBGrid1->Columns->Items[11]->Title->Caption = "Частота памяти";

DBGrid1->Columns->Items[12]->Width =120;
DBGrid1->Columns->Items[12]->Title->Caption = "Ширина шины памяти";

DBGrid1->Columns->Items[13]->Width =70;
DBGrid1->Columns->Items[13]->Title->Caption = "DirectX";

DBGrid1->Columns->Items[14]->Width =150;
DBGrid1->Columns->Items[14]->Title->Caption = "Мощность блока питания";

DBGrid1->Columns->Items[15]->Width =100;
DBGrid1->Columns->Items[15]->Title->Caption = "Гарантия";

DBGrid1->Columns->Items[16]->Width =150;
DBGrid1->Columns->Items[17]->Width =150;
DBGrid1->Columns->Items[18]->Width =150;

DBGrid1->Columns->Items[16]->Visible=false;
DBGrid1->Columns->Items[17]->Visible=false;
DBGrid1->Columns->Items[18]->Visible=false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
Form1->ADOTable1->Delete();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  Form2->Show();
  Form1->ADOTable1->Edit();
  Form2->Edit1->Text=Form1->ADOTable1->FieldByName("Videocard")->AsString;
  Form2->Edit2->Text=Form1->ADOTable1->FieldByName("Kol")->AsString;
  Form2->Edit3->Text=Form1->ADOTable1->FieldByName("Cena")->AsString;
  Form2->Edit4->Text=Form1->ADOTable1->FieldByName("Interface")->AsString;
  Form2->Edit5->Text=Form1->ADOTable1->FieldByName("Proizv_graf_processora")->AsString;
  Form2->Edit6->Text=Form1->ADOTable1->FieldByName("Graf_processor")->AsString;
  Form2->Edit7->Text=Form1->ADOTable1->FieldByName("Chastota_graf_processora")->AsString;
  Form2->Edit8->Text=Form1->ADOTable1->FieldByName("Kol_potok_processov")->AsString;
  Form2->Edit9->Text=Form1->ADOTable1->FieldByName("Obiem_videopamiati")->AsString;
  Form2->Edit10->Text=Form1->ADOTable1->FieldByName("Tip_videopam")->AsString;
  Form2->Edit11->Text=Form1->ADOTable1->FieldByName("Chastota_pamiati")->AsString;
  Form2->Edit12->Text=Form1->ADOTable1->FieldByName("Shirina_shini_pamiati")->AsString;
  Form2->Edit13->Text=Form1->ADOTable1->FieldByName("DirectX")->AsString;
  Form2->Edit14->Text=Form1->ADOTable1->FieldByName("Mosnost_bloka_pit")->AsString;
  Form2->Edit15->Text=Form1->ADOTable1->FieldByName("Garantia")->Text;
  //Form2->ListBox1->Text=Form1->ADOTable1->FieldByName("Others")->AsString;
    Form1->ADOTable1->Post();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid1TitleClick(TColumn *Column)
{
// сортировка
 if (ADOTable1->Active)
  if ((ADOTable1->Sort.Pos(Column->FieldName) > 0) && (ADOTable1->Sort.Pos("ASC") > 0))
     ADOTable1->Sort = Column->FieldName + " DESC";
   else ADOTable1->Sort = Column->FieldName + " ASC";        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
   Form3->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
if (Edit1->Text!="")
{
ADOTable1->Filtered=false;
ADOTable1->Filter="Videocard LIKE '" + Edit1->Text + "%'";
ADOTable1->Filtered = true;   }
  else
 {     if (Edit1->Text=="")
    ADOTable1->Filtered=false;
}        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
if (Edit2->Text!="")
{
ADOTable1->Filtered=false;
ADOTable1->Filter="Proizv_graf_processora LIKE '" + Edit2->Text + "%'";
ADOTable1->Filtered = true;   }
  else
 {     if (Edit2->Text=="")
    ADOTable1->Filtered=false;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
if (Edit3->Text!="")
{
ADOTable1->Filtered=false;
ADOTable1->Filter="Graf_processor LIKE '" + Edit3->Text + "%'";
ADOTable1->Filtered = true;   }
  else
 {     if (Edit3->Text=="")
    ADOTable1->Filtered=false;
}
}
//---------------------------------------------------------------------------

