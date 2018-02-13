#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <fstream>
#include <ctime>
#define DATANUM 150 
using namespace std;

class iris{
	public:	
	double data[4];
	int typenum;		//1 or 2 or 3
	
	iris(){
		data[0]=data[1]=data[2]=data[3]=0;
		typenum=0;
	}
};


class Node{
	public: 
	int attribute;			//using which data
	Node *right,*left;		//left for <= and right for > 
	double threshold;		//where the point cut the data
	int ans;
	
	Node(){
		right = left= NULL;
		threshold=-1;		//if threshold=-1 means the tree ends at here
		ans=-1;				//-1 means not each the end		,otherwise the number is the type
		attribute=-1;
	}
};

int min_remain(double a,double b,double c,double d){		//return value is 0~3
	if(a<=b && a<=c && a<=d)	return 0;
	if (b<=a && b<=c && b<=d)	return 1;
	if (c<=a && c<=b && c<=d)	return 2;
	else 						return 3;
}

double entropy(iris set[],int count){
	double a=0,b=0,c=0,sum=0;
	double ans=0;
	
	for(int i=0;i<count;i++){
		if(set[i].typenum==1)	a+=1;
		else if (set[i].typenum==2)	b+=1;
		else if(set[i].typenum==3)c+=1;
	}
	sum=a+b+c;
	//cout<<sum<<endl<<a<<endl<<b<<endl<<c;
	
	if(a!=0){
		ans-=(double)(a/sum)*(double)log2(a/sum);
	}
	if(b!=0){
		ans-=(double)(b/sum)*(double)(log2(b/sum));
	}
	if(c!=0){
		ans-=(double)(c/sum)*(double)(log2(c/sum));
	}
	
	return ans;
}

bool cmp1(iris const &a,iris const &b){return a.data[0]<b.data[0];}		//used for sorting
bool cmp2(iris const &a,iris const &b){return a.data[1]<b.data[1];}
bool cmp3(iris const &a,iris const &b){return a.data[2]<b.data[2];}
bool cmp4(iris const &a,iris const &b){return a.data[3]<b.data[3];}

double rm1(iris arr[],int counter,double &pi){			//ig_ num is the type number which you want its infomation gain to be caluclated
	std::sort(arr,arr+counter,cmp1);		//counter is how many sets of data
	int prev=-1;
	double pivot;
	double en_a=0,en_b=0;		//entyopy for the temp array
	double smallest_rm=999999,smallest_pivot=0;		//smallest rm and pivot
	
	for(int i=0;i<counter;i++){									//entropy calculating can be speed up here
			if(arr[prev].typenum!=arr[i].typenum && prev!=-1){
				int small=0,large=0;
				double temp_sum=0;
				iris *left=new iris [counter], *right=new iris [counter];
				pivot=(arr[prev].data[0]+arr[i].data[0])/2;		//where the data being cut
				
				for(int j=0;j<counter;j++){		//spliting data into twp array
					if(arr[j].data[0]<=pivot)	{left[small]=arr[j];	small++;}
					else						{right[large]=arr[j];	large++;}
				}
				
				
				if(small!=0)	en_a=entropy(left,small);
				if(large!=0)	en_b=entropy(right,large);
			
				
				delete [ ]left;		delete [] right;
				
				
				if(smallest_rm>(double)(en_a*small/counter)+(double)(en_b*large/counter))	{
					smallest_rm=(double)(en_a*small/counter)+(double)(en_b*large/counter);	smallest_pivot=(arr[prev].data[0]+arr[i].data[0])/2;
					pi=smallest_pivot;
				}
		}
		prev++;
	}
	//cout<<"\nrm1 done\n\n";
	return smallest_rm;
}


double rm2(iris arr[],int counter,double &pi){			//ig_ num is the type number which you want its infomation gain to be caluclated
	std::sort(arr,arr+counter,cmp2);		//counter is how many sets of data
	int prev=-1;
	double pivot;
	double en_a=0,en_b=0;		//entyopy for the temp array
	double smallest_rm=999999,smallest_pivot=0;		//smallest rm and pivot
	
	for(int i=0;i<counter;i++){									//entropy calculating can be speed up here
			if(arr[prev].typenum!=arr[i].typenum && prev!=-1){
				int small=0,large=0;
				iris *left=new iris [counter], *right=new iris [counter];
				pivot=(arr[prev].data[1]+arr[i].data[1])/2;		//where the data being cut
				
				for(int j=0;j<counter;j++){		//spliting data into twp array
					if(arr[j].data[1]<=pivot)	{left[small]=arr[j];	small++;}
					else						{right[large]=arr[j];	large++;}
				}
				
				if(small!=0)	en_a=entropy(left,small);
				if(large!=0)	en_b=entropy(right,large);
				
				en_a=entropy(left,small);	en_b=entropy(right,large);
			
				
				delete [ ]left;		delete [] right;
				
				if(smallest_rm>(double)(en_a*small/counter)+(double)(en_b*large/counter))	{
					smallest_rm=(double)(en_a*small/counter)+(double)(en_b*large/counter);	smallest_pivot=(arr[prev].data[1]+arr[i].data[1])/2;
					pi=smallest_pivot;
				}
		}
		prev++;
	}
	//cout<<"\nrm2 done\n\n";
	return smallest_rm;
}


double rm3(iris arr[],int counter,double &pi){			//ig_ num is the type number which you want its infomation gain to be caluclated
	std::sort(arr,arr+counter,cmp3);		//counter is how many sets of data
	int prev=-1;
	double pivot;
	double en_a=0,en_b=0;		//entyopy for the temp array
	double smallest_rm=999999,smallest_pivot=0;		//smallest rm and pivot
	
	for(int i=0;i<counter;i++){									//entropy calculating can be speed up here
			if(arr[prev].typenum!=arr[i].typenum && prev!=-1){
				int small=0,large=0;
				iris *left=new iris [counter], *right=new iris [counter];
				pivot=(arr[prev].data[2]+arr[i].data[2])/2;		//where the data being cut
				
				for(int j=0;j<counter;j++){		//spliting data into twp array
					if(arr[j].data[2]<=pivot)	{left[small]=arr[j];	small++;}
					else						{right[large]=arr[j];	large++;}
				}
			
				if(small!=0)	en_a=entropy(left,small);
				if(large!=0)	en_b=entropy(right,large);
				
				en_a=entropy(left,small);	en_b=entropy(right,large);
			
				
				delete [ ]left;		delete [] right;
				
				if(smallest_rm>(double)(en_a*small/counter)+(double)(en_b*large/counter))	{
					smallest_rm=(double)(en_a*small/counter)+(double)(en_b*large/counter);	smallest_pivot=(arr[prev].data[2]+arr[i].data[2])/2;
					pi=smallest_pivot;
				}
		}
		prev++;
	}
	//cout<<"\nrm3 done\n\n";
	return smallest_rm;
}


double rm4(iris arr[],int counter,double &pi){			//ig_ num is the type number which you want its infomation gain to be caluclated
	std::sort(arr,arr+counter,cmp4);		//counter is how many sets of data
	int prev=-1;
	double pivot;
	double en_a=0,en_b=0;		//entyopy for the temp array
	double smallest_rm=999999,smallest_pivot=0;		//smallest rm and pivot
	
	for(int i=0;i<counter;i++){									//entropy calculating can be speed up here
			if(arr[prev].typenum!=arr[i].typenum && prev!=-1){
				int small=0,large=0;
				iris *left=new iris [counter], *right=new iris [counter];
				pivot=(arr[prev].data[3]+arr[i].data[3])/2;		//where the data being cut
				
				for(int j=0;j<counter;j++){		//spliting data into twp array
					if(arr[j].data[3]<=pivot)	{left[small]=arr[j];	small++;}
					else						{right[large]=arr[j];	large++;}
				}
			
				if(small!=0)	en_a=entropy(left,small);
				if(large!=0)	en_b=entropy(right,large);
				
				en_a=entropy(left,small);	en_b=entropy(right,large);
			
				
				delete [ ]left;		delete [] right;
				
				if(smallest_rm>(double)(en_a*(small/counter))+(double)(en_b*(large/counter)))	{
					smallest_rm=(double)(en_a*small/counter)+(double)(en_b*large/counter);	smallest_pivot=(arr[prev].data[3]+arr[i].data[3])/2;
					pi=smallest_pivot;
				}
		}
		prev++;
	}
	//cout<<"\nrm4 done\n\n";
	return smallest_rm;
}




void build_tree(iris arr[],Node *now,int counter){		//times 2when using attri1,3when attri2,5 when attri3,7when attri9 		
	if(counter==0){
		now=new Node();
		//cout<<"subarray if full";
		//system("PAUSE");
		return;
	} 
	
	//cout<<"Total array is : \n\n";
	/*for(int k=0;k<counter;k++){
			cout<<arr[k].data[0]<<"\t"<<arr[k].data[1]<<"\t"<<arr[k].data[2]<<"\t"<<arr[k].data[3]<<"\t"<<arr[k].typenum<<"\n";
	}*/
	//cout<<endl<<endl;
	
	double total_entropy=entropy(arr,counter);				//counter=datanums;
	double r[4];												
	double p1=0,p2=0,p3=0,p4=0;
	double &rp0=p1,&rp1=p2, &rp2=p3, &rp3=p4;		//storing the pivot value
	int attribute;					//selected attribute to build the tree in this layer
	int sum=0,a=0,b=0,c=0;								
	//now=new Node();
	
	
	for(int k=0;k<counter;k++){				//
		if(arr[k].typenum==1)	a++;
		else if(arr[k].typenum==2)	b++;
		else if(arr[k].typenum==3)c++;
	}
	sum=a+b+c;
	
	if(total_entropy==0){		//the end of the tree
		
		now->ans = arr[0].typenum;
		//cout<<"the tree ends with answer"<<now->ans<<endl<<endl;
		//system("PAUSE");
		return;
	}
	
	
	
	r[0]=rm1(arr,counter,rp0);
	r[1]=rm2(arr,counter,rp1);
	r[2]=rm3(arr,counter,rp2);
	r[3]=rm4(arr,counter,rp3);
	
	/*cout<<"rm\tpivot\tsum number: "<<sum<<endl;
	cout<<r[0]<<"\t"<<rp0<<endl<<endl;
	cout<<r[1]<<"\t"<<rp1<<endl<<endl;
	cout<<r[2]<<"\t"<<rp2<<endl<<endl;
	cout<<r[3]<<"\t"<<rp3<<endl<<endl;*/
	


	attribute=min_remain(r[0],r[1],r[2],r[3]);			//0~3 means one of the attribute
	
	//cout<<"the min rm:  "<<r[attribute];
	
	//if(attribute==0)	cout<<"\twith pivot "<<rp0<<endl<<endl;
	//else if(attribute==1)	cout<<"\twith pivot "<<rp1<<endl<<endl;
	//else if(attribute==2)	cout<<"\twith pivot "<<rp2<<endl<<endl;
	//else if(attribute==3)	cout<<"\twith pivot "<<rp3<<endl<<endl;
	//	system("PAUSE");		//check the rimainder here
	
	
	//else{					//not the end of the tree
		int small_temp=0,large_temp=0;			//number of element in left array
		iris *leftarr,*rightarr;
		
		now->attribute=attribute;
		leftarr=new iris [counter];
		rightarr=new iris [counter];
		
		switch(attribute){
			case 0:
				now->threshold=rp0;
				break;
			case 1:
				now->threshold=rp1;
				break;
			case 2:
				now->threshold=rp2;
				break;
			case 3:
				now->threshold=rp3;
				break;
		}
		
		for (int j=0;j<counter;j++){
			if(arr[j].data[attribute] <= now->threshold){
				leftarr[small_temp]=arr[j];
				small_temp++;
			}
			else{
				rightarr[large_temp]=arr[j];
				large_temp++;
			}
		}
		
		if(large_temp==counter){		//one side is the full array while other side is zero,then this is the end
			//system("PAUSE");
			
			
			if(a>=b&&a>=c)	now->ans=1;
			else if(b>=a && b>=c) now->ans=2;
			else if(c>=a && c>=b)	now->ans=3;
		
			//now->ans = arr[0].typenum;
			/*cout<<"the tree ends with answer"<<now->ans<<endl<<endl;
			cout<<"\n\n\nwith no precise cut\n\n\n";*/
			return;
		}
		
		if(small_temp==counter){
		//system("PAUSE");

		if(a>=b&&a>=c)	now->ans=1;
		else if(b>=a && b>=c) now->ans=2;
		else if(c>=a && c>=b)	now->ans=3;
		
		//now->ans = arr[0].typenum;
		/*cout<<"the tree ends with answer"<<now->ans<<endl<<endl;
		cout<<"\n\n\nwith no precise cut\n\n\n";*/

		return;
		}
		
		//cout<<"\n\nattribute and threshlod\t"<<attribute<<"\t"<< now->threshold <<endl<<endl;
		
		
		/*cout<<"left array is : \n\n";
		
		for(int k=0;k<small_temp;k++){
			cout<<leftarr[k].data[0]<<"\t"<<leftarr[k].data[1]<<"\t"<<leftarr[k].data[2]<<"\t"<<leftarr[k].data[3]<<"\t"<<leftarr[k].typenum<<"\n";
		}*/
		
		
		//cout<<"enter the left tree with attribute "<<now->attribute<<" and threshold "<<now->threshold<<endl<<endl;
		//system("PAUSE");
		
		now->left=new Node();
		build_tree(leftarr,now->left,small_temp);
		
		/*cout<<"\n\n\n right array is\n\n";
		for(int k=0;k<large_temp;k++){
			cout<<rightarr[k].data[0]<<"\t"<<rightarr[k].data[1]<<"\t"<<rightarr[k].data[2]<<"\t"<<rightarr[k].data[3]<<"\t"<<rightarr[k].typenum<<"\n";
		}*/
		
		//cout<<"enter the right tree with attribute "<<now->attribute<<" and threshold "<<now->threshold<<endl<<endl;
		//system("PAUSE");
		now->right=new Node();
		build_tree(rightarr,now->right,large_temp);
	
		//cout<<"return"<<endl<<endl;	
		
	delete [] leftarr;		delete []rightarr;
		
		return;
	//}
}



int visit(iris test,Node *now){
	/*cout<<"enter visit tree\n";
	cout<< now->ans <<"\t"<<now->attribute<<"\t"<<now->threshold<<"\t\n";*/
	
	if(now->ans!=-1)	return now->ans;
	
	if(now->ans==-1 && now->attribute==-1 && now->threshold == -1){
		//cout<<"no precise predict\n\n\n";
		return (rand()%3+1);			//randomly return a attribute
	}
	
	if(test.data[now->attribute]<= now->threshold){
		return visit(test,now->left);
	}
	else if(test.data[now->attribute]>now->threshold){
		return visit(test,now->right);
	}
	
}

void delete_tree(Node* node) 
{
    if (node == NULL) return;
 
    /* first delete both subtrees */
    delete_tree(node->left);
    delete_tree(node->right);
   
    /* then delete the node */
    //printf("\n Deleting node: %d", node->data);
	delete node;
} 

/*
int main(int argc, char** argv) {	
	iris *arr;
	arr=new iris[DATANUM];
	srand(time(NULL));
	iris temp;
	string type;
	int i=0;
	char useless;
	fstream fin,fout;
	Node *root= new Node();
	
	fin.open("data.txt",ios::in);
	
	while(i<DATANUM){
		fin>>temp.data[0]>>useless>>temp.data[1]>>useless>>temp.data[2]>>useless>>temp.data[3]>>useless>>type;
		if(type=="Iris-setosa")	temp.typenum=1;
		else if (type=="Iris-versicolor")	temp.typenum=2;
		else temp.typenum=3;
		
		arr[i]=temp;
		i++; 
	}
	
	random_shuffle(&arr[0], &arr[DATANUM]);
	
	
	
	build_tree(arr,root,120);
	
	
	int a=0,b=0,c=0,sum=0;
	int sela=0,selb=0,selc=0;
	int truea=0,trueb=0,truec=0;
	
	for(int k=120;k<150;k++){
		int temp=visit(arr[k],root);		//visit result
		
		if(temp==1)	sela+=1;			//how many select 
		else if(temp==2) 	selb+=1;
		else if(temp==3)	selc+=1;
		
		if(arr[k].typenum==1)	truea+=1;		//original type counter
		else if(arr[k].typenum==2)	trueb+=1;
		else if(arr[k].typenum==3)	truec+=1;
		
		if(temp==arr[k].typenum && temp==1)	a+=1;		//correct guess
		else if(temp==arr[k].typenum && temp==2)	b+=1;
		else if(temp==arr[k].typenum && temp==3)	c+=1;
		
		//sum=truea+trueb+truec;
	}
	
	cout<<endl<<endl;
	cout<<a<<"\t"<<sela<<endl<<endl;
	cout<<b<<"\t"<<selb<<endl<<endl;
	cout<<c<<"\t"<<selc<<endl<<endl;
	
	cout<<"precision of typenum==1 is "<<double(a)/double(sela)<<endl<<endl<<endl;
	cout<<"precision of typenum==2 is "<<double(b)/double(selb)<<endl<<endl<<endl;
	cout<<"precision of typenum==3 is "<<double(c)/double(selc)<<endl<<endl<<endl;
	//cout<<"precision of total is "<<double(a+b+c)/double(sela+selb+selc);
	cout<<"recall of typenum==1 is "<<double(a)/double(truea)<<endl<<endl;
	cout<<"recall of typenum==2 is "<<double(b)/double(trueb)<<endl<<endl;
	cout<<"recall of typenum==3 is "<<double(c)/double(truec)<<endl<<endl;
	
	delete [ ]arr;
		
	return 0;
}

*/

int main (void){
	srand(time(NULL));
	iris *arr1,*arr2,*arr3;
	int i=0,j=0,k=0,x=0,y=0;
	int sela=0,selb=0,selc=0;
	int a=0,b=0,c=0;
	int truea=0,trueb=0,truec=0;
	char useless;
	fstream fin;
	string type;
	iris temp;
	fin.open("data.txt",ios::in);
	
	arr1= new iris[120];		//storing the training data
	arr2= new iris[30];			//testing data
	arr3= new iris[150];		//total data,do not change it
	
	while(i<150){
		fin>>temp.data[0]>>useless>>temp.data[1]>>useless>>temp.data[2]>>useless>>temp.data[3]>>useless>>type;
		
		if(type=="Iris-setosa")	temp.typenum=1;
		else if (type=="Iris-versicolor")	temp.typenum=2;
		else temp.typenum=3;
		
		
		arr3[i]=temp;
		i++; 
	}
	
	random_shuffle(&arr3[0], &arr3[150]);
	
	
	

	for(i=0,j=0;i<5;i++,j++){		//if data is between j*30 and (j+1)*30-1,don't put into the array,running 5times
		Node *root=new Node();
		for(k=0 , x=0 ,y=0; k<150 ; k++ ){
		if(k>=(j*30) && k<=((j+1)*30)-1){
			arr2[x]=arr3[k];				//testing data
			x++;
		}
		else{								//training data
			arr1[y]=arr3[k];
			y++;
		}
	}
		
		build_tree(arr1,root,120);
		
		for(int u=0;u<30;u++){
		int temp=visit(arr2[u],root);		//visit result
		
		if(temp==1)	sela+=1;			//how many select 
		else if(temp==2) 	selb+=1;
		else if(temp==3)	selc+=1;
		
		if(arr2[u].typenum==1)	truea+=1;		//original type counter
		else if(arr2[u].typenum==2)	trueb+=1;
		else if(arr2[u].typenum==3)	truec+=1;
		
		if(temp==arr2[u].typenum && temp==1)	a+=1;		//correct guess
		else if(temp==arr2[u].typenum && temp==2)	b+=1;
		else if(temp==arr2[u].typenum && temp==3)	c+=1;
		
		//sum=truea+trueb+truec;
	}
	delete []arr1;	delete []arr2;
	delete_tree(root);
	
	arr1=new iris [120];
	arr2=new iris [30];
	
	
	
/*	cout<<endl<<endl;
	cout<<truea<<"\t"<<sela<<"\t"<<a<<endl;
	cout<<trueb<<"\t"<<selb<<"\t"<<b<<endl;
	cout<<truec<<"\t"<<selc<<"\t"<<c<<endl;*/ 
	
}
	cout<<double(a+b+c)/double(sela+selb+selc)<<endl;	//total pre

	cout<<double(a)/double(sela)<<"\t";		//pre1
	cout<<double(a)/double(truea)<<endl;	//recall1
	cout<<double(b)/double(selb)<<"\t";		//pre2
	cout<<double(b)/double(trueb)<<endl;	//recall2
	cout<<double(c)/double(selc)<<"\t";		//pre3
	cout<<double(c)/double(truec)<<endl;	//recall3
	
	
	
	
	
}


