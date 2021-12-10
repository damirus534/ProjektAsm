#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_SLIDER(22, onSliderChange)
	EVT_BUTTON(20, onInputFileButtonClick)
	EVT_CHECKBOX(41, onCppCheckBoxActivate)
	EVT_CHECKBOX(42, onAsmCheckBoxActivate)
	EVT_BUTTON(1, onRunButtonClick)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "ProjektAsm", wxPoint(560, 240),wxSize(800,600)) {

	//przyciski
	inputFileButton = new wxButton(this, 20, "Wgraj plik", wxPoint(10, 10), wxSize(120, 30));
	openOutputFileButton = new wxButton(this, wxID_ANY, "Otworz plik", wxPoint(340, 10), wxSize(120, 30));
	run = new wxButton(this, 1, "Uruchom", wxPoint(630, 500), wxSize(120, 30));
	run->Disable();

	//checkboxy
	cppCheckBox = new wxCheckBox(this, 41, "c++", wxPoint(10, 120), wxSize(60, 15));
	asmCheckBox = new wxCheckBox(this, 42, "asm", wxPoint(10, 140), wxSize(60, 15));
	cppCheckBox->SetFont(myFont);
	asmCheckBox->SetFont(myFont);


	//slider
	slider = new wxSlider(this, 22, 1, 1, 64, wxPoint(40, 320), wxSize(420, 25));

	//labele stale
	cppLabel = new wxStaticText(this, wxID_ANY, "c++", wxPoint(250, 120), wxSize(25, 15));
	asmLabel = new wxStaticText(this, wxID_ANY, "asm", wxPoint(250, 140), wxSize(25, 15));
	avarageTimeLabel = new wxStaticText(this, wxID_ANY, "avarage time", wxPoint(300, 100), wxSize(100, 15));
	previousTimeLabel = new wxStaticText(this, wxID_ANY, "previous time", wxPoint(400, 100), wxSize(100, 15));
	oneOnSlider = new wxStaticText(this, wxID_ANY, "1", wxPoint(30, 325), wxSize(10, 20));
	sixtyFourOnSlider = new wxStaticText(this, wxID_ANY, "64", wxPoint(460, 325), wxSize(20, 20));

	//labele zmienne
	currentValueOnSlider = new wxStaticText(this, wxID_ANY, "1", wxPoint(240, 345), wxSize(20, 20));
	inputFileNameLabel = new wxStaticText(this, wxID_ANY, "", wxPoint(135, 16), wxSize(120, 20));

	//ustawienie fonta w labelach
	cppLabel->SetFont(myFont);
	asmLabel->SetFont(myFont);
	avarageTimeLabel->SetFont(myFont);
	previousTimeLabel->SetFont(myFont);


}

cMain::~cMain() {

}

void cMain::onSliderChange(wxCommandEvent& evt) { //metoda zmieniajaca liczbe na labelu na aktualna z slidera(liczba watkow)
	int currentValueInt = slider->GetValue();
	wxString currentValueWxString;
	currentValueWxString << currentValueInt;
	currentValueOnSlider->SetLabelText(currentValueWxString);
}

void cMain::onInputFileButtonClick(wxCommandEvent& evt) { //metoda otwierajaca okno wyboru pliku do oczytu po wcisnieciu przycisku
	wxFileDialog openFileDialog(NULL, _("Otworz plik txt z rownaniami"), "", "", "Pliki tekstowe (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_OK) {
		wxString selectedFile = openFileDialog.GetPath(); //bêdzie trzeba zadeklarowac pozniej jako zmienna w klasie
		inputFileNameLabel->SetLabelText(selectedFile);
		if (asmCheckBox->GetValue() == true || cppCheckBox->GetValue() == true) { //zmiana przycisku uruchom na klikalny
			run->Enable();
		}
	}
}

void cMain::onCppCheckBoxActivate(wxCommandEvent& evt) { //metoda która blokuje drugi checkbox
	asmCheckBox->SetValue(false);
	if (inputFileNameLabel->GetLabelText() != "") { //zmiana przycisku uruchom na klikalny
		run->Enable();
	}
}

void cMain::onAsmCheckBoxActivate(wxCommandEvent& evt) { //metoda która blokuje drugi checkbox
	cppCheckBox->SetValue(false);
	if (inputFileNameLabel->GetLabelText() != "") { //zmiana przycisku uruchom na klikalny
		run->Enable();
	}
}

void cMain::onRunButtonClick(wxCommandEvent& evt) {

}
