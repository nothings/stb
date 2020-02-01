#define STB_DEFINE
#include "stb.h"

// true if no error
int run_command(char *batch_file, char *command)
{
   char buffer[4096];
   if (batch_file[0]) {
      sprintf(buffer, "%s && %s", batch_file, command);
      return system(buffer) == 0;
   } else {
      return system(command) == 0;
   }
}

typedef struct
{
   char *compiler_name;
   char *batchfile;
   char *objdir;
   char *compiler;
   char *args;
   char *link;
} compiler_info;

compiler_info *compilers;
char *shared_args;
char *shared_link;

typedef struct
{
   char *filelist;
} project_info;

project_info *projects;

enum { NONE, IN_COMPILERS, IN_ARGS, IN_PROJECTS, IN_LINK };

int main(int argc, char **argv)
{
   int state = NONE;
   int i,j,n;
   char **line;
   if (argc != 2) stb_fatal("Usage: stb_build_matrix {build-file}\n");
   line = stb_stringfile(argv[1], &n);
   if (line == 0) stb_fatal("Couldn't open file '%s'\n", argv[1]);

   for (i=0; i < n; ++i) {
      char *p = stb_trimwhite(line[i]);
      if (p[0] == 0) continue;
      else if (p[0] == '#') continue;
      else if (0 == stricmp(p, "[compilers]")) { state = IN_COMPILERS;                     }
      else if (0 == stricmp(p, "[args]"     )) { state = IN_ARGS     ; shared_args = NULL; }
      else if (0 == stricmp(p, "[projects]" )) { state = IN_PROJECTS ;                     }
      else if (0 == stricmp(p, "[link]"     )) { state = IN_LINK     ; shared_link = NULL; }
      else {
         switch (state) {
            case NONE: stb_fatal("Invalid text outside section at line %d.", i+1);
            case IN_COMPILERS: {
               char buffer[4096];
               int count;
               compiler_info ci;
               char **tokens = stb_tokens_stripwhite(p, ",", &count), *batch;
               if (count > 3) stb_fatal("Expecting name and batch file name at line %d.", i+1);
               batch = (count==1 ? tokens[0] : tokens[1]);
               if (strlen(batch)) 
                  sprintf(buffer, "c:\\%s.bat", batch);
               else
                  strcpy(buffer, "");
               ci.compiler_name = strdup(tokens[0]);
               ci.batchfile     = strdup(buffer);
               ci.compiler      = count==3 ? strdup(tokens[2]) : "cl";
               if (0==strnicmp(batch, "vcvars_", 7))
                  ci.objdir     = strdup(stb_sprintf("vs_%s_%d", batch+7, i));
               else
                  ci.objdir     = strdup(stb_sprintf("%s_%d", batch, i));
               ci.args = shared_args;
               ci.link = shared_link;
               stb_arr_push(compilers, ci);
               break;
            }
            case IN_ARGS: {
               stb_arr_push(shared_args, ' ');
               for (j=0; p[j] != 0; ++j)
                  stb_arr_push(shared_args, p[j]);
               break;
            }
            case IN_LINK: {
               stb_arr_push(shared_link, ' ');
               for (j=0; p[j] != 0; ++j)
                  stb_arr_push(shared_link, p[j]);
               break;
            }
            case IN_PROJECTS: {
               project_info pi;
               pi.filelist = strdup(p);
               stb_arr_push(projects, pi);
               break;
            }
         }
      }
   }

   _mkdir("obj");
   for (j=0; j < stb_arr_len(compilers); ++j) {
      char command[4096];
      for (i=0; i < stb_arr_len(projects); ++i) {
         int r;
         _mkdir(stb_sprintf("obj/%s", compilers[j].objdir));
         if (stb_suffix(compilers[j].compiler, "cl"))
            sprintf(command, "%s %.*s %s /link %.*s",
                                     compilers[j].compiler,
                                     stb_arr_len(compilers[j].args), compilers[j].args,
                                     projects[i].filelist,
                                     stb_arr_len(compilers[j].link), compilers[j].link);
         else
            sprintf(command, "%s %.*s %s %.*s",
                                     compilers[j].compiler,
                                     stb_arr_len(compilers[j].args), compilers[j].args,
                                     projects[i].filelist,
                                     stb_arr_len(compilers[j].link), compilers[j].link);
         r = run_command(compilers[j].batchfile, command);
         stbprint("{%c== Compiler %s == Building %s}\n", r ? '$' : '!', compilers[j].compiler_name, projects[i].filelist);
         stb_copyfile("a.exe", stb_sprintf("obj/%s/a.exe", compilers[j].objdir));
         //printf("Copy: %s to %s\n", "a.exe", stb_sprintf("obj/%s/a.exe", compilers[j].objdir));
         stb_copyfile("temp.exe", stb_sprintf("obj/%s/temp.exe", compilers[j].objdir));
         system("if EXIST a.exe del /q a.exe");
         system("if EXIST temp.exe del /q temp.exe");
         system("if EXIST *.obj del /q *.obj");
         system("if EXIST *.o del /q *.o");
         if (!r)
            return 1;
      }
   }

   return 0;
}
