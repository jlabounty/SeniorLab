int AngularDependence()
{
	//Plot the Simulated angular values for Thompson and KN formulas.

	gStyle->SetOptStat(0);

	TCanvas *c = new TCanvas("c","",750,750);     //Makes canvas large enough for png printing.
		c->cd();
		c->SetGridx(1);
		c->SetGridy(1);
//		c->SetFixedAspectRatio();

//	TH1F *blank = new TH1F("blank","Comparison of Experimental Data with KN and Thompson Formulas",10, 0, 180);
	TH1F *blank = new TH1F("blank","",10, 0, 180);
		blank->GetYaxis()->SetRangeUser(0, 6.0*TMath::Power(10,-25));
		blank->GetXaxis()->SetTitle("#theta_{detector} (Degrees)");
		blank->GetYaxis()->SetTitle("d#sigma/d#Omega (cm^{2}/st)");
		blank->GetYaxis()->SetTitleOffset(1.55);
		blank->GetXaxis()->SetNdivisions(505);
		blank->GetYaxis()->SetNdivisions(505);
		blank->SetLineColor(0);
	blank->Draw();

        leg = new TLegend(0.5,0.9,0.9,0.8);
                leg->SetBorderSize(1);

	double r0 = 2.82*TMath::Power(10,-13);
	double E_gamma = 661.6*1000;
	double m_e = 510998.9;
	double c_light = 1.0;
	double gamma = E_gamma/(m_e * c_light**2);

	cout << "gamma: " << gamma << endl;
	cout << "r0: " << r0 << endl;

	TF1 *KN = new TF1("KN","([0]**2 / 2.0) * ((1 + TMath::Cos(x * TMath::Pi()/180.0)**2)/(1 + [1]*(1 - TMath::Cos(x * TMath::Pi()/180.0)))**2) * (1 + (([1]**2 * (1 - TMath::Cos(x * TMath::Pi()/180.0)))**2)/((1 + TMath::Cos(x * TMath::Pi()/180.0)**2)*(1 + [1]*(1 - TMath::Cos(x * TMath::Pi()/180.0)))))",0,180);
		KN->FixParameter(0,r0);
		KN->FixParameter(1,gamma);
		KN->SetLineColor(3);
//	KN->Draw();
	KN->Draw("SAME");
	leg->AddEntry(KN,"Klein-Nishina","l");

	TF1 *thompson = new TF1("thompson","[0]**2 / 2 * (1 + TMath::Cos(x * TMath::Pi()/180.0)**2)",0,180);
		thompson->FixParameter(0,r0);
	thompson->Draw("SAME");
	leg->AddEntry(thompson,"Thompson","l");

	//Plot Data on the Same Axis
	std::string file_root = "OutputFile_PeakShift.root";
	TFile f(("./"+file_root).c_str(),"UPDATE");
	TTree *t = (TTree*)f.Get("t");
	t->Draw("dsigma_dOmega:angle","","SAME");
	cout << "Angle    |    dSigma/dOmega" << endl;
	for (int i = 0; i < t->GetEntries(); i++)
	{
		cout << t->GetV2()[i] << "       |     " << t->GetV1()[i] << endl;
	}
	leg->AddEntry(t,"Data","p");


	leg->Draw();

	c->Update();
//	c->Print("./plots/KNvsThompson.png");	c->Print("./plots/KNvsThompson.eps");

	TCanvas *c1 = new TCanvas();
	c1->cd();
	t->Draw("dsigma_dOmega:angle","","goff");
	TGraph *gr1 = new TGraph(t->GetEntries(),&(t->GetV2()[0]),&(t->GetV1()[0]));
	gr1->Draw();
	gr1->Fit("KN","Q");
	cout << endl << "KN Reduced Chi^2: " << KN->GetChisquare() / KN->GetNDF() << endl;
	gr1->Fit("thompson", "Q");
	cout << "Thompson Reduced Chi^2: " << thompson->GetChisquare() / thompson->GetNDF() << endl;

	return 0;
}
