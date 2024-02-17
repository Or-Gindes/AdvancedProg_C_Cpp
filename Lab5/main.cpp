#include "Employee.h"


int main() {


	Employee *yael= new Employee((char*)"Yael",11000);
	Employee *barak= new Employee((char*)"Barak",11000);

	//	Operator << overload
	cout <<"<< overload:"<<endl;
	cout <<(*barak)<<endl;

	//	Operator ++ overload
	cout <<"++ overload:"<<endl;
	++(*barak);
	cout <<(*barak)<<endl;

	//	Operator > overload
	cout <<"> overload:"<<endl;
	if(*barak>*yael)
	{
		cout<<"Barak's salary is higher than Yael's \n"<<endl;
	}

	//	Operator + overload
	cout <<"+ overload:"<<endl;
	*barak+*yael;
	cout <<(*barak)<<endl;

	//	Operator += overload
	cout <<"+= overload:"<<endl;
	*barak+=*yael;
	cout <<(*barak)<<endl;


	//	Operator == overload
	if((*barak)==(*yael))
	{
		cout<<"Same name\n"<<endl;
	}

	//Static funciton
	cout<<"There are "<< barak->getNumberOfEmployee() <<" employees"<<endl;
	Employee *yael2= new Employee((char*)"Yael",100);
	cout<<"There are "<< yael2->getNumberOfEmployee() <<" employees"<<endl;

	if((*yael2)==(*yael))
	{
		cout<<"Same name\n"<<endl;
	}
	return 0;


}
