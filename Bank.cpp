#include <string>
#include <iostream>
#include <random>
#include <queue>
#include <iomanip>

using namespace std;

//helper Functions
random_device rd;
mt19937 gen(rd());

//===================================================HELPER FUNCTIONS 
//helper function implementation
bool equality(int num1,int num2){
    if(num1==num2){
        return true;
    }
    else{
        return false;
    }
}
bool rootGreater(int root1,int root2){
    if(root1>root2){
        return true;
    }
    else{
        return false;
    }
}
int random(int low, int high)
{
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}
void addPaddingToArrays(int* arr,int arrSize,int num){
    string myNum=to_string(num);
        arrSize -=1;
        for(int i=myNum.length()-1;i>=0;i--){
            arr[arrSize]=int(myNum[i])-48;
            arrSize--;
        }
}
int intArrayToInt(int* arr,int size){
    string numStr;
    for(int i=0;i<size;i++){
        numStr+= to_string(arr[i]);
    }
    return stoi(numStr);
}





//Account Number
class AccountNum{
    static const int branchSize=3,
                    numberSize=4,
                    accNumSize=9;
    int branch[branchSize]={0},
        number[numberSize]={0},
        accountNumber[accNumSize]={0};
    
    int gender,
        type;

    string accountNumberStr;
    public:
    // default constructor
    AccountNum(){
        gender=type=0;
    }
    //ACCOUNT NUM IMPLEMENTATION
    void generateAccountNum(){
        for(int i=0;i<branchSize;i++){
            accountNumber[i]=branch[i];
            accountNumberStr+= to_string(branch[i]);
        }

        accountNumber[3]=gender;
        accountNumberStr+=to_string(gender);

        accountNumber[3]=type;
        accountNumberStr+=to_string(type);

        for(int i=0;i<numberSize;i++){
            accountNumber[i+numberSize+1]=number[i];
            accountNumberStr+=to_string(number[i]);
        }
    }

    //setters
    void setType(int num){
        type=num;
    }
    void setGender(int num){
        gender=num;
    }
    void setNumber(int num){
        addPaddingToArrays(number,numberSize,num);
    }
    void setBranch(int num){
        addPaddingToArrays(branch,branchSize,num);
    }

    //getters
    int getType(){
        return type;
    }
    int getGender(){
        return gender;
    }
    int getNumber(){
        return intArrayToInt(number,numberSize);
    }
    int getBranch(){
        return intArrayToInt(branch,branchSize);
    }
    int getBranchSize(){
        return branchSize;
    }
    int getNumberSize(){
        return numberSize;
    }
    int getAccountNumberSize(){
        return accNumSize;
    }
    string getAccountNumberStr(){
        return accountNumberStr;
    }

    //AccountNum class helper
    string getGenderStr(){
        if(gender>=0 && gender<=4){
                return "MALE";
        }
        else if(gender>4 && gender<10){
            return "FEMALE";
        }
        else{
            return "UNDEFINED";
        }
    }
    //create Account Input
    void createAccountNumberByInput(){
        int branch;
        int gender;
        int type;
        int accNum;
        
        cout<<"Enter branch number [0-9] :"<<endl;
        cin>>branch;
        setBranch(branch);

        
        cout<<"Enter (0-4) if male, else (5-9) for female: "<<endl;
        cin>>gender;
        //genderZ=5;
        setGender(gender);

        
        cout<<"Enter account typeZ:\n(0)Current\n(1)Saving\n(2)Salary\n(3)Education\n(4)IT\n(5)Government\n(6)Bonds\n(7)Foreign\n(8)Agriculture\n(9)Ehsas\n";
        cin>>type;
        //typeZ=2;
        setType(type);

        cout<<"Enter account number: "<<endl;
        cin>>accNum;
        setNumber(accNum);
        generateAccountNum();
        display();
    }
    //display

    void display(){
        cout<<"Account Number: "<<accountNumberStr<<endl;
    }

    //operator overlaoding =
    AccountNum operator=(AccountNum obj){
        type=obj.type;
            gender=obj.gender;
            int* objBranch=obj.branch;
            for(int i=0;i<branchSize;i++){
                branch[i]=obj.branch[i];
            }

            int* objNum=obj.number;
            for(int i=0;i<numberSize;i++){
                number[i]=objNum[i];
            }
            generateAccountNum();
            return *this;
    }

    
};

//aCCOUNT
class Account{
    AccountNum accountNumber;
    int balance;
    queue<string> transactions;

    class insufficientBalance{
        string msg;
        public:
        insufficientBalance(){
            msg="insufficient balance...";
        }
        void what(){
            cout<<msg<<endl;
        }
    };
    public:
    Account(){
        balance=0;
    }
    //Account Implementation
    
    //setters
    void setAccountNumber(int branch,int number,int gender,int type){
            accountNumber.setBranch(branch);
            accountNumber.setGender(gender);
            accountNumber.setType(type);
            accountNumber.setNumber(number);
            accountNumber.generateAccountNum();
    }
    void setBalance(int num,string msg=""){
        if(num>0){
            balance+=num;
            if(msg==""){
                msg="Deposited "+to_string(num)+" to account.";
            }
            transactionPush(msg);
            }
        else{
            cout<<"value must be greater than 0."<<endl;
        }
    }

    //getters
    int getBalance(){
        return balance;
    }
    AccountNum getAccountNumber(){
        return accountNumber;
    }

    //operations
    void transactionPush(string historyStr){
        if(transactions.size()<5){
                transactions.push(historyStr);
            }
        else{
            transactions.pop();
            transactions.push(historyStr);
        }
    }
    void deposit(int num,string msg){
        setBalance(num,msg);
    }
    void withdraw(int num){
        try{
            if(num>balance){
            throw insufficientBalance();
            }
            else{
                balance-=num;
                string msg= "Withdrew "+to_string(num)+" from account.";
                cout<<msg<<" You are left with "<<balance<<endl;
                transactionPush(msg);
            }
        }
        catch(insufficientBalance error){
            error.what();
        }
        
    }
    void fundTransfer(Account*& obj,int amount){
            try{
                withdraw(amount);
                string msg="Received "+ to_string(amount) + " from "+accountNumber.getAccountNumberStr();
                obj->deposit(amount,msg);
                transactionPush("You transfered "+to_string(amount)+" to account number: "+obj->accountNumber.getAccountNumberStr());
            }
            catch(insufficientBalance error){
                error.what();
            }
    }
    //createAccount
    void createAccount(){
        int balance;
        accountNumber.createAccountNumberByInput();
        cout<<"Enter balance to start your account with: ";
        cin>>balance;
        //balance=4500;
        setBalance(balance);
    }
    //display
    void display(){
        cout<<left<<setw(20)<<accountNumber.getAccountNumberStr()<<setw(15)<<balance;
        formattedHistory();cout<<endl;
    }
    void formattedHistory(){
        bool truez=false;
            for(queue<string> dump=transactions;!dump.empty();dump.pop()){
                if(!truez){
                    cout<<left<<setw(10)<<dump.front()<<"\n";
                    truez=true;
                }
                else{
                    cout<<left<<"\t\t\t\t   "<<dump.front()<<endl;
                }
            }
    }
    void transactionHistory(){
        for(queue<string> dump=transactions;!dump.empty();dump.pop()){
                cout<<dump.front()<<endl;
            }
    }

    //operator overloading
    Account operator = (Account* obj){
            //AccountNum* accNum= &(obj->accountNumber);
            accountNumber = obj->accountNumber;
            balance = obj->balance;
            transactions = obj->transactions;
        }

    
};

//bst node
struct node{
    Account data;
    node* left;
    node* right;
};

//create node
node* createNode(Account newAcc){
    node* newN= new node;
    newN->data=newAcc;
    newN->right=newN->left=nullptr;
    return newN;
}

//bst insertion
node* insert(node* root,Account newAcc){
    if(!root){
        root= createNode(newAcc);
    }
    else if(newAcc.getAccountNumber().getNumber()<root->data.getAccountNumber().getNumber()){
        root->left=insert(root->left,newAcc);
    }
    else{
        root->right=insert(root->right,newAcc);
    }
    return root;
}

//helper function
void generateKAccounts(node*& root,int num){
        bool first=false;
        int branch,gender,type,number;
        Account obj;
        
        int balance=0;
        for(int i=0;i<num;i++){
            Account obj;
            if(!first){
                number=4999;
                first=true;
            }else{
                number=random(1,9999);
            }
            branch=random(1,999);
            gender=random(0,9);
            type=random(0,9);
            balance=random(1,999999);
            obj.setAccountNumber(branch,number,gender,type);
            obj.setBalance(balance,"");
            root=insert(root,obj);

        }
    }


// BST FUNCTIONS
//bst implementation
//searching
node*& searchByNumber(node*& root,int accNum){
    static node* nullPtrz=nullptr;
    if(!root){
        return nullPtrz;
    }
    else if(equality(root->data.getAccountNumber().getNumber(),accNum)){
        return root;
    }
    else if((rootGreater(root->data.getAccountNumber().getNumber(),accNum))){
        //cout<<"going left now "<<root->data.getAccountNumber()getAccountNumberStr()<<endl;
        return searchByNumber(root->left,accNum);
    }
    else if(!(rootGreater(root->data.getAccountNumber().getNumber(),accNum))){ //data>root->data
        //cout<<"going right now "<<root->data.getAccountNumber().getAccountNumberStr()<<endl;
        return searchByNumber(root->right,accNum);
    }
}


//deletion
void deletion(node*& root,int number){
    node*& nodePtr=searchByNumber(root,number);
    if(nodePtr){
        node* tempNodePtr; // Temperary pointer
        if (nodePtr->right == NULL) { // case for leaf and one (left) child
            tempNodePtr = nodePtr;
            nodePtr = nodePtr->left; // Reattach the left child
            delete tempNodePtr;
        }
        else if (nodePtr->left == NULL) { // case for one (right) child
            tempNodePtr = nodePtr;
            nodePtr = nodePtr->right; // Reattach the right child
            delete tempNodePtr;
        }
        else {  // case for two children.
            tempNodePtr = nodePtr->right; // Move one node to the right
            while (tempNodePtr->left) { // Go to the extreme left node
                tempNodePtr = tempNodePtr->left;
            }
            tempNodePtr->left = nodePtr->left; // Reattach the left subtree
            tempNodePtr = nodePtr;
            nodePtr = nodePtr->right; // Reattach the right subtree
            delete tempNodePtr;
        }
    }
    else{
        cout<<"Account not found..."<<endl;
    }
}

//display
void displayByNumber(node* root,int number){
    if(!root){
        return;
    }
    else if(equality(root->data.getAccountNumber().getNumber(),number)){
        root->data.display();
    }
    else if((rootGreater(root->data.getAccountNumber().getNumber(),number))){
        //cout<<"going left now "<<root->data.getAccountNumber()getAccountNumberStr()<<endl;
        return displayByNumber(root->left,number);
    }
    else if(!(rootGreater(root->data.getAccountNumber().getNumber(),number))){ //data>root->data
        //cout<<"going right now "<<root->data.getAccountNumber().getAccountNumberStr()<<endl;
        return displayByNumber(root->right,number);
    }
}
void displayByBranch(node* root,int branch){
    if(!root){
        return;
    }
    if(equality(root->data.getAccountNumber().getBranch(),branch)){
        root->data.display();
    }
    displayByBranch(root->left,branch);
    displayByBranch(root->right,branch);
}
void displayByGender(node* root,string genderStr,int genderInt){
    if(!root){
        return;
    }
    if(root->data.getAccountNumber().getGenderStr()==genderStr){
        root->data.display();
    }
    displayByGender(root->left,genderStr,genderInt);
    displayByGender(root->right,genderStr,genderInt);
}
void displayByType(node* root,int type){
    if(!root){
        return;
    }
    if(root->data.getAccountNumber().getType()==type){
        root->data.display();
    }
    displayByType(root->left,type);
    displayByType(root->right,type);
}

//double display
void displayByBranchGender(node* root,int branch,string gender){
    if(!root){
        return;
    }
    if((root->data.getAccountNumber().getBranch()==branch) && (root->data.getAccountNumber().getGenderStr()==gender)){
        root->data.display();
    }
    displayByBranchGender(root->left,branch,gender);
    displayByBranchGender(root->right,branch,gender);

}
void displayByBranchType(node* root,int branch,int type){
    if(!root){
        return;
    }
    if((root->data.getAccountNumber().getBranch()==branch) && (root->data.getAccountNumber().getType()==type)){
        root->data.display();
    }
    displayByBranchType(root->left,branch,type);
    displayByBranchType(root->right,branch,type);

}

//levelOrder
void levelOrderDisplay(node* root){
    if(!root){
        cout<<"Nothing to show here....."<<endl;
        return;
    }
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* temp=q.front();
        temp->data.display();
        q.pop();
        
        if(temp->left){
            q.push(temp->left);
        }
        if(temp->right){
            q.push(temp->right);
        }
    }
}


//functions
node* addAccount(node* root){
    Account newAcc;
    newAcc.createAccount();
    root=insert(root,newAcc);
    return root;
}
void transferFunds(node*& root,int origAcc,int transferAcc){
    node*& transferBy = searchByNumber(root,origAcc);
    node*& toTransferTo=searchByNumber(root,transferAcc);
    if(toTransferTo && transferBy){
        int amount;
        cout<<"Enter amount you want to transfer: ";
        cin>>amount;
        Account* ptr= &(toTransferTo->data);
        //Account*& ptr2=ptr;
        transferBy->data.fundTransfer(ptr,amount);
    }
    else{
        cout<<"accNum not found.\n";
    }
}
void deposit(node*& root,int number,int amount){
    node*& account= searchByNumber(root,number);
    if(account){
        account->data.setBalance(amount,"");
    }
    else{
        cout<<"account not found"<<endl;
    }
}
void withdraw(node*& root,int number,int amount){
    node*& account=searchByNumber(root,number);
    if(account){
        account->data.withdraw(amount);
    }
    else{
        cout<<"account not found"<<endl;
    }
}
void transactionHistory(node* root,int number){
    node* account;
    account=searchByNumber(root,number);
    if(account){
        root->data.transactionHistory();
    }
    else{
        cout<<"account not found"<<endl;
    }
}


//Menu
class Menu{
    node* root;
    Account obj;
    public:
    Menu(){
        root=nullptr;
    }
    //Menu implementation
void Menuz(){
    int choice;
    char again;
    generateKAccounts(root,5);
    do{
            cout<<"(1)Add new Account\n(2)Delete Account\n(3)Transfer Funds\n(4)Deposit\n(5)Transaction History\n(6)Search\n(7)Display Level Order\n(8)Withdraw\n";
            cin>>choice;
            //root=addAccount(root);
            //choice=6;
            switch (choice)
            {
            case 1:{
                root=addAccount(root);
                break;
            }
            case 2:{
                int accNum;
                cout<<"Enter account number to delete: ";
                cin>>accNum;
                deletion(root,accNum);
                break;
            }
            case 3:{
                int origAcc,toTransfer;
                cout<<"Enter account number of account who wants to transfer: ";
                cin>>origAcc;
                //origAcc=9751;
                cout<<"Enter account number you want to transfer to: ";
                cin>>toTransfer;
                //toTransfer=4962;
                transferFunds(root,origAcc,toTransfer);
                break;
            }
            case 4:{
                int amount;
                int number;
                cout<<"Enter branch number to search by: "<<endl;
                cin>>number;
                //branch="009";
                cout<<"Enter amount to deposit: "<<endl;
                cin>>amount;
                //amount=90;
                deposit(root,number,amount);
                break;
            }
            case 5:{
                int accNum;
                cout<<"Enter accNum number to search by: "<<endl;
                cin>>accNum;
                //branch="005";
                transactionHistory(root,accNum);
                break;
            }
            case 6:{
                int search;
                cout<<"display by :\n(1)Gender\n(2)Type\n(3)Branch\n(4)AccountNum\n(5)Branch & Gender\n(6)Branch & Type\n";
                cin>>search;
                //search=4;
                switch (search)
                {
                    case 1:{
                        string gender;
                        cout<<"Enter MALE or FEMALE"<<endl;
                        cin>>gender;
                        int genderInt;
                        if(gender=="MALE"){
                            genderInt=0;
                        }
                        else if(gender=="FEMALE"){
                            genderInt=8;
                        }
                        cout<<left<<setw(20)<<"Account Number"<<setw(15)<<"Balance"<<setw(25)<<"Transaction History"<<endl;
                        displayByGender(root,gender,genderInt);
                        break;
                        }
                    case 2:{
                        int type;
                        cout<<"Enter type of account to view records of: "<<endl;
                        cout<<"Enter account typeZ:\n(0)Current\n(1)Saving\n(2)Salary\n(3)Education\n(4)IT\n(5)Government\n(6)Bonds\n(7)Foreign\n(8)Agriculture\n(9)Ehsas\n";
                        cin>>type;
                        cout<<left<<setw(20)<<"Account Number"<<setw(15)<<"Balance"<<setw(25)<<"Transaction History"<<endl;
                        displayByType(root,type);
                        break;
                    }
                    case 3:{
                        int branch;
                        cout<<"Enter branch you want to view by: "<<endl;
                        cin>>branch;
                        cout<<left<<setw(20)<<"Account Number"<<setw(15)<<"Balance"<<setw(25)<<"Transaction History"<<endl;
                        displayByBranch(root,branch);
                        break;
                    }
                    case 4:{
                        //int accNum[4];
                        int accNum;
                        cout<<"Enter account number to search by: "<<endl;
                        cin>>accNum;
                        //accNum=9751;
                       cout<<left<<setw(20)<<"Account Number"<<setw(15)<<"Balance"<<setw(25)<<"Transaction History"<<endl;
                        displayByNumber(root,accNum);
                        break;
                    }
                    case 5:{
                        int branch;
                        cout<<"Enter branch you want to view by: "<<endl;
                        cin>>branch;
                        string gender;
                        cout<<"Enter gender you want to search by MALE or FEMALE: "<<endl;
                        cin>>gender;
                        cout<<left<<setw(20)<<"Account Number"<<setw(15)<<"Balance"<<setw(25)<<"Transaction History"<<endl;
                        displayByBranchGender(root,branch,gender);
                        break;
                    }
                    case 6:{
                        int branch;
                        cout<<"Enter branch you want to view by: "<<endl;
                        cin>>branch;
                        int type;
                        cout<<"Enter type of account to view records of: "<<endl;
                        cout<<"Enter account typeZ:\n(0)Current\n(1)Saving\n(2)Salary\n(3)Education\n(4)IT\n(5)Government\n(6)Bonds\n(7)Foreign\n(8)Agriculture\n(9)Ehsas\n";
                        cin>>type;
                        cout<<left<<setw(20)<<"Account Number"<<setw(15)<<"Balance"<<setw(25)<<"Transaction History"<<endl;
                        displayByBranchType(root,branch,type);
                        break;
                    }
                }
                break;
            }
                case 7:{
                    cout<<left<<setw(20)<<"Account Number"<<setw(15)<<"Balance"<<setw(25)<<"Transaction History"<<endl;
                    levelOrderDisplay(root);
                    break;
                }
                case 8:{
                    int accNum;
                    cout<<"Enter accNum to withdraw from: "<<endl;
                    cin>>accNum;
                    int amount;
                    cout<<"Enter amount you wish to withdraw: "<<endl;
                    cin>>amount;
                    withdraw(root,accNum,amount);
                    break;
                }
                default:
                    cout<<"Invalid option"<<endl;
                    break;
            }
            cout<<"AGAIN? (y/n): "<<endl;
            cin>>again;
        }while(again!='n');
}

};




 





int main(){
    Menu obj;
    obj.Menuz();
}