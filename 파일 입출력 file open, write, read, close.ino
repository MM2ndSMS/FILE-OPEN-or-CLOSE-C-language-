## filename

FILE *f;
f = fopen("c:\\work\\test.txt", "r+b");
if (f == NULL){
  printf("file open error\n");
}

## char *fputs(const char *str, FILE *stream)

FILE *f;
char *str = "this is string";

f = fopen("fputs_test.txt\n", "wt");
if(f != NULL) {
  fputs(str, f); 
  fclose(f);
}

## char *fgets(char *buf, int size, FILE *stream)

FILE *f;
char buffer[256];
f = fopen("fgets_test.txt", "rt");
if(f != NULL) {
  while(fgets(buffer, 256, f) != NULL) {
  }
  fclose(f);
}

## test1.dat의 내용을 읽어와서 test2.dat를 새로 만들어 복사하는 과정

FILE *f1, *f2;
char buf[256];
int nRead;

f1 = fopen("test1.dat", "rb");
if(f1 != NULL) {
    f2 = fopen("test2.dat", "wb");
    if(f2 != NULL) {
       while(!feof(f1)) {
          nRead = fread(buf, 1, 256, f1);
          fwrite(buf, 1, nRead, f2);
       }
      fclose(f2);
    }
  fclose(f1);
}

## int fseek(FILE *stream, long offset, int origin)

FILE *f;
char buf[100];
f = fopen("test.dat", "rb");
if(f !=NULL) {
  fseek(f, -100, SEEK_END);
  fread(buf, 1, 100, f);
  fclose(f);
} 
