#pragma once
#include <Windows.h>
#include "Config.h"

#include "AES.h"

#define SetBlockMode(x, y, z) (x) ? (EBM_128) : ((y) ? (EBM_192) : (EBM_256))
#define SetKeyMode(x, y, z) (x) ? (EKM_128) : ((y) ? (EKM_192) : (EKM_256))


namespace AESCLI {

	


	void open_file_dialog_for_textbox(TextBox^ textbox) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog;
		ofd->Filter = "All files (*.*) | *.*";
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			textbox->Text = ofd->FileName;
	}

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
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
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ Intro_Label;
	private: System::Windows::Forms::Label^ initialtext_label;
	private: System::Windows::Forms::TextBox^ initialtext_textbox;

	private: System::Windows::Forms::Button^ initialtext_open_button;
	private: System::Windows::Forms::Label^ finaltext_label;
	private: System::Windows::Forms::TextBox^ finaltext_textbox;
	private: System::Windows::Forms::Button^ finaltext_open_button;
	private: System::Windows::Forms::Label^ key_label;
	private: System::Windows::Forms::TextBox^ key_textbox;


	private: System::Windows::Forms::Label^ mode_label;
	private: System::Windows::Forms::Panel^ block_mode_panel;
	private: System::Windows::Forms::RadioButton^ block_mode_128_radiobutton;
	private: System::Windows::Forms::RadioButton^ block_mode_192_radiobutton;
	private: System::Windows::Forms::RadioButton^ block_mode_256_radiobutton;
	private: System::Windows::Forms::Panel^ key_mode_panel;

	private: System::Windows::Forms::RadioButton^ key_mode_128_radiobutton;
	private: System::Windows::Forms::RadioButton^ key_block_256_radiobutton;
	private: System::Windows::Forms::RadioButton^ key_mode_192_radiobutton;
	private: System::Windows::Forms::RadioButton^ encrypt_mode_radiobutton;
	private: System::Windows::Forms::RadioButton^ decrypt_mode_radiobutton;
	private: System::Windows::Forms::Button^ start_button;
	private: System::Windows::Forms::StatusStrip^ status_strip;
	private: System::Windows::Forms::ToolStripStatusLabel^ status_label;


		   LPCWSTR settings_ini_path = L".//settings.ini";
	private: System::Windows::Forms::Button^ look_button;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainWindow::typeid));
			this->Intro_Label = (gcnew System::Windows::Forms::Label());
			this->initialtext_label = (gcnew System::Windows::Forms::Label());
			this->initialtext_textbox = (gcnew System::Windows::Forms::TextBox());
			this->initialtext_open_button = (gcnew System::Windows::Forms::Button());
			this->finaltext_label = (gcnew System::Windows::Forms::Label());
			this->finaltext_textbox = (gcnew System::Windows::Forms::TextBox());
			this->finaltext_open_button = (gcnew System::Windows::Forms::Button());
			this->key_label = (gcnew System::Windows::Forms::Label());
			this->key_textbox = (gcnew System::Windows::Forms::TextBox());
			this->mode_label = (gcnew System::Windows::Forms::Label());
			this->block_mode_panel = (gcnew System::Windows::Forms::Panel());
			this->block_mode_256_radiobutton = (gcnew System::Windows::Forms::RadioButton());
			this->block_mode_192_radiobutton = (gcnew System::Windows::Forms::RadioButton());
			this->block_mode_128_radiobutton = (gcnew System::Windows::Forms::RadioButton());
			this->key_mode_panel = (gcnew System::Windows::Forms::Panel());
			this->key_block_256_radiobutton = (gcnew System::Windows::Forms::RadioButton());
			this->key_mode_192_radiobutton = (gcnew System::Windows::Forms::RadioButton());
			this->key_mode_128_radiobutton = (gcnew System::Windows::Forms::RadioButton());
			this->encrypt_mode_radiobutton = (gcnew System::Windows::Forms::RadioButton());
			this->decrypt_mode_radiobutton = (gcnew System::Windows::Forms::RadioButton());
			this->start_button = (gcnew System::Windows::Forms::Button());
			this->status_strip = (gcnew System::Windows::Forms::StatusStrip());
			this->status_label = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->look_button = (gcnew System::Windows::Forms::Button());
			this->block_mode_panel->SuspendLayout();
			this->key_mode_panel->SuspendLayout();
			this->status_strip->SuspendLayout();
			this->SuspendLayout();
			// 
			// Intro_Label
			// 
			this->Intro_Label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Intro_Label->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Intro_Label->Location = System::Drawing::Point(12, 9);
			this->Intro_Label->Name = L"Intro_Label";
			this->Intro_Label->Size = System::Drawing::Size(440, 18);
			this->Intro_Label->TabIndex = 0;
			this->Intro_Label->Text = L"AES";
			this->Intro_Label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// initialtext_label
			// 
			this->initialtext_label->AutoSize = true;
			this->initialtext_label->Location = System::Drawing::Point(13, 46);
			this->initialtext_label->Name = L"initialtext_label";
			this->initialtext_label->Size = System::Drawing::Size(48, 13);
			this->initialtext_label->TabIndex = 1;
			this->initialtext_label->Text = L"Initialtext";
			// 
			// initialtext_textbox
			// 
			this->initialtext_textbox->Location = System::Drawing::Point(67, 43);
			this->initialtext_textbox->Name = L"initialtext_textbox";
			this->initialtext_textbox->Size = System::Drawing::Size(353, 20);
			this->initialtext_textbox->TabIndex = 2;
			// 
			// initialtext_open_button
			// 
			this->initialtext_open_button->Location = System::Drawing::Point(426, 43);
			this->initialtext_open_button->Name = L"initialtext_open_button";
			this->initialtext_open_button->Size = System::Drawing::Size(26, 20);
			this->initialtext_open_button->TabIndex = 3;
			this->initialtext_open_button->Text = L"...";
			this->initialtext_open_button->UseVisualStyleBackColor = true;
			this->initialtext_open_button->Click += gcnew System::EventHandler(this, &MainWindow::initialtext_open_button_Click);
			// 
			// finaltext_label
			// 
			this->finaltext_label->AutoSize = true;
			this->finaltext_label->Location = System::Drawing::Point(13, 86);
			this->finaltext_label->Name = L"finaltext_label";
			this->finaltext_label->Size = System::Drawing::Size(46, 13);
			this->finaltext_label->TabIndex = 4;
			this->finaltext_label->Text = L"Finaltext";
			// 
			// finaltext_textbox
			// 
			this->finaltext_textbox->Location = System::Drawing::Point(67, 83);
			this->finaltext_textbox->Name = L"finaltext_textbox";
			this->finaltext_textbox->Size = System::Drawing::Size(353, 20);
			this->finaltext_textbox->TabIndex = 5;
			// 
			// finaltext_open_button
			// 
			this->finaltext_open_button->Location = System::Drawing::Point(426, 82);
			this->finaltext_open_button->Name = L"finaltext_open_button";
			this->finaltext_open_button->Size = System::Drawing::Size(26, 20);
			this->finaltext_open_button->TabIndex = 6;
			this->finaltext_open_button->Text = L"...";
			this->finaltext_open_button->UseVisualStyleBackColor = true;
			this->finaltext_open_button->Click += gcnew System::EventHandler(this, &MainWindow::finaltext_open_button_Click);
			// 
			// key_label
			// 
			this->key_label->AutoSize = true;
			this->key_label->Location = System::Drawing::Point(13, 126);
			this->key_label->Name = L"key_label";
			this->key_label->Size = System::Drawing::Size(25, 13);
			this->key_label->TabIndex = 7;
			this->key_label->Text = L"Key";
			// 
			// key_textbox
			// 
			this->key_textbox->Location = System::Drawing::Point(67, 123);
			this->key_textbox->Name = L"key_textbox";
			this->key_textbox->PasswordChar = '*';
			this->key_textbox->Size = System::Drawing::Size(353, 20);
			this->key_textbox->TabIndex = 8;
			// 
			// mode_label
			// 
			this->mode_label->AutoSize = true;
			this->mode_label->Location = System::Drawing::Point(13, 166);
			this->mode_label->Name = L"mode_label";
			this->mode_label->Size = System::Drawing::Size(34, 13);
			this->mode_label->TabIndex = 10;
			this->mode_label->Text = L"Mode";
			// 
			// block_mode_panel
			// 
			this->block_mode_panel->Controls->Add(this->block_mode_256_radiobutton);
			this->block_mode_panel->Controls->Add(this->block_mode_192_radiobutton);
			this->block_mode_panel->Controls->Add(this->block_mode_128_radiobutton);
			this->block_mode_panel->Location = System::Drawing::Point(67, 159);
			this->block_mode_panel->Name = L"block_mode_panel";
			this->block_mode_panel->Size = System::Drawing::Size(385, 30);
			this->block_mode_panel->TabIndex = 11;
			// 
			// block_mode_256_radiobutton
			// 
			this->block_mode_256_radiobutton->AutoSize = true;
			this->block_mode_256_radiobutton->Location = System::Drawing::Point(247, 5);
			this->block_mode_256_radiobutton->Name = L"block_mode_256_radiobutton";
			this->block_mode_256_radiobutton->Size = System::Drawing::Size(87, 17);
			this->block_mode_256_radiobutton->TabIndex = 14;
			this->block_mode_256_radiobutton->Text = L"Block 256 bit";
			this->block_mode_256_radiobutton->UseVisualStyleBackColor = true;
			// 
			// block_mode_192_radiobutton
			// 
			this->block_mode_192_radiobutton->AutoSize = true;
			this->block_mode_192_radiobutton->Location = System::Drawing::Point(125, 5);
			this->block_mode_192_radiobutton->Name = L"block_mode_192_radiobutton";
			this->block_mode_192_radiobutton->Size = System::Drawing::Size(87, 17);
			this->block_mode_192_radiobutton->TabIndex = 13;
			this->block_mode_192_radiobutton->Text = L"Block 192 bit";
			this->block_mode_192_radiobutton->UseVisualStyleBackColor = true;
			// 
			// block_mode_128_radiobutton
			// 
			this->block_mode_128_radiobutton->AutoSize = true;
			this->block_mode_128_radiobutton->Checked = true;
			this->block_mode_128_radiobutton->Location = System::Drawing::Point(3, 5);
			this->block_mode_128_radiobutton->Name = L"block_mode_128_radiobutton";
			this->block_mode_128_radiobutton->Size = System::Drawing::Size(87, 17);
			this->block_mode_128_radiobutton->TabIndex = 12;
			this->block_mode_128_radiobutton->TabStop = true;
			this->block_mode_128_radiobutton->Text = L"Block 128 bit";
			this->block_mode_128_radiobutton->UseVisualStyleBackColor = true;
			// 
			// key_mode_panel
			// 
			this->key_mode_panel->Controls->Add(this->key_block_256_radiobutton);
			this->key_mode_panel->Controls->Add(this->key_mode_192_radiobutton);
			this->key_mode_panel->Controls->Add(this->key_mode_128_radiobutton);
			this->key_mode_panel->Location = System::Drawing::Point(67, 188);
			this->key_mode_panel->Name = L"key_mode_panel";
			this->key_mode_panel->Size = System::Drawing::Size(385, 30);
			this->key_mode_panel->TabIndex = 12;
			// 
			// key_block_256_radiobutton
			// 
			this->key_block_256_radiobutton->AutoSize = true;
			this->key_block_256_radiobutton->Location = System::Drawing::Point(247, 7);
			this->key_block_256_radiobutton->Name = L"key_block_256_radiobutton";
			this->key_block_256_radiobutton->Size = System::Drawing::Size(78, 17);
			this->key_block_256_radiobutton->TabIndex = 2;
			this->key_block_256_radiobutton->Text = L"Key 256 bit";
			this->key_block_256_radiobutton->UseVisualStyleBackColor = true;
			// 
			// key_mode_192_radiobutton
			// 
			this->key_mode_192_radiobutton->AutoSize = true;
			this->key_mode_192_radiobutton->Location = System::Drawing::Point(125, 7);
			this->key_mode_192_radiobutton->Name = L"key_mode_192_radiobutton";
			this->key_mode_192_radiobutton->Size = System::Drawing::Size(78, 17);
			this->key_mode_192_radiobutton->TabIndex = 1;
			this->key_mode_192_radiobutton->Text = L"Key 192 bit";
			this->key_mode_192_radiobutton->UseVisualStyleBackColor = true;
			// 
			// key_mode_128_radiobutton
			// 
			this->key_mode_128_radiobutton->AutoSize = true;
			this->key_mode_128_radiobutton->Checked = true;
			this->key_mode_128_radiobutton->Location = System::Drawing::Point(3, 7);
			this->key_mode_128_radiobutton->Name = L"key_mode_128_radiobutton";
			this->key_mode_128_radiobutton->Size = System::Drawing::Size(78, 17);
			this->key_mode_128_radiobutton->TabIndex = 0;
			this->key_mode_128_radiobutton->TabStop = true;
			this->key_mode_128_radiobutton->Text = L"Key 128 bit";
			this->key_mode_128_radiobutton->UseVisualStyleBackColor = true;
			// 
			// encrypt_mode_radiobutton
			// 
			this->encrypt_mode_radiobutton->AutoSize = true;
			this->encrypt_mode_radiobutton->Checked = true;
			this->encrypt_mode_radiobutton->Location = System::Drawing::Point(70, 225);
			this->encrypt_mode_radiobutton->Name = L"encrypt_mode_radiobutton";
			this->encrypt_mode_radiobutton->Size = System::Drawing::Size(61, 17);
			this->encrypt_mode_radiobutton->TabIndex = 13;
			this->encrypt_mode_radiobutton->TabStop = true;
			this->encrypt_mode_radiobutton->Text = L"Encrypt";
			this->encrypt_mode_radiobutton->UseVisualStyleBackColor = true;
			// 
			// decrypt_mode_radiobutton
			// 
			this->decrypt_mode_radiobutton->AutoSize = true;
			this->decrypt_mode_radiobutton->Location = System::Drawing::Point(192, 225);
			this->decrypt_mode_radiobutton->Name = L"decrypt_mode_radiobutton";
			this->decrypt_mode_radiobutton->Size = System::Drawing::Size(62, 17);
			this->decrypt_mode_radiobutton->TabIndex = 14;
			this->decrypt_mode_radiobutton->Text = L"Decrypt";
			this->decrypt_mode_radiobutton->UseVisualStyleBackColor = true;
			// 
			// start_button
			// 
			this->start_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->start_button->Location = System::Drawing::Point(12, 252);
			this->start_button->Name = L"start_button";
			this->start_button->Size = System::Drawing::Size(440, 43);
			this->start_button->TabIndex = 15;
			this->start_button->Text = L"Start";
			this->start_button->UseVisualStyleBackColor = true;
			this->start_button->Click += gcnew System::EventHandler(this, &MainWindow::start_button_Click);
			// 
			// status_strip
			// 
			this->status_strip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->status_label });
			this->status_strip->Location = System::Drawing::Point(0, 305);
			this->status_strip->Name = L"status_strip";
			this->status_strip->Size = System::Drawing::Size(464, 22);
			this->status_strip->TabIndex = 16;
			this->status_strip->Text = L"statusStrip1";
			// 
			// status_label
			// 
			this->status_label->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->status_label->Name = L"status_label";
			this->status_label->Size = System::Drawing::Size(290, 17);
			this->status_label->Text = L"Enter file paths, select algorithm mode and press Start";
			// 
			// look_button
			// 
			this->look_button->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"look_button.Image")));
			this->look_button->Location = System::Drawing::Point(426, 123);
			this->look_button->Name = L"look_button";
			this->look_button->Size = System::Drawing::Size(26, 21);
			this->look_button->TabIndex = 17;
			this->look_button->UseVisualStyleBackColor = true;
			this->look_button->Click += gcnew System::EventHandler(this, &MainWindow::look_button_Click);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(464, 327);
			this->Controls->Add(this->look_button);
			this->Controls->Add(this->status_strip);
			this->Controls->Add(this->start_button);
			this->Controls->Add(this->decrypt_mode_radiobutton);
			this->Controls->Add(this->encrypt_mode_radiobutton);
			this->Controls->Add(this->key_mode_panel);
			this->Controls->Add(this->block_mode_panel);
			this->Controls->Add(this->mode_label);
			this->Controls->Add(this->key_textbox);
			this->Controls->Add(this->key_label);
			this->Controls->Add(this->finaltext_open_button);
			this->Controls->Add(this->finaltext_textbox);
			this->Controls->Add(this->finaltext_label);
			this->Controls->Add(this->initialtext_open_button);
			this->Controls->Add(this->initialtext_textbox);
			this->Controls->Add(this->initialtext_label);
			this->Controls->Add(this->Intro_Label);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainWindow";
			this->Text = L"AES";
			this->Load += gcnew System::EventHandler(this, &MainWindow::MainWindow_Load);
			this->block_mode_panel->ResumeLayout(false);
			this->block_mode_panel->PerformLayout();
			this->key_mode_panel->ResumeLayout(false);
			this->key_mode_panel->PerformLayout();
			this->status_strip->ResumeLayout(false);
			this->status_strip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: void save_new_settingsfile() {
	auto initialtext_path = Marshal::StringToHGlobalUni(initialtext_textbox->Text);
	auto finaltext_path = Marshal::StringToHGlobalUni(finaltext_textbox->Text);
	auto mk_path = Marshal::StringToHGlobalUni(key_textbox->Text);

	WritePrivateProfileString(L"Main", L"initialtext", (LPCWSTR)initialtext_path.ToPointer(), settings_ini_path);
	WritePrivateProfileString(L"Main", L"finaltext", (LPCWSTR)finaltext_path.ToPointer(), settings_ini_path);
	WritePrivateProfileString(L"Main", L"Key phrase", (LPCWSTR)mk_path.ToPointer(), settings_ini_path);

	Marshal::FreeHGlobal(initialtext_path);
	Marshal::FreeHGlobal(finaltext_path);
	Marshal::FreeHGlobal(mk_path);
}



private: System::Void initialtext_open_button_Click(System::Object^ sender, System::EventArgs^ e) {
		open_file_dialog_for_textbox(initialtext_textbox);
	}
private: System::Void finaltext_open_button_Click(System::Object^ sender, System::EventArgs^ e) {
	open_file_dialog_for_textbox(finaltext_textbox);
}
private: System::Void MainWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	FileInfo^ save_file = gcnew FileInfo(gcnew String(settings_ini_path));
	if (save_file->Exists) {
		const WORD SIZE = 256;
		TCHAR buffer[SIZE] = {};

		GetPrivateProfileString(L"Main", L"initialtext", L"", buffer, SIZE, settings_ini_path);
		initialtext_textbox->Text = gcnew String(buffer);
		GetPrivateProfileString(L"Main", L"finaltext", L"", buffer, SIZE, settings_ini_path);
		finaltext_textbox->Text = gcnew String(buffer);
		GetPrivateProfileString(L"Main", L"Key phrase", L"", buffer, SIZE, settings_ini_path);
		key_textbox->Text = gcnew String(buffer);
	}

}
private: System::Void start_button_Click(System::Object^ sender, System::EventArgs^ e) {
	status_label->Text = "Data initializating. . .";
	Application::DoEvents();

	String^ path_initialtext = initialtext_textbox->Text;
	String^ path_finaltext = finaltext_textbox->Text;

	File^ file_path;
	if (file_path->Exists(path_initialtext)) {
		E_BlockMode block_mode = SetBlockMode(block_mode_128_radiobutton->Checked, block_mode_192_radiobutton->Checked,
												block_mode_256_radiobutton->Checked);

		E_KeyMode key_mode = SetKeyMode(key_mode_128_radiobutton->Checked, key_mode_192_radiobutton->Checked,
										key_mode_256_radiobutton->Checked);
		E_EncryptMode encrypt_mode = (E_EncryptMode)encrypt_mode_radiobutton->Checked;
		
		String^ key_phrase = key_textbox->Text;

		status_label->Text = "AES process is working. . .";
		Application::DoEvents();

		AESProcess(path_initialtext, path_finaltext, key_phrase, block_mode, key_mode, encrypt_mode);
		
		status_label->Text = "Done! Result saved in " + finaltext_textbox->Text;

		save_new_settingsfile();
	}
	else
		status_label->Text = "Invalid paths to initialtext file";
}
private: System::Void look_button_Click(System::Object^ sender, System::EventArgs^ e) {
	key_textbox->PasswordChar = key_textbox->PasswordChar ? '\0' : '*';
}
};
}
