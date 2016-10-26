
#include "headers/exist_test.h"

#include "GetAuPeaks.C"
#include "GetAgPeaks.C"
#include "GetCdPeaks.C"
#include "GetCoPeaks.C"
#include "GetCuPeaks.C"
#include "GetGdPeaks.C"
#include "GetInPeaks.C"
#include "GetMoPeaks.C"
#include "GetNbPeaks.C"
#include "GetNiPeaks.C"
#include "GetPbPeaks.C"
#include "GetSnPeaks.C"
#include "GetTaPeaks.C"
#include "GetTiPeaks.C"
#include "GetUXPeaks.C"
#include "GetVXPeaks.C"
#include "GetWXPeaks.C"
#include "GetYXPeaks.C"
#include "GetZnPeaks.C"
#include "GetZrPeaks.C"

int makePlot_Moseley()
{

	//Create Empty Root File
        std::string file_root = "OutputFile.root";
        TFile f(("./"+file_root).c_str(),"RECREATE");
        TTree *t = new TTree("t","Peaks of Functions and their Standard Deviations");
        double mean_i, stdev_i, energy_i, Z_i; 
	int line_i;

        TBranch *b_mean = t->Branch("mean",&mean_i,"Mean bin of the energy peak/D");
        TBranch *b_stdev = t->Branch("stdev",&stdev_i,"Standard deviation of gaussian fit to the energy peak/D");
        TBranch *b_energy = t->Branch("energy",&energy_i,"Known energy of the peak/D");
        TBranch *b_Z = t->Branch("Z",&Z_i,"Atomic Number/D");
	TBranch *b_line = t->Branch("Ident", &line_i,"Identifier of the specific transition. Kalpha = 01, Lbeta = 12, etc./I");

	f.Write();
	f.Close();

	//Run Fitting macros which write to file
	GetAgPeaks();
	GetAuPeaks();
	GetCdPeaks();
	GetCoPeaks();
	GetCuPeaks();
	GetGdPeaks();
	GetInPeaks();
	GetMoPeaks();
	GetNbPeaks();
	GetNiPeaks();
	GetPbPeaks();
	GetSnPeaks();
	GetTaPeaks();
	GetTiPeaks();
	GetUXPeaks();
	GetVXPeaks();
	GetWXPeaks();
	GetYXPeaks();
	GetZnPeaks();
	GetZrPeaks();
	//Perform analysis on output data
	gStyle->SetOptStat(0); 

	std::string file = "./OutputFile.root";
	TFile f(file.c_str());
	TTree *t = (TTree*)f.Get("t");
	t->Draw("mean:stdev:energy:Z","","goff");
	vector<double> err_energy;
	vector<double> mean, stdev, energy, Z, err_Z, X, err_X;
	for(int i = 0; i < t->GetEntries(); i++) 
	{
		energy.push_back((t->GetV3())[i]);
		err_energy.push_back(0.00000);
		mean.push_back((t->GetV1())[i]);
		stdev.push_back(TMath::Abs((t->GetV2())[i]));
		X.push_back(sqrt(((( 1.6*(10**(-16.))*((0.0245644*(mean[i]) - 0.0545754))) / TMath::H() )/ 10**16.)));
		err_X.push_back((stdev[i]*X[i]) / (2.*mean[i]) );
		Z.push_back((t->GetV4())[i]);
		err_Z.push_back(0.00000);

		// cout << Z[i] << " | " << mean[i] << endl;

	}
	f.Close();

	std::string titleZ = "";
	//Makes canvas large enough for png printing.
        TCanvas *c31 = new TCanvas("c31",titleZ.c_str(),750,750);
		c31->cd();
		c31->SetGridx(1);
		c31->SetGridy(1);
		//		c->SetFixedAspectRatio();
        //Use blank histogram to set the parameters of the canvas
        TH1F *hcalibZ = new TH1F("hcalibZ",titleZ.c_str(),10, 0, 29);
                hcalibZ->GetYaxis()->SetRangeUser(0, 100);
                hcalibZ->GetXaxis()->SetTitle("#sqrt{#frac{#nu}{10^{16}}} [s^{- #frac{1}{2}}]");
                hcalibZ->GetYaxis()->SetTitle("Z");
                hcalibZ->GetXaxis()->SetNdivisions(505);
                hcalibZ->GetYaxis()->SetNdivisions(505);
                hcalibZ->SetLineColor(0);
        hcalibZ->Draw();

	TGraphErrors *grZ = new TGraphErrors(err_energy.size(), &(X[0]), &(Z[0]), &(err_X[0]), &(err_Z[0]) );
	grZ->SetMarkerColor(kRed);
	grZ->Draw("p SAME");

	// c31->Print("../../Plots/XRF_XRD/MoseleyPrelimPlot.png");


	/*Seperate Each Line into Different TGraphs*/
	std::string title = "";
	//Makes canvas large enough for png printing.
        TCanvas *c_sep = new TCanvas("c_sep",title.c_str(),750,750);
		c_sep->cd();
		c_sep->SetGridx(1);
		c_sep->SetGridy(1);
		//		c_sep->SetFixedAspectRatio();
        //Use blank histogram to set the parameters of the canvas
        hcalibZ->Draw();

	/*======Just K1 Line======*/

	std::string fileK1 = "./OutputFile.root";
	TFile fK1(fileK1.c_str());
	TTree *t = (TTree*)fK1.Get("t");
	t->Draw("mean:stdev:energy:Z","Ident==1","goff");
	vector<double> err_energyK1;
	vector<double> meanK1, stdevK1, energyK1, ZK1, err_ZK1, XK1, err_XK1;
	for(int iK1 = 0; iK1 < t->GetSelectedRows(); iK1++) 
	{

		energyK1.push_back((t->GetV3())[iK1]);
		err_energyK1.push_back(0.00000);
		meanK1.push_back((t->GetV1())[iK1]);
		stdevK1.push_back(TMath::Abs((t->GetV2())[iK1]));
		XK1.push_back(sqrt(((( 1.6*(10**(-16.))*((0.0245644*(meanK1[iK1]) - 0.0545754))) / TMath::H() )/ 10**16.)));
		err_XK1.push_back((stdevK1[iK1]*XK1[iK1]) / (2.*meanK1[iK1]) );
		ZK1.push_back((t->GetV4())[iK1]);
		err_ZK1.push_back(0.00000);

	}
	f.Close();

	TGraphErrors *grK1 = new TGraphErrors(err_energyK1.size(), &(XK1[0]), &(ZK1[0]), &(err_XK1[0]), &(err_ZK1[0]) );
	grK1->SetMarkerColor(kRed);
	grK1->Draw("P SAME");
	grK1->Fit("pol1", "Q");
	TF1* K1Line = grK1->GetFunction("pol1");
	K1Line->SetLineColor(kRed);
	K1Line->SetLineStyle(2);
	// cout << K1Line->GetChisquare() << endl;
	// cout << K1Line->GetNDF() << endl;

	/*========================*/

	/*======Just K2 Line======*/

	std::string fileK2 = "./OutputFile.root";
	TFile fK2(fileK2.c_str());
	TTree *t = (TTree*)fK2.Get("t");
	t->Draw("mean:stdev:energy:Z","Ident==2","goff");
	vector<double> err_energyK2;
	vector<double> meanK2, stdevK2, energyK2, ZK2, err_ZK2, XK2, err_XK2;
	for(int iK2 = 0; iK2 < t->GetSelectedRows(); iK2++) 
	{

		energyK2.push_back((t->GetV3())[iK2]);
		err_energyK2.push_back(0.00000);
		meanK2.push_back((t->GetV1())[iK2]);
		stdevK2.push_back(TMath::Abs((t->GetV2())[iK2]));
		XK2.push_back(sqrt(((( 1.6*(10**(-16.))*((0.0245644*(meanK2[iK2]) - 0.0545754))) / TMath::H() )/ 10**16.)));
		err_XK2.push_back((stdevK2[iK2]*XK2[iK2]) / (2.*meanK2[iK2]) );
		ZK2.push_back((t->GetV4())[iK2]);
		err_ZK2.push_back(0.00000);

	}
	f.Close();

	TGraphErrors *grK2 = new TGraphErrors(err_energyK2.size(), &(XK2[0]), &(ZK2[0]), &(err_XK2[0]), &(err_ZK2[0]) );
	grK2->SetMarkerColor(kOrange+7);
	grK2->Draw("P SAME");
	grK2->Fit("pol1", "Q");
	TF1* K2Line = grK2->GetFunction("pol1");
	K2Line->SetLineColor(kOrange+7);
	K2Line->SetLineStyle(2);
	// cout << K2Line->GetChisquare() << endl;
	// cout << K2Line->GetNDF() << endl;

	/*========================*/

	/*======Just L1 Line======*/

	std::string fileL1 = "./OutputFile.root";
	TFile fL1(fileL1.c_str());
	TTree *t = (TTree*)fL1.Get("t");
	t->Draw("mean:stdev:energy:Z","Ident==11","goff");
	vector<double> err_energyL1;
	vector<double> meanL1, stdevL1, energyL1, ZL1, err_ZL1, XL1, err_XL1;
	for(int iL1 = 0; iL1 < t->GetSelectedRows(); iL1++) 
	{

		energyL1.push_back((t->GetV3())[iL1]);
		err_energyL1.push_back(0.00000);
		meanL1.push_back((t->GetV1())[iL1]);
		stdevL1.push_back(TMath::Abs((t->GetV2())[iL1]));
		XL1.push_back(sqrt(((( 1.6*(10**(-16.))*((0.0245644*(meanL1[iL1]) - 0.0545754))) / TMath::H() )/ 10**16.)));
		err_XL1.push_back((stdevL1[iL1]*XL1[iL1]) / (2.*meanL1[iL1]) );
		ZL1.push_back((t->GetV4())[iL1]);
		err_ZL1.push_back(0.00000);

	}
	f.Close();

	TGraphErrors *grL1 = new TGraphErrors(err_energyL1.size(), &(XL1[0]), &(ZL1[0]), &(err_XL1[0]), &(err_ZL1[0]) );
	grL1->SetMarkerColor(kGreen+3);
	grL1->Draw("P SAME");
	grL1->Fit("pol1", "Q");
	TF1* L1Line = grL1->GetFunction("pol1");
	L1Line->SetLineColor(kGreen+3);
	L1Line->SetLineStyle(2);
	// cout << L1Line->GetChisquare() << endl;
	// cout << L1Line->GetNDF() << endl;

	/*========================*/

	/*======Just L2 Line======*/

	std::string fileL2 = "./OutputFile.root";
	TFile fL2(fileL2.c_str());
	TTree *t = (TTree*)fL2.Get("t");
	t->Draw("mean:stdev:energy:Z","Ident==12","goff");
	vector<double> err_energyL2;
	vector<double> meanL2, stdevL2, energyL2, ZL2, err_ZL2, XL2, err_XL2;
	for(int iL2 = 0; iL2 < t->GetSelectedRows(); iL2++) 
	{

		energyL2.push_back((t->GetV3())[iL2]);
		err_energyL2.push_back(0.00000);
		meanL2.push_back((t->GetV1())[iL2]);
		stdevL2.push_back(TMath::Abs((t->GetV2())[iL2]));
		XL2.push_back(sqrt(((( 1.6*(10**(-16.))*((0.0245644*(meanL2[iL2]) - 0.0545754))) / TMath::H() )/ 10**16.)));
		err_XL2.push_back((stdevL2[iL2]*XL2[iL2]) / (2.*meanL2[iL2]) );
		ZL2.push_back((t->GetV4())[iL2]);
		err_ZL2.push_back(0.00000);

	}
	f.Close();

	TGraphErrors *grL2 = new TGraphErrors(err_energyL2.size(), &(XL2[0]), &(ZL2[0]), &(err_XL2[0]), &(err_ZL2[0]) );
	grL2->SetMarkerColor(kBlue);
	grL2->Draw("P SAME");
	grL2->Fit("pol1", "Q");
	TF1* L2Line = grL2->GetFunction("pol1");
	L2Line->SetLineColor(kBlue);
	L2Line->SetLineStyle(2);
	// cout << L2Line->GetChisquare() << endl;
	// cout << L2Line->GetNDF() << endl;

	/*========================*/

	/*======Just L3 Line======*/

	std::string fileL3 = "./OutputFile.root";
	TFile fL3(fileL3.c_str());
	TTree *t = (TTree*)fL3.Get("t");
	t->Draw("mean:stdev:energy:Z","Ident==13","goff");
	vector<double> err_energyL3;
	vector<double> meanL3, stdevL3, energyL3, ZL3, err_ZL3, XL3, err_XL3;
	for(int iL3 = 0; iL3 < t->GetSelectedRows(); iL3++) 
	{

		energyL3.push_back((t->GetV3())[iL3]);
		err_energyL3.push_back(0.00000);
		meanL3.push_back((t->GetV1())[iL3]);
		stdevL3.push_back(TMath::Abs((t->GetV2())[iL3]));
		XL3.push_back(sqrt(((( 1.6*(10**(-16.))*((0.0245644*(meanL3[iL3]) - 0.0545754))) / TMath::H() )/ 10**16.)));
		err_XL3.push_back((stdevL3[iL3]*XL3[iL3]) / (2.*meanL3[iL3]) );
		ZL3.push_back((t->GetV4())[iL3]);
		err_ZL3.push_back(0.00000);

	}
	f.Close();

	TGraphErrors *grL3 = new TGraphErrors(err_energyL3.size(), &(XL3[0]), &(ZL3[0]), &(err_XL3[0]), &(err_ZL3[0]) );
	grL3->SetMarkerColor(kViolet);
	grL3->Draw("P SAME");
	grL3->Fit("pol1", "Q");
	TF1* L3Line = grL3->GetFunction("pol1");
	L3Line->SetLineColor(kViolet);
	L3Line->SetLineStyle(2);
	// cout << L3Line->GetChisquare() << endl;
	// cout << L3Line->GetNDF() << endl;

	/*========================*/

	TLegend *l_sep = new TLegend(0.20, 0.70, 0.40, 0.87);
	l_sep->SetNColumns(1);
	l_sep->AddEntry(grK1->GetFunction("pol1"), "K_{#alpha} Transitions", "l");
	l_sep->AddEntry(grK2->GetFunction("pol1"), "K_{#beta} Transitions", "l");
	l_sep->AddEntry(grL1->GetFunction("pol1"), "L_{#alpha} Transitions", "l");
	l_sep->AddEntry(grL2->GetFunction("pol1"), "L_{#beta} Transitions", "l");
	l_sep->AddEntry(grL3->GetFunction("pol1"), "L_{#gamma} Transitions", "l");
	l_sep->Draw();

	// c_sep->Print("../../Plots/XRF_XRD/MoseleySeperatedPlot.png");
	// c_sep->Print("plots/MoseleyLawPlot.png");

	cout << "!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "========================" << endl;
	cout << "=Moseley's Law Analysis=" << endl;
	cout << "========================" << endl;

	cout << "==Screening Parameters==" << endl;
	cout << "K1: " << K1Line->GetParameter(0) << " +/- " << K1Line->GetParError(0) << endl;
	cout << "K2: " << K2Line->GetParameter(0) << " +/- " << K2Line->GetParError(0) << endl;
	cout << "L1: " << L1Line->GetParameter(0) << " +/- " << L1Line->GetParError(0) << endl;
	cout << "L2: " << L2Line->GetParameter(0) << " +/- " << L2Line->GetParError(0) << endl;
	cout << "L3: " << L3Line->GetParameter(0) << " +/- " << L3Line->GetParError(0) << endl;
	cout << "========================" << endl;
	cout << "====Rydberg Constant====" << endl;
	cout << "1. Get slope..." << endl;
	double slopeK1 = K1Line->GetParameter(1) / (10**8);
	double ErrslopeK1 = K1Line->GetParError(1) / (10**8);
	double slopeK2 = K2Line->GetParameter(1) / (10**8);
	double ErrslopeK2 = K2Line->GetParError(1) / (10**8);
	double slopeL1 = L1Line->GetParameter(1) / (10**8);
	double ErrslopeL1 = L1Line->GetParError(1) / (10**8);
	double slopeL2 = L2Line->GetParameter(1) / (10**8);
	double ErrslopeL2 = L2Line->GetParError(1) / (10**8);
	double slopeL3 = L3Line->GetParameter(1) / (10**8);
	double ErrslopeL3 = L3Line->GetParError(1) / (10**8);
	cout << "K1: " << slopeK1 << " +/- " << ErrslopeK1 << endl;
	cout << "K2: " << slopeK2 << " +/- " << ErrslopeK2 << endl;
	cout << "L1: " << slopeL1 << " +/- " << ErrslopeL1 << endl;
	cout << "L2: " << slopeL2 << " +/- " << ErrslopeL2 << endl;
	cout << "L3: " << slopeL3 << " +/- " << ErrslopeL3 << endl;

	cout << "2. Calculate A..." << endl;
	cout << "K1: " << TMath::H() / (slopeK1**2) << " +/- " << 2.*TMath::H()*ErrslopeK1/(slopeK1**3.) << endl;
	cout << "K2: " << TMath::H() / (slopeK2**2) << " +/- " << 2.*TMath::H()*ErrslopeK2/(slopeK2**3.) << endl;
	cout << "L1: " << TMath::H() / (slopeL1**2) << " +/- " << 2.*TMath::H()*ErrslopeL1/(slopeL1**3.) << endl;
	cout << "L2: " << TMath::H() / (slopeL2**2) << " +/- " << 2.*TMath::H()*ErrslopeL2/(slopeL2**3.) << endl;
	cout << "L3: " << TMath::H() / (slopeL3**2) << " +/- " << 2.*TMath::H()*ErrslopeL3/(slopeL3**3.) << endl;

	cout << "3. Calculate Theory..." << endl;
	double R = 1.097373156*(10**7);
	cout << "K1: " << TMath::H()*TMath::C()*R*((1./1.)**2. - (1./2.)**2.) << endl;
	cout << "K2: " << TMath::H()*TMath::C()*R*((1./1.)**2. - (1./3.)**2.) << endl;
	cout << "L1: " << TMath::H()*TMath::C()*R*((1./2.)**2. - (1./3.)**2.) << endl;
	cout << "L2: " << TMath::H()*TMath::C()*R*((1./2.)**2. - (1./4.)**2.) << endl;
	cout << "L3: " << TMath::H()*TMath::C()*R*((1./2.)**2. - (1./5.)**2.) << endl;

	return 0;
}
