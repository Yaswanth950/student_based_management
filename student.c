#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct student
{
	int rollno;
	char name[20];
	float marks;
	struct student *next;
}sll;
void stud_add(sll **);
void stud_show(sll *);
void stud_save(sll **);
void stud_del(sll **);
void stud_mod(sll *);
static int c=1;
void main()
{
	sll *headptr=0;
	char op;
	while(1)
	{
		printf("  ----------------------------\n");
		printf(" |***** STUDENT DATABASE*****|\n");
		printf("  ----------------------------\n");
		printf(" |\ta)ADD STUDENT DATA   |\n | \ts)SHOW THE LIST      |\n | \tv)SAVE               |\n | \td)DELETE A RECORD    |\n | \tm)MODIFY             |\n | \te)EXIT               |\n");
		printf("  ----------------------------\n");
		printf("enter your choice\n");
		scanf(" %c",&op);
		switch(op)
		{
			case 'a':stud_add(&headptr);break;
			case 's':stud_show(headptr);break;
			case 'v':stud_save(&headptr);break;
			case 'd':stud_del(&headptr);break;
			case 'm':stud_mod(headptr);break;
			case 'e':exit(0);
		}
	}
}
void stud_add(sll **ptr)
{
	int c=1,f;
	sll *new,*last,*t;
	new=malloc(sizeof(sll));
	while(1)
	{
		f=0;
		t=*ptr;
		while(t!=0)
		{
			if(t->rollno==c)
			{
				f=1;
				break;
			}
			t=t->next;
		}
		if(f)
			c++;
		else
			break;
	}
	new->rollno=c;
	printf("enter the name and marks\n");
	scanf("%s %f",new->name,&new->marks);
	new->next=0;
	if(*ptr==0)
		*ptr=new;
	else
	{
		last=*ptr;
		while(last->next)
			last=last->next;
		last->next=new;
	}
}
void stud_show(sll *ptr)
{
	printf("*************************\n");
	if(ptr==0)
	{
		printf("no records present\n");
		printf("*************************\n");
		return;
	}
	while(ptr)
	{
		printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
		ptr=ptr->next;
	}
	printf("*************************\n");
}
void stud_save(sll **ptr)
{ 
	char op1;
	printf("v)save t)sort l)delete all r)reverse\n");
	scanf(" %c",&op1);
	if(op1=='v')
	{
		char op2;
		printf("s)save and exit e)exit without saving\n");
		scanf(" %c",&op2);
		if(op2=='s')
		{
			if(*ptr==0)
			{
				printf("no records present\n");
				return;
			}
			c=1;
			sll *s=*ptr;
			FILE *fp;
			fp=fopen("data","w");
			while(s)
			{
				s->rollno=c++;
				fprintf(fp,"%d %s %f\n",s->rollno,s->name,s->marks);
				s=s->next;
			}
			printf("file is saved\n");
			exit(0);
		}
		else if(op2=='e')
		{
			exit(0);
		}
	}
	else if(op1=='t')
	{
		char op3;
		printf("n)sort with name p)sort with percentage\n");
		scanf(" %c",&op3);
		if(op3=='p')
		{
			if(*ptr==0)
			{
				printf("no records present\n");
				return;
			}
			sll *p1=*ptr,*p2,t,*p3=*ptr;
			int i,j,c=0;
			while(p3)
			{
				c++;
				p3=p3->next;
			}
			for(i=0;i<c-1;i++)
			{
				p2=p1->next;
				for(j=0;j<c-1-i;j++)
				{
					if(p1->marks > p2->marks)
					{
						t.marks=p1->marks;
						strcpy(t.name,p1->name);
						t.rollno=p1->rollno;

						p1->marks=p2->marks;
						strcpy(p1->name,p2->name);
						p1->rollno=p2->rollno;

						p2->marks=t.marks;
						strcpy(p2->name,t.name);
						p2->rollno=t.rollno;
					}
					p2=p2->next;
				}
				p1=p1->next;
			}
		}
		else if(op3=='n')
		{
			sll *p1=*ptr,*p2,t,*l=*ptr;
			int i,j,c=0;
			while(l)
			{
				c++;
				l=l->next;
			}
			for(i=0;i<c-1;i++)
			{
				p2=p1->next;
				for(j=0;j<c-1-i;j++)
				{
					if(strcmp(p1->name,p2->name)>=0)
					{
						t.marks=p1->marks;
						strcpy(t.name,p1->name);
						t.rollno=p1->rollno;

						p1->marks=p2->marks;
						strcpy(p1->name,p2->name);
						p1->rollno=p2->rollno;

						p2->marks=t.marks;
						strcpy(p2->name,t.name);
						p2->rollno=t.rollno;
					}
					p2=p2->next;
				}
				p1=p1->next;
			}
		}
	}
	else if(op1=='l')
	{
		if(*ptr==0)
		{
			printf("no records present\n");
			return;
		}
		int c=1;
		sll *del=*ptr;
		while(del)
		{
			*ptr=del->next;
			free(del);
			printf("delete node:%d\n",c++);
			sleep(1);
			del=*ptr;
		}
		printf("all  node deleted\n");
	}
	else if(op1=='r')
	{
		if(*ptr==0)
		{
			printf("no records present\n");
			return;
		}
		sll *t,*p=*ptr;
		int i,j,c1=0;
		while(p)
		{
			c1++;
			p=p->next;
		}
		for(i=0;i<c1;i++)
		{
			t=*ptr;
			for(j=0;j<c1-1-i;j++)
				t=t->next;
			printf("%d %s %f\n",t->rollno,t->name,t->marks);
		}
	}
}
void stud_del(sll **ptr)
{
	char op1;
	printf("r)rollno n)name\n");
	scanf(" %c",&op1);
	if(op1=='n')
	{
		if(*ptr==0)
		{
			printf("no records present\n");
			return;
		}
		sll *del=*ptr,*prev=*ptr;
		char name[20];
		printf("enter the name\n");
		scanf("%s",name);
		while(del)
		{
			if(strcmp(name,del->name)==0)
			{
				if(*ptr==del)
				{
					*ptr=del->next;
					free(del);
				}
				else
				{
					prev->next=del->next;
					free(del);
				}
			}
			prev=del;
			del=del->next;
		}
	}
	else if(op1=='r')
	{
		if(*ptr==0)
		{
			printf("no records present\n");
			return;
		}
		sll *del=*ptr,*prev=*ptr;
		int num;
		printf("enter the num\n");
		scanf("%d",&num);
		while(del)
		{
			if(num==del->rollno)
			{
				if(del==*ptr)
				{
					*ptr=del->next;
					free(del);
				}
				else
				{
					prev->next=del->next;
					free(del);
				}
			}
			prev=del;
			del=del->next;
		}
	}
}
void stud_mod(sll *ptr)
{
	char op1;
	int n;
	printf("r)rollno n)name p)percentage\n");
	scanf(" %c",&op1);
	if(op1=='r')
	{
		if(ptr==0)
		{
			printf("no records present\n");
			return;
		}
		int num;
		printf("enter the num\n");
		scanf("%d",&num);
		while(ptr)
		{
			if(num==ptr->rollno)
			{
				printf("enter the modified rollnumber:\n");
				scanf("%d",&n);
				ptr->rollno=n;
				printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
				return;
			}
			ptr=ptr->next;
		}
		printf("rollno not present\n");
	}
	else if(op1=='n')
	{
		char n[20];
		if(ptr==0)
		{
			printf("no records present\n");
			return;
		}
		char name[20];
		printf("enter the name\n");
		scanf("%s",name);
		while(ptr)
		{
			if(strcmp(name,ptr->name)==0)
			{
				printf("enter the modified name:\n");
				scanf("%s",n);
				strcpy(ptr->name,n);
				printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
				return;
			}
			ptr=ptr->next;
		}
		printf("Name not present\n");
	}
	else if(op1=='p')
	{
		float m;
		if(ptr==0)
		{
			printf("no records present\n");
			return;
		}
		int num;
		printf("enter the num\n");
		scanf("%d",&num);
		while(ptr)
		{
			if(num==ptr->marks)
			{
				printf("enter the modified marks:\n");
				scanf("%f",&m);
				ptr->marks=m;
				printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
				return;
			}
			ptr=ptr->next;
		}
		printf("Marks not present\n");
	}
}

