
extern int M2dft(short*, int);
extern short TabSig[];

int tab[64];

int main(void)
{
	for (int k=0; k < 64; ++k)
	{
		tab[k] = M2dft(TabSig, k);
	}
	while (1) {}
}
