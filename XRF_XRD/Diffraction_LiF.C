int Diffraction_LiF()
{
	std::string file_path = "./data/";
	std::string file_name = "Diffraction_LiF_101716.txt";

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

	TGraphErrors *LiF_K1 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K1 = new TF1("fSpec_K1", "gaus", 0., 90.);
		fSpec_K1->SetLineColor(kGreen-3);
	/*Estimate Parameters of Fit*/
	fSpec_K1->SetParameters(15, 75, 2);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	LiF_K1->Fit("fSpec_K1", "Q", "", 19., 21.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = LiF_K1->GetFunction("fSpec_K1");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding K1 Peak   !" << endl;
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

	LiF_K1->Draw();
	fSpec_K1->Draw("SAME");
	//************************************************************************************************

	TGraphErrors *LiF_K2 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K2 = new TF1("fSpec_K2", "gaus", 0., 90.);
	/*Estimate Parameters of Fit*/
	fSpec_K2->SetParameters(15, 75, 2);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	LiF_K2->Fit("fSpec_K2", "Q", "", 21., 30.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = LiF_K2->GetFunction("fSpec_K2");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding K2 Peak   !" << endl;
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

	LiF_K2->Draw();
	fSpec_K2->Draw("SAME");

	//************************************************************************************************

	TGraphErrors *LiF_K1_2 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K1_2 = new TF1("fSpec_K1_2", "gaus", 0., 90.);
		fSpec_K1_2->SetLineColor(kGreen-1);
	/*Estimate Parameters of Fit*/
	fSpec_K1_2->SetParameters(43, 75, 2);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	LiF_K1_2->Fit("fSpec_K1_2", "Q", "", 41., 46.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = LiF_K1_2->GetFunction("fSpec_K1_2");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding K1_2 Peak   !" << endl;
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

	LiF_K1_2->Draw();
	fSpec_K1_2->Draw("SAME");
	//************************************************************************************************

	TGraphErrors *LiF_K2_2 = new TGraphErrors(t1->GetEntries(), &AngleCrystal[0], &Cavg[0], &err_AngleCrystal[0], &err_Cavg[0]);
	/*Define Spectrum Fit Function*/
	TF1 *fSpec_K2_2 = new TF1("fSpec_K2_2", "gaus", 0., 90.);
		fSpec_K2_2->SetLineColor(kRed-3);
	/*Estimate Parameters of Fit*/
	fSpec_K2_2->SetParameters(43, 75, 2);
	TCanvas *c_AuL2 = new TCanvas();
	/*Fit Pre-Defined Function to Spectrum*/
	LiF_K2_2->Fit("fSpec_K2_2", "Q", "", 48., 51.);

	/*Obtain Fit Function from Histogram*/
	TF1 *fStat_L2 = LiF_K2_2->GetFunction("fSpec_K2_2");

	/*Assign Fit Parameters to Variables*/
	double Peak_L2 = fStat_L2->GetParameter(1);
	double Stdv_L2 = fStat_L2->GetParameter(2);
	/*Assign Fit Statistics to Variables*/
	double Chi_L2 = fStat_L2->GetChisquare();
	double NDF_L2 = fStat_L2->GetNDF();
	double Red_L2 = Chi_L2/NDF_L2;

	/*Output Results to Terminal*/
	cout << "=======================" << endl;
	cout << "!   Finding K2_2 Peak   !" << endl;
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

	LiF_K2_2->Draw();
	fSpec_K2_2->Draw("SAME");
	//************************************************************************************************
        std::string title = "Diffraction Spectrum of LiF";
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

//	c->Print("./report/plots/Diffraction_LiF.eps"); c->Print("./report/plots/Diffraction_LiF.png");

	return 0;
}
