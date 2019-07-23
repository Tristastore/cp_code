#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int rd_fd;
	int wr_fd;
	int wr_sum=0;
	char rd_buf[128]={0};
	int wr_ret;
	int rd_ret;
	
	rd_fd=open(argv[1],O_RDONLY); //O_APPEND  O_TRUNC   
	if(rd_fd<0)
	{
		printf("open file1 %s fail\n",argv[1]);
		return -1;
	}
	
	printf("open file1 %s success\n",argv[1]);
	printf("rd_fd=%d\n",rd_fd);
	
	rd_ret=read(rd_fd,rd_buf,128);
	printf("rd_ret=%d\n",rd_ret);
	
	
	
	wr_fd=open(argv[2],O_CREAT|O_RDWR); //O_APPEND  O_TRUNC   
	if(wr_fd<0)
	{
		printf("creat file2 %s fail\n",argv[2]);
		return -1;
	}
	
	printf("creat file2 %s success\n",argv[2]);
	
	while(1)
	{
		rd_ret=read(rd_fd,rd_buf,128);
		if(rd_ret<128)
			break;
		wr_ret=write(wr_fd,rd_buf,rd_ret);
		wr_sum=wr_sum+wr_ret;
		memset(rd_buf,0,128);  //将rd_buf中全部内容清零
	}
	
	wr_ret=write(wr_fd,rd_buf,rd_ret);
	wr_sum=wr_sum+wr_ret;
	
	printf("write success\n");
	printf("wr_sum=%d\n",wr_sum); //复制文件字节数
	
	close(rd_fd);
	close(wr_fd);
	return 0;

}

