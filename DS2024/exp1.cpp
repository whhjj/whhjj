#include <iostream>
#include<stdlib.h> 
#include<time.h>
#include<math.h>
#include"Vector.cpp"
using namespace std;
class Complex{
	private:
		double _real,_imag;
	public:
		Complex()
		{
			_real=double(rand());
			_imag=double(rand());
		}
		Complex(double a,double b)
		{
			_real=a;
			_imag=b;
		}
		double real()const
		{
			return _real;
		}
		
		double imag()const
		{
			return _imag;
		}
		double modulus() const
		{
			return pow((pow(_real,2)+pow(_imag,2)),0.5);
		}
		void Out()
		{
			cout<<"�ø���Ϊ:"<<_real<<"+"<<_imag<<"i"<<"ģΪ��"<<pow((pow(_real,2)+pow(_imag,2)),0.5)<<endl;
		}
		Complex operator=(Complex const& a)
		{
			_real=a._real;
			_imag=a._imag;
			return *this;
		}
		bool operator==(Complex const & a)const
		{
			return _real==a._real && _imag==a._imag;
		}
		bool operator!=(Complex const & a)const
		{
			return _real!=a._real || _imag!=a._imag;
		}
		bool operator>(const Complex& a) const {  
        if (modulus() != a.modulus()) return modulus() > a.modulus();  
        else if (_real != a._real) return _real > a._real;  
        else return _imag > a._imag;  
    	} 
    	bool operator<(const Complex& a) const {  
        if (modulus() != a.modulus()) return modulus() < a.modulus();  
        else if (_real != a._real) return _real < a._real;  
        else return _imag < a._imag;  
    	}  
  
    	bool operator<=(const Complex& a) const {  
        return !(*this > a);  
    	}
		
};
Vector<Complex> Search(Vector<Complex> const &e,int p,int q)
{
	Complex a(0,0);
	Vector<Complex> h(3,0,a);
	Rank x=0,y=e.size()-1;
	while(e[x++].modulus()<p && x<=e.size());x--;
	if(x==e.size()) return h;
	while(e[y--].modulus()>=q&&y>=x);y++;
	for(int i=0;i<=(y-x);i++)
	h.insert(e[x++]);
	return h; 
} 
int main(int argc, char** argv) {
	srand(time(NULL));
	int a=100;
	int sa=0;
	clock_t st,end;
	Complex c(0,0);
	Complex c1,c2,c3;
	Vector<Complex> m(a*2,a,c),m1(a*2,a,c);
	Vector<Complex> n(a*2,a,c),n1(a*2,a,c);
	Vector<Complex> test(a*2,a,c);
	cout<<"����"<<a<<"������"<<endl; 
	for(int i=0;i<a;i++)
	{
		Complex r;r.Out();
		m[i]=r;
	}
	m.insert(a/rand(),c);
	for(int i=0;i<rand()%10;i++)m.insert(a/rand(),m[a/rand()]);
	n=m;m1=m;n1=m;

	m.unsort();
 	
 	cout<<"��c��ͬ��Ԫ����Ϊ"<<m.find(c)<<endl;

	m.insert(0,c1);
	m.insert(m.size()/2,c2);
	m.insert(c3);

	m.remove(0);
	m.remove(m.size()-1);
	m.remove(m.size()/4,m.size()/2); 

	cout<<"ȥ����"<<m. deduplicate()<<"���ظ�Ԫ��"<<endl;

	st=clock();
	cout<<"����ð������ʼ"<<endl;
	m.bubbleSort(0,m.size());
	end=clock();
	long eff1=end-st;
	cout<<"�������,����ð����ʱ"<<eff1<<"ms"<<endl;

	st=clock();
	cout<<"˳��ð������ʼ"<<endl;
	m.bubbleSort(0,m.size());
	end=clock();
	long eff2=end-st;
	cout<<"�������,˳��ð����ʱ"<<eff2<<"ms"<<endl; 
	
	for(int i=0;i<m.size();i++)
	{
		m[i]=m1[m1.size()-i-1];
	} 
	n1=m;
	st=clock();
	cout<<"����ð������ʼ"<<endl;
	m.bubbleSort(0,m.size());
	end=clock();
	long eff3=end-st;
	cout<<"�������,����ð����ʱ"<<eff3<<"ms"<<endl; 

	st=clock();
	cout<<"����鲢����ʼ"<<endl;
	n.mergeSort(0,n.size());
	end=clock();
	long eff4=end-st;
	cout<<"�������,����鲢��ʱ"<<eff4<<"ms"<<endl;

	st=clock();
	cout<<"˳��鲢����ʼ"<<endl;
	n.mergeSort(0,n.size());
	end=clock();
	long eff5=end-st;
	cout<<"�������,˳��鲢��ʱ"<<eff5<<"ms"<<endl; 

	n=n1; 
	st=clock();
	cout<<"����鲢����ʼ"<<endl;
	n.mergeSort(0,n.size());
	end=clock();
	long eff6=end-st;
	cout<<"�������,����鲢��ʱ"<<eff6<<"ms"<<endl; 

	test=Search(m,100,10000);
	if(test.size()==0) cout<<"û��ģ�ڴ����������"<<endl;
	else{
		cout<<"����������ģ�ڴ�����"<<endl;
		for(int i=0;i<test.size();i++)
		test[i].Out();
	}	
	return 0;
}

