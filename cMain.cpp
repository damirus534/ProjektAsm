#include "cMain.h"
#include <fstream>
#include <sstream>
#include <vector>
#include "CppGausEliminationLib.h"
#include <thread>
#include <chrono>
#include <iomanip>
#include <Windows.h>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_SLIDER(22, onSliderChange)
	EVT_BUTTON(20, onInputFileButtonClick)
	EVT_CHECKBOX(41, onCppCheckBoxActivate)
	EVT_CHECKBOX(42, onAsmCheckBoxActivate)
	EVT_BUTTON(1, onRunButtonClick)
	EVT_BUTTON(21, onOpenOutputFileButton)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "ProjektAsm", wxPoint(720, 360),wxSize(480,360)) {

	//przyciski
	inputFileButton = new wxButton(this, 20, "Wgraj plik", wxPoint(10, 10), wxSize(120, 30));
	openOutputFileButton = new wxButton(this, 21, "Otworz plik", wxPoint(10, 50), wxSize(120, 30));
	openOutputFileButton->Disable();
	run = new wxButton(this, 1, "Uruchom", wxPoint(165, 260), wxSize(120, 30));
	run->Disable();

	//checkboxy
	cppCheckBox = new wxCheckBox(this, 41, "c++", wxPoint(10, 120), wxSize(60, 15));
	asmCheckBox = new wxCheckBox(this, 42, "asm", wxPoint(10, 140), wxSize(60, 15));
	cppCheckBox->SetFont(myFont);
	asmCheckBox->SetFont(myFont);


	//slider
	slider = new wxSlider(this, 22, 1, 1, 64, wxPoint(20, 190), wxSize(420, 25));

	//labele stale
	cppLabel = new wxStaticText(this, wxID_ANY, "c++", wxPoint(250, 120), wxSize(25, 15));
	asmLabel = new wxStaticText(this, wxID_ANY, "asm", wxPoint(250, 140), wxSize(25, 15));
	TimeLabel = new wxStaticText(this, wxID_ANY, "time(ms)", wxPoint(350, 100), wxSize(100, 15));
	oneOnSlider = new wxStaticText(this, wxID_ANY, "1", wxPoint(10, 195), wxSize(10, 20));
	sixtyFourOnSlider = new wxStaticText(this, wxID_ANY, "64", wxPoint(440, 198), wxSize(20, 20));

	//labele zmienne
	currentValueOnSlider = new wxStaticText(this, wxID_ANY, "1", wxPoint(220, 215), wxSize(20, 20));
	inputFileNameLabel = new wxStaticText(this, wxID_ANY, "", wxPoint(135, 16), wxSize(120, 20));
	outputFileNameLabel = new wxStaticText(this, wxID_ANY, "", wxPoint(135, 56), wxSize(120, 20));
	cppTimeLabel = new wxStaticText(this, wxID_ANY, "", wxPoint(350, 120), wxSize(25, 15));

	//ustawienie fonta w labelach
	cppLabel->SetFont(myFont);
	asmLabel->SetFont(myFont);
	TimeLabel->SetFont(myFont);
	cppTimeLabel->SetFont(myFont);


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

void cMain::onOpenOutputFileButton(wxCommandEvent& evt) {
	system("start C:\\Users\\Damian\\source\\repos\\ProjektAsemblerDamianRussok\\result.txt");
}

void cMain::onRunButtonClick(wxCommandEvent& evt) {

	wxString inputInWxString = inputFileNameLabel->GetLabelText();
	std::string input = std::string(inputInWxString.mb_str());
	std::ifstream file(input, std::ios::in);

	std::vector<std::vector<int>>wektor2D;

	if (!file.is_open()) {
		wxMessageBox("input file error", "Error", wxICON_ERROR);
	}
	else {
		std::string temp;
		while (std::getline(file, temp))
		{
			std::vector<int> row;
			std::istringstream iss(temp);
			int value;
			while (iss >> value) {
				row.push_back(value);
			}
			wektor2D.push_back(row);
		}
		file.close();

		std::vector<int>wektorRozmiarow;
		std::vector<int>wektorRozmiarowY;
		std::vector<int>wektorRozmiarowX;

		int tempCounter = 0;
		for (int i = 0; i < wektor2D.size(); i++) {//wyliczenie rozmiaru dla ka¿dego wektora 1 wymiarowego oraz jego rozmiary x i y
			if (wektor2D[i].size() == 0) {
				wektorRozmiarow.push_back(tempCounter);
				if (wektor2D[i - 1].size() != 0) {
					wektorRozmiarowX.push_back(wektor2D[i - 1].size());
					wektorRozmiarowY.push_back(tempCounter / wektor2D[i - 1].size());
				}
				tempCounter = 0;
			}
			else {
				tempCounter += wektor2D[i].size();
			}
		}


		//trimming size vector
		int realSizeOfXArrayChanger = std::count(wektorRozmiarow.begin(), wektorRozmiarow.end(), 0);;
		for (int i = 0; i < realSizeOfXArrayChanger; i++) {
			wektorRozmiarow.pop_back();
		}


		//create and set size of 2dim array
		float** myWholeArray = new float* [wektorRozmiarow.size()];
		float** myResultArray = new float* [wektorRozmiarow.size()];
		for (int i = 0; i < wektorRozmiarow.size(); i++) {
			myWholeArray[i] = new float[wektorRozmiarow[i]];
			myResultArray[i] = new float[wektorRozmiarowY[i]];
		}

		//seting data to 2dim array
		int tempCounterToYArray = 0, tempCounterToSize = 0;
		for (int i = 0; i < wektor2D.size(); i++) {
			for (int j = 0; j < wektor2D[i].size(); j++) {
				myWholeArray[tempCounterToSize][tempCounterToYArray] = (float)wektor2D[i][j];
				tempCounterToYArray++;
				if (tempCounterToYArray == wektorRozmiarow[tempCounterToSize]) {
					tempCounterToYArray = 0;
					tempCounterToSize++;
				}
			}
		}


		int threadNumber = slider->GetValue();
		std::vector <std::thread> myThreads;
		int myLinearEquationCounter = wektorRozmiarow.size();
		long long timeInMicrosec = 0;
		while (myLinearEquationCounter > 0) {
			//gdy ilosc threadow jest wieksza niz liczba rownan
			if (threadNumber >= myLinearEquationCounter) {
				for (int k = myLinearEquationCounter; k > 0; k--) {
					myThreads.push_back(std::thread(CppGausEliminationLib, myWholeArray[myLinearEquationCounter - k], wektorRozmiarowX[myLinearEquationCounter - k], wektorRozmiarowY[myLinearEquationCounter - k], myResultArray[myLinearEquationCounter - k]));
				}
				int i;
				auto startTimer = std::chrono::high_resolution_clock::now();
				for (i = 0; i < myLinearEquationCounter; i++) {
					myThreads[i].join();
				}
				auto stopTimer = std::chrono::high_resolution_clock::now();
				auto durationOfExecution = std::chrono::duration_cast<std::chrono::microseconds>(stopTimer - startTimer);
				timeInMicrosec += durationOfExecution.count();
				myLinearEquationCounter -= i;
			}
			else {//gdy ilosc threadow jest mniejsza niz liczba rownan
				for (int k = threadNumber; k > 0; k--) {
					myThreads.push_back(std::thread(CppGausEliminationLib, myWholeArray[myLinearEquationCounter - k], wektorRozmiarowX[myLinearEquationCounter - k], wektorRozmiarowY[myLinearEquationCounter - k], myResultArray[myLinearEquationCounter - k]));
				}
				int i;
				auto startTimer = std::chrono::high_resolution_clock::now();
				for (i = 0; i < threadNumber; i++) {
					myThreads[i].join();
				}
				auto stopTimer = std::chrono::high_resolution_clock::now();
				auto durationOfExecution = std::chrono::duration_cast<std::chrono::microseconds>(stopTimer - startTimer);
				timeInMicrosec += durationOfExecution.count();
				myLinearEquationCounter -= i;
				myThreads.clear();
			}
		}
		wxString wynik;
		double timeInMilisec = 1.0* timeInMicrosec / 1000;
		wynik<< timeInMilisec;
		cppTimeLabel->SetLabelText(wynik);
		std::ofstream file("result.txt");
		if (file.is_open()) {
			for (int i = 0; i < wektorRozmiarow.size(); i++) {
				file << i + 1 << " rownanie: " << std::endl;
				for (int j = 0; j < wektorRozmiarowY[i]; j++) {
					file << "x" << j+1 << ":";
					file << std::setprecision(5) << myResultArray[i][j] << "  ";
				}
				file << std::endl;
			}
		}
		outputFileNameLabel->SetLabelText("C:\\Users\\..\\..\\..\\ProjektAsemblerDamianRussok\\result.txt");
		openOutputFileButton->Enable();
	}
}
