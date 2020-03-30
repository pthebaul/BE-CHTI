extern double sommeTrigo(int);

int main(void) {
	double max, min, tmp;
	for (int i = 0; i < 64; ++i)
	{
		tmp = sommeTrigo(i);
		if (tmp > max)
		{
			max = tmp;
		}
		if (tmp < min)
		{
			min = tmp;
		}
	}
	while	(1) {}
}
