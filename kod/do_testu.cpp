if(!stw->czy_inteligentne())
		{
			if(plansza[stw->daj_pole() + 1 ] ->spr() )
			{
				if(stw->czy_atakowac(*plansza[stw->daj_pole()+1]->daj_stworzenie()))
				{
					stw->interakcjuj(*plansza[stw->daj_pole()+1]->daj_stworzenie());
					if(plansza[stw->daj_pole()+1]->daj_stworzenie()->daj_zdrowie() < = 0)
						;//postaw(stw);


				}
			}
			else
				if(plansza[stw->daj_pole() - 1 ] ->spr() )
				{
					if(stw->czy_atakowac(*plansza[stw->daj_pole()-1]->daj_stworzenie()))
					{
							stw->interakcjuj(*plansza[stw->daj_pole()-1]->daj_stworzenie());

					}
				}
			else
				if(plansza[stw->daj_pole() + sz +2 ] ->spr() )
				{
					if(stw->czy_atakowac(*plansza[stw->daj_pole()+sz +2]->daj_stworzenie()))
					{
						stw->interakcjuj(*plansza[stw->daj_pole()+sz +2]->daj_stworzenie());
					}
				}
			else
				if(plansza[stw->daj_pole() -sz - 2 ] ->spr() )
				{
					if(stw->czy_atakowac(*plansza[stw->daj_pole() -sz  - 2]->daj_stworzenie()))
					{
							stw->interakcjuj(*plansza[stw->daj_pole() - sz - 2]->daj_stworzenie());
					}
				}
			if(stw->daj_zdrowie() <= 0 || stw->daj_ruch() <= 0)
			{
				int temp = 0;
				for(auto s : stwory)
				{
					if(s == stw)
					{
						stwory.erase(stwory.begin()+temp);
					}
						temp++;
					}
					plansza[stw->daj_pole()]->usun_z_pola();
				}
		}