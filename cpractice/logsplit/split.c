#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>

#define SIZE 100
#define LENGTH ((SIZE)+1)
#define DATESIZE 11
#define LINESIZE 200

void init_time(struct tm *start_time,struct tm *end_time){
	if(start_time == NULL || end_time == NULL){
		perror("start_time or end_time can't be null");
		exit(1);
	}
	
	start_time->tm_year = 2021-1900;
	start_time->tm_mon = 8-1;
	start_time->tm_mday = 19;
	start_time->tm_hour = 0;
	start_time->tm_min = 0;
	start_time->tm_sec = 0;
	start_time->tm_isdst = -1;

	end_time->tm_year = 2022-1900;
	end_time->tm_mon = 8-1;
	end_time->tm_mday = 12;
	end_time->tm_hour = 0;
	end_time->tm_min = 0;
	end_time->tm_sec = 0;
	end_time->tm_isdst = -1;
}

time_t convert_str_to_time(char *str){
	if(strlen(str) != 10){
		perror("convert str to time error,the str format is wrong");
		exit(1);
	}
	char year[5], month[3],day[3];
	int year_int,month_int,day_int;
	char *str_source = str;
	memcpy(year, str_source, 4);
	year[4] = '\0';	
	str_source += 5;

	memcpy(month, str_source, 2);
	month[2] = '\0';
	str_source += 3;

	memcpy(day, str_source, 2);
	day[2] = '\0';
	
	year_int = atoi(year);
	month_int = atoi(month);
	day_int = atoi(day);	
	//printf("convert year is %d,month is %d,day is %d\n", year_int, month_int, day_int);

	struct tm time_tm;
	time_tm.tm_year = year_int - 1900;
	time_tm.tm_mon = month_int - 1;
	time_tm.tm_mday = day_int;
	time_tm.tm_hour = 0;
	time_tm.tm_min = 0;
	time_tm.tm_sec = 0;
	time_tm.tm_isdst = -1;
	
	time_t str_time = mktime(&time_tm);
//	printf("convert year is %d,month is %d,day is %d,time_t is %d\n", year_int, month_int, day_int, str_time);
	return str_time;
}

void set_filename(char *filename, int size, time_t time){
	const time_t *param_time = &time;
	struct tm *time_tm = localtime(param_time);
	int year = time_tm->tm_year + 1900;
	int month = time_tm->tm_mon + 1;
	int day = time_tm->tm_mday;
	
	snprintf(filename, size, "catalina.%d-%02d-%02d.log",year, month, day);

}

int extract_time(char *str, char *dst){
	if(strlen(str) < 10){
		return -1;	
	}
	for(int i=0; i<10; i++){
		dst[i]=str[i];
	}
	dst[10] = '\0';
} 

int extract_year(char *date){
	char year_str[5];
	for(int i=0;i<4;i++){
		year_str[i]=date[i];
	}
	year_str[4] = '\0';
	return atoi(year_str);
}

int extract_month(char *date){
	char month_str[3];
	for(int i=5;i<7;i++){
		month_str[i-5]=date[i];
	}
	month_str[2]='\0';
	return atoi(month_str);
}

int extract_day(char *date){
	char day_str[3];
	for(int i=8;i<10;i++){
		day_str[i-8]=date[i];
	}
	day_str[2] = '\0';
	return atoi(day_str);
}

bool date_is_valid(char *date){
	int yy = extract_year(date);
	int mm = extract_month(date);
	int dd = extract_day(date);

	if(yy >= 1900 && yy <= 9999){
		if(mm >= 1 && mm <= 12){
			if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                		return true;
            		else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                		return true;
            		else if((dd>=1 && dd<=28) && (mm==2))
                		return true;
            		else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
                		return true;
            		else
                		return false;	
		}else{
			return false;
		}
	}else{
		return false;
	}		
}

char *readline(FILE *fp, int *indicate){
	int malloc_size = LINESIZE;
	char *linestr = calloc(sizeof(char), malloc_size);
	char str[LENGTH];
	int bool_indi = 0;
	while(fgets(str, LENGTH, fp) != NULL){
		bool_indi = 1;
		size_t len = strlen(str);
		if(strlen(linestr) + len > malloc_size -1){
			malloc_size = malloc_size + malloc_size/2;
			linestr = realloc(linestr, malloc_size);
		}
		strcat(linestr, str);
		if(len < SIZE || (len == SIZE && str[len-1] == '\n'))
			break;
	}
	*indicate = bool_indi;
	size_t len = strlen(linestr);
	linestr[len] = '\0';
	return linestr;
}

int main()
{
	FILE *fp, *fpout;
	char str[LENGTH];

	fp = fopen("catalinalog.2022-08-12manual.log","r");
	if(fp == NULL){
		perror("Error open file.");
		return -1;
	}

	struct tm start_time, end_time;
	init_time(&start_time, &end_time);

	time_t start_time_t = mktime(&start_time);
	time_t end_time_t = mktime(&end_time);

	char *leftstr;
	leftstr = malloc(1);
	leftstr[0] = '\0';

	while(((int)difftime(end_time_t, start_time_t)) >= 0){
		time_t next_time_t = start_time_t + 60 * 60 * 24;
		char filename[24];		
		set_filename(filename, sizeof(filename), start_time_t);			

		fpout = fopen(filename, "w+");
		fputs(leftstr, fpout);
		free(leftstr);
		//bool can_extract_time = true;
		int indicate = 0;
		char *linestr =	readline(fp, &indicate);
		printf("indicate value %d\n", indicate);
		if(indicate == 0) break;
		//printf("line content is %s\n", linestr);
		//printf("linestr len is %d\n", strlen(linestr));
		int count = 0;
		while(true){
			count++;
			char extract_date_str[11];

			int sign_num = extract_time(linestr, extract_date_str);
			
			if(sign_num == -1){
				fputs(linestr, fpout);
			}else{
				if(!date_is_valid(extract_date_str)){
					fputs(linestr,fpout);
				}else{
					time_t logtime = convert_str_to_time(extract_date_str);
					if(next_time_t == logtime){
						printf("extract_date is %s,before count is %d\n",extract_date_str, count);
						printf("next_time_t number is %d,logtime number is %d\n",next_time_t , logtime);

						//printf("leftstr address is %p\n", leftstr);
						//free(leftstr);
						leftstr = malloc(strlen(linestr) + 1);
						memcpy(leftstr, linestr, strlen(linestr));
						leftstr[strlen(linestr)] = '\0';
						fclose(fpout);
						break;
					}else{
						fputs(linestr,fpout);
					}
				}
			}	
			
			//printf("linestr address is %p\n", linestr);
			free(linestr);
			linestr = readline(fp, &indicate);
			if(indicate == 0) break;
			//printf("line content is %s\n", linestr);

		}
		printf("start_time is %d,next_time_t is %d\n", start_time_t, next_time_t);
		start_time_t = next_time_t;
	}

	fclose(fp);

	return 0;
}
