
extern int M2dft(short*, int);

// Table générée avec Fnor = 1; Ph = 0; A = 2048
extern short TabSig[];

// Jeux de tests
extern short TabSig1[]; // f 1,45
extern short TabSig2[]; // f 17,30 f 28,135
extern short TabSig3[]; // f 23,25 f 24,116

int tab[64];

int main(void)
{
	for (int k=0; k < 64; ++k)
	{
		// Changer l'argument TabSig pour choisir le signal
		tab[k] = M2dft(TabSig2, k);
	}
	while (1) {}
}
