/*
struct compute_information
{
int hostname;
int num_tested;
int current_range;
}
*/

struct message {
int type;

union {
  int per_num;
  int value;
  int current_range[2];
      } data;

} msg;

struct map_host
{       
char flag;
char hostname[30];
};

