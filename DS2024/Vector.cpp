typedef int Rank;
#ifndef HEADER_FILE
#define HEADER_FILE
#define DEFAULT_CAPACITY 3
#include<stdlib.h>
#include<iostream>
#endif
using namespace std;
template <typename T> class Vector{
protected:
	Rank _size;int _capacity;T* _elem;
	void copyFrom(T const*a,Rank lo,Rank hi)//��������A[lo,hi)
	{
		_elem=new T[_capacity=(hi-lo)*2];
		_size=0;
		while(lo<hi)
		{
			_elem[_size++]=a[lo++];
		}
	}
	void expand()//���� 
	{
		if(_size<_capacity) return;
		if(_capacity<DEFAULT_CAPACITY) _capacity=DEFAULT_CAPACITY;
		T*oldelem=_elem;
		_elem=new T[_capacity <<=1];
		for(int i=0;i<_size;i++)
			_elem[i]=oldelem[i];
		delete [] oldelem;
		
	}
	void shrink()
	{
		if(_capacity<DEFAULT_CAPACITY) return;
		if(_size<<2 > _capacity) return;
		T * oldElem=_elem;
		_elem=new T[_capacity>>=1];
		for(int i=0;i<_size;i++)
		{
			_elem[i]=oldElem[i];
		}
		delete [] oldElem;
	}
	

public:
	//���캯�� 
	Vector(int c=DEFAULT_CAPACITY,int s=0, T v=0)
	{_elem=new T[_capacity=c];for(_size=0;_size<s;_elem[_size++]=v);}//����Ϊc,��ģΪs������Ԫ�س�ʼΪv 
	//��������
	~Vector(){delete [] _elem;}
	//ֻ���ӿ� 
	int size()const{return _size;}//��ģ 
	bool empty()const{return !_size;}//�п� 
	Rank find(T const& e)const//����������� 
	{
		return find(e,0,_size);
	}
    Rank find(T const& e,Rank lo,Rank hi)const  //����������� �������ķ��ϵ��� 
	{
		while((lo<hi--)&&(e != _elem[hi]));
		if(hi<lo) return -1;
		else
		return hi;
	}                                        
	Rank search(T const &e,Rank lo,Rank hi);//�����������(δ���) 
	
	//����������� ��δ��ɣ�
	//��д�ӿ� 
	
	void mergeSort() {  //�鲢���� 
        mergeSort(0, _size);  
    }  
  
    void mergeSort(Rank lo, Rank hi) {  
        if (hi - lo < 2) return;  
        Rank mi = (lo + hi) / 2;  
        mergeSort(lo, mi);  
        mergeSort(mi, hi);  
        merge(lo, mi, hi);  
    }  
  
    void merge(Rank lo, Rank mi, Rank hi) {  
        T* a = _elem + lo;  
        int lb = mi - lo;  
        T* b = new T[lb];  
        for (Rank i = 0; i < lb; ++i) {  
            b[i] = a[i];  
        }  
        int lc = hi - mi;  
        T* c = _elem + mi;  
        Rank i = 0, j = 0, k = lo;  
        while (j < lb && k < hi) {  
            if (b[j] <= c[k - mi]) {  
                a[i++] = b[j++];  
            } else {  
                a[i++] = c[k++];  
            }  
        }  
        while (j < lb) {  
            a[i++] = b[j++];  
        }  
        while (k < hi) {  
            a[i++] = c[k++];  
        }  
        delete[] b;  
    }  
	bool bubble(Rank lo,Rank hi)//ð�ݵ��� 
		{
			bool sorted=true;
			while(lo++<hi)
			{
				if(_elem[lo-1]>_elem[lo])
				{
					sorted=false;
					swap(_elem[lo-1],_elem[lo]);
				}
			}
			return sorted;
		}
	void bubbleSort(Rank lo,Rank hi)//ð������
	{
		while(!bubble(lo,hi--));
	}
	void unsort(Rank lo,Rank hi)//����
	{
		T*a=_elem+lo;
		for(Rank i=hi-lo;i>0;i--)
			swap(a[i-1],a[rand() %i]);
	} 
	void unsort(){unsort(0,_size);}//�������� 
	Rank insert(Rank r,T const&e)//��rλ�ò���
	{
		expand();
		for(int i=_size;i>r;i--)
			_elem[i]=_elem[i-1];
			_size++;
			_elem[r]=e;
		return r;
	} 
	Rank insert(T const&e) {insert(_size,e);}//Ĭ��ĩβ���� 
	T remove(Rank r){T e=_elem[r];remove(r,r+1);return e;}//ɾ����Ϊr��Ԫ��
	int remove(Rank lo,Rank hi)//ɾ��[lo,hi)��Ԫ��
	{
		if(hi==lo) return 0;
		while(hi<_size) _elem[lo++]=_elem[hi++];
		_size=lo;
		shrink();
		return hi-lo;
	}
	int deduplicate() //����ȥ�� 
	{  
    int oldSize = _size;  
    Rank i = 1;  
    while (i < _size) {  
        Rank pos = find(_elem[i], 0, i);  
        if (pos >= 0) {   
            remove(i);  
            
        } else {  
            i++;   
        	}  
    	}  
    shrink();  
    return oldSize - _size;  
	}
	T &operator[] (Rank r)const//���������[]
	{
		return _elem[r];
	}
	Vector<T>&operator= (Vector<T> const &a)//���������=
	{
		if(_elem) delete [] _elem;
		copyFrom(a._elem,0,a.size());
		return *this;
	} 
};
