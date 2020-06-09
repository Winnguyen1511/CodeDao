#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>

using namespace std;
typedef struct
{
	int LRU;
	int tag;
} line_t;
int data,tag,index,tmp,LRUi,checker;
int read_hit, read_miss, write_hit, write_miss, write, read;
int comm[20],cache[20],num=0;
int LRU_big1[16384], space1[16384];
int LRU_big2[16384], space2[16384];
line_t set2[2];
line_t set4[4];
line_t instr_cache[16384][2];
line_t data_cache[16384][4];
line_t tmp_value[16384][10];
void getdata();
void readdata4w(int data2,int index2,int tag2);
void writedata4w(int data2,int index2,int tag2);
void readdata2w(int data2,int index2,int tag2);
void clear();
void printout();
int gettag(int tagg);
int getindex(int indexx);
/*------------------------------------------------------*/
void getdata()
{
	ifstream myfile ;
	myfile.open("test.txt",ios::out);
	if (myfile.fail())
	{
		cout << "Unable to open this file" << endl;
	}
	else
	{
		while (!myfile.eof())
		{
			num++;
			myfile >> dec >> comm[num] >> hex >> cache[num];
			for (int i=1;i<=num;i++)
			{
				cout << comm[i] << "  ";
				cout << cache[i] << endl;
			}
		}
	}
		
	myfile.close();
}	
// lay bit tag
int gettag(int tagg)
{
	int bit_tag;
	tagg = tagg/64;
	bit_tag = tagg/16384;
	return bit_tag;
}
// Lay bit index
int getindex(int indexx)
{
	int bit_index;
	indexx = indexx/64;
	indexx = indexx%16384;
	bit_index = indexx;
	
	return bit_index;
}
// doc du lieu vao L1 2 way
void readdata2w(int data2,int index2,int tag2)
{
	int k = 0;
	LRU_big2[index2]++;
	for (int i=1;i<=2;i++)
	{
			if (tag2 == instr_cache[index2][i].tag)
			{
				read_hit++;
				k = 1;	
				instr_cache[index2][i].LRU = LRU_big2[index2];
			}
	}
	if (k == 0)
	{
		read_miss++;
		cout << "Read from L2 < " << hex  << data2 << " >"<< endl;
		cout << "----------------------" << endl;
		if (space2[index2]<2 )
		{ 
			space2[index2]++;
			instr_cache[index2][space2[index2]].LRU = LRU_big2[index2];
			instr_cache[index2][space2[index2]].tag = tag2;
		}
		else
		{
			int l,vt;
            l= instr_cache[index2][1].LRU;
            vt=1;
            if (l > instr_cache[index2][2].LRU)
                {
                    l=instr_cache[index2][2].LRU;
                    vt=2;
                }
                instr_cache[index2][vt].tag = tag2;
                instr_cache[index2][vt].LRU = LRU_big2[index2];
		}
	
	} 
}
// doc du lieu vao L1 4 way
void readdata4w(int data2,int index2,int tag2)
{
	int k = 0;
	LRU_big1[index2]++;
		for (int i=1;i<=4;i++)
		{
			if (tag2 == data_cache[index2][i].tag)
			{
				read_hit++;
				k = 1;	
				data_cache[index2][i].LRU = LRU_big1[index2];
			}
		}
	
	if (k == 0)
	{
		read_miss++;
		cout << "Read from L2 " << hex << "< " << data2 << " >"<< endl;
		cout << "----------------------";
		if (space1[index2] < 4)
		{
			space1[index2]++;
			data_cache[index2][space1[index2]].LRU = LRU_big1[index2];
			data_cache[index2][space1[index2]].tag = tag2;
		}
		else 
		{
			int l,vt;
            l = data_cache[index2][1].LRU;
            vt = 1;
            for (int i=2; i<=4; i++)
            {
                if (l > data_cache[index2][i].LRU)
                {
                    l=data_cache[index2][i].LRU;
                    vt=i;
                }
            }

                data_cache[index2][vt].tag = tag2;
                data_cache[index2][vt].LRU = LRU_big1[index2];
		}	
		
	}
	}
// ghi du lieu vao L1 4 way
void writedata4w(int data2,int index2,int tag2)
{
	getdata();
	int k = 0;
	LRU_big1[index2]++;
	for (int i=1;i<=4;i++)
		{
			if (tag2 == data_cache[index2][i].tag)
			{
				write_hit++;
				k = 1;	
				data_cache[index2][i].LRU = LRU_big1[index2];
			}
		}
	if (k == 0)
	{
		write_miss++;
		cout << "Read for Ownership from L2 < " << hex << data2 << " >" << endl;
		cout << "----------------------" << endl;
		if (space1[index2] < 4)
		{
			space1[index2]++;
			data_cache[index2][space1[index2]].LRU = LRU_big1[index2];
			data_cache[index2][space1[index2]].tag = tag2;
		}
		else 
		{
			int l,vt;
            l = data_cache[index2][1].LRU;
            vt = 1;
            for (int i=2; i<=4; i++)
            {
                if (l > data_cache[index2][i].LRU)
                {
                    l=data_cache[index2][i].LRU;
                    vt=i;
                }
            }
                data_cache[index2][vt].tag = tag2;
                data_cache[index2][vt].LRU = LRU_big1[index2];
		}
	}
}
void clear()
{
	int *begin1 = &space1[1],
		*end1 = &space1[16384],
		*begin2 = &LRU_big1[1],
		*end2 = &LRU_big1[16384],
		*begin3 = &space2[1],
		*end3 = &space2[16384],
		*begin4 = &LRU_big2[1],
		*end4 = &LRU_big2[16384];
	std::fill(begin1, end1, 0);
    std::fill(begin2, end2, 0);
    std::fill(begin3, end3, 0);
    std::fill(begin4, end4, 0);
    read_hit=0;
    read_miss=0;
    write_hit=0;
    write_miss=0;
    read=0;
    write=0;
    cout << "----CLEAR CACHE----" << endl;
}
// in ra man hinh
void printout()
{
	double ratio;
	ratio = (double) (read_hit+read_miss)/(read+write);
	cout << "----------------------" << endl;
	cout << "Number of cache reads: " << read << endl;
	cout << "Number of cache writes: " << write << endl;
	cout << "----------------------" << endl;
	cout << "Read hit: " << read_hit << endl;
	cout << "Read miss: " << read_miss << endl;
	cout << "----------------------" << endl;
	cout << "Write hit: " << write_hit << endl;
	cout << "Write miss: " << write_miss << endl;
	cout << "----------------------" << endl;
	cout << "Number of cache hit: " << read_hit+write_hit << endl;
	cout << "Number of cache miss: " << read_miss+write_miss << endl;
	cout << "----------------------" << endl;
	cout << "Cache hit ratio: " << 	fixed << setprecision(2) << ratio*100 << "%" << endl;
	cout << "----------------------" << endl;
}			
int main()
{
	getdata();
	for (int i=1;i<=num;i++)
		{
			index = getindex(cache[i]);
			tag = gettag(cache[i]);
			if (comm[i] == 0 )
			{
				read++;
				readdata4w(cache[i],index,tag);
			}
			if (comm[i] == 1)
			{
				write++;
				writedata4w(cache[i],index,tag);
			}
			if (comm[i] == 2)
			{
				read++;
				readdata2w(cache[i],index,tag);
			}
			if (comm[i] == 3)
			{
				// evict command from L2
			}
			if (comm[i] == 8)
			{
				clear();
			}
			if (comm[i] == 9)
			{
				printout();
			}
		}
	return 0;
}
