#define SIZE 7

int input[] = {60, 41, 46, 50, 44, 3, 84, 80, 55, 57, 91, 22, 21, 12, 64, 59, 71, 34, 81, 77, 69, 95, 2, 24, 61, 73, 25, 19, 29, 91, 45, 53, 39, 15, 47, 58, 3, 62, 81, 0, 33, 83, 12, 64, 75, 59, 32, 68, 98, 68, 53, 74, 88, 30, 65, 23, 97, 66, 49, 46, 18, 22, 0, 30, 3, 33, 13, 33, 31, 61, 14, 87, 57, 95, 20, 92, 67, 71, 42, 52, 18, 98, 2, 93, 95, 69, 90, 8, 97, 46, 26, 68, 69, 84, 73, 35, 44, 88, 79, 65};

void swap(int *a, int *b)
{
	int sw = *a;
	*a = *b;
	*b = sw;
}

int main()
{

	int buf[SIZE];
	int i,j;

	for(i=0; i < SIZE; i++)
	{
		buf[i] = input[i];
	}


	for(i=SIZE; i > 1; i--)
	{
		for(j=0; j < i-1; j++)
		{
			if(buf[j] > buf[j+1])
			{
				swap(&(buf[j]), &(buf[j+1]));
			}
		}
	}

	asm volatile ("break");
    return 0;
}

void __start()
{
  asm volatile ("lui $sp, 0xf00");
  main();
  // does not return
}

