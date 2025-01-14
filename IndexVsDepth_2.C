void IndexVsDepth_2()
{
	const Double_t MaxDepth = 150.0;
	const Double_t MinDepth = 0.0;
	const Double_t MaxIndex = 1.9;
	const Double_t MinIndex = 1.0;
	gStyle->SetOptStat(0);
	TCanvas *c = new TCanvas("c","c",1000,1000);
	TPad *p = new TPad("p","p",0,0,1,1);
	p->SetLeftMargin(0.15);
	p->SetRightMargin(0.15);
	p->SetGridx();
	p->SetGridy();
	p->Draw();
	p->cd();
	TH2F *h2 = new TH2F("h2","",10,-MaxDepth,MinDepth,10,MinIndex,MaxIndex);
	h2->GetXaxis()->SetTitle("Depth (m)");
	h2->GetXaxis()->SetTitleOffset(1.5);
	h2->GetYaxis()->SetTitleOffset(1.5);
	h2->GetYaxis()->SetTitle("n(z)");
	h2->Draw("");
	gPad->SetFixedAspectRatio();
	
	TGraph *load1 = new TGraph("ARIANNA_BoreHole_1.dat");
	Double_t *x1 = load1->GetX();
	Double_t *y1 = load1->GetY();
	for(Int_t i=0;i<load1->GetN();++i)
	{
		x1[i] = -x1[i];
		y1[i] = 1.0+0.86*y1[i]/1000.0;
	}
	TGraph *Moores_Bay_Hole_1 = new TGraph(load1->GetN(),x1,y1);
	delete load1;
	
	TGraph *load2 = new TGraph("ARIANNA_BoreHole_2.dat");
	Double_t *x2 = load2->GetX();
	Double_t *y2 = load2->GetY();
	for(Int_t i=0;i<load2->GetN();++i)
	{
		x2[i] = -x2[i];
		y2[i] = 1.0+0.86*y2[i]/1000.0;
	}
	TGraph *Moores_Bay_Hole_2 = new TGraph(load2->GetN(),x2,y2);
	delete load2;
	
	TGraph *load3 = new TGraph("SPICE_data.dat");
	Double_t *x3 = load3->GetX();
	Double_t *y3 = load3->GetY();
	for(Int_t i=0;i<load3->GetN();++i)
	{
		x3[i] = -x3[i];
		y3[i] = 1.0+0.86*y3[i]/1000.0;
	}
	TGraph *SPICE_Hole = new TGraph(load3->GetN(),x3,y3);
	delete load3;
	
	TGraph *RICE_Data = new TGraph("RICE_data.csv");
	TGraph *Eisen_Data = new TGraph("Eisen_Maud_data.csv");
	TGraph *Gow_Data = new TGraph("Gow_withOnePlus86_data.csv");
	TGraph *Byrd_Data = new TGraph("Byrd_data.csv");
	TGraph *Mizuho_Data = new TGraph("Mizuho_data.csv");
	
	TF1 *Hole_1_Fit = new TF1("Hole_1_Fit","1.78-[0]*exp([1]*x)",-MaxDepth,MinDepth);
	TF1 *Hole_2_Fit = new TF1("Hole_2_Fit","1.78-[0]*exp([1]*x)",-MaxDepth,MinDepth);
	TF1 *SPICE_Fit = new TF1("SPICE_Fit","1.78-[0]*exp([1]*x)",-MaxDepth,MinDepth);
	SPICE_Fit->SetParameter(0,0.3);
	SPICE_Fit->SetParameter(1,0.02);
	TF1 *RICE_Data_Fit = new TF1("RICE_Data_Fit","1.78-[0]*exp([1]*x)",-MaxDepth,MinDepth);
	TF1 *Eisen_Data_Fit = new TF1("Eisen_Data_Fit","1.78-[0]*exp([1]*x)",-MaxDepth,MinDepth);
	TF1 *Gow_Data_Fit = new TF1("Gow_Data_Fit","1.78-[0]*exp([1]*x)",-MaxDepth,MinDepth);
	TF1 *Byrd_Data_Fit = new TF1("Byrd_Data_Fit","1.78-[0]*exp([1]*x)",-MaxDepth,MinDepth);
	TF1 *Mizuho_Data_Fit = new TF1("Mizuho_Data_Fit","1.78-[0]*exp([1]*x)",-MaxDepth,MinDepth);
	TF1 *Asymp = new TF1("Asymp","1.78",-MaxDepth,MinDepth);
	TF1 *Asymp2 = new TF1("Asymp2","1.29",-MaxDepth,MinDepth);
	Moores_Bay_Hole_1->Fit("Hole_1_Fit","R0");
	Moores_Bay_Hole_2->Fit("Hole_2_Fit","R0");
	RICE_Data->Fit("RICE_Data_Fit","R0");
	Eisen_Data->Fit("Eisen_Data_Fit","R0");
	Gow_Data->Fit("Gow_Data_Fit","R0");
	Byrd_Data->Fit("Byrd_Data_Fit","R0");
	Mizuho_Data->Fit("Mizuho_Data_Fit","R0");
	SPICE_Hole->Fit("SPICE_Fit","R0");
	
	char result1[100];
	sprintf(result1,"A-B exp(Cz), B: %2.2f +/- %1.2f, C: %2.3f +/- %1.3f",
		Hole_1_Fit->GetParameter(0),Hole_1_Fit->GetParError(0),Hole_1_Fit->GetParameter(1),Hole_1_Fit->GetParError(1));
	char result2[100];
	sprintf(result2,"A-B exp(Cz), B: %2.3f +/- %1.3f, C: %2.3f +/- %1.3f",
		Hole_2_Fit->GetParameter(0),Hole_2_Fit->GetParError(0),Hole_2_Fit->GetParameter(1),Hole_2_Fit->GetParError(1));
	char result3[100];
	sprintf(result3,"A-B exp(Cz), B: %2.3f +/- %1.3f, C: %2.3f +/- %1.3f",
		RICE_Data_Fit->GetParameter(0),RICE_Data_Fit->GetParError(0),RICE_Data_Fit->GetParameter(1),RICE_Data_Fit->GetParError(1));
	char result4[100];
	sprintf(result4,"A-B exp(Cz), B: %2.3f +/- %1.3f, C: %2.3f +/- %1.3f",
		Eisen_Data_Fit->GetParameter(0),Eisen_Data_Fit->GetParError(0),Eisen_Data_Fit->GetParameter(1),Eisen_Data_Fit->GetParError(1));
	char result5[100];
	sprintf(result5,"A-B exp(Cz), B: %2.3f +/- %1.3f, C: %2.3f +/- %1.3f",
		Gow_Data_Fit->GetParameter(0),Gow_Data_Fit->GetParError(0),Gow_Data_Fit->GetParameter(1),Gow_Data_Fit->GetParError(1));
	char result6[100];
	sprintf(result6,"A-B exp(Cz), B: %2.3f +/- %1.3f, C: %2.4f +/- %1.4f",
		Byrd_Data_Fit->GetParameter(0),Byrd_Data_Fit->GetParError(0),Byrd_Data_Fit->GetParameter(1),Byrd_Data_Fit->GetParError(1));
	char result7[100];
	sprintf(result7,"A-B exp(Cz), B: %2.3f +/- %1.3f, C: %2.3f +/- %1.3f",
		Mizuho_Data_Fit->GetParameter(0),Mizuho_Data_Fit->GetParError(0),Mizuho_Data_Fit->GetParameter(1),Mizuho_Data_Fit->GetParError(1));
	char result8[100];
	sprintf(result8,"A-B exp(Cz), B: %2.3f +/- %1.3f, C: %2.3f +/- %1.4f",
		SPICE_Fit->GetParameter(0),SPICE_Fit->GetParError(0),SPICE_Fit->GetParameter(1),SPICE_Fit->GetParError(1));
	
	Moores_Bay_Hole_1->SetMarkerStyle(2);
	Moores_Bay_Hole_2->SetMarkerStyle(4);
	RICE_Data->SetMarkerStyle(8);
	Eisen_Data->SetMarkerStyle(21);
	Gow_Data->SetMarkerStyle(3);
	Byrd_Data->SetMarkerStyle(20);
	Mizuho_Data->SetMarkerStyle(21);
	SPICE_Hole->SetMarkerStyle(22);
	
	Moores_Bay_Hole_1->SetMarkerSize(2);
	Moores_Bay_Hole_2->SetMarkerSize(2);
	SPICE_Hole->SetMarkerSize(2);
	RICE_Data->SetMarkerSize(2);
	Eisen_Data->SetMarkerSize(2);
	Gow_Data->SetMarkerSize(2);
	Byrd_Data->SetMarkerSize(1);
	Mizuho_Data->SetMarkerSize(1);
	
	Moores_Bay_Hole_1->SetMarkerColor(14);
	Moores_Bay_Hole_2->SetMarkerColor(14);
	RICE_Data->SetMarkerColor(kBlack);
	Eisen_Data->SetMarkerColor(kBlack);
	Gow_Data->SetMarkerColor(kBlack);
	SPICE_Hole->SetMarkerColor(kBlack);
	Byrd_Data->SetMarkerColor(14);
	Mizuho_Data->SetMarkerColor(14);
	
	Moores_Bay_Hole_1->GetYaxis()->SetRangeUser(MinIndex,MaxIndex);
	Moores_Bay_Hole_1->GetXaxis()->SetRangeUser(-MaxDepth,MinDepth);
	Moores_Bay_Hole_2->GetYaxis()->SetRangeUser(MinIndex,MaxIndex);
	Moores_Bay_Hole_2->GetXaxis()->SetRangeUser(-MaxDepth,MinDepth);
	SPICE_Hole->GetXaxis()->SetRangeUser(-MaxDepth,MinDepth);
	SPICE_Hole->GetYaxis()->SetRangeUser(MinIndex,MaxIndex);
	RICE_Data->GetYaxis()->SetRangeUser(MinIndex,MaxIndex);
	RICE_Data->GetXaxis()->SetRangeUser(-MaxDepth,MinDepth);
	Eisen_Data->GetYaxis()->SetRangeUser(MinIndex,MaxIndex);
	Eisen_Data->GetXaxis()->SetRangeUser(-MaxDepth,MinDepth);
	Gow_Data->GetYaxis()->SetRangeUser(-MaxDepth,MinDepth);
	Gow_Data->GetXaxis()->SetRangeUser(MinIndex,MaxIndex);
	Byrd_Data->GetYaxis()->SetRangeUser(-MaxDepth,MinDepth);
	Byrd_Data->GetXaxis()->SetRangeUser(MinIndex,MaxIndex);
	Mizuho_Data->GetYaxis()->SetRangeUser(-MaxDepth,MinDepth);
	Mizuho_Data->GetXaxis()->SetRangeUser(MinIndex,MaxIndex);
	
	Hole_1_Fit->SetLineColor(14);
	Hole_2_Fit->SetLineColor(14);
	SPICE_Fit->SetLineColor(kRed);
	RICE_Data_Fit->SetLineColor(kBlack);
	Eisen_Data_Fit->SetLineColor(kBlack);
	Gow_Data_Fit->SetLineColor(kBlack);
	Byrd_Data_Fit->SetLineColor(14);
	Mizuho_Data_Fit->SetLineColor(14);
	Asymp->SetLineColor(kBlack);
	Asymp2->SetLineColor(kBlack);
	
	Hole_1_Fit->SetLineWidth(3);
	Hole_2_Fit->SetLineWidth(3);
	SPICE_Fit->SetLineWidth(3);
	RICE_Data_Fit->SetLineWidth(3);
	Eisen_Data_Fit->SetLineWidth(3);
	Gow_Data_Fit->SetLineWidth(3);
	Byrd_Data_Fit->SetLineWidth(3);
	Mizuho_Data_Fit->SetLineWidth(3);
	Asymp->SetLineWidth(4);
	Asymp2->SetLineWidth(4);
	
	Hole_1_Fit->SetLineStyle(1);
	Hole_2_Fit->SetLineStyle(9);
	RICE_Data_Fit->SetLineStyle(1);
	Eisen_Data_Fit->SetLineStyle(9);
	Gow_Data_Fit->SetLineStyle(2);
	Byrd_Data_Fit->SetLineStyle(7);
	Mizuho_Data_Fit->SetLineStyle(2);
	SPICE_Fit->SetLineStyle(1);
	Asymp->SetLineStyle(1);
	Asymp2->SetLineStyle(1);
	
	Moores_Bay_Hole_1->Draw("P same");
	Moores_Bay_Hole_2->Draw("P same");
	RICE_Data->Draw("P same");
	Eisen_Data->Draw("P same");
	Gow_Data->Draw("P same");
	Byrd_Data->Draw("P same");
	Mizuho_Data->Draw("P same");
	SPICE_Hole->Draw("P same");
	
	Hole_1_Fit->Draw("same");
	Hole_2_Fit->Draw("same");
	SPICE_Fit->Draw("same");
	Asymp->Draw("same");
	Asymp2->Draw("same");
	RICE_Data_Fit->Draw("same");
	Eisen_Data_Fit->Draw("same");
	Gow_Data_Fit->Draw("same");
	Byrd_Data_Fit->Draw("same");
	Mizuho_Data_Fit->Draw("same");
	
	TLegend *legend = new TLegend(0.18,0.125,0.73,0.5); //wide
	//~ TLegend *legend = new TLegend(0.28,0.5,0.83,0.85); //zoom
	legend->AddEntry(Moores_Bay_Hole_1,"MB #1 (n(z) = 1.0+0.86#rho(z)) (ARIANNA 2016)","p");
	legend->AddEntry(Hole_1_Fit,result1,"l");
	legend->AddEntry(Moores_Bay_Hole_2,"MB #2 (n(z) = 1.0+0.86#rho(z)) (ARIANNA 2016)","p");
	legend->AddEntry(Hole_2_Fit,result2,"l");
	legend->AddEntry(Byrd_Data,"Byrd: Ebimuna et al (1983)","p");
	legend->AddEntry(Byrd_Data_Fit,result6,"l");
	legend->AddEntry(Mizuho_Data,"Mizuho: Ebimuna et al (1983)","p");
	legend->AddEntry(Mizuho_Data_Fit,result7,"l");
	legend->AddEntry(RICE_Data,"SP: RICE data (2004)","p");
	legend->AddEntry(RICE_Data_Fit,result3,"l");
	legend->AddEntry(Eisen_Data,"SP: Eisen et al (2003)","p");
	legend->AddEntry(Eisen_Data_Fit,result4,"l");
	legend->AddEntry(Gow_Data,"SP: Gow et al (xxxx)","p");
	legend->AddEntry(Gow_Data_Fit,result5,"l");
	legend->AddEntry(SPICE_Hole,"SP: SPICE Core (n(z) = 1.0+0.86#rho(z)) (2015)","p");
	legend->AddEntry(SPICE_Fit,result8,"l");
	legend->AddEntry(Asymp,"Bulk ice value (n = 1.78)","l");
	legend->AddEntry(Asymp2,"Surface value (n = 1.29+/-0.02) (Hanson 2013)","l");
	legend->Draw("same");
	
	char fileOut[100];
	sprintf(fileOut,"April21_plot1.pdf");
	c->Print(fileOut);
}
