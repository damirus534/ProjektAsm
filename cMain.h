#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class cMain : public wxFrame
{
private:
	wxFont myFont = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

public:

	wxFont myFontGetter() {
		return this->myFont;
	}

	//loading asm dll
	typedef int(_fastcall* AsmGausEliminationLib)(float* tablicaJednowymiarowa, int xLength, int yLength, float* tablicaWynikow);
	HINSTANCE dllHandle = NULL;

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
	wxStaticText* TimeLabel = nullptr;
	wxStaticText* oneOnSlider = nullptr;
	wxStaticText* sixtyFourOnSlider = nullptr;

	//labele zmienne
	wxStaticText* inputFileNameLabel = nullptr;
	wxStaticText* outputFileNameLabel = nullptr;
	wxStaticText* cppTimeLabel = nullptr;
	wxStaticText* asmTimeLabel = nullptr;
	wxStaticText* currentValueOnSlider = nullptr;

	//slider
	wxSlider* slider = nullptr;

	void onSliderChange(wxCommandEvent& evt);

	void onInputFileButtonClick(wxCommandEvent& evt);

	void onCppCheckBoxActivate(wxCommandEvent& evt);

	void onAsmCheckBoxActivate(wxCommandEvent& evt);

	void onRunButtonClick(wxCommandEvent& evt);

	void onOpenOutputFileButton(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();

};

