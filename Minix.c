#include <ctype.h>
#include <time.h>
#include <linux/minix_fs.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>


#define __BLOCK_SIZE 1024
#define __DIR_ENT_SIZE 32
#define __DEFAULT_PATH "imagefile.img"

void permissionString(unsigned short mode, char* holdingCell);
void nodeSeek(int inode, int firstInode);
void showsuper();
void minimount(char* fname);
void miniumount();
void traverse(char* flag);
void showzone(int zone_num);
void showfile(char *fname);
int parse(char* input);
int fd = -1;
int zone_num = -1;
char* fname;
char* FLAG;
void help();


//mikes

void help() {
    fprintf(stdout, "The available minix commands are:\n");
    fprintf(stdout, "    help                    - show the commands list.\n");
    fprintf(stdout, "    minimount argument      - mount a local minix disk\n");
    fprintf(stdout, "    miniumount              - umount the mounted minix disk\n");
    fprintf(stdout, "    showsuper               - to list the information of the super block\n");
    fprintf(stdout, "    traverse [-l]           - list the content in the root directory. Optional -l flag gives a long listing of the root directory.\n");
    fprintf(stdout, "    showzone [zone number]  - show the ASCII content of the specified zone number\n");
    fprintf(stdout, "    showfile                - show the content of the target file in the hex dump\n");
}



void permissionString(unsigned short mode, char* holdingCell) {
	
    // print the permission bits
    holdingCell[0] = (mode & S_IFDIR) ? 'd' : '-';
    holdingCell[1] = (mode & S_IRUSR) ? 'r' : '-';
    holdingCell[2] = (mode & S_IWUSR) ? 'w' : '-';
    holdingCell[3] = (mode & S_IXUSR) ? 'x' : '-';
    holdingCell[4] = (mode & S_IRGRP) ? 'r' : '-';
    holdingCell[5] = (mode & S_IWGRP) ? 'w' : '-';
    holdingCell[6] = (mode & S_IXGRP) ? 'x' : '-';
    holdingCell[7] = (mode & S_IROTH) ? 'r' : '-';
    holdingCell[8] = (mode & S_IWOTH) ? 'w' : '-';
    holdingCell[9] = (mode & S_IXOTH) ? 'x' : '-';
    holdingCell[10] = '\0';

}

void nodeSeek(int inode, int firstInode) {
    lseek(fd, firstInode + (inode-1)*sizeof(struct minix_inode), SEEK_SET);
}


/**
 * Mounts a Minix disk image from the path given by img.
 * @param img A path to a Minix disk image.
 * @returns SUCCESS on successful mount, FAILURE otherwise.
 */
void minimount(char* fname){
    if ((fd = open(fname,O_RDONLY)) >= 0) { //read only
        return;
    } else {
        fprintf(stdout, "The file was not found\n");
        return;
    }
}

/**
 * Unmounts a mounted disk image.
 * @returns SUCCESS on successful dismount, FAILURE otherwise.
 */
void miniumount() {
    if(fd < 0) {
        //print error
        fprintf(stdout, "No file has been mounted.\n");
        return;
    }
    close(fd);
    fd = -1;
    return;
}


void showsuper() {     
    int boot = __BLOCK_SIZE;    //Boot block
    if(fd < 0) {
        //print error
    	fprintf(stdout, "Cannot find super.\n");
        return;
    }
    struct minix_super_block* messageBuf = (struct minix_super_block*)malloc(sizeof(struct minix_super_block));
    lseek(fd, boot, SEEK_SET); 



    read(fd, messageBuf, sizeof(struct minix_super_block));
    fprintf(stdout, "Number of inodes: %d\n", messageBuf->s_ninodes);
    fprintf(stdout, "Number of zones: %d\n", messageBuf->s_nzones);
    fprintf(stdout, "Number of imap_blocks: %d\n", messageBuf->s_imap_blocks);
    fprintf(stdout, "Number of zmap_blocks: %d\n", messageBuf->s_zmap_blocks);
    fprintf(stdout, "First data zone: %d\n", messageBuf->s_firstdatazone);
    fprintf(stdout, "Log zone size: %d\n", messageBuf->s_log_zone_size);
    fprintf(stdout, "Max size: %d\n", messageBuf->s_max_size);
    fprintf(stdout, "Magic: %d\n", messageBuf->s_magic);
    fprintf(stdout, "State: %d\n", messageBuf->s_state);
    fprintf(stdout, "Zones: %d\n", messageBuf->s_zones);

    lseek(fd, 0, SEEK_SET);
    free(messageBuf);
}

//Contains super block information

void traverse(char* flag) {
    	if (fd < 0) {
        fprintf(stdout, "Cannot transverse\n");
        //exits program if the input was incorrect
    }
    //locate the superblock
    lseek(fd, __BLOCK_SIZE, SEEK_SET);   
    struct minix_super_block* messageBuf = (struct minix_super_block*)malloc(sizeof(struct minix_super_block));
    read(fd, messageBuf, sizeof(struct minix_super_block));    
    //Read the SuperBlock
    int firstINode = __BLOCK_SIZE*(messageBuf->s_imap_blocks + messageBuf->s_zmap_blocks + 2);
    lseek(fd, firstINode, SEEK_SET);//Move to first inode
    struct minix_inode* root = (struct minix_inode*)malloc(sizeof(struct minix_inode));
    read(fd, root, sizeof(struct minix_inode)); //Read the first inode
    int ls, r, loc;
    struct minix_inode* tmpNode = (struct minix_inode*)malloc(sizeof(struct minix_inode)); 
    char* permissions = (char*)malloc(sizeof(char)*11);
    struct minix_dir_entry* dir = (struct minix_dir_entry*)malloc(__DIR_ENT_SIZE);
    if(flag == NULL) {
        //Go to the block where the root's data is stored
        ls = lseek(fd, __BLOCK_SIZE*root->i_zone[0], SEEK_SET); 
        //Read each directory entry
        r = read(fd, dir, __DIR_ENT_SIZE);
        while(dir->inode != 0) {
            if((strcmp(dir->name, ".") != 0) && (strcmp(dir->name, "..") != 0)) {
            	fprintf(stdout, "%s\n", dir->name);
            }
            r = read(fd, dir, __DIR_ENT_SIZE);
        }
    } else if(!strcmp(flag, "-l")) {
        loc = ls = lseek(fd, __BLOCK_SIZE*root->i_zone[0], SEEK_SET);
        //Read each directory entry
        r = read(fd, dir, __DIR_ENT_SIZE);
        while(dir->inode != 0) {
            loc = loc + r;  
            //Stores the current location
            lseek(fd, firstINode + (dir->inode-1)*sizeof(struct minix_inode), SEEK_SET);   
            //lseek to the first inode
            read(fd, tmpNode, __DIR_ENT_SIZE); 
            //Read the node
            lseek(fd, loc, SEEK_SET);    
            if((strcmp(dir->name, ".") != 0) && (strcmp(dir->name, "..") != 0)) {
                
                permissionString(tmpNode->i_mode, permissions);
                fprintf(stdout, "%s\t", permissions);
                fprintf(stdout, "%u\t", tmpNode->i_uid);
                fprintf(stdout, "%u\t", tmpNode->i_size);
                //Convert the time from seconds to date
		time_t modTime = tmpNode->i_time;
                fprintf(stdout, "%.6s%.5s\t", 4+ctime(&modTime) ,19+ctime(&modTime)); 
                // time conversion
                printf("%s\n", dir->name);
            }
            r = read(fd, dir, __DIR_ENT_SIZE);
            //read the file & its size
        }

    } else {
        fprintf(stdout, "Transverse not found\n");
    }

    lseek(fd, 0, SEEK_SET);
    free(permissions);
    free(tmpNode);
    free(dir);
    free(root);
    free(messageBuf);
    return;
}
// This is where the ASCII content will be shown from the zone number 
/**
 * Shows zone information on a given zone number.
 * @param zonenumber A zonenumber from the mounted image.
 * @returns SUCCESS if the zone was read suceesfully, FAILURE otherwise.
 */
void showzone(int zone_num) {
    if(fd < 0) {
        fprintf(stdout, "Cannot find zone\n");
    }
    lseek(fd, __BLOCK_SIZE*zone_num, SEEK_SET); //Get to zone number

    char* hold = (char*)malloc(sizeof(char)*16);
    fprintf(stdout, "\t");
    for(int i = 0; i < 16; i++) {
        fprintf(stdout, "%x ", i);
    }
    fprintf(stdout, "\n");
    for(int i = 0; i < __BLOCK_SIZE; i = i + 16) {  
        //every line should be incremented by 16 
        read(fd, hold, __DIR_ENT_SIZE/2);
        fprintf(stdout, "%x\t", i);
        for(int j = 0; j < 16; j++) {
            if(isprint(hold[j])) { 
                // excludes inodes  
                fprintf(stdout, "%c ", hold[j]);
            } else {
                fprintf(stdout, "  ");
            }
        }
        printf("\n");
    }
    free(hold);
    return;
}

//exits if the file is not found
//void findFile(char *fname, int inode, int firstInode) retun type error because the names have to match
int findFile(char *fname, int inode, int firstInode) {
    int fileInumber = -1;
    struct minix_dir_entry* dir = (struct minix_dir_entry*)malloc(__DIR_ENT_SIZE);
    lseek(fd, firstInode + (inode-1)*sizeof(struct minix_inode), SEEK_SET);
    struct minix_inode* tmpNode = (struct minix_inode*)malloc(sizeof(struct minix_inode));
    read(fd, tmpNode, sizeof(struct minix_inode));
    int ls = lseek(fd, tmpNode->i_zone[0]*__BLOCK_SIZE, SEEK_SET);
    //lseek to inodes in the directory
    int r;
    int loc = ls;
    struct minix_inode* dirNode = (struct minix_inode*)malloc(sizeof(struct minix_inode));
    //Tries to locate the dir entry 
    for(int i = 0; i < __BLOCK_SIZE; i = i + __DIR_ENT_SIZE) {
        r = read(fd, dir, __DIR_ENT_SIZE);
        loc = loc + r;
        nodeSeek(dir->inode, firstInode);
        read(fd, dirNode, sizeof(struct minix_inode));
        lseek(fd, loc, SEEK_SET);
        if(dir->inode == 0) {
            break;
        }
        if((dir->inode != inode) && (strcmp(dir->name, ".")) && (strcmp(dir->name, ".."))) {
            //search the directory
            if(((dirNode->i_mode & S_IFDIR) ? 1 : 0)){
                fileInumber = findFile(fname, dir->inode, firstInode);
                lseek(fd, loc, SEEK_SET);
            } else {
                if(!strcmp(fname, dir->name)) {
                    fileInumber = dir->inode;
                    break;
                }
            }
        }
    }
    free(dirNode);
    free(dir);
    free(tmpNode);
    return fileInumber;
}

/**
 * Shows the contents of a file in the root directory of the mounted Minix image.
 * @param filename A filename frm the root directory of the image.
 * @returns SUCCESS if the file was read successfully, FAILURE otherwise.
 */

void showfile(char *fname) {

    if(fd < 0)  {
        fprintf(stdout, "Cannot find file\n");
        ;
    }

    if(fname == NULL) {
        fprintf(stdout, "File not found\n");
      
    }
    /* Steps needed to implement this method:
     * 1.) Grab the root inode
     * 2.) Starting at the first zone (dir)...
     *  a.) Read in the entire block representing the zone
     *  b.) Convert every 32 bytes to a minix_dir_entry and check the name
     *  c.) If the name mathces the given filename then go to step 3
     *  d.) Otherwise repeat until all direntries have been checked
     *  e.) If not found advance to the next zone
     * 3.) Assuming we found the minix_dir_entry corresponding to the given filename:
     *  a.) Grab the inode from the filesystem
     *  b.) Starting at the first file zone
     *   i.) Grab the entire block representing the zone
     *   ii.) Print out the zone as hex
     * 4.) If the filename is not found, then print out a message saying so
     */
  
    struct minix_inode* tmpNode = (struct minix_inode*)malloc(sizeof(struct minix_inode));  //Used for temporary inode in -l
     
    //hex dump
    //reads the superblock & moves to the first inode 
    lseek(fd, __BLOCK_SIZE, SEEK_SET);    
    struct minix_super_block* messageBuf = (struct minix_super_block*)malloc(sizeof(struct minix_super_block));
    read(fd, messageBuf, sizeof(struct minix_super_block));
    
    int firstInode = __BLOCK_SIZE*(messageBuf->s_imap_blocks + messageBuf->s_zmap_blocks + 2);
    lseek(fd, firstInode, SEEK_SET);

    int inumber = findFile(fname, 1, firstInode);
    if(inumber == -1) {
        fprintf(stdout, "File error, please try again\n");
        return;
    }
    nodeSeek(inumber, firstInode);
    read(fd, tmpNode, sizeof(struct minix_inode));

    char* data = (char*)malloc(sizeof(char)*16);
    fprintf(stdout, "File name: %s\n", fname);
    for(int i = 0; i < 7; i++) {  
        if(tmpNode->i_zone[i] == 0) {
            break;
        }
        //relocate nodes 
        lseek(fd, (tmpNode->i_zone[i])*__BLOCK_SIZE, SEEK_SET); 
        for(int j = 0; j < __BLOCK_SIZE; j = j + 16) {  //16 per line
            read(fd, data, 16);
            for(int q = 0; q < 16; q++) {
            	fprintf(stdout, " ");
                fprintf(stdout, "%02x ", data[q]);
            }
            fprintf(stdout, "\n");
        }
    }

    //free varibles
    free(data);
    free(tmpNode);
    free(messageBuf);
    return;
}


//zone_num AND fname AND FLAG CHANGED HERE
int parse(char* input) {
    int maxArgs = 10; //arbitrary maximum tokens should never even come close to 10 args
    int option = -1;    //returns different id based on the input given

    char* tokens[maxArgs];
    int i = 0;
    char* cmd = strtok(input, " ");
    while((tokens[i] = strtok(NULL, " ")) != NULL) {
        i++;
        if(i >= maxArgs) {
            return -1;
        }
    }

    if(!strcmp(cmd, "help")) {
        option = 0;
        //no args
    } else if(!strcmp(cmd, "minimount")) {
        option = 1;
        //First token is filepath
        if(tokens[0] == NULL) {
            fname = __DEFAULT_PATH;
        } else {
            fname = tokens[0];
        }
    } else if(!strcmp(cmd, "miniumount")) {
        option = 2;
        //no args
    } else if(!strcmp(cmd, "showsuper")) {
        option = 3;
        //no args
    } else if(!strcmp(cmd, "traverse")) {
        option = 4;
        //First token is flag
        FLAG = tokens[0];
        //Second token is filepath. Don't actually need but why not?
    } else if(!strcmp(cmd, "showzone")) {
        option = 5;
        //First token is actually an int << Zone number
        zone_num = atoi(tokens[0]);
    } else if(!strcmp(cmd, "showfile")) {
        option = 6;
        //First token is a filepath
        fname = tokens[0];
    } else if(!strcmp(cmd, "quit")) {
        option = 7;
        //no args
    }

    return option;
}

int main(void) {
    int breakout = 1;
    //int command
    char* input = malloc(sizeof(char)*4096);   //4K char limit
    int option = -1;
    fprintf(stdout, "Enter 'help' for command options.\n");
    while(breakout) {
        fprintf(stdout, "Minix Command: ");
        //fgets(input, 50, stdin); //reads line
        //sscanf(input, "%s", command);
        scanf("%[^\n]%*c", input); 
        option = parse(input);
        if (option == 0)
                help();
              //if (strcmp("help", command) == 0) {
			 //help();
        else if (option == 1){
                //grabs minimount function
                minimount(fname);
        }
        else if (option == 2){
                miniumount();
        }
        else if (option == 3){
                showsuper();
        }
        else if (option == 4){
                traverse(FLAG);
        }
        else if (option == 5){
                showzone(zone_num);
        }
        else if (option == 6){
                showfile(fname);
        }
        else if (option == 7){
                //if (strcmp("quit", command) == 0) {
                breakout = 0;
        }
        else{
                fprintf(stdout, "Error, please try again\n");
                //Invalid input
        }
        }
    
    if(fd != -1) {
        miniumount();
    }
    free(input);
    return 1;
}
