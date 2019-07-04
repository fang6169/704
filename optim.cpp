#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>


using namespace std;

void Cal()
{
	/*
	int i = 1;
    for(i; i <= 100; i++)
    {
        if((i % 3 == 0 && i % 5 == 0))// 1%3 = 0: is 3,6,9...1%3 = 1: 4,7,10...
		{
			std::cout << "PR\n";
			//std::cout <<i<< "PR\n";
		}
        else if(i % 3 == 0)
		{
			std::cout << "P\n";
		}
        else if(i % 5 == 0)
		{
			std::cout << "R\n";
		}
        else
		{
			std::cout << i <<"\n";
		}
    }
	*/
	//it is better than above
	for (int i = 0; i <= 100; ++i)
	{
		bool fizz = (i % 3) == 0;
		bool buzz = (i % 5) == 0;
		if (fizz)
			std::cout << "Fizz";
		if (buzz)
			std::cout << "Buzz";
		if (!fizz && !buzz)
			std::cout << i;
		std::cout << std::endl;
  }

}

void  Calcul()
{
	vector <int>v;//vector <int>my_numbers;

	v.push_back(4);
	v.push_back(2);
	v.push_back(64);
	v.push_back(18);
	v.push_back(25);

	//Unoptimized loop with index
#if 0
	int sum = 0;
	for(unsigned x =0; x< v.size(); x++)
		sum = sum + v[x];
#endif
   
#if 0
	//method 1: Unoptimized loop with iterator:
	int sum = 0;
	std::vector<int>::const_iterator it;
	for (it = v.begin(); it != v.end(); it++)
		sum += *it;
#endif

#if 0
	//Cached std::vector::end iterator:
	int sum = 0;
	std::vector<int>::const_iterator it, end = v.end();
	for (it = v.begin(); it != end; it++)
		sum += *it;
#endif

#if 1
	//Cached & Pre-increment iterators
	int sum = 0;
	std::vector<int>::const_iterator it, end = v.end();
	for (it = v.begin(); it != end;  ++it)
		sum += *it;
#endif

	std::cout<<sum<<"\n";


}

//better in performance
void FlipBuffer0(unsigned char *pixels, int width, int height, int bytes_per_pixel)
{
	const size_t stride = width * bytes_per_pixel;
    unsigned char *row;// = malloc(stride);
	row = new unsigned char[stride];
    unsigned char *low = pixels;
    unsigned char *high = &pixels[(height - 1) * stride];

    for (; low < high; low += stride, high -= stride) 
	{
        memcpy(row, low, stride);
        memcpy(low, high, stride);
        memcpy(high, row, stride);
    }
   // free(row);

	#if 1
    int btt=0, r =0, g =0, b=0, flg =0;
	for(int yy =0; yy < height; yy++)
	{
		for(int xx=0; xx < width; xx++)
		{
			//tt = tt + *(rBuf + yy * nW + xx)*3;
				r = *(pixels + yy * width + xx);
				g = *(pixels + yy * width + xx + 1);
				b = *(pixels + yy * width + xx + 2);
				btt = btt + 3*r;
			
		}
	 }

    cout<<btt<<"\n";
    #endif

	if(row !=NULL)
	{
		delete row;
		row = NULL;
	}


}

void FlipBuffer(unsigned char *rBuf, int nWi, int nHi, int nPer)
{
	unsigned char *LnBuf;//desternation
	LnBuf = new unsigned char[nWi*nPer];
	int offset =0, line = nPer* nWi;
	int Topset=0, Downset =0;

	for(int nn =0; nn < nHi/2; nn++)
	{
		Topset = nn * line;
		Downset = (nHi-1 - nn)*line;

		memcpy(LnBuf, (rBuf + Topset), line);
		memcpy((rBuf + Topset), (rBuf +Downset), line);
		memcpy((rBuf + Downset), LnBuf, line);
	}


	
#if 1  ////test
    int btt=0, r =0, g =0, b=0, flg =0;
	for(int yy = 0; yy < nHi; yy++)
	{
		for(int xx=0; xx <nWi; xx++)
		{
			//tt = tt + *(rBuf + yy * nW + xx)*3;
				r = *(rBuf + yy * nWi + xx);
				g = *(rBuf + yy * nWi + xx + 1);
				b = *(rBuf + yy * nWi + xx + 2);
				btt = btt + 3*r;
			
		}
	}

    cout<<btt<<"ok"<<"\n";
#endif
	if(LnBuf !=NULL)
	{
		delete LnBuf;
		LnBuf = NULL;
	}
}


void main()
{
  //  Calcul();//case 1
  // Cal();//case 2
    unsigned char *rBuf;
	int nW = 100;
	int nH = 40;
	int nByePer = 3;
	rBuf = new unsigned char[nW * nH * nByePer];
	int test=0;

	for(int yy =0; yy < nH; yy++)
	{
		for(int xx=0; xx <nW; xx++)
		{
			if( yy < 0.4*nH)
			{
				*(rBuf + yy * nW + xx) = 0;
			//	test++;
				*(rBuf + yy * nW + xx + 1) = 0;
			//	test++;
				*(rBuf + yy * nW + xx + 2) = 0;
				test = test +  *(rBuf + yy * nW + xx)*3;
			}
			else
			{
			//	rBuf[yy * nW + xx] = 1;
			//	rBuf[yy * nW + xx + 1] = 1;
			//	rBuf[yy * nW + xx + 2] = 1;
				*(rBuf + yy * nW + xx) = 1;
				
				*(rBuf + yy * nW + xx + 1) = 1;
				
				*(rBuf + yy * nW + xx + 2) = 1;

				test = test +  *(rBuf + yy * nW + xx)*3;
				
			}
		}
	}
	test = test;
	cout<<test<<"\n";
	FlipBuffer(rBuf, nW, nH, nByePer);

#if 0
    int tt=0, r =0, g =0, b=0, flg =0;
	for(int yy =0; yy < nH; yy++)
	{
		for(int xx=0; xx <nW; xx++)
		{
			//tt = tt + *(rBuf + yy * nW + xx)*3;
				r = *(rBuf + yy * nW + xx);
				g = *(rBuf + yy * nW + xx + 1);
				b = *(rBuf + yy * nW + xx + 2);
				tt = tt + 3*r;
			
		}
	}

    cout<<tt<<"\n";
#endif
	if(rBuf !=NULL)
	{
		delete rBuf;
		rBuf = NULL;
	}
}