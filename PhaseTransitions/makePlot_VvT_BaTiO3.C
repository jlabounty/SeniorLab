int makePlot_VvT_BaTiO3(
			TString infile = "data/mV_vs_T111416_Run2.txt"
)
{

  TTree *TData = new TTree();
  TData->ReadFile(infile, "T/D:V:null");
  int n = TData->Draw("V:T", "", "goff");

  vector<double> V, T, C1, C2, k;
  for(int i = 0; i<n; i++)
    {
      V.push_back(TData->GetV1()[i]);
      T.push_back(TData->GetV2()[i]);

      C1.push_back(TMath::Abs(V[i]/1.99) / (2*TMath::Pi()*25000.*1029));
      C2.push_back(1.99*(1 - sqrt(1 - 4*(V[i]/1.99)**2. )) / (2*TMath::Pi()*25000.*1029*2*TMath::Abs(V[i])));

      // k.push_back( C2[i]/ (8.854*(10**(-12.)) ));

      k.push_back( C2[i] / (3.2384*10**(-13.)));

    }


  TCanvas *c1 = new TCanvas();  
  TGraph *g_VvT = new TGraph(n, &T[0], &V[0]);
  g_VvT->Draw("AP");

  // TCanvas *c2 = new TCanvas();
  // TGraph *g_C1vT = new TGraph(n, &T[0], &C1[0]);
  // g_C1vT->Draw("AP");

  TCanvas *c3 = new TCanvas();  
  TGraph *g_C2vT = new TGraph(n, &T[0], &C2[0]);
  g_C2vT->Draw("AP");

  TCanvas *c4 = new TCanvas();  
  TGraph *g_kvT = new TGraph(n, &T[0], &k[0]);
  g_kvT->Draw("AP");

  return 0;
}
