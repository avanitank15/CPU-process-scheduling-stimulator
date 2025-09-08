#include<bits/stdc++.h>

using namespace std;

class X{
	public:
	    int process;
	    int beg_time=0;
	    int end_time=0;
	    
	    void display(){
	    	cout<<process<<"\t"<<"beginning time:"<<beg_time<<"  finish time:"<<end_time<<endl;
		}
	
};
int findFirst(int pn, vector <int> v,int data){
	for(int i=0;i<v.size();i++){
		if(v[i]==data){
			return i;
		}
	}
}
int findLast(int pn, vector <int> v,int data){
	
	for(int i=v.size()-1;i>=0;i--){
		if(v[i]==data){
			return i;
		}
	}
}
void table_displayStrf(int pn, vector <int> v,vector<int> matrix[]){
	cout<<"RT \t TAT \t WT"<<endl;
	cout<<"------------------------"<<endl;
	int rt,tat,wt;
	for(int i=1;i<=pn;i++){
		
		
		rt=(findFirst(pn,v,i))- matrix[i][1];
	    tat=(findLast(pn,v,i))- matrix[i][1]+1;
		wt=tat-matrix[i][2];
		cout<<rt<<"\t"<<tat<<"\t"<<wt<<endl;	
		


	}
	
}



void table_displaySjf(int pn, list<X> ls,vector<int> matrix[]){
	cout<<"RT \t TAT \t WT"<<endl;
	cout<<"------------------------"<<endl;
	int rt,tat,wt;
	for(int i=1;i<=pn;i++){

        list<X> ::iterator it=ls.begin();
        while(it!=ls.end()){
        	if((it->process)==i){
        	    rt=(it->beg_time)- matrix[i][1];
	         	tat=(it->end_time)- matrix[i][1];
		        wt=tat-matrix[i][2];
		        cout<<rt<<"\t"<<tat<<"\t"<<wt<<endl;	
		        break;
			}
			++it;
		}

	}
	
}
void table_displayFcfs(int pn, list<X> ls,vector<int> matrix[]){
	cout<<"RT \t TAT \t WT"<<endl;
	cout<<"------------------------"<<endl;
	int rt,tat,wt;
	list<X> ::iterator it=ls.begin();
	for(int i=1;i<=pn&& it!=ls.end();i++){
		rt=(it->beg_time)- matrix[i][1];
		tat=(it->end_time)- matrix[i][1];
		wt=tat-matrix[i][2];
		cout<<rt<<"\t"<<tat<<"\t"<<wt<<endl;
		++it;
	}
	
}

void sort(int pn, vector<int> m2[]) {
    for (int i = 1; i < pn; i++) {
        int min = i;
        for (int j = i + 1; j <= pn; j++) {
            if (m2[j][3] > 0 && (m2[min][3] == 0 || m2[min][3] > m2[j][3])) {
                min = j;
            }
        }
        vector<int> temp = m2[i];
        m2[i] = m2[min];
        m2[min] = temp;
    }
}

vector<int> srtf(int pn,vector<int> matrix[]){
	vector<int> v; //cpu run will be maximum of 1000 units
	vector<int> m2[pn+1];
	
	
	for(int i=1;i<=pn;i++){
		for(int j=0;j<=2;j++){
			m2[i].push_back(matrix[i][j]);
		}
		m2[i].push_back(m2[i][2]);
		
	}

	int time=0;
    int count=0;
    while(count<pn){
    	sort(pn,m2);
    	for(int i=1;i<=pn;i++){
    		if(time>=m2[i][1]){
    			v.push_back(m2[i][0]);
    			m2[i].at(3)=m2[i].at(3)-1;
    			if(m2[i].at(3)==0){
			        count++;
	         	}
	         	break;
			}
			else if(i==pn){
				v.push_back(0);
			}
			
		}
		time++;
	}

	return v;
}

list<X> sjf(int pn,vector<int> matrix[]){
	list<X> ls;
	int task[pn];
	for(int i=1;i<=pn;i++){
		task[i]=0;
	}
	vector<int> m2[pn+1];
	for(int i=1;i<=pn;i++){
		for(int j=0;j<=2;j++){
			m2[i].push_back(matrix[i][j]);
		}
		
	}
	
//sorting according to process time
    for(int i=1;i<pn;i++){
    	int min=i;
		for(int j=i+1;j<=pn;j++){
			if(m2[min].at(2)>m2[j].at(2)){
				min=j;
			}
		}
		{
			m2[0]=m2[min];
			m2[min]=m2[i];
			m2[i]=m2[0];
		}
	}
	int time=0;
	int count=0;
	while(count<pn){
	
		for(int i=1;i<=pn;i++){
			if(task[i]!=1 &&time>=m2[i].at(1)){
			count++;
			X p;
			p.process=m2[i].at(0);
			p.beg_time=time;
			p.end_time=p.beg_time+m2[i].at(2);
			time=p.end_time;
			task[i]=1;
			ls.push_back(p);
		    break;
	    	}
	    }
	    if(count<pn){
	    	int min=10000;
	    	for( int k=1;k<=pn;k++){
	    	    if(task[k]!=1 && min>m2[k].at(1)){
	    				min=m2[k].at(1);
				}
				
		    }
			time=(time>min)?time:min;
	    
    	}
    }
    //table_displaySjf(pn, ls, matrix);
	return ls;
}
	
		
list<X> fcfs(int pn,vector<int> matrix[]){
	list<X> ls;
	int time=0;
	for(int i=1;i<=pn;i++){
		X p;
		p.process=i;
		p.beg_time=(matrix[i][1]>time)?matrix[i][1]:time;
		p.end_time=p.beg_time+matrix[i][2];
		time=p.end_time;
		ls.push_back(p);
	}
	table_displayFcfs(pn,ls,matrix);
	return ls;
}
int main(){
	int pn;
	int ch;
	cout<<"enter the number of processes:";
	cin>>pn;
	
	vector<int> matrix[pn+1];
	
	for(int i=1;i<=pn;i++){
		matrix[i].push_back(i);
		int t;
	    cout<<"enter the arrival and processing time (in the sequence of arrival of jobs)";
		for(int j=1;j<=2;j++){
			cin>>t;
		    matrix[i].push_back(t);
		}
		
	}
	

    




	list<X> ls;
	list<X> ll;
	vector <int> v;
	do{ cout<<"1. FCFS \t 2. SJF \t 3. STRF \t 4. Exit \n ";
		cout<<"enter choice";
		cin>>ch;
		switch(ch){
			case 1://list<X> ls;
	               ls=fcfs(pn,matrix);
	               for (auto it = ls.begin(); it != ls.end(); ++it) {
                        it->display();
                    }
                    cout<<"\n \n";

			       break;
			case 2: //list<X> ll;
	               ll=sjf(pn,matrix);
	                for (auto it = ll.begin(); it != ll.end(); ++it) {
                       it->display();
                    }
                    table_displaySjf(pn, ll, matrix);
                    cout<<"\n \n";
                    break;
            case 3:    v=srtf(pn,matrix);
            
//	                   for (int it = 0; it < v.size(); it++) {
//                            cout<<v.at(it)<<" ";
//                        }
                        cout<<endl;
                        table_displayStrf(pn, v,matrix);
                        cout<<"\n \n";
                        break;
            case 4:exit(0);
			
			default:cout<<"invalid";
			
		}
	}while(1);
	return 0;
}
