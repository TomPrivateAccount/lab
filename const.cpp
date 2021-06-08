#include<iostream>
#include<vector>
#if __cplusplus >= 201103L
#include<memory>
#endif
using namespace std;

class Complex{
public:
    static int cnt;
    static int cnt_move;
    bool is_move;
    double real, imag;
    vector<int> vec;

    explicit Complex(double r,double i){
        is_move = false;
        real = r; 
        imag = i;
        vec.push_back(100);
        vec.push_back(150);
        cnt++;
     
        cout<<"Normal Constructor Complex num |"<<"Normal Complex num "<<cnt<<" Moved Complex num "<<cnt_move<<std::endl<<std::flush;
    }
    ~Complex(){
        if(is_move){
            cnt_move--;
        }else{
            cnt--;
        }
        cout<<"Destory Complex num |"<<"Normal Complex num "<<cnt<<" Moved Complex num "<<cnt_move<<std::endl<<std::flush;
    }
    Complex(const Complex & c){
        is_move = false;
        cnt++;
        real = c.real; imag = c.imag;
        cout<<"Copy Constructor called |"<<"Normal Complex num "<<cnt<<" Moved Complex num "<<cnt_move<<endl ;
    }
    #if __cplusplus >= 201103L
    Complex(Complex && c){
        is_move = true;
        real = move(c.real); imag = c.imag;
        vec = move(c.vec);
        cnt_move ++;
        cout<<"Move Constructor called |"<<"Normal Complex num "<<cnt_move<<" Moved Complex num "<<cnt_move<<endl ;
    }
    #endif
};

Complex foo1(Complex input, bool change = false){
    cout<<"                            foo1 func begin"<<endl;
    change?input.imag = 100:input.imag;
    Complex tmp(1,2);
    cout<<"                            foo1 func begin to return "<<endl;
        return tmp;
}
#if __cplusplus >= 201103L
Complex foo2(Complex input){
    cout<<"                           foo2 func begin"<<endl;
    Complex tmp(1,2);
    cout<<"                           foo2 func begin to return"<<endl;
    return move(tmp);
}
#endif
Complex foo3(Complex &input){
    cout<<"                           foo3 func begin"<<endl;
    Complex tmp(1,2);
     cout<<"                          foo3 func begin to return "<<endl;

    return tmp;
}

int Complex::cnt = 0;
int Complex::cnt_move=0;


int main(){
    cout<<" show all funct is normal or not"<<endl;
    {
        Complex cl(1, 2);
        Complex c2 (cl);  
        Complex tmp = c2;
    }

    cout<<" ==================================exp begin =================================================================="<<endl;
    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 1 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
    {
        Complex c3(1,2);
        Complex c4 = foo1(c3);
    }

    #if __cplusplus >= 201103L
    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 2 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
    
    {
        Complex c5(1,2);
        Complex c6 = foo2(c5);
    }


    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 3 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
    
    {
        Complex c7(1,2);
        Complex c8 = move(foo1(c7));
    }


    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 4 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
    
    {
        Complex c9(9,10);
        Complex c10 = foo1(move(c9),true);
        cout<<"TEST "<<c9.imag<<" "<<c9.real<<" "<<c9.vec.size()<<endl;
    }


    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 5 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
    
    {
        shared_ptr<Complex> c11 = make_shared<Complex>(1,2);
        Complex c12 = foo3(*c11);
    }


    #endif
    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 6 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
   
    {
        Complex c13(1,2);
        Complex c14 = foo3(c13);
    }


    #if __cplusplus >= 201103L
    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 8 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
    
    {
        shared_ptr<Complex> c15 = make_shared<Complex>(1,2);
        Complex c16 = foo1(move(*c15));
        cout<<"TEST 1 "<<c15.use_count()<<endl;
        if(c15.use_count())
        cout<<"TEST 2 "<<c15->vec.size()<<endl;
    }   


    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 9 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
    
    {
        Complex c17 = foo1(Complex(1,2));
    }


    std::cout<<"---------------------------------------"<<endl;
    std::cout<<"exp 10 Complex num "<<Complex::cnt<<Complex::cnt_move<<std::endl;
    std::cout<<"---------------------------------------"<<endl;
    
    {
        Complex c18 = foo1(move(Complex(1,2)));
    }

    #endif

    return 0;
}