#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<stdio.h>

// 2). Implementation of basic ls functionality.

int main(){

    char buf[1000];
    char* ans;

    //get currunt working directory
    ans = getcwd(buf,sizeof(buf));

    // open dir 
    DIR* d = opendir(ans);

    // struct dirent refers to directory entry.

    // struct dirent {
    //     ino_t          d_ino;       /* inode number */
    //     off_t          d_off;       /* offset to the next dirent */
    //     unsigned short d_reclen;    /* length of this record */
    //     unsigned char  d_type;      /* type of file; not supported
    //                                 by all file system types */
    //     char           d_name[256]; /* filename */
    // };
    struct dirent* de;

    printf("%s\n",ans);
    while(de = readdir(d)){
        if(de->d_name[0] == '.') continue;
        printf("%s\n",de->d_name);
    }

    return 0;
}