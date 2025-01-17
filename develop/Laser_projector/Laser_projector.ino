#define ledpin 15 // GPIO1/TXD01
#define step_x 1 //
#define dir_x 3 //
#define step_y 13
#define dir_y 12
#define button 16

const int count = 5;
int work_status = 1;
int level_x = HIGH;
int level_y = HIGH;
int duration = 48;

// int a[18][32] = {
//   {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//   {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
//   {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
// };
int a[18][32] = {

  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};



void setup() {

pinMode(step_x, OUTPUT);
pinMode(dir_x, OUTPUT);

pinMode(step_y, OUTPUT);
pinMode(dir_y, OUTPUT);

pinMode(ledpin, OUTPUT);
pinMode(button, INPUT);
digitalWrite(ledpin, HIGH);

digitalWrite(dir_x, level_x);
digitalWrite(dir_y, level_y);
digitalWrite(ledpin, LOW);
// one_imp();
}

void one_imp(int pin, int delay){
  digitalWrite(pin, HIGH);
  delayMicroseconds(delay);
  digitalWrite(pin, LOW);
  // delayMicroseconds(delay);
}


// void move_to_x(int* level_x, int now_x, int to_x)
// {
//   if (now_x > to_x){
//     if (level_x == HIGH){
//       change_dir(level_x);
//     }
//     for (int i = 0; i < now_x - to_x){
//       one_imp(step_x, 70);
//     }
//   }else{
//     if(level_x == LOW) change_dir(level_x);
//     for (int i = 0; i < to_x - now_x; i++) one_imp(step_x, 70);
//   }
// }
// void move_to_y(int* level_y, int now_y, int to_y)
// {
//   if (now_y > to_y){
//     if (level_y == HIGH){
//       change_dir(level_y);
//     }
//     for (int i = 0; i < now_y - to_y; i++){
//       one_imp(step_y, 70);
//     }
//   }else{
//     if(level_x == LOW) change_dir(level_x);
//     for (int i = 0; i < to_x - now_x; i++) one_imp(step_x, 70);
//   }
// }

void move_to(int now_x, int now_y, int to_x, int to_y, int* level_x, int* level_h)
{
  return;
}

void move_to(int* level, int now, int to, int dir, int step)
{
  if (now > to){
    if (*level == HIGH) change_dir(dir, level);
    for (int i = 0; i < now - to; i++) one_imp(step, 70);
  }else{
    if(*level == LOW) change_dir(dir, level);
    for (int i = 0; i < to - now; i++) one_imp(step, 70);
  }
}

void picture_print(int** a, int size_x, int size_y, int* level_x, int* level_y)
{
  int now_x = 0;
  int now_y = 0;
  for(int j = 0; j < size_y; j++){
    for (int i = 0; i < size_x; i++){
      if(a[j][i]){
        move_to(level_x, now_x, i, dir_x, step_x);
        // digitalWrite(ledpin, HIGH);
        // delay(10);
        // digitalWrite(ledpin, LOW);
        now_x = i;
      }
    }
    move_to(level_y, now_y, j, dir_y, step_y);
    now_y = j;
    move_to(level_x, now_x, 0, dir_x, step_x);
    now_x = 0;
  }
  move_to(level_y, now_y, 0, dir_y, step_y);
  now_y = 0;
  move_to(level_x, now_x, 0, dir_x, step_x);
  now_x = 0;
}


void change_status(){
  // int signal = 1;
  int signal = digitalRead(button);
  if (!signal){
    // work_status = !work_status;
    delay(10);
    while(!digitalRead(button)){
    }
    if(work_status == 1) work_status = 0;
    else work_status = 1;
    duration = 48;
    delay(10);
  }
}

void change_dir(int pin, int* level)
{
    digitalWrite(pin, !(*level));
    *level = !(*level);
}


// void picture(int[][] pic, int size_h, int size_v)
void picture(int* level_h, int* level_v)
{
  int size_h = 32;
  int size_v = 18;
  for(int j = 0; j < size_v; j++)
  {
    for (int i = 0; i < size_h; i++)
    {
      one_imp(step_x, 1);
      if(a[j][i])
        one_imp(ledpin, 35);
    }
    change_dir(dir_x, level_h);
    one_imp(step_y, 1);
  }
  change_dir(dir_y, level_v);
  for (int i = 0; i < size_v; i++){
    one_imp(step_y, 1);
  }
  change_dir(dir_y, level_v);
}

void loop() {
  change_status();
  if(work_status){
    digitalWrite(ledpin, LOW);
    // while (duration >= 0){
    picture(&level_x, &level_y);
    // picture_print((int**)a, 32, 18, &level_x, &level_y);
      // duration--;
    // }
    // for(int i = 0; i < 100; i++)
    // {
    //   one_imp(step_x);
    // }
    // change_dir(dir_x, &level_h);
    
    // horisontal_loop();
    // vertical_loop();
    // one_imp(step_x);
    // digitalWrite(step_x, HIGH);
    // delay(1);
    // digitalWrite(step_x, LOW);
    // delay(1);
  }else{
    digitalWrite(ledpin, LOW);
    delay(10);
  }
}