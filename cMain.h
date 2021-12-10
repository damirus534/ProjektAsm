#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
private:
	wxFont myFont = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

public:

	wxFont myFontGetter() {
		return this->myFont;
	}



	//constructor
	cMain();


	//destructor
	~cMain();

public:
	//Deklaracja przycisków
	wxButton* inputFileButton = nullptr; //Przycisk do wgrania pliku tekstowego
	wxButton* openOutputFileButton = nullptr; //Przycisk do otworzenia pliku tekstowego z wynikami
	wxButton* run = nullptr; //Przycisk do uruchomienia i wygenerowania pliku z wynikami

	//Deklaracja checkboxów (asm, c++)
	wxCheckBox* cppCheckBox = nullptr;
	wxCheckBox* asmCheckBox = nullptr;

	//labele stale
	wxStaticText* cppLabel = nullptr;
	wxStaticText* asmLabel = nullptr;
	wxStaticText* avarageTimeLabel = nullptr;
	wxStaticText* previousTimeLabel = nullptr;
	wxStaticText* oneOnSlider = nullptr;
	wxStaticText* sixtyFourOnSlider = nullptr;

	//labele zmienne
	wxStaticText* inputFileNameLabel = nullptr;
	wxStaticText* outputFileNameLabel = nullptr;
	wxStaticText* cppAvarageTimeLabel = nullptr;
	wxStaticText* cppLastTimeLabel = nullptr;
	wxStaticText* asmAvarageTimeLabel = nullptr;
	wxStaticText* asmLastTimeLabel = nullptr;
	wxStaticText* currentValueOnSlider = nullptr;

	//slider
	wxSlider* slider = nullptr;

	void onSliderChange(wxCommandEvent& evt);

	void onInputFileButtonClick(wxCommandEvent& evt);

	void onCppCheckBoxActivate(wxCommandEvent& evt);

	void onAsmCheckBoxActivate(wxCommandEvent& evt);

	void onRunButtonClick(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

};

