#pragma once
#include "MainHeader.h"

namespace Konsolowy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  tabControl1;
	protected:
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFile1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::SaveFileDialog^  saveFile1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->openFile1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFile1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Location = System::Drawing::Point(13, 13);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(259, 237);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->radioButton2);
			this->tabPage1->Controls->Add(this->radioButton1);
			this->tabPage1->Controls->Add(this->label12);
			this->tabPage1->Controls->Add(this->label11);
			this->tabPage1->Controls->Add(this->label10);
			this->tabPage1->Controls->Add(this->label9);
			this->tabPage1->Controls->Add(this->label8);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->listBox1);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(251, 211);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"BMP -> MMSS";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(84, 157);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(93, 17);
			this->radioButton2->TabIndex = 16;
			this->radioButton2->Text = L"Skala szaroœci";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(10, 157);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(68, 17);
			this->radioButton1->TabIndex = 15;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Kolorowy";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(214, 106);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(16, 13);
			this->label12->TabIndex = 14;
			this->label12->Text = L"...";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(136, 106);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(81, 13);
			this->label11->TabIndex = 13;
			this->label11->Text = L"Liczba kolorów:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(194, 94);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(16, 13);
			this->label10->TabIndex = 12;
			this->label10->Text = L"...";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(136, 94);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(60, 13);
			this->label9->TabIndex = 11;
			this->label9->Text = L"Wysokoœæ:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(194, 81);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(16, 13);
			this->label8->TabIndex = 10;
			this->label8->Text = L"...";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(136, 81);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(60, 13);
			this->label7->TabIndex = 9;
			this->label7->Text = L"Szerokoœæ:";
			this->label7->Click += gcnew System::EventHandler(this, &MyForm::label7_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(136, 68);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(93, 13);
			this->label6->TabIndex = 8;
			this->label6->Text = L"Informacje o pliku:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(57, 140);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(16, 13);
			this->label5->TabIndex = 7;
			this->label5->Text = L"...";
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(7, 140);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(53, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Wybrano:";
			this->label4->Click += gcnew System::EventHandler(this, &MyForm::label4_Click);
			// 
			// listBox1
			// 
			this->listBox1->DisplayMember = L"Sub";
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"None", L"Sub", L"Up", L"Average", L"Paeth" });
			this->listBox1->Location = System::Drawing::Point(10, 68);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 69);
			this->listBox1->TabIndex = 5;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 51);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(95, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Wybierz predyktor:";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(70, 182);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(112, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Konwertuj i zapisz";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(200, 24);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(45, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"...";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Enabled = false;
			this->textBox1->Location = System::Drawing::Point(4, 24);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(189, 20);
			this->textBox1->TabIndex = 1;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(4, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Wybierz plik:";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->button3);
			this->tabPage2->Controls->Add(this->button4);
			this->tabPage2->Controls->Add(this->textBox3);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(251, 211);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"MMSS -> BMP";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(70, 182);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(112, 23);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Konwertuj i zapisz";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(200, 24);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(45, 23);
			this->button4->TabIndex = 6;
			this->button4->Text = L"...";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// textBox3
			// 
			this->textBox3->Enabled = false;
			this->textBox3->Location = System::Drawing::Point(4, 24);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(189, 20);
			this->textBox3->TabIndex = 5;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(4, 7);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Wybierz plik:";
			// 
			// tabPage3
			// 
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(251, 211);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Informacje";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// openFile1
			// 
			this->openFile1->FileName = L"Wybierz plik...";
			this->openFile1->Filter = L"Mapa bitowa 6-bitowa (*.bmp)|*.bmp";
			// 
			// saveFile1
			// 
			this->saveFile1->FileName = L"image.mmss";
			this->saveFile1->Filter = L"Rozszerzenie graficzne typu MMSS (*.mmss)|*.mmss";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"Wybierz plik...";
			this->openFileDialog1->Filter = L"Rozszerzenie graficzne typu MMSS (*.mmss)|*.mmss";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileName = L"image.bmp";
			this->saveFileDialog1->Filter = L"Mapa bitowa 6-bitowa (*.bmp)|*.bmp";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->tabControl1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MyForm";
			this->Text = L"Konwerter BMP <-> MMSS";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
				 info i;
				 ConvertToMMSS cl;
				 infoAboutImage x;
				 openFile1->ShowDialog();
				 System::String ^path1 = openFile1->FileName;
				 textBox1->Text = path1;
				 char* pathChar = (char*)(void*)Marshal::StringToHGlobalAnsi(textBox1->Text);
				 int k = cl.ReadAndPrepare(pathChar);
				 x = i.GetInfo(pathChar);
				 label8->Text = System::Convert::ToString(x.width);
				 label10->Text = System::Convert::ToString(x.height);
				 label12->Text = System::Convert::ToString(x.colors);
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 //konwersja
				 ConvertToMMSS cl;
				 char* pathChar = (char*)(void*)Marshal::StringToHGlobalAnsi(textBox1->Text);
				 int k = cl.ReadAndPrepare(pathChar);
				 if (k == 0)
				 {
					 //zapisywanie
					 saveFile1->ShowDialog();
					 System::String ^path2 = saveFile1->FileName;
					 char* pathSave = (char*)(void*)Marshal::StringToHGlobalAnsi(path2);
					 int m = cl.saveFile(pathSave);
					 if (m == 0){
						 MessageBox::Show("Konwersja zakonczona");
					 }
				 }
	}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
{
	ConvertToBMP bmpC;
	char* pathChar2 = (char*)(void*)Marshal::StringToHGlobalAnsi(textBox3->Text);
	int k = bmpC.ReadAndPrepare(pathChar2);
	if (k == 0)
	{
		//zapisywanie
		saveFileDialog1->ShowDialog();
		System::String ^path3 = saveFileDialog1->FileName;
		char* pathSave1 = (char*)(void*)Marshal::StringToHGlobalAnsi(path3);
		int m = bmpC.saveFile(pathSave1);
		if (m == 0){
			MessageBox::Show("Konwersja zakonczona");
		}
	}
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) 
{
	openFileDialog1->ShowDialog();
	System::String ^path3 = openFileDialog1->FileName;
	textBox3->Text = path3;
	//WYBIERZ PLIK
}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 String^ curItem = listBox1->SelectedItem->ToString();
			 label5->Text = curItem;
}
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (radioButton1->Checked == 1)
			 {
				 radioButton2->Checked = 0;
			 }
}
private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (radioButton2->Checked == 1)
			 {
				 radioButton1->Checked = 0;
			 }
}
};
}
