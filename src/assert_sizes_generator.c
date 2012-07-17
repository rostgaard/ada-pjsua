/**
 * assert_sizes_generator.c
 *
 * Generates an Ada spec from the C files
 */

#include <pjsua-lib/pjsua.h>
#include <pj/types.h>
#include <stdio.h>
#include <limits.h>


#define indention_size 3
#define indention_char ' '

static int indention_level = 0;
char buffer[256] = "\0";

void usage (char *program_name) {
  printf ("Usage: %s <Ada package name>\n",program_name);
}

void new_line() {
  printf("\n");

}

void indention_print (char *string) {
  int i;
  for ( i=0; i < indention_level; i++) {
    int j;
    for (j=0; j < indention_size; j++) {
      printf("%c",indention_char);
    }
  }

  printf("%s",string);
  printf("\n");
}

void add_constant(char *name, int size) {
  sprintf(buffer,"%s : constant Natural := %d;",name , size);
  indention_print (buffer);
}

int main(int argc, char *argv[])
{
  if (argc < 2) {
    usage(argv[0]);
    exit(1);
  }

  /* Header */
  indention_print("-- This file is autogenerated, please do not make changes to it");


  sprintf(buffer,"package %s is",argv[1]);
  indention_print(buffer);
  indention_level++;

  /* Start by defining the size of a byte */
  sprintf(buffer,"Byte_Size : constant Natural := %d;",CHAR_BIT);
  indention_print(buffer);
  
  new_line();

  pjsua_logging_config log_cfg;
  add_constant("Logging_Config_Type_Size",sizeof log_cfg);

  pj_str_t str;
  add_constant("String_T_Size",sizeof str);
  
  pj_time_val time_val;
  add_constant("Time_Value_Type_Size", sizeof time_val);

  pjsua_acc_id acc_id;
  add_constant("Account_Info_Type_Size", sizeof acc_id);
  
  pjsua_call_info call_info;
  add_constant("Call_Info_Type_Size", sizeof call_info);

  pjsua_config cfg;
  add_constant("Config_Type_Size", sizeof cfg);
  
  pjsip_host_info host_info;
  add_constant("Host_Info_Type_Size", sizeof host_info);
  
  pjsua_transport_config transport_cfg;
  add_constant("Transport_Config_Type_Size", sizeof transport_cfg);

  /* End the file */
  new_line();

  indention_level--;
  sprintf(buffer,"end %s;",argv[1]);
  indention_print(buffer);
  exit(0);
}

