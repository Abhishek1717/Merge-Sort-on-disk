#include<stdio.h>
#include<string.h>
#include<sys/time.h>

int comparator(const void *a,const void * b){

	int c= *(int *)a;
	int d= *(int *)b;

	return c-d;


}

void heapify(int *heap,int heap_size,int position){

	int left=position*2+1;
	int right=position*2+2;
	int min=heap[position],min_pos=position;
	
	if(left<heap_size && heap[left]<min){
		min=heap[left];min_pos=left;
	
	}
	if(right<heap_size && heap[right]<min){
		min=heap[right];min_pos=right;
	}
	
	
	
	if(position!=min_pos){
		int temp=heap[position];
		heap[position]=heap[min_pos];
		heap[min_pos]=temp;
		heapify(heap,heap_size,min_pos);	
	}
	

}

void heapsort(int *heap,int heap_size){
	int i=0;
	for(i=heap_size/2;i>=0;i--){
		heapify(heap,heap_size,i);

	}
}

void merge(int runs,char *out_file,char *input_file){

	FILE *out;
        out=fopen(out_file,"wb");
        FILE *files[runs];
        int input_buffer[runs][1000/runs];
        int pointers[runs];
	int i;
	for(i=0;i<runs;i++){
		   char buffer[50]="";
                        strcpy(buffer,input_file);
                        char x[10];
                        sprintf(x,".%03d",i);
                        strcat(buffer,x);
               
           
                files[i]=fopen(buffer,"rb");
                fread(input_buffer[i],sizeof(int),1000/runs,files[i]);
                pointers[i]=0;
        }
	
	int output_buffer[1000];
        int out_pointer=0;
        int empty_files=runs;
        int success_read[runs];
        for( i=0;i<runs;i++) success_read[i]=-1;

	while(empty_files >0){

                int max=-1,max_run=-1;
                for(i=0;i<runs;i++){
                                                                                                                                if(pointers[i]!=-1 && (max>input_buffer[i][pointers[i]] || max==-1)){
                                max=input_buffer[i][pointers[i]];
                                max_run=i;
                        }
		}

		pointers[max_run]++;
                if(pointers[max_run]==1000/runs || pointers[max_run]==success_read[max_run]){
                        if(success_read[max_run]!=0){

                                pointers[max_run]=0;
                                success_read[max_run]=fread(input_buffer[max_run],sizeof(int),1000/runs,files[max_run]);
                                if(success_read[max_run]==0){
                                        empty_files--;
                                        pointers[max_run]=-1;
                                        fclose(files[max_run]);
                                }

                        }

                }
		
		output_buffer[out_pointer]=max;
                out_pointer++;
                if(out_pointer==1000|| empty_files==0){
                        fwrite(output_buffer,sizeof(int),out_pointer,out);
                        out_pointer=0;
               		for(i=0;i<1000;i++)
                        	output_buffer[i]=0;
                //write it to output buffer and reset the output pointer
                //                //and clear the output buffer and last write may not contain 1000 elements
                }

            }

	fclose(out);		
}

int main(int argc,int *argv[]){

FILE *fp;
char *file1;
file1=argv[2]; 

	
	fp=fopen(file1,"rb");
	int input[1000];
	fseek(fp,0,SEEK_END);
	int size= ftell(fp)/sizeof(int);
	fseek(fp,0,SEEK_SET);
	int i;
	struct timeval tm,tm1;
        
	if(strcmp(argv[1],"--basic")==0){
		gettimeofday(&tm,NULL);
		int runs=size/1000;
		if(size%1000)runs++;
	 	if(size<1000){
		fread(input,sizeof(int),1000,fp);
		qsort((void *)input,size,sizeof(input[0]),comparator);
		 char buffer[50]="";
                        strcpy(buffer,argv[2]);
                        char x[10];
                        sprintf(x,".%03d",i);
                        strcat(buffer,x);
                        FILE *fp2;
			fp2=fopen(buffer,"wb");

                        fwrite(input,sizeof(int),size,fp2);
			fclose(fp2);
			fp2=fopen(argv[3],"wb");
			fwrite(input,sizeof(int),size,fp2);
			fclose(fp2);
			gettimeofday(&tm1,NULL);
        if(tm1.tv_usec-tm.tv_usec<0){
                tm1.tv_sec-=1;
                tm1.tv_usec+=1000000;                                                                                           }

        printf( "Time: %ld.%06ld", tm1.tv_sec-tm.tv_sec, tm1.tv_usec-tm.tv_usec );
			return 0;
		}	 
		for(i=0;i<runs;i++){
			FILE *fp1;
			fread(input,sizeof(int),1000,fp);	          //check if there are 1000 eleements
			qsort((void *)input,1000,sizeof(input[0]),comparator);
		
		
		
		
			char buffer[50]="";
			strcpy(buffer,argv[2]);
			char x[10];
			sprintf(x,".%03d",i);
			strcat(buffer,x);
			fp1=fopen(buffer,"wb");
			
			fwrite(input,sizeof(int),1000,fp1);
			fclose(fp1);
			
		}	
	
		fclose(fp);
		if(runs!=1)
		merge(runs,argv[3],argv[2]);
        	gettimeofday(&tm1,NULL);
		if(tm1.tv_usec-tm.tv_usec<0){
			tm1.tv_sec-=1;
			tm1.tv_usec+=1000000;
		}
		
		printf( "Time: %ld.%06ld", tm1.tv_sec-tm.tv_sec, tm1.tv_usec-tm.tv_usec );
	}
	else if(strcmp(argv[1],"--replacement")==0){
		
		gettimeofday(&tm,NULL);	
		 if(size<1000){
                fread(input,sizeof(int),1000,fp);
                qsort((void *)input,size,sizeof(input[0]),comparator);
                 char buffer[50]="";
                        strcpy(buffer,argv[2]);
                        char x[10];
                        sprintf(x,".%03d",i);
                        strcat(buffer,x);
                        FILE *fp2;
                        fp2=fopen(buffer,"wb");

                        fwrite(input,sizeof(int),size,fp2);
                        fclose(fp2);
                        fp2=fopen(argv[3],"wb");
                        fwrite(input,sizeof(int),size,fp2);
                        fclose(fp2);
        		gettimeofday(&tm1,NULL);
        if(tm1.tv_usec-tm.tv_usec<0){
                tm1.tv_sec-=1;
                tm1.tv_usec+=1000000;                                                                                           }

        printf( "Time: %ld.%06ld", tm1.tv_sec-tm.tv_sec, tm1.tv_usec-tm.tv_usec ); 
	               return 0;
                }
		int count=0;
		int num_runs=0;
		int prim_heap[750],sec_heap[750], buff[250];
		int buf_pointer=0,success_read=-1,out_pointer=0,sec_pointer=0;
		fread(prim_heap,sizeof(int),750,fp);
		heapsort(prim_heap,750);
		int prim_heap_size=750;
		int out_size=750;
		int *out_buffer;
		out_buffer= (int *)malloc(750* sizeof(int));
		fread(buff,sizeof(int),250,fp);
		while(success_read!=0){
	
			if(prim_heap[0]<=buff[buf_pointer]){
			
				out_buffer[out_pointer]=prim_heap[0];
				out_pointer++;
				prim_heap[0]=buff[buf_pointer];
				buf_pointer++;
				heapify(prim_heap,prim_heap_size,0);
			}
			else{
	     			out_buffer[out_pointer]=prim_heap[0];
	     			out_pointer++;
	     			prim_heap[0]= prim_heap[prim_heap_size-1];	
	     			sec_heap[sec_pointer]=buff[buf_pointer];
	    			buf_pointer++;
	     			sec_pointer++;
	     			prim_heap_size--;
	     			heapify(prim_heap,prim_heap_size,0);
			}
	
			if(out_pointer==out_size){
				out_size=out_size+100;
				out_buffer=realloc(out_buffer,out_size*(sizeof(int)));
			}	
			
			if(prim_heap_size==0){
	
				char file[15];
				count++;
				   char buffer[50]="";
                        	  strcpy(buffer,argv[2]);
                       		 char x[10];
                        	sprintf(x,".%03d",num_runs);
                        	strcat(buffer,x);
                        
				
				num_runs++;
				FILE *out;
				out=fopen(buffer,"wb");
				fwrite(out_buffer,sizeof(int),out_pointer,out);
				fclose(out);
				out_size=750; 
				out_buffer=realloc(out_buffer,out_size*(sizeof(int)));
				prim_heap_size=sec_pointer;
				sec_pointer=0;
				out_pointer=0;
				int j=0;
				for(;j<prim_heap_size;j++)
					prim_heap[j]=sec_heap[j];
				heapsort(prim_heap,prim_heap_size);
				
				}
			if(buf_pointer==250){
				success_read=fread(buff,sizeof(int),250,fp);
				buf_pointer=0;
			}	
	
	
	

		}
	 
                 char buffer[50]="";
                        strcpy(buffer,argv[2]);
                        char x[10];
                        sprintf(x,".%03d",num_runs);
                        strcat(buffer,x);
                             
		num_runs++;
	 
		while(prim_heap_size>0){
			out_buffer[out_pointer]=prim_heap[0];                                           			out_pointer++;  
		
		 if(out_pointer==out_size){
			out_size=out_size+100;
			out_buffer=realloc(out_buffer,out_size*(sizeof(int)));
        	}
		prim_heap[0]=prim_heap[prim_heap_size-1];
		prim_heap_size--;
		heapify(prim_heap,prim_heap_size,0);
				 
	}
		 FILE *out;
		 out=fopen(buffer,"wb");
                   fwrite(out_buffer,sizeof(int),out_pointer,out);
                  fclose(out);
		 out_pointer=0;   	
		 out_buffer=realloc(out_buffer,750*(sizeof(int)));
		heapsort(sec_heap,sec_pointer);
		while(sec_pointer>0){ 
		 out_buffer[out_pointer]=sec_heap[0];
                 out_pointer++;
      		sec_heap[0]=sec_heap[sec_pointer-1];
                sec_pointer--;
                heapify(sec_heap,sec_pointer,0);                                                    
        }
		     char buffer1[50]="";
                        strcpy(buffer1,argv[2]);
                        char x1[10];
                        sprintf(x1,".%03d",num_runs);
                        strcat(buffer1,x1);
                        
                num_runs++;
		 out=fopen(buffer1,"wb");                                                                                   fwrite(out_buffer,sizeof(int),out_pointer,out);
                  fclose(out);
	
				
	merge(num_runs,argv[3],argv[2]);
	gettimeofday(&tm1,NULL);
	if(tm1.tv_usec-tm.tv_usec<0){
		tm1.tv_sec-=1;
		tm1.tv_usec+=1000000;
	}

	printf( "Time: %ld.%06ld", tm1.tv_sec-tm.tv_sec, tm1.tv_usec-tm.tv_usec );
	}
	

	else if(strcmp(argv[1],"--multistep")==0){
		gettimeofday(&tm,NULL);
		 if(size<1000){
                fread(input,sizeof(int),1000,fp);
                qsort((void *)input,size,sizeof(input[0]),comparator);
                 char buffer[50]="";
                        strcpy(buffer,argv[2]);
                        char x[10];
                 	strcat(buffer,".super");
		        sprintf(x,".%03d",i);
                        strcat(buffer,x);
                        FILE *fp2;
                        fp2=fopen(buffer,"wb");

                        fwrite(input,sizeof(int),size,fp2);
                        fclose(fp2);
                        fp2=fopen(argv[3],"wb");
                        fwrite(input,sizeof(int),size,fp2);
                        fclose(fp2);
			gettimeofday(&tm1,NULL);
       			 if(tm1.tv_usec-tm.tv_usec<0){
                	tm1.tv_sec-=1;
        	        tm1.tv_usec+=1000000;                                                                                           }
	
        printf( "Time: %ld.%06ld", tm1.tv_sec-tm.tv_sec, tm1.tv_usec-tm.tv_usec );	
                        return 0;
                }

		int runs=size/1000;
		if(size%1000)runs++;
	
		for(i=0;i<runs;i++){

			fread(input,sizeof(int),1000,fp);	          //check if there are 1000 eleements
			qsort((void *)input,1000,sizeof(input[0]),comparator);
			FILE *fp1;
			char buffer1[50]="";
                        strcpy(buffer1,argv[2]);
                        char x1[10];
                        sprintf(x1,".%03d",i);
                        strcat(buffer1,x1); 
			
			fp1=fopen(buffer1,"wb");
			fwrite(input,sizeof(int),1000,fp1);
			fclose(fp1);
		}	
	
		fclose(fp);
	int super_runs=runs/15;
	if(runs%15!=0) super_runs++;
	
	for(i=0;i<super_runs;i++) {
	int num_runs= 15;
	if((i+1)*15>runs)
		num_runs=runs- i*15;

	FILE *out;
	
	char buffer1[50]="";
                        strcpy(buffer1,argv[2]);
                        char x1[10];
			strcat(buffer1,".super");
                        sprintf(x1,".%03d",i);
                        strcat(buffer1,x1); 
	
       //	merge(num_runs,buffer);}
	 
	out=fopen(buffer1,"wb");
        FILE *files[num_runs];
        int input_buffer[num_runs][1000/num_runs];
        int pointers[num_runs];	
	int k;
	for(k=i*15;k<i*15+num_runs;k++){
             
		char buffer1[50]="";
                        strcpy(buffer1,argv[2]);
                        char x1[10];
                        sprintf(x1,".%03d",k);
                        strcat(buffer1,x1); 
	//	sprintf(buffer1,"input.bin.%03d",k);
                files[k%15]=fopen(buffer1,"rb");
                fread(input_buffer[k%15],sizeof(int),1000/num_runs,files[k%15]);
                pointers[k%15]=0;
	 	}
		
	int output_buffer[1000];
	int out_pointer=0;
	int empty_files=num_runs;
	int success_read[num_runs];
	for( k=0;k<num_runs;k++) success_read[k]=-1;
	while(empty_files>0){

		int max=-1,max_run=-1;
		for(k=0;k<num_runs;k++){
			if(pointers[k]!=-1 &&(max>input_buffer[k][pointers[k]] || max==-1 )){
				max=input_buffer[k][pointers[k]];
				max_run=k;	
			}
		}
	
		pointers[max_run]++;
		if(pointers[max_run]==1000/num_runs|| pointers[max_run]==success_read[max_run]){
	
			if(success_read[max_run]!=0){
				pointers[max_run]=0;
			success_read[max_run]=fread(input_buffer[max_run],sizeof(int),1000/num_runs,files[max_run]);
                                
				if(success_read[max_run]==0){
                                       
					empty_files--;
                                        pointers[max_run]=-1;
                                        fclose(files[max_run]);
                                }
	
			}
	
		}
		output_buffer[out_pointer]=max;                                                                         out_pointer++;
                if(out_pointer==1000 || empty_files==0){
                        fwrite(output_buffer,sizeof(int),out_pointer,out);
              		 
                	out_pointer=0;

                	for(k=0;k<1000;k++)
                        	output_buffer[k]=0;
                //write it to output buffer and reset the output pointer
                //                //and clear the output buffer and last write may not contain 1000 elements
                //                                }	
	
		}	

	
	}
	
	
	
	
	fclose(out);		
	}


	//creating super runs completed
	FILE *out;	
	out=fopen(argv[3],"wb");
	FILE *files1[super_runs];	
	int input_buffer1[super_runs][1000/super_runs];
	int pointers1[super_runs];
	for(i=0;i<super_runs;i++){
		
		char buffer1[50]="";
                        strcpy(buffer1,argv[2]);
                        char x1[10];
			strcat(buffer1,".super");
                        sprintf(x1,".%03d",i);
                        strcat(buffer1,x1); 
                  
		files1[i]=fopen(buffer1,"rb");
		fread(input_buffer1[i],sizeof(int),1000/super_runs,files1[i]);
		pointers1[i]=0;
	}
	
	int output_buffer[1000];
	int out_pointer=0;
	int empty_files=super_runs;
	int success_read[super_runs];
	for( i=0;i<super_runs;i++) success_read[i]=-1;
	while(empty_files >0){
		int max=-1,max_run=-1;
		for(i=0;i<super_runs;i++){
			//max shouldn't be initialized to -1
			if(pointers1[i]!=-1 
&& (max>input_buffer1[i][pointers1[i]] || max==-1)){
				max=input_buffer1[i][pointers1[i]];
				max_run=i;	
			}
		
			
		}
		
		pointers1[max_run]++;
		if(pointers1[max_run]==1000/super_runs || pointers1[max_run]==success_read[max_run]){
			if(success_read[max_run]!=0){

				pointers1[max_run]=0;
				success_read[max_run]=fread(input_buffer1[max_run],sizeof(int),1000/super_runs,files1[max_run]);
				if(success_read[max_run]==0){
					empty_files--;
					pointers1[max_run]=-1;
					fclose(files1[max_run]);
				}
				
				
			}

		}
		output_buffer[out_pointer]=max;
		out_pointer++;
		if(out_pointer==1000){
			fwrite(output_buffer,sizeof(int),1000,out);
		out_pointer=0;
	
		for(i=0;i<1000;i++)
			output_buffer[i]=0;
		//write it to output buffer and reset the output pointer
		//and clear the output buffer and last write may not contain 1000 elements
		}
	
	}
	fclose(out);
	gettimeofday(&tm1,NULL);
	if(tm1.tv_usec-tm.tv_usec<0){
		tm1.tv_sec-=1;
		tm1.tv_usec+=1000000;
	}

	printf( "Time: %ld.%06ld", tm1.tv_sec-tm.tv_sec, tm1.tv_usec-tm.tv_usec );		
	}	
	return 0;	

}



