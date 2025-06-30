

// 1.Takes data form employee_data.csv
// 2.Add New Employee
// 3.Edit Employee
// 4.Delete Employee
// 5.Show Employee detail
// 6.Show all Employee detail
// 7.Exit



#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Employee{
    string name="";
    string department="";
    string salary="";
    string addres="";
    string phone_no="";
    public:
    string e_id="";
    
    
    static int num_of_object; //Class varible 
    
    
    
    void store_detail(string na,string l,string br,string sal ,string addr,string pho){
        name=na;
        e_id=l;
        department=br;
        salary=sal;
        addres=addr;
        phone_no=pho;
    }
    
    
    
    void new_employee(Employee *obj){
        cout<<"Enter Employee E_id: ";
        getline(cin,e_id);

        // ---Cheaks if Employee Already Exist or not------
        if (get_employee_sno(e_id,obj)!=-1){
            cout<<"Employee already Exist"<<endl;
            return;
        }
        // --------------------------------------

        cout<<"Enter Employee name: ";
        getline(cin,name);
        cout<<"Enter Employee department: ";
        getline(cin,department);
        cout<<"Enter Employee salary: ";
        getline(cin,salary);
        cout<<"Enter Employee addres: ";
        getline(cin,addres);
        cout<<"Enter Employee phone number: ";
        getline(cin,phone_no);

        // ---------Storing  to object-------------
        store_detail(name, e_id, department,salary, addres, phone_no);
        num_of_object++; // counts number of stored data


        
        store_to_csv(name, e_id, department,salary, addres, phone_no);
    }

    
    
    // ****************Storing to Csv file name employee_data.csv****************
    static void store_to_csv(string na,string l,string br,string sal ,string addr,string pho){

        ofstream out("employee_data.csv",ios::app); // ios::app tells console to open file in append mode
        out<<endl<<na<<','<<l<<','<<br<<','<<sal<<','<<addr<<','<<pho;
        out.close();
    }     
    // ---------------------------------------------------
    
    // ***************Stoter all current data to csv************ 
    static void replace_console_data_to_csv(Employee *obj){
        ofstream erase("employee_data.csv");
        erase<<obj[0].name<<','<<obj[0].e_id<<','<<obj[0].department<<','<<obj[0].salary<<','<<obj[0].addres<<','<<obj[0].phone_no;
        for (int i=1;i<num_of_object;i++){
            cout<<obj[i].name<<endl;
            erase<<endl<<obj[i].name<<','<<obj[i].e_id<<','<<obj[i].department<<','<<obj[i].salary<<','<<obj[i].addres<<','<<obj[i].phone_no;   
        }
        erase.close();
    }
    // ------------------------------------------------------



    // ----------------Return's  index of object of array---------------- 
    static int get_employee_sno(string num,Employee *obj){
        int emp_sno=-1;
        for (int i=0;i<Employee::num_of_object;i++){
            
            if (obj[i].e_id==num){
                emp_sno=i;
                break;
            }
        }
        return emp_sno;
    }
    //-------------------------------------------------------------------- 



    void show_employee_detail(){
        cout<<name<<"\t\t"<<e_id<<"\t\t"<<department<<"\t\t"<<salary<<"\t\t"<<addres<<"\t\t"<<phone_no<<endl;
    }


    friend void edit_employee(Employee *obj);
    friend void delete_obj(int index,Employee *obj);


};



// assiging 0 to num_of_object
int Employee::num_of_object=0;
// --------------------------------

// ****************Delete one row by taking index and object**********
void delete_obj(int index,Employee *obj){
    
    if(index>=1){
        for(int i=index;i<Employee::num_of_object-1;i++){
            obj[i].store_detail(obj[i+1].name,obj[i+1].e_id,obj[i+1].department,obj[i+1].salary,obj[i+1].addres,obj[i+1].phone_no);
        }

        Employee::num_of_object--;
        Employee::replace_console_data_to_csv(obj);
    }
}
// --------------------------------------------------



// *********Edit Employee function***************
void edit_employee(Employee *obj){
    string id;
    int choice;
    cout<<"Enter Id: "<<endl;
    cin>>id;
    if (Employee::get_employee_sno(id,obj)!=-1){
        cout<<"1.Edit department"<<endl;
        cout<<"2.Edit Salary"<<endl;
        cout<<"3.Edit Address"<<endl;
        cout<<"4.Edit Phone number"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        cin.ignore();
        if (choice==1){
            string bra;
            cout<<"Enter New department: ";
            getline(cin,bra);
            obj[Employee::get_employee_sno(id,obj)].department=bra;
        }
        else if (choice==2){
            string sa;
            cout<<"Enter New Salary: ";
            getline(cin,sa);
            obj[Employee::get_employee_sno(id,obj)].salary=sa;
        }
        else if (choice==3){
            string addr;
            cout<<"Enter New Address: ";
            getline(cin,addr);
            obj[Employee::get_employee_sno(id,obj)].addres=addr;
        }
        else if (choice==4){
            string pho;
            cout<<"Enter New Phone Number: ";
            getline(cin,pho);
            obj[Employee::get_employee_sno(id,obj)].phone_no=pho;
        }
        else{
            cout<<"Enter wrong choice"<<endl;
        }
        
        
        Employee::replace_console_data_to_csv(obj);
    }



}

// -----------------------------------------------



// --------Takes object and display all containt in console---------
void show_all_employee(Employee *obj){
    for (int i=0;i<Employee::num_of_object;i++){
        obj[i].show_employee_detail();
    }
}
// ------------------------------------------------------









int main(){
    Employee e[100];
    ifstream in;
    in.open("employee_data.csv");
    if (!in.is_open()){
        cout<<"Error in opening employee_data.csv"<<endl;
        return 1;
    }

// ====================
    
    string name;
    string e_id;
    string department;
    string salary;
    string addres;
    string phone_no;
// ===================



// 
    
    while (!in.eof()){
        getline(in,name,',') ; // takes up to ','
        getline(in,e_id,',') ; // takes up to ','
        getline(in,department,',');  // takes up to ','
        getline(in,salary,',') ; // takes up to ','
        getline(in,addres,',') ; // takes up to ','
        getline(in, phone_no); // takes up to '\n'
        
        
        e[Employee::num_of_object].store_detail(name, e_id, department,salary, addres, phone_no);
        Employee::num_of_object++;
        
    }
    in.close();  //Colsing the file
    int choice;

    


    while(true){
        cout<<"1.Add New Employee"<<endl;
        cout<<"2.Edit Employee"<<endl;
        cout<<"3.Delete Employee"<<endl;
        cout<<"4.Show Employee detail"<<endl;
        cout<<"5.Show all Employee detail"<<endl;
        cout<<"6.Exit"<<endl;
        cout<<"Enter Your choice: ";
        cin>>choice;
        cin.ignore(); // Add this line to ignore the newline character
        
        if (choice == 1) {
            e[Employee::num_of_object].new_employee(e);
        } 
        else if (choice == 2) {
            edit_employee(e);
        } 
        else if (choice == 3) {
            string emp_id;
            cout<<"Enter Employee ID: ";
            cin>>emp_id;
            if (Employee::get_employee_sno(emp_id,e)!=-1){
                delete_obj(Employee::get_employee_sno(emp_id,e),e);
                cout<<emp_id<<" Has removed"<<endl;
            }
            else{
                cout<<emp_id<<" is not our Employee"<<endl;
            }
        } 

        else if (choice == 4) {
            string id; 
            int s_no;
            cout<<"Enter E_id of Employee: ";
            cin>>id;
            s_no=Employee::get_employee_sno(id,e);
            
            if (s_no==-1){
                cout<<"Wrong ID"<<endl;
                continue;
            }
            else{
                e[s_no].show_employee_detail();
            }
        } 
        else if (choice == 5) {
            show_all_employee(e);
        } 
        else if (choice == 6) {
            return 1;
        }


    cout<<endl<<endl;
    }

    return 0;
}

// ---------------Project Ends -------------------