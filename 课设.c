#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
	char xh[10]; //学号
	char xm[20]; //姓名
	char xb[10];  //性别
	int zhuanye;  //专业，1-8
}Student;
typedef struct
{
	char kh[10]; //课号
	char km[25]; //课程名
	float  xuefen;    //课程学分，为一个浮点数
}Course;
typedef struct
{
	char xh[10]; //学号
	char kh[10]; //课程号
	float  chengji;    //成绩，浮点数
}Select;
typedef struct
{
	char xh[10]; //学号
	char xm[20]; //姓名
	float cj[30];//各门课程成绩
	float pjf;    //平均分
	float zxf;    //总学分
}Score;
void init(Student slist[], int* scount, Course clist[], int* ccount, Select sclist[], int* sccount);//通过指定的文件装入相关必要信息
int create_cjlist(Student slist[], int scount, Select sclist[], int sccount, Course clist[], int ccount, Score cjlist[]);
//显示学生信息表、课程信息表和成绩单(加权平均分和总学分)
void disp_stud(Student slist[], int scount);//显示所有学生信息(10条一页)
void disp_course(Course clist[], int ccount);//显示所有课程信息(10条一页)
void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount);//显示成绩单信息(10条一页)
void sort_slist(Student slist[], int scount);//按照学号升序排序
void sort_clist(Course clist[], int ccount);// 按照课程号升序排序
void sort_cjlist(Score cjlist[], int cjcount);// 按照平均成绩降序排序
int input_stud(Student slist[], int scount); //输入学生信息记录
int input_course(Course clist[], int ccount); //输入课程信息记录
int input_select(Select sclist[], int sccount); //输入选课记录
int delete_stud(Student slist[], int scount); //根据姓名或学号删除学生记录，返回数组中的还剩下的记录数
int delete_course(Course clist[], int ccount); //根据课程名或课程号删除课程记录，返回数组中还剩下的记录数
int delete_select(Select sclist[], int sccount); //根据学号删除选课记录，返回数组中还剩下的记录数
void query_stud(Student slist[], int scount);//根据学号或姓名查询学生记录并显示
void query_course(Course clist[], int ccount);//根据课程号或课程名查询课程记录并显示
void query_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount);//根据学号查询成绩单，显示对应同学的所有课程成绩、平均分、学分以及排名情况，并显示
void write_to_file1(Student slist[], int scount, Course clist[], int ccount, Select sclist[], int sccount);// 把学生信息表、课程信息表和选课信息表分别保存到文件中
void write_to_file2(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount);// 把成绩单保存到文件中，包括名次、学号、姓名、性别、各门课成绩、平均分以及总学分
int menu_select(); //显示功能菜单并获取用户选择的功能项
int menu1_select();//显示选择菜单进行精确选择
int menu2_select();//显示选择菜单进行精确选择
int menu3_select();//显示选择菜单进行精确选择
int menu4_select();//显示选择菜单进行精确选择
int menu5_select();//显示选择菜单进行精确选择
int main()
{
	printf("******** 欢迎使用学生成绩管理系统 ********\n");
	Student slist[20];//学生信息表
	int scount = 0;//学生人数
	Course clist[20];//课程信息表
	int ccount = 0;//课程数
	Select sclist[100];//选课信息表
	int sccount = 0;//选课数
	Score cjlist[20];//成绩单
	int cjcount = 0;//成绩列数
    for (; ; )
    {
        switch (menu_select())
        {
        case 1:
            printf("*****输入学生、课程、选课信息*****\n");
			switch (menu1_select())
			{
			case 1:
				//通过指定的文件装入相关必要信息
				init(slist, &scount, clist, &ccount, sclist, &sccount);
				printf("文件信息导入完成\n");
				break;
			case 2:
				//输入学生信息记录
				scount=input_stud(slist, scount); 
				break;
			case 3:
				//输入课程信息记录
				ccount=input_course(clist, ccount);
				break;
			case 4:
				//输入选课记录
				sccount=input_select(sclist, sccount);
				break;
			}
            system("pause");
            break;
        case 2:
            printf("*****显示所有数据*****\n");
			//显示学生信息表、课程信息表和成绩单(加权平均分和总学分)
			create_cjlist(slist, scount, sclist, sccount, clist, ccount, cjlist);
			switch (menu2_select())
			{ 
			case 1:
				//按照学号升序排序
				sort_slist(slist, scount);
				//显示所有学生信息(10条一页)
				disp_stud( slist, scount);
				break;
			case 2:
				// 按照课程号升序排序
				sort_clist(clist, ccount);
				//显示所有课程信息(10条一页)
				disp_course(clist, ccount);
				break;
			case 3:
				// 按照平均成绩降序排序
				sort_cjlist(cjlist, cjcount);
				//显示成绩单信息(10条一页)
				disp_cjlist(cjlist, cjcount, clist, ccount, slist, scount);
				break;
			}
			printf("\n数据展示完成\n");
            system("pause");
            break;
        case 3:
            printf("*****按条件删除记录*****\n");
			switch (menu3_select())
			{
			case 1:
				//根据姓名或学号删除学生记录，返回数组中的还剩下的记录数
				scount=delete_stud(slist, scount); 
				printf("\n还剩下%d个学生记录\n", scount);
				break;
			case 2:
				//根据课程名或课程号删除课程记录，返回数组中还剩下的记录数
				ccount=delete_course(clist,  ccount);
				printf("\n还剩下%d个课程记录\n", ccount);
				break;
			case 3:
				//根据学号删除选课记录，返回数组中还剩下的记录数
				sccount=delete_select(sclist, sccount);
				printf("\n还剩下%d个选课记录\n", sccount);
				break;
			}
            system("pause");
            break;
        case 4:
            printf("*****查询信息*****\n");
			switch (menu2_select())
			{
			case 1:
				//根据学号或姓名查询学生记录并显示
				query_stud(slist, scount);
				break;
			case 2:
				//根据课程号或课程名查询课程记录并显示
				query_course(clist, ccount);
				break;
			case 3:
				//根据学号查询成绩单，显示对应同学的所有课程成绩、平均分、学分以及排名情况，并显示
				query_cjlist(cjlist, cjcount, clist, ccount, slist, scount);
				break;
			}
            system("pause");
			break;
        case 5:
            printf("*****保存数据到文件*****\n");
			switch (menu2_select())
			{
			case 1:
				// 把学生信息表、课程信息表和选课信息表分别保存到文件中
				write_to_file1(slist, scount, clist, ccount, sclist, sccount);
				break;
			case 2:
				// 把成绩单保存到文件中，包括名次、学号、姓名、性别、各门课成绩、平均分以及总学分
				write_to_file2(cjlist, 20, clist, ccount, slist, scount);
				break;
			}
			system("pause");
            break;
        case 0:
            printf("*****Goodbye!*****\n");
            system("pause");
            exit(0);
        }
        system("cls");
    }
    return 0;
}
//显示功能菜单并获取用户选择的功能项
int menu_select()
{
    char c;
    do {
        system("cls");					 /*  清屏  */
        //选择功能菜单
        printf("请选择一项功能:\n");
        printf("1. 输入学生、课程、选课信息\n");
        printf("2. 显示所有数据\n");
        printf("3. 按条件删除记录\n");
        printf("4. 查询信息\n");
        printf("5. 保存数据到文件\n");
        printf("0. 退出系统\n");
        c = getchar();
    } while (c < '0' || c>'5');
    return(c - '0');
}
//显示选择菜单进行精确选择
int menu1_select()
{
	char c;
	do {
		system("cls");					 /*  清屏  */
		//选择功能菜单
		printf("请选择:\n");
		printf("1. 从文件中录入\n");
		printf("2. 输入学生信息\n");
		printf("3. 输入课程信息\n");
		printf("4. 输入选课信息\n");
		c = getchar();
	} while (c < '1' || c>'4');
	return(c - '0');
}
int menu2_select()
{
	char c;
	do {
		system("cls");					 /*  清屏  */
		//选择功能菜单
		printf("请选择:\n");
		printf("1. 显示所有学生信息\n");
		printf("2. 显示所有课程信息\n");
		printf("3. 显示所有选课信息\n");
		c = getchar();
	} while (c < '1' || c>'3');
	return(c - '0');
}
int menu3_select()
{
	char c;
	do {
		system("cls");					 /*  清屏  */
		//选择功能菜单
		printf("请选择:\n");
		printf("1. 删除学生记录\n");
		printf("2. 删除课程记录\n");
		printf("3. 删除选课记录\n");
		c = getchar();
	} while (c < '1' || c>'3');
	return(c - '0');
}
int menu4_select()
{
	char c;
	do {
		system("cls");					 /*  清屏  */
		//选择功能菜单
		printf("请选择:\n");
		printf("1. 查询学生记录\n");
		printf("2. 查询课程记录\n");
		printf("3. 查询选课记录\n");
		c = getchar();
	} while (c < '1' || c>'3');
	return(c - '0');
}
int menu5_select()
{
	char c;
	do {
		system("cls");					 /*  清屏  */
		//选择功能菜单
		printf("请选择:\n");
		printf("1. 把学生信息表、课程信息表和选课信息表分别保存到文件中\n");
		printf("2. 把成绩单保存到文件中\n");
		c = getchar();
	} while (c < '1' || c>'2');
	return(c - '0');
}
//通过指定的文件装入相关必要信息
void init(Student slist[], int* scount, Course clist[], int* ccount, Select sclist[], int* sccount)
{
	FILE* fs, * fc, * fsc;
	*scount = 0;
	*ccount = 0;
	*sccount = 0;
	fs = fopen("slist.txt", "r");
	fc = fopen("clist.txt", "r");
	fsc = fopen("sclist.txt", "r");
	if (fs == NULL || fc == NULL || fsc == NULL)
	{
		printf("文件打开失败！\n");
		return;
	}
	// 读取学生信息
	while (1)
	{
		int ret = fscanf(fs, "%s %s %s %d", slist[*scount].xh, slist[*scount].xm, slist[*scount].xb, &slist[*scount].zhuanye);
		if (ret == EOF) break;
		if (ret == 4) (*scount)++;
	}
	// 读取课程信息
	while (1)
	{
		int ret = fscanf(fc, "%s %s %f", clist[*ccount].kh, clist[*ccount].km, &clist[*ccount].xuefen);
		if (ret == EOF) break;
		if (ret == 3) (*ccount)++;
	}
	// 读取选课信息
	while (1)
	{
		int ret = fscanf(fsc, "%s %s %f", sclist[*sccount].xh, sclist[*sccount].kh, &sclist[*sccount].chengji);
		if (ret == EOF) break;
		if (ret == 3) (*sccount)++;
	}
	fclose(fs);
	fclose(fc);
	fclose(fsc);
}
//显示学生信息表、课程信息表和成绩单(平均分和总学分)
int create_cjlist(Student slist[], int scount, Select sclist[], int sccount, Course clist[], int ccount, Score cjlist[])
{
		int i, j, k;
		for (i = 0; i < scount; i++)
		{
			strcpy(cjlist[i].xh, slist[i].xh);
			strcpy(cjlist[i].xm, slist[i].xm);
			cjlist[i].pjf = 0;
			cjlist[i].zxf = 0;
			for (j = 0; j < sccount; j++)
			{
				if (strcmp(sclist[j].xh, slist[i].xh) == 0)
				{
					for (k = 0; k < ccount; k++)
					{
						if (strcmp(sclist[j].kh, clist[k].kh) == 0)
						{
							cjlist[i].cj[k] = sclist[j].chengji;
							cjlist[i].pjf += sclist[j].chengji;
							cjlist[i].zxf += clist[k].xuefen;
						}
					}
				}
			}
			if (cjlist[i].zxf > 0)
			{
				cjlist[i].pjf /= ccount;
			}
		}
		return scount;
}
//显示所有学生信息(10条一页)
void disp_stud(Student slist[], int scount)
{
	int i, page = 0;
	while (page * 10 < scount)
	{
		system("cls");
		printf("学号\t姓名\t性别\t专业\n");
		for (i = page * 10; i < (page + 1) * 10 && i < scount; i++)
		{
			printf("%s\t%s\t%s\t%d\n", slist[i].xh, slist[i].xm, slist[i].xb, slist[i].zhuanye);
		}
		page++;
		if (page * 10 < scount)
		{
			printf("按任意键继续...");
			getchar();
		}
	}
}
//显示所有课程信息(10条一页)
void disp_course(Course clist[], int ccount)
{	
	int i, page = 0;
	while (page * 10 < ccount)
	{
		system("cls");
		printf("课号\t课程名\t学分\n");
		for (i = page * 10; i < (page + 1) * 10 && i < ccount; i++)
		{
			printf("%s\t%s\t%.2f\n", clist[i].kh, clist[i].km, clist[i].xuefen);
		}
		page++;
		if (page * 10 < ccount)
		{
			printf("按任意键继续...");
			getchar();
		}
	}
}
//显示成绩单信息(10条一页)
void disp_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount)
{
		int i, page = 0;
		while (page * 10 < cjcount)
		{
			system("cls");
			printf("学号\t姓名\t");
			for (i = 0; i < ccount; i++)
			{
				printf("%s\t", clist[i].km);
			}
			printf("平均分\t总学分\n");
			for (i = page * 10; i < (page + 1) * 10 && i < cjcount; i++)
			{
				printf("%s\t%s\t", cjlist[i].xh, cjlist[i].xm);
				for (int j = 0; j < ccount; j++)
				{
					if (cjlist[i].cj[j] > 0)
					{
						printf("%.2f\t", cjlist[i].cj[j]);
					}
					else
					{
						printf("-\t");
					}
				}
				printf("%.2f\t%.2f\n", cjlist[i].pjf, cjlist[i].zxf);
			}
			page++;
			if (page * 10 < cjcount)
			{
				printf("按任意键继续...");
				getchar();
			}
		}
}
//按照学号升序排序
void sort_slist(Student slist[], int scount)
{	
	int i, j;
	Student temp;
	for (i = 0; i < scount - 1; i++)
	{
		for (j = 0; j < scount - 1 - i; j++)
		{
			if (strcmp(slist[j].xh, slist[j + 1].xh) > 0)
			{
				temp = slist[j];
				slist[j] = slist[j + 1];
				slist[j + 1] = temp;
			}
		}
	}
}
// 按照课程号升序排序
void sort_clist(Course clist[], int ccount)
{
		int i, j;
		Course temp;
		for (i = 0; i < ccount - 1; i++)
		{
			for (j = 0; j < ccount - 1 - i; j++)
			{
				if (strcmp(clist[j].kh, clist[j + 1].kh) > 0)
				{
					temp = clist[j];
					clist[j] = clist[j + 1];
					clist[j + 1] = temp;
				}
			}
		}
}
// 按照平均成绩降序排序
void sort_cjlist(Score cjlist[], int cjcount)
{
	int i, j;
		Score temp;
		for (i = 0; i < cjcount - 1; i++)
		{
			for (j = 0; j < cjcount - 1 - i; j++)
			{
				if (cjlist[j].pjf < cjlist[j + 1].pjf)
				{
					temp = cjlist[j];
					cjlist[j] = cjlist[j + 1];
					cjlist[j + 1] = temp;
				}
			}
		}
}
//输入学生信息记录
int input_stud(Student slist[], int scount)
{
	    printf("请输入学生信息(学号 姓名 性别 专业),输入。结束：\n");
    while (scount < 20) {
        char xh[16];
        if (scanf("%15s", xh)!=1) break;
        if (strcmp(xh, "。") == 0) break;
        strncpy(slist[scount].xh, xh, sizeof(slist[scount].xh)-1);
        slist[scount].xh[sizeof(slist[scount].xh)-1]=0;
        scanf("%19s %2s %d", slist[scount].xm, slist[scount].xb, &slist[scount].zhuanye);
        scount++;
    }
    return scount;
}
//输入课程信息记录
int input_course(Course clist[], int ccount)
{
		int i;
		printf("请输入课程信息记录(课号 课程名 学分)，输入。结束：\n");
		while (1)
		{
			char kh[10];
			scanf("%s", kh);
			if (strcmp(kh, "。") == 0)
			{
				break;
			}
			strcpy(clist[ccount].kh, kh);
			scanf("%s %f", clist[ccount].km, &clist[ccount].xuefen);
			ccount++;
		}
		return ccount;
}
//输入选课记录
int input_select(Select sclist[], int sccount)
{		int i;
		printf("请输入选课记录(学号 课号 成绩)，输入。结束：\n");
		while (1)
		{
			char xh[10];
			scanf("%s", xh);
			if (strcmp(xh, "。") == 0)
			{
				break;
			}
			strcpy(sclist[sccount].xh, xh);
			scanf("%s %f", sclist[sccount].kh, &sclist[sccount].chengji);
			sccount++;
		}
		return sccount;
}
 //根据姓名或学号删除学生记录，返回数组中的还剩下的记录数
int delete_stud(Student slist[], int scount)
{
		int i, j;
		char key[20];
		printf("请输入要删除的学生的学号或姓名：\n");
		scanf("%s", key);
		for (i = 0; i < scount; i++)
		{
			if (strcmp(slist[i].xh, key) == 0 || strcmp(slist[i].xm, key) == 0)
			{
				for (j = i; j < scount - 1; j++)
				{
					slist[j] = slist[j + 1];
				}
				scount--;
				i--;
			}
		}
		return scount;
}
//根据课程名或课程号删除课程记录，返回数组中还剩下的记录数
int delete_course(Course clist[], int ccount)
{
		int i, j;
		char key[25];
		printf("请输入要删除的课程的课程号或课程名：\n");
		scanf("%s", key);
		for (i = 0; i < ccount; i++)
		{
			if (strcmp(clist[i].kh, key) == 0 || strcmp(clist[i].km, key) == 0)
			{
				for (j = i; j < ccount - 1; j++)
				{
					clist[j] = clist[j + 1];
				}
				ccount--;
				i--;
			}
		}
		return ccount;
}
//根据学号删除选课记录，返回数组中还剩下的记录数
int delete_select(Select sclist[], int sccount)
{
		int i, j;
		char xh[10];
		printf("请输入要删除选课记录的学生学号：\n");
		scanf("%s", xh);
		for (i = 0; i < sccount; i++)
		{
			if (strcmp(sclist[i].xh, xh) == 0)
			{
				for (j = i; j < sccount - 1; j++)
				{
					sclist[j] = sclist[j + 1];
				}
				sccount--;
				i--;
			}
		}
		return sccount;
}
//根据学号或姓名查询学生记录并显示
void query_stud(Student slist[], int scount)
{
		int i;
		char key[20];
		printf("请输入要查询的学生的学号或姓名：\n");
		scanf("%s", key);
		printf("学号\t姓名\t性别\t专业\n");
		for (i = 0; i < scount; i++)
		{
			if (strcmp(slist[i].xh, key) == 0 || strcmp(slist[i].xm, key) == 0)
			{
				printf("%s\t%s\t%s\t%d\n", slist[i].xh, slist[i].xm, slist[i].xb, slist[i].zhuanye);
			}
		}
}
//根据课程号或课程名查询课程记录并显示
void query_course(Course clist[], int ccount)
{
		int i;
		char key[25];
		printf("请输入要查询的课程的课程号或课程名：\n");
		scanf("%s", key);
		printf("课号\t课程名\t学分\n");
		for (i = 0; i < ccount; i++)
		{
			if (strcmp(clist[i].kh, key) == 0 || strcmp(clist[i].km, key) == 0)
			{
				printf("%s\t%s\t%.2f\n", clist[i].kh, clist[i].km, clist[i].xuefen);
			}
		}
}
//根据学号查询成绩单，显示对应同学的所有课程成绩、平均分、学分以及排名情况，并显示
void query_cjlist(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount)
{
	int i, j;
		char xh[10];
		printf("请输入要查询成绩单的学生学号：\n");
		scanf("%s", xh);
		printf("学号\t姓名\t");
		for (i = 0; i < ccount; i++)
		{
			printf("%s\t", clist[i].km);
		}
		printf("平均分\t总学分\n");
		for (i = 0; i < cjcount; i++)
		{
			if (strcmp(cjlist[i].xh, xh) == 0)
			{
				printf("%s\t%s\t", cjlist[i].xh, cjlist[i].xm);
				for (j = 0; j < ccount; j++)
				{
					if (cjlist[i].cj[j] > 0)
					{
						printf("%.2f\t", cjlist[i].cj[j]);
					}
					else
					{
						printf("-\t");
					}
				}
				printf("%.2f\t%.2f\n", cjlist[i].pjf, cjlist[i].zxf);
			}
		}
}
// 把学生信息表、课程信息表和选课信息表分别保存到文件中
void write_to_file1(Student slist[], int scount, Course clist[], int ccount, Select sclist[], int sccount)
{
	FILE* fp1, * fp2, * fp3;
	// 保存学生信息
	fp1 = fopen("slist.txt", "w");
	if (fp1 == NULL)
	{
		printf("无法打开文件！\n");
		return;
	}
	fprintf(fp1, "%d\n", scount);
	for (int i = 0; i < scount; i++)
	{
		fprintf(fp1, "%s %s %s %d\n", slist[i].xh, slist[i].xm, slist[i].xb, slist[i].zhuanye);
	}
	fclose(fp1);
	// 保存课程信息
	fp2 = fopen("clist.txt", "w");
	if (fp2 == NULL)
	{
		printf("无法打开文件！\n");
		return;
	}
	fprintf(fp2, "%d\n", ccount);
	for (int i = 0; i < ccount; i++)
	{
		fprintf(fp2, "%s %s %.2f\n", clist[i].kh, clist[i].km, clist[i].xuefen);
	}
	fclose(fp2);
	// 保存选课信息
	fp3 = fopen("sclist.txt", "w");
	if (fp3 == NULL)
	{
		printf("无法打开文件！\n");
		return;
	}
	fprintf(fp3, "%d\n", sccount);
	for (int i = 0; i < sccount; i++)
	{
		fprintf(fp3, "%s %s %.2f\n", sclist[i].xh, sclist[i].kh, sclist[i].chengji);
	}
	fclose(fp3);
}
// 把成绩单保存到磁盘文件中，包括名次、学号、姓名、性别、各门课成绩、平均分以及总学分
void write_to_file2(Score cjlist[], int cjcount, Course clist[], int ccount, Student slist[], int scount)
{
	FILE* fp;
	fp = fopen("cjlist.txt", "w");
	if (fp == NULL)
	{
		printf("无法打开文件！\n");
		return;
	}
	fprintf(fp, "名次\t学号\t姓名\t性别\t");
	for (int i = 0; i < ccount; i++)
	{
		fprintf(fp, "%s\t", clist[i].km);
	}
	fprintf(fp, "平均分\t总学分\n");
	for (int i = 0; i < cjcount; i++)
	{
		fprintf(fp, "%d\t%s\t%s\t", i + 1, cjlist[i].xh, cjlist[i].xm);
		for (int j = 0; j < ccount; j++)
		{
			if (cjlist[i].cj[j] > 0)
			{
				fprintf(fp, "%.2f\t", cjlist[i].cj[j]);
			}
			else
			{
				fprintf(fp, "-\t");
			}
		}
		fprintf(fp, "%.2f\t%.2f\n", cjlist[i].pjf, cjlist[i].zxf);
	}
	fclose(fp);
}
