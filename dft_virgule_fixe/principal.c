extern int sommeTrigo(int);

int main(void) {
	signed int resultat;
	signed int min = 40000;
	signed int max = 20000;
	for (int i = 0; i < 64; ++i)
	{
		resultat = sommeTrigo(i);
		if (resultat > max)
		{
			max = resultat;
		}
		if (resultat < min)
		{
			min = resultat;
		}
	}
	while	(1) {}
}
