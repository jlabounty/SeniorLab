int Diffraction_NaCl()
{
	std::string file_path = "./data/";
	std::string file_name = "Diffraction_NaCl_101916.txt";

	TTree *t1 = new TTree();
	t1->ReadFile((file_path + file_name).c_str(),"AngleDet:AngleCrystal:C1:C2:C3:Time");
	
	t1->Draw("C1:C2:C3:Time","","goff");
	vector<double> Cavg, AngleCrystal;
	vector<double> err_Cavg, err_AngleCrystal;

	for(int i = 0; i < t1->GetEntries(); i++)
	{
		Cavg.push_back(((( (t1->GetV1())[i] + t1->GetV2())[i] + t1->GetV3())[i] )/(3.0*t1->GetV4()[i]));
		err_Cavg.push_back(TMath::Sqrt(TMath::Sqrt((t1->GetV1())[i])**2 + TMath::Sqrt((t1->GetV3())[i])**2 + TMath::Sqrt((t1->GetV3())[i])**2)/(3.0*t1->GetV4()[i]));
	}

	t1->Draw("AngleCrystal","","goff");
	for(int i = 0; i < t1->GetEntries(); i++)
	{
		AngleCrystal.push_back(t1->GetV1()[i]);
		err_AngleCrystal.push_back(0.125);
	}

        gStyle->SetOptStat(0);

	//************************************************************************************************

	TGraphErrors *NaCl_K1 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K1 = new TF1("fSpec_K1", "gaus", 0., 90.);
		fSpec_K1->SetLineColor(kGreen-3);
	/*Estimate Parameters of Fit*/
	fSpec_K1->SetParameters(15, 75, 2);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	NaCl_K1->Fit("fSpec_K1", "Q", "", 12.5., 14.4.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = NaCl_K1->GetFunction("fSpec_K1");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding Kbeta Peak   !" << endl;
	cout << "-----------------------" << endl;
	cout << "Peak Occurs at: " << endl;
	cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
	cout << "-----------------------" << endl;
	cout << "-----Fit Statistics----" << endl;
	cout << "-----------------------" << endl;
	cout << "Chi-Sq     |  " << Chi_L2 << endl;
	cout << "DoF        |  " << NDF_L2 << endl;
	cout << "Red Chi-Sq |  " << Red_L2 << endl;
	cout << "=======================" << endl;

	NaCl_K1->Draw();
	fSpec_K1->Draw("SAME");
	//************************************************************************************************

	TGraphErrors *NaCl_K2 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K2 = new TF1("fSpec_K2", "gaus", 0., 90.);
	/*Estimate Parameters of Fit*/
	fSpec_K2->SetParameters(15, 75, 2);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	NaCl_K2->Fit("fSpec_K2", "Q", "",14.5., 20.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = NaCl_K2->GetFunction("fSpec_K2");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding Kalpha Peak   !" << endl;
	cout << "-----------------------" << endl;
	cout << "Peak Occurs at: " << endl;
	cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
	cout << "-----------------------" << endl;
	cout << "-----Fit Statistics----" << endl;
	cout << "-----------------------" << endl;
	cout << "Chi-Sq     |  " << Chi_L2 << endl;
	cout << "DoF        |  " << NDF_L2 << endl;
	cout << "Red Chi-Sq |  " << Red_L2 << endl;
	cout << "=======================" << endl;

	NaCl_K2->Draw();
	fSpec_K2->Draw("SAME");

	//************************************************************************************************

	TGraphErrors *NaCl_K1_2 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K1_2 = new TF1("fSpec_K1_2", "gaus", 0., 90.);
		fSpec_K1_2->SetLineColor(kGreen-1);
	/*Estimate Parameters of Fit*/
	fSpec_K1_2->SetParameters(29, 75, 2);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	NaCl_K1_2->Fit("fSpec_K1_2", "Q", "", 28., 30.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = NaCl_K1_2->GetFunction("fSpec_K1_2");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding Kbeta_2 Peak   !" << endl;
	cout << "-----------------------" << endl;
	cout << "Peak Occurs at: " << endl;
	cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
	cout << "-----------------------" << endl;
	cout << "-----Fit Statistics----" << endl;
	cout << "-----------------------" << endl;
	cout << "Chi-Sq     |  " << Chi_L2 << endl;
	cout << "DoF        |  " << NDF_L2 << endl;
	cout << "Red Chi-Sq |  " << Red_L2 << endl;
	cout << "=======================" << endl;

	NaCl_K1_2->Draw();
	fSpec_K1_2->Draw("SAME");
	//************************************************************************************************

	TGraphErrors *NaCl_K2_2 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K2_2_int = new TF1("fSpec_K2_2_int", "gaus", 0., 90.);
		fSpec_K2_2_int->SetLineColor(kRed-3);
	/*Estimate Parameters of Fit*/
	fSpec_K2_2_int->SetParameters(29, 75, 2);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	NaCl_K2_2->Fit("fSpec_K2_2_int", "Q", "", 32, 34.);

	TF1 *fSpec_K2_2 = new TF1("fSpec_K2_2", "gaus", 0., 90.);
	Double_t param[4];
	fSpec_K2_2_int->GetParameters(param);
	fSpec_K2_2->SetParameters(&param[0]);
	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = fSpec_K2_2;

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding Kalpha_2 Peak   !" << endl;
	cout << "-----------------------" << endl;
	cout << "Peak Occurs at: " << endl;
	cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
	cout << "-----------------------" << endl;
	cout << "-----Fit Statistics----" << endl;
	cout << "-----------------------" << endl;
	cout << "Chi-Sq     |  " << Chi_L2 << endl;
	cout << "DoF        |  " << NDF_L2 << endl;
	cout << "Red Chi-Sq |  " << Red_L2 << endl;
	cout << "=======================" << endl;

	NaCl_K2_2->Draw();
	fSpec_K2_2->Draw("SAME");
	//************************************************************************************************

	TGraphErrors *NaCl_K1_3 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K1_3 = new TF1("fSpec_K1_3", "gaus", 0., 90.);
		fSpec_K1_3->SetLineColor(kGreen-5);
	/*Estimate Parameters of Fit*/
	fSpec_K1_3->SetParameters(41, 75, 2, 15);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	NaCl_K1_3->Fit("fSpec_K1_3", "Q", "", 46, 48.5.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = NaCl_K1_3->GetFunction("fSpec_K1_3");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding Kbeta_3 Peak   !" << endl;
	cout << "-----------------------" << endl;
	cout << "Peak Occurs at: " << endl;
	cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
	cout << "-----------------------" << endl;
	cout << "-----Fit Statistics----" << endl;
	cout << "-----------------------" << endl;
	cout << "Chi-Sq     |  " << Chi_L2 << endl;
	cout << "DoF        |  " << NDF_L2 << endl;
	cout << "Red Chi-Sq |  " << Red_L2 << endl;
	cout << "=======================" << endl;

	NaCl_K1_3->Draw();
	fSpec_K1_3->Draw("SAME");
	//************************************************************************************************

	TGraphErrors *NaCl_K2_3 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K2_3 = new TF1("fSpec_K2_3", "gaus", 0., 90.);
		fSpec_K2_3->SetLineColor(kRed-5);
	/*Estimate Parameters of Fit*/
	fSpec_K2_3->SetParameters(46.7, 75, 2, 15);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	NaCl_K2_3->Fit("fSpec_K2_3", "Q", "", 53., 56.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = NaCl_K2_3->GetFunction("fSpec_K2_3");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding Kalpha_3 Peak   !" << endl;
	cout << "-----------------------" << endl;
	cout << "Peak Occurs at: " << endl;
	cout << Peak_L2 << " +/- " << Stdv_L2 << endl;
	cout << "-----------------------" << endl;
	cout << "-----Fit Statistics----" << endl;
	cout << "-----------------------" << endl;
	cout << "Chi-Sq     |  " << Chi_L2 << endl;
	cout << "DoF        |  " << NDF_L2 << endl;
	cout << "Red Chi-Sq |  " << Red_L2 << endl;
	cout << "=======================" << endl;

	NaCl_K2_3->Draw();
	fSpec_K2_3->Draw("SAME");
	//************************************************************************************************
        std::string title = "Diffraction Spectrum of NaCl";
        //Makes canvas large enough for png printing.
        TCanvas *c = new TCanvas("c",title.c_str(),750,750);
                c->cd();
                c->SetGridx(1);
                c->SetGridy(1);
//              c->SetFixedAspectRatio();
        //Use blank histogram to set the parameters of the canvas
        TH1F *hcalib = new TH1F("hcalib",title.c_str(),10, 0, 65);
                hcalib->GetYaxis()->SetRangeUser(0.001, 1000);
                hcalib->GetXaxis()->SetTitle("#theta (Degrees)");
                hcalib->GetYaxis()->SetTitle("Counts / Second");
		hcalib->GetYaxis()->SetTitleOffset(1.55);
                hcalib->GetXaxis()->SetNdivisions(505);
                hcalib->GetYaxis()->SetNdivisions(505);
                hcalib->SetLineColor(0);
        hcalib->Draw();

	TGraphErrors *gr = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	gr->Draw("pl SAME");
	fSpec_K2->Draw("l SAME");
	fSpec_K1->Draw("l SAME");
	fSpec_K1_2->Draw("l SAME");
	fSpec_K2_2->Draw("l SAME");
	fSpec_K1_3->Draw("l SAME");
	fSpec_K2_3->Draw("l SAME");

//	c->Print("./report/plots/Diffraction_NaCl.eps"); c->Print("./report/plots/Diffraction_NaCl.png");

	return 0;
}
