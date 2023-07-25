#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    uid_t user_id;
    gid_t group_id;
    struct passwd *user_info;

    user_id = getuid();
    group_id = getgid();

    printf("User is %s\n", getlogin());

    printf("User IDs: uid=%d, gid=%d\n", user_id, group_id);

    user_info = getpwuid(user_id);
    printf("UID passwd entry:\n name=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
           user_info->pw_name, user_info->pw_uid, user_info->pw_gid, user_info->pw_dir, user_info->pw_shell);

    user_info = getpwnam("root");
    printf("root passwd entry:\n");
    printf("name=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
           user_info->pw_name, user_info->pw_uid, user_info->pw_gid, user_info->pw_dir, user_info->pw_shell);
    
    exit(0);
}

