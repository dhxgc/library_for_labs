// Temperature
#ifndef _temp_H_
#define _temp_H_

char* get_temp_raw(void){
		int str_len=100;
		system("find /sys/bus/w1/devices/ -name 28* >$PWD/temp_way.txt");
		static char temp_raw_result[200]={0};
		char buff[100];
		FILE *way_file = fopen("temp_way.txt", "r");
		fgets(buff, str_len,way_file);
		for (int count = 0; count < (int)strlen(buff); count++)
			if(buff[count]=='\n') buff[count]=0;
		fclose(way_file);
		strcat(buff,"/w1_slave");
		FILE *sensor_file=fopen(buff, "r");
		while (fgets(buff,str_len, sensor_file) != NULL)
		{
			strcpy(temp_raw_result, buff);
		}
		//printf("\nTESTS BUFF:   %s\n", buff);
		//printf("\nTESTS BUFF T::: %s\n", temp_raw_result);
		return temp_raw_result;
}

float get_temp(void) {
		char* mas = get_temp_raw();
		char str_temp[10]={0};
		int str_pos=0;
		int char_pos=0;
		while(mas[char_pos]!='t') char_pos++;
		char_pos+=2;
		for (int count = char_pos; count < (int)strlen(mas); count++)
		{
			str_temp[str_pos]=mas[count];
			str_pos++;
		}
		float temp=(atof(str_temp)/1000);
		return temp;
}
#endif