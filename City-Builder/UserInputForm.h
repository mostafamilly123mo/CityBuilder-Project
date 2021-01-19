#pragma once


#include "UsefulStuff.h"
#include "GLFWProgram.h"

namespace GUI
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public
	ref class UserInputForm : public System::Windows::Forms::Form
	{
		private:
		std::vector<std::pair<std::pair<int, int>, OBJECT_TYPE>>& objects;

		private:
		int& coolorMapWidth;

		private:
		System::Windows::Forms::Button^ run;

		private:
		int& colorMapHeight;

		private:
		unsigned int building4FloorsCount;

		private:
		OBJECT_TYPE selectedObject;

		private:
		GROUND_TYPE groundType;

		private:
		System::Windows::Forms::Label^ label1;

		private:
		System::Windows::Forms::ListBox^ environmentTimeList;

		private:
		System::Windows::Forms::Button^ clearAll;

		private:
		System::Windows::Forms::ListBox^ groundTexureList;

		private:
		System::Windows::Forms::Label^ label2;

		private:
		System::Windows::Forms::Button^ blend;

		private:
		System::Windows::Forms::RichTextBox^ building4FloorInput;

		private:
		System::Windows::Forms::Label^ label4;

		private:
		ENVIRONMENT_TIME environmentTime;

		public:
		UserInputForm(
			std::vector<std::pair<std::pair<int, int>, OBJECT_TYPE>>& objects,
			int& coolorMapWidth, int& colorMapHeight)
			: objects(objects),
			coolorMapWidth(coolorMapWidth),
			colorMapHeight(colorMapHeight)
		{
			InitializeComponent();

			this->coolorMapWidth = this->colorMap->Width;
			this->colorMapHeight = this->colorMap->Height;

			this->environmentTime = NONE;
			this->selectedObject = NOTHING;
		}

		protected:
		~UserInputForm()
		{
			if (components)
			{
				delete components;
			}
		}

		private:
		System::Windows::Forms::PictureBox^ colorMap;

		private:
		System::Windows::Forms::Button^ streetHorizontal;

		private:
		System::Windows::Forms::Button^ tree;

		private:
		System::Windows::Forms::Button^ building1;

		private:
		System::Windows::Forms::Button^ building2;

		private:
		System::Windows::Forms::Button^ building3;

		private:
		System::Windows::Forms::Button^ building4;

		private:
		System::Windows::Forms::Button^ car;

		private:
		System::Windows::Forms::Button^ lamp;

		private:
		System::Windows::Forms::Button^ streetVertical;

		private:
		System::ComponentModel::Container^ components;

		#pragma region Windows Form Designer generated code

		private:
		void InitializeComponent(void)
		{
			this->colorMap = (gcnew System::Windows::Forms::PictureBox());
			this->streetHorizontal = (gcnew System::Windows::Forms::Button());
			this->tree = (gcnew System::Windows::Forms::Button());
			this->building1 = (gcnew System::Windows::Forms::Button());
			this->building2 = (gcnew System::Windows::Forms::Button());
			this->building3 = (gcnew System::Windows::Forms::Button());
			this->building4 = (gcnew System::Windows::Forms::Button());
			this->car = (gcnew System::Windows::Forms::Button());
			this->lamp = (gcnew System::Windows::Forms::Button());
			this->streetVertical = (gcnew System::Windows::Forms::Button());
			this->run = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->environmentTimeList = (gcnew System::Windows::Forms::ListBox());
			this->clearAll = (gcnew System::Windows::Forms::Button());
			this->groundTexureList = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->blend = (gcnew System::Windows::Forms::Button());
			this->building4FloorInput = (gcnew System::Windows::Forms::RichTextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->colorMap))->BeginInit();
			this->SuspendLayout();
			// 
			// colorMap
			// 
			this->colorMap->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->colorMap->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->colorMap->Location = System::Drawing::Point(13, 13);
			this->colorMap->Name = L"colorMap";
			this->colorMap->Size = System::Drawing::Size(553, 648);
			this->colorMap->TabIndex = 0;
			this->colorMap->TabStop = false;
			this->colorMap->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &UserInputForm::colorMapPaint);
			this->colorMap->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &UserInputForm::colorMapMouseClicked);
			// 
			// streetHorizontal
			// 
			this->streetHorizontal->AutoSize = true;
			this->streetHorizontal->BackColor = System::Drawing::Color::DarkGray;
			this->streetHorizontal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->streetHorizontal->Location = System::Drawing::Point(572, 13);
			this->streetHorizontal->Name = L"streetHorizontal";
			this->streetHorizontal->Size = System::Drawing::Size(107, 40);
			this->streetHorizontal->TabIndex = 1;
			this->streetHorizontal->Text = L"Street H";
			this->streetHorizontal->UseVisualStyleBackColor = false;
			this->streetHorizontal->Click += gcnew System::EventHandler(this, &UserInputForm::streetHorizontalClicked);
			// 
			// tree
			// 
			this->tree->AutoSize = true;
			this->tree->BackColor = System::Drawing::Color::Green;
			this->tree->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tree->Location = System::Drawing::Point(572, 105);
			this->tree->Name = L"tree";
			this->tree->Size = System::Drawing::Size(107, 40);
			this->tree->TabIndex = 2;
			this->tree->Text = L"Tree";
			this->tree->UseVisualStyleBackColor = false;
			this->tree->Click += gcnew System::EventHandler(this, &UserInputForm::treeClicked);
			// 
			// building1
			// 
			this->building1->AutoSize = true;
			this->building1->BackColor = System::Drawing::Color::OrangeRed;
			this->building1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->building1->Location = System::Drawing::Point(572, 151);
			this->building1->Name = L"building1";
			this->building1->Size = System::Drawing::Size(107, 40);
			this->building1->TabIndex = 3;
			this->building1->Text = L"Building 1";
			this->building1->UseVisualStyleBackColor = false;
			this->building1->Click += gcnew System::EventHandler(this, &UserInputForm::building1Clicked);
			// 
			// building2
			// 
			this->building2->AutoSize = true;
			this->building2->BackColor = System::Drawing::Color::Sienna;
			this->building2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->building2->Location = System::Drawing::Point(572, 197);
			this->building2->Name = L"building2";
			this->building2->Size = System::Drawing::Size(107, 40);
			this->building2->TabIndex = 4;
			this->building2->Text = L"Building 2";
			this->building2->UseVisualStyleBackColor = false;
			this->building2->Click += gcnew System::EventHandler(this, &UserInputForm::building2Clicked);
			// 
			// building3
			// 
			this->building3->AutoSize = true;
			this->building3->BackColor = System::Drawing::Color::Chocolate;
			this->building3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->building3->Location = System::Drawing::Point(572, 243);
			this->building3->Name = L"building3";
			this->building3->Size = System::Drawing::Size(107, 40);
			this->building3->TabIndex = 5;
			this->building3->Text = L"Building 3";
			this->building3->UseVisualStyleBackColor = false;
			this->building3->Click += gcnew System::EventHandler(this, &UserInputForm::building3Clicked);
			// 
			// building4
			// 
			this->building4->AutoSize = true;
			this->building4->BackColor = System::Drawing::Color::Orange;
			this->building4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->building4->Location = System::Drawing::Point(572, 289);
			this->building4->Name = L"building4";
			this->building4->Size = System::Drawing::Size(107, 40);
			this->building4->TabIndex = 6;
			this->building4->Text = L"Building 4";
			this->building4->UseVisualStyleBackColor = false;
			this->building4->Click += gcnew System::EventHandler(this, &UserInputForm::building4Clicked);
			// 
			// car
			// 
			this->car->AutoSize = true;
			this->car->BackColor = System::Drawing::Color::Aqua;
			this->car->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->car->Location = System::Drawing::Point(572, 335);
			this->car->Name = L"car";
			this->car->Size = System::Drawing::Size(107, 40);
			this->car->TabIndex = 7;
			this->car->Text = L"Car";
			this->car->UseVisualStyleBackColor = false;
			this->car->Click += gcnew System::EventHandler(this, &UserInputForm::carClicked);
			// 
			// lamp
			// 
			this->lamp->AutoSize = true;
			this->lamp->BackColor = System::Drawing::Color::Gold;
			this->lamp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lamp->Location = System::Drawing::Point(572, 381);
			this->lamp->Name = L"lamp";
			this->lamp->Size = System::Drawing::Size(107, 40);
			this->lamp->TabIndex = 8;
			this->lamp->Text = L"Lamp";
			this->lamp->UseVisualStyleBackColor = false;
			this->lamp->Click += gcnew System::EventHandler(this, &UserInputForm::lampClicked);
			// 
			// streetVertical
			// 
			this->streetVertical->AutoSize = true;
			this->streetVertical->BackColor = System::Drawing::Color::DarkGray;
			this->streetVertical->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->streetVertical->Location = System::Drawing::Point(572, 59);
			this->streetVertical->Name = L"streetVertical";
			this->streetVertical->Size = System::Drawing::Size(107, 40);
			this->streetVertical->TabIndex = 9;
			this->streetVertical->Text = L"Street V";
			this->streetVertical->UseVisualStyleBackColor = false;
			this->streetVertical->Click += gcnew System::EventHandler(this, &UserInputForm::streetVerticalClicked);
			// 
			// run
			// 
			this->run->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->run->Location = System::Drawing::Point(572, 576);
			this->run->Name = L"run";
			this->run->Size = System::Drawing::Size(232, 84);
			this->run->TabIndex = 10;
			this->run->Text = L"RUN";
			this->run->UseVisualStyleBackColor = true;
			this->run->Click += gcnew System::EventHandler(this, &UserInputForm::runGLFW);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(685, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(162, 25);
			this->label1->TabIndex = 11;
			this->label1->Text = L"Environment time";
			// 
			// environmentTimeList
			// 
			this->environmentTimeList->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->environmentTimeList->FormattingEnabled = true;
			this->environmentTimeList->ItemHeight = 25;
			this->environmentTimeList->Items->AddRange(gcnew cli::array< System::Object^  >(2)
			{
				L"DAY", L"NIGHT"
			});
			this->environmentTimeList->Location = System::Drawing::Point(690, 41);
			this->environmentTimeList->Name = L"environmentTimeList";
			this->environmentTimeList->Size = System::Drawing::Size(205, 29);
			this->environmentTimeList->TabIndex = 12;
			this->environmentTimeList->SelectedIndexChanged += gcnew System::EventHandler(this, &UserInputForm::environmentTimeChanged);
			// 
			// clearAll
			// 
			this->clearAll->AutoSize = true;
			this->clearAll->BackColor = System::Drawing::Color::Transparent;
			this->clearAll->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->clearAll->Location = System::Drawing::Point(695, 427);
			this->clearAll->Name = L"clearAll";
			this->clearAll->Size = System::Drawing::Size(107, 40);
			this->clearAll->TabIndex = 13;
			this->clearAll->Text = L"clear";
			this->clearAll->UseVisualStyleBackColor = false;
			this->clearAll->Click += gcnew System::EventHandler(this, &UserInputForm::clearAllClicked);
			// 
			// groundTexureList
			// 
			this->groundTexureList->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->groundTexureList->FormattingEnabled = true;
			this->groundTexureList->ItemHeight = 25;
			this->groundTexureList->Items->AddRange(gcnew cli::array< System::Object^  >(4)
			{
				L"Rocks", L"Grass", L"Solid", L"Sand"
			});
			this->groundTexureList->Location = System::Drawing::Point(690, 133);
			this->groundTexureList->Name = L"groundTexureList";
			this->groundTexureList->Size = System::Drawing::Size(205, 29);
			this->groundTexureList->TabIndex = 16;
			this->groundTexureList->SelectedIndexChanged += gcnew System::EventHandler(this, &UserInputForm::groundTextureClicked);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(690, 105);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(141, 25);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Ground texture";
			// 
			// blend
			// 
			this->blend->AutoSize = true;
			this->blend->BackColor = System::Drawing::Color::WhiteSmoke;
			this->blend->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->blend->Location = System::Drawing::Point(572, 427);
			this->blend->Name = L"blend";
			this->blend->Size = System::Drawing::Size(107, 40);
			this->blend->TabIndex = 17;
			this->blend->Text = L"blend";
			this->blend->UseVisualStyleBackColor = false;
			this->blend->Click += gcnew System::EventHandler(this, &UserInputForm::blendClicked);
			// 
			// building4FloorInput
			// 
			this->building4FloorInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->building4FloorInput->Location = System::Drawing::Point(810, 295);
			this->building4FloorInput->Name = L"building4FloorInput";
			this->building4FloorInput->Size = System::Drawing::Size(85, 31);
			this->building4FloorInput->TabIndex = 18;
			this->building4FloorInput->Text = L"0";
			this->building4FloorInput->TextChanged += gcnew System::EventHandler(this, &UserInputForm::building4FloorInputChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(692, 295);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(112, 25);
			this->label4->TabIndex = 20;
			this->label4->Text = L"floors count";
			// 
			// UserInputForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(921, 673);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->building4FloorInput);
			this->Controls->Add(this->blend);
			this->Controls->Add(this->groundTexureList);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->clearAll);
			this->Controls->Add(this->environmentTimeList);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->run);
			this->Controls->Add(this->streetVertical);
			this->Controls->Add(this->lamp);
			this->Controls->Add(this->car);
			this->Controls->Add(this->building4);
			this->Controls->Add(this->building3);
			this->Controls->Add(this->building2);
			this->Controls->Add(this->building1);
			this->Controls->Add(this->tree);
			this->Controls->Add(this->streetHorizontal);
			this->Controls->Add(this->colorMap);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"UserInputForm";
			this->Text = L"OpenGL DEMO";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->colorMap))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		#pragma endregion

		private:
		System::Void colorMapMouseClicked(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			int x = e->X, y = e->Y;

			Brush^ color;
			int width, height;

			Graphics^ g = colorMap->CreateGraphics();

			if (selectedObject == STREET_HORIZONTAL)
			{
				color = Brushes::DarkGray;
				width = 350;
				height = 20;
				objects.push_back(
					std::make_pair(std::make_pair(x, y), STREET_HORIZONTAL));
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
			}

			if (selectedObject == STREET_VERTICAL)
			{
				color = Brushes::DarkGray;
				width = 20;
				height = 350;
				objects.push_back(std::make_pair(std::make_pair(x, y), STREET_VERTICAL));
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
			}

			if (selectedObject == TREE)
			{
				color = Brushes::Green;
				width = height = 10;
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
				objects.push_back(std::make_pair(std::make_pair(x, y), TREE));
			}

			if (selectedObject == BUILDING1)
			{
				color = Brushes::OrangeRed;
				width = height = 40;
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
				y += 25;
				objects.push_back(std::make_pair(std::make_pair(x, y), BUILDING1));
			}

			if (selectedObject == BUILDING2)
			{
				color = Brushes::Sienna;
				width = 80;
				height = 120;
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
				objects.push_back(std::make_pair(std::make_pair(x, y), BUILDING2));
			}

			if (selectedObject == BUILDING3)
			{
				color = Brushes::Chocolate;
				width = 100;
				height = 100;
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
				x += 20;
				y += 80;
				objects.push_back(std::make_pair(std::make_pair(x, y), BUILDING3));
			}

			if (selectedObject == BUILDING4)
			{
				color = Brushes::Orange;
				width = height = 100;
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
				x += 30;
				y += 15;
				objects.push_back(std::make_pair(std::make_pair(x, y), BUILDING4));
			}

			if (selectedObject == CAR)
			{
				color = Brushes::Aqua;
				width = height = 15;
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
				objects.push_back(std::make_pair(std::make_pair(x, y), CAR));
			}

			if (selectedObject == LAMP)
			{
				color = Brushes::Gold;
				width = height = 10;
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
				objects.push_back(std::make_pair(std::make_pair(x, y), LAMP));
			}

			if (selectedObject == BLENDING_OBJECT)
			{
				color = Brushes::WhiteSmoke;
				;
				width = height = 20;
				x = x - width / 2;
				y = y - height / 2;
				g->FillRectangle(color, x, y, width, height);
				objects.push_back(std::make_pair(std::make_pair(x, y), BLENDING_OBJECT));
			}
		}

		private:
		System::Void streetHorizontalClicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = STREET_HORIZONTAL;
		}

		private:
		System::Void streetVerticalClicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = STREET_VERTICAL;
		}

		private:
		System::Void treeClicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = TREE;
		}

		private:
		System::Void building1Clicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = BUILDING1;
		}

		private:
		System::Void building2Clicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = BUILDING2;
		}

		private:
		System::Void building3Clicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = BUILDING3;
		}

		private:
		System::Void building4Clicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = BUILDING4;
		}

		private:
		System::Void carClicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = CAR;
		}

		private:
		System::Void lampClicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = LAMP;
		}

		private:
		System::Void blendClicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->selectedObject = BLENDING_OBJECT;
		}

		private:
		System::Void colorMapPaint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;

			Pen^ pen = gcnew Pen(Color::Red, 1);
			SolidBrush^ brush = gcnew SolidBrush(Color::Red);
			SolidBrush^ brush_2 = gcnew SolidBrush(Color::White);

			for (int i = 0; i < colorMap->Width; i += 25)
			{
				for (int j = 0; j < colorMap->Height; j += 25)
				{
					g->DrawRectangle(pen, i, j, 50, 50);
					g->FillEllipse(brush, i - 1.5, j - 1.5, 5, 5);
				}
			}

			g->FillEllipse(brush_2, colorMap->Width / 2, colorMap->Height / 2, 10, 10);
		}

		private:
		System::Void runGLFW(System::Object^ sender, System::EventArgs^ e)
		{
			//============================================================
			// start the glfw window
			if (GLFWRunner())
			{
				render(objects, coolorMapWidth, colorMapHeight, environmentTime, groundType, building4FloorsCount);
				GLFWDestroyer();
			}
			//============================================================
		}

		private:
		System::Void environmentTimeChanged(System::Object^ sender, System::EventArgs^ e)
		{
			int selectedIndex = environmentTimeList->SelectedIndex;
			switch (selectedIndex)
			{
				case 0:
					this->environmentTime = DAY;
					break;
				case 1:
					this->environmentTime = NIGHT;
					break;
				default:
					this->environmentTime = NONE;
					break;
			}
		}

		private:
		System::Void clearAllClicked(System::Object^ sender, System::EventArgs^ e)
		{
			this->colorMap->Refresh();
			this->objects.clear();
		}

		private:
		System::Void groundTextureClicked(System::Object^ sender, System::EventArgs^ e)
		{
			// L"Rocks" , L"Grass", L"Solid", L"Sand"
			int selectedIndex = groundTexureList->SelectedIndex;
			switch (selectedIndex)
			{
				case 0:
					this->groundType = ROCKS;
					break;
				case 1:
					this->groundType = GRASS;
					break;
				case 2:
					this->groundType = SOLID;
					break;
				case 3:
					this->groundType = SAND;
					break;
			}
		}

		private:
		System::Void building4FloorInputChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (this->building4FloorInput->Text != "")
				this->building4FloorsCount =
				UInt32::Parse(this->building4FloorInput->Text);
		}
	};
}  // namespace GUI
