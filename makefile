main:
	g++ mysqld_lib.h
	g++ mysql.cpp -o mysql.exe `mysql_config --cflags --libs`