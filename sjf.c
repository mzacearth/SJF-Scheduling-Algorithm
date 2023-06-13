#include<stdio.h>
#include<stdlib.h>
struct process{
	int pid,at,bt,ct,tat,wt;
};
void swap( int i, int j, struct process p[20]){
	struct process temp=p[i];
	p[i]=p[j];
	p[j]=temp;
}
void atSort( struct process p[20],int n){
	int i,j;
	for (i=0;i<n;i++){
		for (j=i+1;j<n;j++){
			if(p[i].at>p[j].at)
				swap(i,j,p);
		}
	}
}
void pidSort(struct process p[20],int n){
	for (int i=0;i<n;i++){
		for (int j=i+1;j<n;j++){
			if((p[i].at==p[j].at) && (p[i].pid > p[j].pid)){
				swap(i,j,p);
			}
		}
	}
}
void btSort( struct process p[20],int i, int n,int ict){
	for (int a=i+1;a<n;a++){
		for (int b=a;b<n;b++){
			if((p[a].at <= ict)&&( p[b].at <= ict)){
				if (p[a].bt > p[b].bt)
					swap(a,b,p);
			}
		}
	}
}
void sjf(struct process p[20],int n){
	atSort(p,n);
	pidSort(p,n);
	int ict =p[0].at;
	for (int i=0;i<n;i++){
		if (ict < p[i].at)
			p[i].ct=p[i].at+p[i].bt;
		else 
			p[i].ct=ict+p[i].bt;
		ict=p[i].ct;
		p[i].tat=p[i].ct-p[i].at;
		p[i].wt=p[i].tat-p[i].bt;
		btSort(p,i,n,ict);
	}
}
void main(){
	struct process p[20];
	int n;
	float avwt,avtat;
	float twt=0;
	float ttat=0;
	printf("Enter the number of processes :");
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		printf("Process ID of %d :",i+1);
		scanf("%d",&p[i].pid);
		printf("Arrival Time :");
		scanf("%d",&p[i].at);
		printf("Burst Time :");
		scanf("%d",&p[i].bt);
	}
	sjf(p,n);
	printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
	for (int i=0;i<n;i++){
		twt+=p[i].wt;
		ttat+=p[i].tat;
		printf("\n%d\t%d\t%d\t%d\t%d\t%d\t",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
	}
	avwt=twt/(float)n;
	avtat=ttat/(float)n;
	printf("\nAverage waiting time :%f\n",avwt);
	printf("Average turn around time :%f\n",avtat);
}

